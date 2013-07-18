<?php

/**
 * @file
 * Admin pages and forms.
 */

/**
 * Menu callback.
 *
 * This page gathers and displays custom config forms.
 */
function custom_config_admin_page() {
  $output = array();

  // Find all custom config forms.
  // Create any blocks that we need to.
  $forms = module_invoke_all('custom_config_forms');

  $info_defaults = array(
    'access callback' => 'user_access',
    'access arguments' => array('access custom config'),
  );

  foreach ($forms as $form_id => $form_info) {

    if (!is_array($form_info)) {
      // Backwards compatability for forms with only the title specified.
      $form_info = array(
        'title' => $form_info
      );
    }
    $form_info += $info_defaults;
    $access = call_user_func_array($form_info['access callback'], $form_info['access arguments']);

    if (!$access) {
      continue;
    }

    $output[$form_id . '_fieldset'] = array(
      '#type' => 'fieldset',
      '#title' => $form_info['title'],
    );
    $output[$form_id . '_fieldset'][$form_id] = drupal_get_form($form_id);
  }

  // If we have no settings... lets say something so we don't have
  // a blank page.
  if (empty($output)) {
    $output['info'] = array(
      '#type' => 'item',
      '#title' => t("Nothing to configure... that's probably a good thing! Yay!"),
    );
  }

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
}

/**
 * Settings form
 */
function custom_config_settings_form($form, &$form_state) {
  $form = array();

  $form['custom_config_project_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Project Name'),
    '#description' => t('This should be the machine name of the installation profile being used for the project.'),
    '#default_value' => variable_get('custom_config_project_name', 'custom_config'),
    '#required' => TRUE,
  );
  $form['custom_config_project_label'] = array(
    '#type' => 'textfield',
    '#title' => t('Project Label'),
    '#description' => t('This is the human readable name of the project.'),
    '#default_value' => variable_get('custom_config_project_label', variable_get('site_name', 'Custom Config')),
    '#required' => TRUE,
  );
  $form['custom_config_admin_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Project Admin Path'),
    '#description' => t('This is the path to the site settings that will be used by site admins.'),
    '#default_value' => variable_get('custom_config_admin_path', 'admin/config/custom'),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}
