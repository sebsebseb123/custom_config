<?php

/**
 * @file
 * Admin pages and forms.
 */

/**
 * Menu callback.
 */
function custom_config_admin_page() {
  $output = array();

  $output['info'] = array(
    '#type' => 'item',
    '#title' => t('Nothing to report.'),
  );

  return $output;
}


/**
 * Menu callback.
 *
 * This callback runs the install hooks for our custom and
 * feature modules. The re-directs you to the base config path.
 */
function custom_config_install_callback() {
  // Call function to run install hooks.
  custom_config_run_install_hooks();

  // Redirect.
  drupal_goto(CUSTOM_CONFIG_ADMIN_PATH);
}

/**
 * Menu callback.
 *
 * This callback simply sets the 'custom_config_ran' var, which will trigger
 * hook_init to run all of our post-install stuff.
 */
function custom_config_postinstall_callback() {
  // Call function to run post install routines.
  custom_config_run_postinstall_hooks();

  // Redirect.
  drupal_goto(CUSTOM_CONFIG_ADMIN_PATH);
}
