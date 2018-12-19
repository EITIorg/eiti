<?php

/**
 * @file
 * Contains RestfulFormatterEitiJson.
 */

class RestfulFormatterEitiJson extends \RestfulFormatterJson implements \RestfulFormatterInterface {

  /**
   * {@inheritdoc}
   */
  public function prepare(array $data) {
    $output = parent::prepare($data);

    if (isset($output['count'])) {
      // Add possible additions.
      if (method_exists($this->handler, 'getAdditionalListData')) {
        $first_part = array_slice($output, 0, 2);
        $second_part = array_slice($output, 2);
        $additional_data = $this->handler->getAdditionalListData();
        $output = array_merge($first_part, $additional_data, $second_part);
      }
    }

    return $output;
  }

}
