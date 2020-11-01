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

	$commands['add-tcrop-species'] = array(
    'description' => 'Adds the specified species and configures the resource for it.',
    'aliases' => array('tcrop-species'),
		'arguments' => array(
			'genus' => '',
			'species' => '',
			'common_name' => '',
			'abbreviation' => '',
		),
		'callback' => 'drush_add_tcrop_species',
    'examples' => array(
       'drush tcrop-species Lens culinaris Lentil "L. culinaris"' => 'Adds Lentil to the resource configuration.',
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

	// Modules which don't need configuration:
	//  - chado_custom_search
	//  - trpdownload_api
	//  - divseek_search
	//  - tripal_qtl
	//  - vcf_filter: Configuration is per VCF file added.
	//  - tripal_germplasm_importer
	//  - tripal_map


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

}

/**
 * Adds the specified species and configures the resource for it.
 */
function drush_add_tcrop_species($genus, $species, $common_name, $abbreviation) {

	// Create the organism record.
	$organism = [
		'genus' => $genus,
		'species' => $species,
		'common_name' => $common_name,
		'abbreviation' => $abbreviation
	];
	chado_insert_record('organism', $organism);

	// Configure Analyzed Phenotypes
	// -- Create cvs and db.
	$trait_cv = 'Phenotypic Data: ' . $genus . ' Traits';
	$trait_cvobj = chado_insert_cv(
		$trait_cv,
		'A collection of breeder-specified traits for ' . $genus
	);
	$method_cv = 'Phenotypic Data: ' . $genus . ' Methods';
	$method_cvobj = chado_insert_cv(
		$method_cv,
		'A collection of breeder-specified methods for ' . $genus
	);
	$unit_cv = 'Phenotypic Data: ' . $genus . ' Units';
	$unit_cvobj = chado_insert_cv(
		$unit_cv,
		'A collection of breeder-specified units for ' . $genus
	);
	$db = 'Phenotypic Data: ' . $genus . ' References';
	$trait_dbobj = chado_insert_db([
		'name' => $db,
		'description' => "Contains database references for $genus phenotypic data."
	]);

	// -- Add configuration.
	$basename = 'analyzedphenotypes_systemvar_';
	$sanitized_genus = strtolower(preg_replace('/\s+/', '_', $genus));
	$vars = [
		$basename . $sanitized_genus . '_cv' => $trait_cvobj->cv_id,
		$basename . $sanitized_genus . '_method' => $method_cvobj->cv_id,
		$basename . $sanitized_genus . '_unit' => $unit_cvobj->cv_id,
		$basename . $sanitized_genus . '_db' => $trait_dbobj->db_id,
	];
	foreach ($vars as $varname => $value) {
		variable_set($varname, $value);
	}

}
