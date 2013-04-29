<?php

/**
 * @file
 * Hooks provided by the Custom Config module.
 */

/**
 * Define blocks to be added to the block table in the DB.
 *
 * This hook gets called during the post install process. It allows
 * you to define an array of blocks which will be inserted into the block
 * table in the database. Or, if the block exists it will update the block.
 *
 * Default values are assigned to any values you do not define. You should
 * however set some variables.
 *
 * @return
 *   An array of block variables.
 */
function hook_install_blocks() {
  // Simply returning an array.
  return array(
    // FYI, the array key has no impact on the block, and is more so there
    // for developer clarity. In this case, the array key is "language_switcher"
    'language_switcher' => array(
      'module' => 'locale',
      'title' => 'Language Switcher',
      'region' => 'language',
      'delta' => 'language',
    ),
    'other_block' => array(
      'module' => 'some_module',
      'title' => 'This is my other block.',
      'region' => 'top_right_region',
    ),
  );
}

/**
 * Define taxonomy terms to be added.
 *
 * This hook gets called during the post install process. It allows
 * you to define an array of terms which will be created.
 *
 * If the vocabulary does not exist, then the group will not be added to
 * anything.
 *
 * @return
 *   An array of terms to add keyed and grouped by vocabulary machine name.
 */
function hook_install_terms() {
  // Simply returning an array.
  return array(
    // FYI, the array key should be the machine name of the vocabulary. In
    // this case, it's tags.
    'tags' => array(
      'cats',
      'dogs',
      'ducks',
      'horses',
    ),
    'things' => array(
      'paper',
      'pen',
      'ducks',
      'stapler',
    ),
  );
}

/**
 * Post install hook to do additional tasks after site install.
 *
 * This hook gets called last during the post install process. It allows
 * you to do additional tasks after ensuring that the site is fully
 * operational. At this point, all the modules should be installed and
 * features enabled. So, you can safely rely on a lot of things being setup.
 */
function hook_install_postinstall() {
  // Set some variables.
  variable_set('some_variable', TRUE);
  variable_get('other_var', 123);

  // Do other things.
  $things = array(
    'setting' => 'value',
  );
}


/**
 * Define insert or update queries to be executed.
 *
 * This hook gets called during the post install process. It allows
 * you to define an array of queries which will be executed via try/catch.
 * This prevents the build from crashing and burning, if a query fails
 * it will be logged by watchdog.
 *
 * @return
 *   An array of query objects.
 */
function hook_queries() {
  // Init a query array.
  $queries = array();

  // If we're doing an insert, it's generally a good idea to make sure that
  // the block doesn't already exist. This is a way to check.
  $check = db_select('multiblock', 'm')
    ->fields('m')
    ->condition('title', 'My block query.', '=')
    ->condition('module', 'some_module', '=')
    ->condition('orig_delta', 'delta', '=')
    ->execute()
    ->fetchAssoc();

  // If the block doesn't already exist, create the insert query.
  if (empty($check)) {
    // Add the insert query.
    $queries['multiblock'] = db_insert('multiblock')
      ->fields(array(
        'title' => 'My block query.',
        'module' => 'some_module',
        'orig_delta' => 'delta',
      ));
  }

  return $queries;
}
