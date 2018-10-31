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
      // Additions for organisations.
      if (method_exists($this->handler, 'getOrganisationCountData')) {
        $first_part = array_slice($output, 0, 2);
        $second_part = array_slice($output, 2);
        $count_data = $this->handler->getOrganisationCountData();
        $output = array_merge($first_part, $count_data, $second_part);
      }
    }

    return $output;
  }

}
