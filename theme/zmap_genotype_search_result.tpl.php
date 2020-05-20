<style>
.btn-default {border-color: #4eb3d3; margin-right: 0;}
</style>
<div class="row">
	<div class="col-xs-12">
		<i id="spinner" class="fas fa-sync fa-spin" style="display:none;"></i>
	</div>
</div>
<div id="messagebox"></div>
<?php

$zmap_genotype_form = drupal_get_form('zmap_genotype_form');
$html = '<div class="zmap_genotype_form">'.drupal_render($zmap_genotype_form).'</div>';
$html .= '<div id="genotype_search_result"></div>';
echo $html;
