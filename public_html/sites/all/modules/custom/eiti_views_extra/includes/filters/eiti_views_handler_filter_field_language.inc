<?php
/**
 * @file
 * Contains a language filter handler - that applies only if there is a table in
 * the query already, otherwise we ignore this filter.
 *
 * Why? Well, it creates duplicates if there are > 1 deltas (and we don't want that),
 * Neither we like slow queries (with Distinct in'em).
 */

/**
 * Extends the locale language filter in order for it to work with the entity
 * translation table structure WHEN NEEDED.
 */
class eiti_views_handler_filter_field_language extends views_handler_filter_locale_language {

  /**
   * Override the default behaviour, apply only when field is queried.
   * This way we won't have duplicates created.
   */
  function op_simple() {
    if (empty($this->value)) {
      return;
    }
    // We want to apply this only if the table is already present.
    $node_tables = $this->query->tables['node'];

    if (in_array($this->table, array_keys($node_tables))) {
      $this->ensure_my_table();
      $this->query->add_where($this->options['group'], "$this->table_alias.$this->real_field", array_values($this->value), $this->operator);
    }
  }
}
