# Tripal Crop Configure

Provides drush commands to configure Tripal sites focused on crop and breeding research.

## Drush Commands

### enable-tcrop-modules (tcrop-enable)
Enables all the modules in the Tripal Crop package.

```
drush tcrop-enable
```

### reset-tcrop-config (tcrop-config)
Resets the configuration for all Tripal Crop modules to the defaults.

```
drush tcrop-config
```

### add-tcrop-species (tcrop-species)
Adds the specified species and configures the resource for it.

Arguements (required):
 - genus
 - species
 - common_name
 - abbreviation

```
drush tcrop-species Lens culinaris Lentil "L. culinaris"
```

### reset-tcrop-display (tcrop-display)
Resets the display for all Tripal Content Types.

```
drush tcrop-display
```

## Pre-requisites

- Drupal 7.x
- Tripal 3.x (including Tripal DS)
- the following Drupal and Tripal extension modules:

		chado_custom_search, trpfancy_fields, tripald3, trpdownload_api,
		analyzedphenotypes, divseek_search, nd_genotypes, tripal_elasticsearch,
		tripal_galaxy, tripal_jbrowse_page, tripal_jbrowse_mgmt,
		tripal_qtl, vcf_filter, tripal_germplasm_importer, tripal_map

It is recommended to use this module with [Tripal Crop Docker](https://www.divseekcanada.ca/tripal-crop-docker/) which already contains all the above modules!
