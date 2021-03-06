<?php

/**
 * Class TidioChat.
 */
class TidioChat {

  // Set keys constant for using if no connection via email.
  const PUBLIC_KEY = 'jt52m9yeblw3gazqg9w2bmf8uafr1t03';
  const PRIVATE_KEY = 'jioooxhbums2qfsod4ttylkhw2qze2re';

  private $platform = 'drupal';
  private $domain;

  public function __construct() {
    global $base_url;
    $this->domain = $base_url;
  }

  public function getEditorUrl() {
    $privateKey = $this->getPrivateKey();
    return 'http://external.tidiochat.com/access?privateKey=' . $privateKey;
  }

  /**
   * Performs consistent way to check if current site is admin area or not.
   * @return boolean
   */
  public function isAdminArea() {
    $uri = $_GET['q'];
    if (strpos($uri, 'admin') !== FALSE) {
      return TRUE;
    }
    else {
      return FALSE;
    }
  }

  public function isAdmin() {

    global $user;
    return in_array('administrator', array_values($user->roles));
  }

  public function getPublicKey() {

    $publicKey = variable_get('tidiochat-key-public');

    if (isset($publicKey)) {
      return $publicKey;
    }

    $this->getPrivateKey();

    return variable_get('tidiochat-key-public');
  }

  public function getPrivateKey() {

    $privateKey = variable_get('tidiochat-key-private');

    if (isset($privateKey)) {
      return $privateKey;
    }

    $data = $this->getContentData($this->getPrivateKeyUrl());
    $data = json_decode($data, true);
    $private_key = $data['value']['private_key'];
    $public_key = $data['value']['public_key'];
    if (empty($data['value']['private_key'])) {
      $private_key = self::PRIVATE_KEY;
      watchdog('tidiochat', 'Tidiochat connected by public/private keys');
    }
    if (empty($data['value']['public_key'])) {
      $public_key = self::PUBLIC_KEY;
    }

    variable_set('tidiochat-key-private', $private_key);
    variable_set('tidiochat-key-public', $public_key);

    return $data['value']['private_key'];
  }

  public function getPrivateKeyUrl() {

    global $user;
    $user_email = $user->email;

    global $base_url;

    return 'http://www.tidiochat.com/access/create?url=' . urlencode($base_url) . '&platform=' . $this->platform . '&email=' . urlencode($user_email) . '&_ip=' . $_SERVER['REMOTE_ADDR'];
  }

  public function getJsUrl() {
    $publicKey = $this->getPublicKey();
    return 'https://www.tidiochat.com/uploads/redirect/' . $publicKey . '.js';
  }

  private function getContentData($url, $urlGet = null) {
    if ($urlGet && is_array($urlGet)) {
      $url = $url . '?' . http_build_query($urlGet);
    }
    $ch = curl_init();

    curl_setopt($ch, CURLOPT_AUTOREFERER, TRUE);
    curl_setopt($ch, CURLOPT_HEADER, 0);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($ch, CURLOPT_URL, $url);
    curl_setopt($ch, CURLOPT_URL, $url);
    curl_setopt($ch, CURLOPT_USERAGENT, 'Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1)');
    curl_setopt($ch, CURLOPT_FOLLOWLOCATION, TRUE);

    $data = curl_exec($ch);
    curl_close($ch);

    return $data;
  }

}
