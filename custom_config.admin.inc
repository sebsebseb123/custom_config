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
  foreach (custom_config_module_implements('custom_config_forms') as $module) {
    $forms = module_invoke($module, 'custom_config_forms');

    foreach ($forms as $form_id => $title) {
      $output[$form_id . '_fieldset'] = array(
        '#type' => 'fieldset',
        '#title' => t($title),
      );
      $output[$form_id . '_fieldset'][$form_id] = drupal_get_form($form_id);
    }
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
