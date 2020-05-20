# ZEAMAP Genotype Data Search Module

Browse the genotype of certain germplasms within the region of interest.

## Platform

- [Drupal](https://www.drupal.org/)

## Prerequisite

- [htslib](https://github.com/samtools/htslib)
- [bcftools](https://github.com/samtools/bcftools)

## Installation and Usage

- Make sure htslib and bcftools were correctly installed, and make sure the path of bcftools executable file was added to $PATH variable.
- Download this repository
- Switch to drupal environment, and lunch this module with
    `drush en -y zmap_genotype`
- this module needs a **genotype_dataset.txt** file to record the dataset and the file paths of related variant (in vcf.gz format) and sample list in format below:

| DatasetName        | DataSetFile               | SampleListFile                |
| :----------------- | :------------------------ | :---------------------------- |
| MaizeAMP_snp_InDel | AMP_snp_indel_anno.vcf.gz | MaizeAMP_snp_InDel_sample.txt |
| ... | ... | ... |






