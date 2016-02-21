<?php

/**
 * @file
 * Contains \RestfulDataProviderEITICharts
 */

abstract class RestfulDataProviderEITICharts extends \RestfulBase implements \RestfulDataProviderInterface {
  /**
   * Constructs a RestfulDataProviderDbQuery object.
   *
   * @param array $plugin
   *   Plugin definition.
   * @param RestfulAuthenticationManager $auth_manager
   *   (optional) Injected authentication manager.
   * @param DrupalCacheInterface $cache_controller
   *   (optional) Injected cache backend.
   * @param string $language
   *   (optional) The language to return items in.
   */
  public function __construct(array $plugin, \RestfulAuthenticationManager $auth_manager = NULL, \DrupalCacheInterface $cache_controller = NULL, $language = NULL) {
    parent::__construct($plugin, $auth_manager, $cache_controller, $language);

    // Validate keys exist in the plugin's "data provider options".
//    $required_keys = array(
//      'chart_id',
//    );
//    $options = $this->processDataProviderOptions($required_keys);
//    $this->tableName = $options['table_name'];
  }

  /**
   * {@inheritdoc}
   */
  public static function controllersInfo() {
    // For prepared charts we only need an opportunity to fetch the data and to
    // list available charts.
    return array(
      '' => array(
        // GET returns a list of entities.
        \RestfulInterface::GET => 'listPreparedCharts',
        \RestfulInterface::HEAD => 'listPreparedCharts',
      ),
      '^.*$' => array(
        \RestfulInterface::GET => 'viewPreparedChart',
        \RestfulInterface::HEAD => 'viewPreparedChart',
      ),
    );
  }

  /**
   * Lists all of the defined charts in this resource.
   */
  public function listPreparedCharts() {
    $output = array();

    // Populate the output.
    $charts = $this->getDefinedChartData();
    foreach ($charts as $id => $chart) {
      $output[] = array(
        'id' => $id,
        'label' => isset($chart['label']) ? $chart['label'] : 'undefined',
        'description' => isset($chart['description']) ? $chart['description'] : 'undefined',
        'self' => $this->versionedUrl($id),
      );
    }

    return $output;
  }

  /**
   * View a single chart data.
   */
  public function viewPreparedChart($chart_id) {
    $allCharts = $this->getDefinedChartData();
    if (isset($allCharts[$chart_id]['query_builder'])) {
      $query = static::executeCallback(array($this, $allCharts[$chart_id]['query_builder']));

      // Execute the query, add filters and stuff.
      $results = $query->execute();
      if (is_a($query, 'EntityFieldQuery')) {
        pc($results, 're');
        $results = reset($results);
      }
      else {
        $results = $results->fetchAll();
      }

      if (isset($allCharts[$chart_id]['public_fields_info'])) {
        $fields = static::executeCallback(array($this, $allCharts[$chart_id]['public_fields_info']), array($results));
        return $fields;
      }
      else {
        throw new \RestfulServiceUnavailable(format_string('Restful plugin class (@plugin) was not configured properly. Check if there are public_fields_info callbacks defined.', array('@plugin' => get_class($this))));
      }
    }
    else {
      throw new \RestfulServiceUnavailable(format_string('Restful plugin class (@plugin) was not configured properly. Check if there are query_builder callbacks defined.', array('@plugin' => get_class($this))));
    }
  }

  /**
   * This is where we define our charts for this specific resource.
   *
   * @return array
   *  An array which has the keys - id's of the charts, and the value an array with keys:
   *  - 'label': Which specifies which label we'd have to use for this chart.
   *  - 'description': Describes the chart.
   *  - 'query_builder': A callback that builds the custom query for this chart.
   *  - 'public_fields_info': A callback that builds the presentation of the data.
   *
   */
  public function getDefinedChartData() {
    $charts = array();
    return $charts;
  }

  /**
   * {@inheritdoc}
   */
  public function getTotalCount() {
    $allCharts = $this->getDefinedChartData();
    return intval(count($allCharts));
  }

  /**
   * Implementing the required method, not that we use it anywhere.
   */
  public function publicFieldsInfo() {}
}
