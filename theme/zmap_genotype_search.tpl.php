<?php

$zmap_genotype_form = drupal_get_form('zmap_genotype_form');
$html = '<div class="zmap_genotype_form">'.drupal_render($zmap_genotype_form).'</div>';
echo $html;

