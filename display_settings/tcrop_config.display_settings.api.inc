<?php

/**
 * Creates a Tripal Pane.
 *
 * @param array $pane_properties
 *   - bundle_name
 *   - group_name
 *   - label
 *   - children
 *   - hide
 *   - weight
 */
function tcrop_config_create_pane($pane_properties) {

	$bundle_name = $pane_properties['bundle_name'];

	$field_group_tripalpane = new stdClass();
  $field_group_tripalpane->disabled = FALSE;
  $field_group_tripalpane->api_version = 1;
  $field_group_tripalpane->identifier = $pane_properties['group_name'] . '|TripalEntity|' . $bundle_name . '|default';
  $field_group_tripalpane->group_name = $pane_properties['group_name'];
  $field_group_tripalpane->entity_type = 'TripalEntity';
  $field_group_tripalpane->bundle = $bundle_name;
  $field_group_tripalpane->mode = 'default';
  $field_group_tripalpane->parent_name = '';
  $field_group_tripalpane->data = [
    'label' => $pane_properties['label'],
    'weight' => $pane_properties['weight'],
    'children' => $pane_properties['children'],
    'format_type' => 'tripalpane',
    'format_settings' => [
      'label' => $pane_properties['label'],
      'instance_settings' => [
        'id' => 'tripal_ds-fieldset-' . $pane_properties['group_name'],
        'classes' => $pane_properties['group_name'] . ' field-group-tripalpane',
        'description' => '',
        'hide' => $pane_properties['hide'],
      ],
    ],
  ];
  drupal_write_record('field_group', $field_group_tripalpane);
  //Write to the tripal_ds table to record the new tripal pane.
  tripal_ds_bundle_menu_item(
		$bundle_name,
		$pane_properties['label'],
		$pane_properties['group_name'],
		'TripalEntity'
	);

	return $field_group_tripalpane;
}

/**
 * Hide Field Instance.
 *
 * @param object $instance
 *  The full instance object you want to hide.
 */
function tcrop_config_display_hide_instance($instance) {
	$instance['display']['default']['type'] = 'hidden';
	$instance['display']['default']['label'] = 'hidden';
	field_update_instance($instance);
}

/**
 *
 */
function tcrop_config_display_reset_ds_display($bundle_name) {
	$ds_identifier = 'TripalEntity|'.$bundle_name.'|default';
	$instances = field_info_instances('TripalEntity', $bundle_name);

	// -- Check to see if the layout already exists.
	$result = db_select('ds_layout_settings', 'ds')
		->fields('ds')
		->condition('id', $ds_identifier, '=')
		->execute()
		->fetchField();
	// -- Check to see if there are any field groups associated with the bundle.
	$result_fg = db_select('field_group', 'fg')
		->fields('fg')
		->condition('bundle', $bundle_name, '=')
		->execute()
		->fetchField();
	// -- Check to see if there are any tripal ds fields associated with the bundle.
	$result_tds = db_select('tripal_ds', 'tds')
		->fields('tds')
		->condition('bundle', $bundle_name, '=')
		->execute();

	// -- Check to see if there are any field settings associated with the bundle.
	$result_fs = db_select('ds_field_settings', 'fs')
		->fields('fs')
		->condition('bundle', $bundle_name, '=')
		->execute();

	// -- If the layout exists, delete it.
	if(!empty($result)) {
		db_delete('ds_layout_settings')
			->condition('id', $ds_identifier, '=')
			->execute();
	}
	// -- Then delete the field_group_fields associated with the identifier.
	if(!empty($result_fg)) {
		db_delete('field_group')
			->condition('bundle', $bundle_name, '=')
			->execute();
	}
	// -- Then delete the ds_field_settings associated with the identifier.
	if(!empty($result_tds)) {
		db_delete('ds_field_settings')
			->condition('bundle', $bundle_name, '=')
			->execute();
	}
	// -- Then delete the tripal_ds menu item.
	if(!empty($result_fs)) {
		db_delete('tripal_ds')
			->condition('bundle', $bundle_name, '=')
			->execute();
	}

	// -- Now you can build the layout fresh.
	$instances = field_info_instances('TripalEntity', $bundle_name);
	$bundle_data_table = $bundle->data_table;
	if($bundle_data_table == 'pub'){
		$success = _ds_layout_pub_settings_info($bundle_name, $instances);
	}
	else {
		$success = _ds_layout_settings_info($bundle_name, $instances);
	}
}
