<?php
/**
 * Callback URL for RBKmoney server response
 *
 * @see https://rbkmoney.github.io/webhooks-events-api/
 */
function rbkmoney_checkout_ubercart_callback_result()
{
  $type = 'callback_result';
  $content = file_get_contents('php://input');
  _rbkmoney_checkout_ubercart_logger($type, "<pre>%logs</pre>", ['%logs' => var_export(['content' => $content], TRUE)]);

  if (empty($_SERVER[SIGNATURE])) {
    http_response_code(HTTP_CODE_BAD_REQUEST);
    _rbkmoney_checkout_ubercart_logger($type, "Webhook notification signature missing. <pre>%logs</pre>", ['%logs' => var_export(['content' => $content], TRUE)]);
    echo json_encode(array('message' => 'Webhook notification signature missing'));
    exit();
  }

  try {
    $signature_from_header = _rbkmoney_checkout_ubercart_get_signature_from_header($_SERVER[SIGNATURE]);
  } catch (Exception $ex) {
    _rbkmoney_checkout_ubercart_logger($type, "Webhook notification signature missing. <pre>%logs</pre>",
      ['%logs' => var_export([
        $_SERVER[SIGNATURE],
        $content,
        MERCHANT_CALLBACK_PUBLIC_KEY
      ], TRUE)]);
    http_response_code(HTTP_CODE_BAD_REQUEST);
    echo json_encode(array('message' => $ex->getMessage()));
    exit();
  }

  $signature = _rbkmoney_checkout_ubercart_urlsafe_b64decode($signature_from_header);
  if (!_rbkmoney_checkout_ubercart_verification_signature($content, $signature, MERCHANT_CALLBACK_PUBLIC_KEY)) {
    _rbkmoney_checkout_ubercart_logger($type, "Webhook notification signature mismatch. <pre>%logs</pre>",
      ['%logs' => var_export([
        $_SERVER[SIGNATURE],
        $content,
        $signature,
        MERCHANT_CALLBACK_PUBLIC_KEY
      ], TRUE)]);
    http_response_code(HTTP_CODE_BAD_REQUEST);
    echo json_encode(array('message' => 'Webhook notification signature mismatch'));
    exit();
  }

  $required_fields = [INVOICE, EVENT_TYPE];
  $data = json_decode($content, TRUE);

  foreach ($required_fields as $field) {
    if (empty($data[$field])) {
      _rbkmoney_checkout_ubercart_logger($type, "One or more required fields are missing <pre>%logs</pre>",
        ['%logs' => var_export([
          'input_content' => $content,
          'required_fields' => $required_fields
        ], TRUE)]);
      http_response_code(HTTP_CODE_BAD_REQUEST);
      echo json_encode(array('message' => 'One or more required fields are missing'));
      exit();
    }
  }

  $current_shop_id = variable_get('uc_rbkmoney_shop_id');
  if ($data[INVOICE][INVOICE_SHOP_ID] != $current_shop_id) {
    _rbkmoney_checkout_ubercart_logger($type, 'Webhook notification ' . INVOICE_SHOP_ID . ' mismatch<pre>%logs</pre>', ['%logs' => var_export($content, TRUE)]);
    http_response_code(HTTP_CODE_BAD_REQUEST);
    echo json_encode(array('message' => INVOICE_SHOP_ID . ' is missing'));
    exit();
  }

  if (empty($data[INVOICE][INVOICE_METADATA][ORDER_ID])) {
    _rbkmoney_checkout_ubercart_logger($type, ORDER_ID . ' is missing <pre>%logs</pre>', ['%logs' => var_export($content, TRUE)]);
    http_response_code(HTTP_CODE_BAD_REQUEST);
    echo json_encode(array('message' => ORDER_ID . ' is missing'));
    exit();
  }


  $order_id = $data[INVOICE][INVOICE_METADATA][ORDER_ID];
  $order = uc_order_load($order_id);
  $order_amount = _rbkmoney_checkout_ubercart_prepare_amount($order->order_total);
  $invoice_amount = $data[INVOICE][INVOICE_AMOUNT];

  if ($order_amount != $invoice_amount) {
    _rbkmoney_checkout_ubercart_logger($type, 'Received amount vs Order amount mismatch <pre>%logs</pre>', ['%logs' => var_export($content, TRUE)]);
    http_response_code(HTTP_CODE_BAD_REQUEST);
    echo json_encode(array('message' => 'Received amount vs Order amount mismatch'));
    exit();
  }

  $allowed_event_types = [EVENT_TYPE_INVOICE_PAID, EVENT_TYPE_INVOICE_CANCELLED];
  if (in_array($data[EVENT_TYPE], $allowed_event_types)) {
    $invoice_status = $data[INVOICE][INVOICE_STATUS];
    _rbkmoney_checkout_ubercart_update_status_order($order_id, $invoice_status);
  }

  exit();
}

function _rbkmoney_checkout_ubercart_urlsafe_b64decode($string)
{
  return base64_decode(strtr($string, '-_,', '+/='));
}

function _rbkmoney_checkout_ubercart_get_signature_from_header($content_signature)
{
  $signature = preg_replace(SIGNATURE_PATTERN, '', $content_signature);

  if (empty($signature)) {
    throw new Exception('Signature is missing');
  }

  return $signature;

}

function _rbkmoney_checkout_ubercart_verification_signature($data = '', $signature = '', $public_key = '')
{
  if (empty($data) || empty($signature) || empty($public_key)) {
    return FALSE;
  }

  $public_key_id = openssl_get_publickey($public_key);
  if (empty($public_key_id)) {
    return FALSE;
  }

  $verify = openssl_verify($data, $signature, $public_key_id, OPENSSL_SIGNATURE_ALG);
  return ($verify == OPENSSL_VERIFY_SIGNATURE_IS_CORRECT);
}
