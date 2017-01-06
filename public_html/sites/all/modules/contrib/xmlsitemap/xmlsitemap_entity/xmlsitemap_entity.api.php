<?php
/**
 * @file
 * Describes the hooks provided by the Workflow module.
 */

/**
 * This is a placeholder for describing further keys for hook_entity_info(),
 * which are introduced by XML sitemap entity to provide more control concerning
 * the XML sitemap integration.
 *
 * The XML sitemap entity module supports following keys:
 * - xmlsitemap: (optional) A boolean indicating if the entity should be available
 *   for indexing or an array of xmlsitemap settings/callbacks. The following
 *   additional keys are used by the XML sitemap entity module:
 *   - use entity module: for internal usage only, indicates that the XML sitemap
 *     entity module is used for this entity type.
 *   - changed property: (optional) Name of the property that contains the last
 *     changed UNIX timestamp.
 */
function xmlsitemap_entity_hook_entity_info() {
  return array(
    'user' => array(
      'xmlsitemap' => FALSE,
    ),
  );
}
