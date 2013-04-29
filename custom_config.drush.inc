<?php

/**
 * @file
 * Drush integration for the devel module.
 */

/**
 * Implements hook_drush_command().
 */
function custom_config_drush_command() {
  $items['custom_config-run-install-hooks'] = array(
    'description' => 'Run install hooks for our custom and feature modules.',
    'aliases' => array('cc-ri'),
  );
  $items['custom_config-run-postinstall-hooks'] = array(
    'description' => 'Run post-install hooks for our custom and feature modules.',
    'aliases' => array('cc-rpi'),
  );
  return $items;
}

/**
 * Run the install hooks for our custom and feature modules.
 */
function drush_custom_config_run_install_hooks() {
  // Run the hooks.
  custom_config_run_install_hooks();

  // Verbose complete.
  drush_log('Custom Config ran our custom and feature module install hooks.');
}

/**
 * Run the install hooks for our custom and feature modules.
 */
function drush_custom_config_run_postinstall_hooks() {
  // Run the hooks.
  custom_config_run_postinstall_hooks();

  // Verbose complete.
  drush_log('Custom Config ran our custom and feature module post-install hooks.');
}
