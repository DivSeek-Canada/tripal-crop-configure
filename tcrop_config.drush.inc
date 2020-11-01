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

	$commands['reset-tcrop-config'] = array(
    'description' => 'Resets the configuration for all Tripal Crop modules to the defaults.',
    'aliases' => array('tcrop-config'),
		'callback' => 'drush_reset_tcrop_config',
    'examples' => array(
       'drush tcrop-config' => 'Resets the configuration for all Tripal Crop modules to the defaults.',
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

/**
 * Resets the configuration for all Tripal Crop modules to the defaults.
 */
function drush_reset_tcrop_config () {

	// chado_custom_search
	//------------------------------------
	// No configuration needed.

	// trpfancy_fields
	//------------------------------------
	// Set the default identifier prefix.
	variable_set('trpfancy_field_identifier_prefix', 'DvskCA:');

	// tripald3
	//------------------------------------
	variable_set('tripald3_autoResize', TRUE);
	variable_get('tripald3_colorScheme', 'NvGr');
	variable_set('tripald3_stock_pedigree_rels',
		'a:2:{s:6:"object";a:2:{i:3632;s:21:"is_maternal_parent_of";i:3633;s:21:"is_paternal_parent_of";}s:7:"subject";a:5:{i:3712;s:17:"is_extracted_from";i:3678;s:27:"is_individual_of_population";i:3634;s:24:"is_progeny_of_selfing_of";i:3679;s:25:"is_registered_cultivar_of";i:3684;s:15:"is_selection_of";}}');

	// trpdownload_api
	//------------------------------------
	// No configuration needed.

	// analyzedphenotypes
	//------------------------------------
	$basename = 'analyzedphenotypes_systemvar_';
	// Display configuration.
	variable_set($basename . 'allownew', TRUE);
	variable_set('ap_config_watermark_what', 'all');
	variable_set('ap_config_watermark_url', 'https://staging.divseekcanada.ca/tripal/sites/default/files/DivseekCan_Monochrome_CapYes.png');
	// Default Terms set on install.
	$default_ontology = ap_load_defaultontology();
	$sysvars = ap_construct_variablenames();
	foreach($sysvars['terms'] as $v => $var) {
		$v = trim(str_replace('ap_', '', $v));
		variable_set($var, $default_ontology[$v]);
	}
	// Update mview to include default cvterms.
	ap_update_mview_phenotypesummary();
	// Rest of the configuration is per crop.

	// divseek_search
	//------------------------------------
	// No configuration needed.

	// nd_genotypes
	//------------------------------------
	// @todo configure when we have data.

	// tripal_elasticsearch
	//------------------------------------
	// @todo configure once elastic search is available.

	// tripal_galaxy
	//------------------------------------
	// @todo configure once galaxy is available.

	// tripal_jbrowse_page
	//------------------------------------
	// @todo configure once JBrowse is available.

	// tripal_jbrowse_mgmt
	//------------------------------------
	// @todo configure once JBrowse is available.

	// tripal_qtl
	//------------------------------------
	// No configuration needed.

	// vcf_filter
	//------------------------------------
	// Configuration is per VCF file added.

	// tripal_germplasm_importer
	//------------------------------------
	// No configuration needed.

	// tripal_map
	//------------------------------------
	// No configuration needed.

}
