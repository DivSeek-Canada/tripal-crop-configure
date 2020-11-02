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

## Future Work

 - More automatic display configuration for even more intuitive pages for breeders.
 - Automatic configuration of permissions.
 - Integration with JBrowse and Galaxy.
 - Automatic data submission to multiple modules (e.g. an VCF file could be added to VCF Filter, Tripal JBrowse, Tripal Galaxy and ND Genotypes)
 
 ## Funding

The first iteration of the platform is funded under a [Genome Canada Project](https://www.genomecanada.ca/en/divseek-canada-harnessing-genomics-accelerate-crop-improvement-canada) with co-funding from other partners.

## Citation

Lacey-Anne Sanderson, Kirstin E. Bett, Loren H. Rieseberg (2020) Tripal Crop Config: drush commands to configure Tripal sites focused on crop and breeding research. DEVELOPMENT VERSION. DivSeek Canada Pilot Project: Harnessing Genomics to Accelerate Crop Improvement in Canada.
