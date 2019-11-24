<?php

/**
 * @file
 * eiti_webforms.captcha.inc
 */

/**
 * Implements hook_captcha_default_points().
 */
function eiti_webforms_captcha_default_points() {
  $export = array();

  $captcha = new stdClass();
  $captcha->disabled = FALSE; /* Edit this to true to make a default captcha disabled initially */
  $captcha->api_version = 1;
  $captcha->form_id = 'webform_client_form_11045';
  $captcha->module = 'recaptcha';
  $captcha->captcha_type = 'reCAPTCHA';
  $export['webform_client_form_11045'] = $captcha;

  return $export;
}
