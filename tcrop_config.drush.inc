<?php

/**
 * Implements hook_drush_command().
 */
function tcrop_config_drush_command() {

  $commands['enable-tcrop-modules'] = array(
    'description' => 'Enables all the modules in the Tripal Crop package.',
    'aliases' => array('tcrop-enable'),
		'callback' => 'drush_enable_tcrop_modules',
    'examples' => array(
       'drush tcrop-enable' => 'Enables all the modules in the Tripal Crop package.',
     ),
  );

  return $commands;
}

/**
 * Enables all the modules including dependencies.
 */
function drush_enable_tcrop_modules() {

	$modules = tcrop_configure_get_modules(TRUE);
	foreach($modules as $module_name) {
		if (!module_exists($module_name)) {
		  module_enable([$module_name], TRUE);
		}
	}
	drush_log(dt('Successfully enabled all Tripal Crop Modules.'), 'success');
}
