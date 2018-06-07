<?php

/**
 * Define payment statuses
 */
define('UC_RBKMONEY_STATUS_FAILED', 'cancelled');
define('UC_RBKMONEY_STATUS_SUCCESS', 'paid');

define('ANONYMOUS_USER_ID', 0);

/**
 * Module data
 */
define('MODULE_NAME', 'rbkmoney_checkout_ubercart');
define('MODULE_BASE_PATH', base_path() . drupal_get_path('module', MODULE_NAME));

/**
 * Api URL
 */
define('API_URL', 'https://api.rbk.money/v2/');

/**
 * Merchant settings
 */
define('MERCHANT_PRIVATE_KEY', trim(variable_get('uc_rbkmoney_merchant_private_key', 'merchant_private_key')));
define('MERCHANT_CALLBACK_PUBLIC_KEY', trim(variable_get('uc_rbkmoney_merchant_callback_public_key', 'merchant_callback_public_key')));

/**
 * Payment form
 */
define('BASE_URL', $GLOBALS['base_url']);
define('PAYMENT_FORM_URL', 'https://checkout.rbk.money/checkout.js');
define('PAYMENT_FORM_SUCCESS_URL', BASE_URL . '/'.MODULE_NAME.'/success');

/**
 * Payment method logo
 */
define('PAYMENT_METHOD_PATH_IMG_LOGO', MODULE_BASE_PATH . '/images/logo_rbkmoney.png');

/**
 * Payment form default css button
 */
define('PAYMENT_FORM_DEFAULT_CSS_BUTTON', trim(variable_get('uc_rbkmoney_payform_css_button', '
  button.rbkmoney-button {
    border: 1px solid #e4e4e4;
      border-bottom: 1px solid #b4b4b4;
      border-left-color: #d2d2d2;
      border-right-color: #d2d2d2;
      color: #2f2f2f;
      cursor: pointer;
      text-align: center;
      margin-top: 2px;
      margin-bottom: 1em;
      margin-right: 0.6em;
      padding: 4px 17px;
      border-radius: 15px;
      background: #eee;
      box-shadow: none;
      font: normal 0.929em/1.1em "Lucida Grande", "Lucida Sans Unicode", Verdana, sans-serif;
  }
  button.rbkmoney-button:hover {
    background: #dedede;
  }'
)));

/**
 * Create invoice settings
 */
define('CREATE_INVOICE_TEMPLATE_DUE_DATE', 'Y-m-d\TH:i:s\Z');
define('CREATE_INVOICE_DUE_DATE', '+1 days');

/**
 * Constants for Callback
 */

define('SIGNATURE', 'HTTP_CONTENT_SIGNATURE');
define('SIGNATURE_PATTERN', "/alg=(\S+);\sdigest=/");


define('EVENT_TYPE', 'eventType');

// EVENT TYPE INVOICE
define('EVENT_TYPE_INVOICE_CREATED', 'InvoiceCreated');
define('EVENT_TYPE_INVOICE_PAID', 'InvoicePaid');
define('EVENT_TYPE_INVOICE_CANCELLED', 'InvoiceCancelled');
define('EVENT_TYPE_INVOICE_FULFILLED', 'InvoiceFulfilled');

// EVENT TYPE PAYMENT
define('EVENT_TYPE_PAYMENT_STARTED', 'PaymentStarted');
define('EVENT_TYPE_PAYMENT_PROCESSED', 'PaymentProcessed');
define('EVENT_TYPE_PAYMENT_CAPTURED', 'PaymentCaptured');
define('EVENT_TYPE_PAYMENT_CANCELLED', 'PaymentCancelled');
define('EVENT_TYPE_PAYMENT_FAILED', 'PaymentFailed');


define('INVOICE', 'invoice');
define('INVOICE_ID', 'id');
define('INVOICE_SHOP_ID', 'shopID');
define('INVOICE_STATUS', 'status');
define('INVOICE_DUE_DATE', 'dueDate');
define('INVOICE_AMOUNT', 'amount');
define('INVOICE_CURRENCY', 'currency');
define('INVOICE_REASON', 'reason');
define('INVOICE_METADATA', 'metadata');

define('ORDER_ID', 'order_id');

define('PAYMENT', 'payment');
define('PAYMENT_ID', 'id');
define('PAYMENT_AMOUNT', 'amount');
define('PAYMENT_CURRENCY', 'currency');
define('PAYMENT_STATUS', 'status');

/**
 * Api params
 */
define('API_INVOICE_ID', 'invoice_id');
define('API_INVOICE_ACCESS_TOKEN', 'invoice_access_token');

/**
 * Openssl verify
 */
define('OPENSSL_VERIFY_SIGNATURE_IS_CORRECT', 1);
define('OPENSSL_VERIFY_SIGNATURE_IS_INCORRECT', 0);
define('OPENSSL_VERIFY_ERROR', -1);
define('OPENSSL_SIGNATURE_ALG', OPENSSL_ALGO_SHA256);

/**
 * HTTP CODE
 */
define('HTTP_CODE_OK', 200);
define('HTTP_CODE_CREATED', 201);
define('HTTP_CODE_MOVED_PERMANENTLY', 301);
define('HTTP_CODE_BAD_REQUEST', 400);
define('HTTP_CODE_INTERNAL_SERVER_ERROR', 500);

/**
 * HTTP METHOD
 */
define('HTTP_METHOD_GET', 'GET');
define('HTTP_METHOD_POST', 'POST');
