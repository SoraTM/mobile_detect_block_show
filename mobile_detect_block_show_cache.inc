<?php
  
/**

  Since the core Drupal cache provider uses the URL as the cache id
  it's possible to get incorrect pages served from the cache when
  using the Mobile Switch module if your mobile and non-mobile pages
  share the same URL. Mobile Switch comes with a replacement for the
  core Drupal database caching provider that appends the theme and an
  indicator specifying whether the request is from a mobile device or
  not to the cache id. To use this new cache provider for the page
  cache simply add the following to the end of your settings.php file.

    $conf['cache_backends'][] = 'sites/all/modules/contrib/mobile_switch/mobile_switch_database_cache.inc';
    $conf['cache_class_cache_page'] = 'MobileSwitchDatabaseCache';

  Just make sure the path to the Mobile Switch module directory
  matches your installation.

*/
 
/**
 * @file
 * Provides a cache implementation to be used in conjunction with the
 * mobile_switch module.
 *
 * This is only intended to be used as a replacement for the page cache
 * although it can be used as the default cache.
 * It appends the override from the URL or cookie and whether or not
 * the request was from a mobile device to the cache id.
 */

class BrowscapDatabaseCache extends DrupalDatabaseCache implements DrupalCacheInterface {

  /**
   * Overrides DrupalDatabaseCache::getMultiple().
   */
  function getMultiple(&$cids) {
    if (is_array($cids)) {
      foreach ($cids as $key => $cid) {
        $cids[$key] = $cid . $this->getExtraCid();
      }
    }
    return parent::getMultiple($cids);
  }

  /**
   * Overrides DrupalDatabaseCache::set().
   */
  function set($cid, $data, $expire = CACHE_PERMANENT) {
    $cid .= $this->getExtraCid();
    return parent::set($cid, $data, $expire);
  }

  protected function getExtraCid() {
    $extra = '';

    if (function_exists('mobile_detect_get_object')) {
      $detect = mobile_detect_get_object();
      $is_mobile = $detect->isMobile();
      $is_tablet = $detect->isTablet();      
        if ($is_tablet) {
          $extra .= ':tablet';
        } 
        elseif ($is_mobile) {
          $extra .= ':mobile';
        }
        else {
          $extra .= ':standard';
        }
    }
    return $extra;
 }
}