

-- SUMMARY --

The Custom Config module is a module intended for use by developers who are using the "installation profile" development strategy.


-- REQUIREMENTS --

This module works alongside the "installation profile" development strategy, and therefore is relying on a certain file structure. In particular, the path for custom and feature modules should be from drupal root:
  /profiles/project_name/modules/custom
  or
  /profiles/project_name/modules/features


-- USE --

* As a developer, you'll need to implement some hooks to take advantage of this module. You can refer to custom_config.api.php for more information on how to do this.

* As a site administrator, it's useful to know that the configuration page is where you could find configuration options which were created for this project. Also, that page has some local tasks which are useful, although these are also available as drush commands. The default path for the configuration page is in Administration È Configuration È Custom:

  - Run Install Hooks

    If you've added more functionality to an install hook and need a way to run the install hooks, then this is the callback for you. It will find any and all install hooks in your install profile, and the modules/custom and modules/features directories.

  - Run Post-Install Hooks

    If you've implemented any of the hooks to create a block or term, or the hook_queries hook, or the hook_postinstall hook, then this is the callback which will find them and execute them.
