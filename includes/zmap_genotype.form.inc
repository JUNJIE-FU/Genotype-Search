<?php

/**
 * Implements hook_form.
 */
function zmap_genotype_form($form, &$form_state)
{
    $description = 'Browse the genotype of certain germplasms. Simply select a dataset, and then enter the name of germplasms and select for the genomic regions of interest to get the genotype information.';

    $form['descriptions'] = array(
        '#type' => 'item',
        '#markup' => t($description),
    );

    $form['germplasm'] = array(
        '#type' => 'fieldset',
        '#title' => t("Choose dataset and germplasms you are interested in."),
        '#collapsible' => false,
        '#collapsed' => false,
    );

    $dataset_options = array(
        'MaizeAMP_haplotype_tag_variants' => 'MaizeAMP_haplotype_tag_variants',
        'MaizeAMP_snp_InDel' => 'MaizeAMP_snp_InDel',
        'B73_vs_SK_SVs' => 'B73_vs_SK_SVs'
    );

    $description = 'Select a set of genetic variants.';
    $form['germplasm']['select_dataset'] = array(
        '#type' => 'select',
        '#title' => 'Dataset',
        '#required' => true,
        '#options' => $dataset_options,
	'#description' => $description,
        '#default_value' => !empty($_SESSION['zmap_genotype']['form']['dataset']) ? $_SESSION['zmap_genotype']['form']['dataset'] : $dataset_options['MaizeAMP_haplotype_tag_variants'],
    );

    $form['germplasm']['germplasm_fuzzy_search'] = array(
        '#type' => 'textfield',
	    '#title' => 'Germplasm*',
	    '#size' => 30,
    );

    $form['germplasm']['germplasms_tree'] = array(
        '#type' => 'item',
        '#size' => 30,
        '#markup' => '<div id="germplasms_tree" class="ztree"></div>',
    );

    $form['germplasm']['selected_germplasms'] = array(
        '#type' => 'item',
        '#markup' => '<div id="selected_nodes">Selected germplasms: </div>',
    );

    $form['germplasm']['selected_germplasms_hidden'] = array(
        '#type' => 'hidden'
    );
    

    $description = 'To optimize the search experience, the selected region should be no more than 1 Mb.';

    $form['region'] = array(
        '#type' => 'fieldset',
        '#title' => t("Restrict to the region of the genome."),
        '#description' => t($description),
        '#collapsible' => false,
        '#collapsed' => false,
    );

    $form['region']['chr'] = array(
        '#type' => 'select',
	'#title' => 'Chr',
        '#required' => true,
        '#options' => array_combine(range(1, 10), range(1, 10)),
	'#default_value' => !empty($_SESSION['zmap_genotype']['form']['chr']) ? $_SESSION['zmap_genotype']['form']['chr'] : '',
    );

    $form['region']['start'] = array(
        '#type' => 'textfield',
	'#title' => 'from',
        '#required' => true,
	'#default_value' => !empty($_SESSION['zmap_genotype']['form']['start']) ? $_SESSION['zmap_genotype']['form']['start'] : '',
    );

    $form['region']['end'] = array(
        '#type' => 'textfield',
	'#title' => 'end',
        '#required' => true,
	'#default_value' => !empty($_SESSION['zmap_genotype']['form']['end']) ? $_SESSION['zmap_genotype']['form']['end'] : '',
    );


    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => 'Search',
    );

    $form['#validate'][] = 'zmap_genotype_form_validate';
    $form['#submit'][] = 'zmap_genotype_form_submit';

    return $form;
}

function zmap_genotype_form_submit($form, $form_state)
{
    //cache submit values
    $_SESSION['zmap_genotype']['form']['dataset'] = $form_state['values']['select_dataset'];
    $_SESSION['zmap_genotype']['form']['chr'] = $form_state['values']['chr'];
    $_SESSION['zmap_genotype']['form']['start'] = $form_state['values']['start'];
    $_SESSION['zmap_genotype']['form']['end'] = $form_state['values']['end'];

    $germplasm = $form_state['values']['selected_germplasms_hidden'];
    $dataset = $form_state['values']['select_dataset'];
    $chr = $form_state['values']['chr'];
    $pos_start = $form_state['values']['start'];
    $pos_end = $form_state['values']['end'];
    drupal_goto('zmap_genotype/result/genotype/dataset/'.$dataset.'/germplasms/'.$germplasm.'/chr/'.$chr.'/start/'.$pos_start.'/end/'.$pos_end);
}

/**
 * Implements hook_form_validate.
 */
function zmap_genotype_form_validate($form, &$form_state)
{
    if (empty($form_state['values']['selected_germplasms_hidden'])) {
        form_set_error('germplasm', t('At least 1 germplasm should be provided.'));
    }

    if (empty($form_state['values']['select_dataset'])) {
        form_set_error('select_dataset', t('dataset should be provided.'));
    }

    if (empty($form_state['values']['chr'])) {
        form_set_error('select_chr', t('Chr should be provided.'));
    }

    if (empty($pos_start = $form_state['values']['start'])) {
        form_set_error('select_chr', t('Start position should be provided.'));
    }

    if (empty($pos_end = $form_state['values']['end'])) {
        form_set_error('select_chr', t('End position should be provided.'));
    }

    if ((int) ($pos_end - $pos_start) >= 1e6) {
        form_set_error('region', t('Region should be less than 1M.'));
    }

    $form_state['values']['start'] = htmlspecialchars($form_state['values']['start']);
    $form_state['values']['end'] = htmlspecialchars($form_state['values']['end']);
}
