<?php
/**
 * @file
 * Defines the entity main class.
 */

/**
 * The entity main class.
 */
class ScoreReqValueEntity extends Entity {
  // Define some default values.
  public $id = NULL;

  public $score_req_id = NULL;
  /** @var ScoreReqEntity $score_req */
  public $score_req = NULL;

  public $value = NULL;
  public $progress_value = NULL;
  public $is_applicable = NULL;
  public $is_required = NULL;
  public $description = NULL;

  /**
   * Set up the object instance on construction or unserializiation.
   */
  protected function setUp() {
    parent::setUp();

    if (!empty($this->score_req_id)) {
      $this->score_req = entity_load_single('score_req', $this->score_req_id);
      if (empty($this->score_req)) {
        drupal_set_message(t('Cannot create an Score Requirement Value without a valid Score Requirement. Please checks requirements with suggestions to <strong>EDIT</strong>.'), 'warning');
      }
    }
  }

  /**
   * URI method for entity_class_uri().
   */
  protected function defaultUri() {
    return NULL;
  }

  /**
   * Getter callback for score_req_id.
   *
   * @return entity
   *   ScoreReq entity.
   */
  public function score_reqid() {
    return entity_load_single('score_req', $this->score_req_id);
  }

  /**
   * Setter for score_req_id.
   *
   * @param entity $score_req
   *
   *  ScoreReq entity instance.
   */
  public function setScoreReqid($score_req) {
    $this->score_req_id = is_object($score_req->id) ? $score_req->id : $score_req;
  }
}
