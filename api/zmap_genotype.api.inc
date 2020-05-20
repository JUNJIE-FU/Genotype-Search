<?php

function zmap_genotype_api_retrive_germplasm($dataset)
{
    $sample_list = '/var/www/html/sites/default/files/zmap_genotype/'. $dataset . '_sample.txt';
    $img_path = '/'.drupal_get_path('module', 'zmap_genotype').'/theme/css/img';
    $germplasms = file_get_contents($sample_list);
    $germplasms = explode(PHP_EOL, $germplasms);
    $data = array();
    $data[] = array(
	'id' => 1,
	'pId' => "0",
	'name' => 'Germplasms',
	't' => 'id=1',
	'icon' => $img_path.'/folder.png',
    );
    $i = 2;
    foreach ($germplasms as $germplasm) {
        $node = array(
            'id' => (string) $i++,
            'pId' => "1",
            'name' => $germplasm,
            't' => 'id='.$i,
	    'icon' => $img_path.'/trait.png',
        );
        $data[] = $node;
    }

    drupal_json_output($data);
}


function zmap_genotype_api_retrive_genotype_search_result($dataset, $germplasms, $chr, $start, $end)
{
	$dataset = arg(4);
	$germplasms = arg(6);
	$chr = arg(8);
	$start = arg(10);
	$end = arg(12);
	$path = DRUPAL_ROOT.'/'.drupal_get_path('module', 'zmap_genotype');
    $command_path = $path.'/includes';
    $command = '/bin/bash '.$command_path.'/zeamap_genotype'." $dataset"." $germplasms"." $chr:$start-$end";
    exec($command, $result_genotype, $returnVar);
    $data = [];
	$germplasms = explode(',', $germplasms);
    if($result_genotype)
    {
    	foreach ($result_genotype as $key => $line) {
    		$genotypes = explode("\t", $line);
    		if(in_array('Position', $genotypes)){
    			continue;
    		} else {
    			$_data['position'] = $genotypes[0];
    			$_data['snpid'] = $genotypes[1];
    			$_data['ref'] = $genotypes[2];
    			$_data['alt'] = $genotypes[3];
    			foreach ($germplasms as $k=>$germplasm){
    				$index = ($k+3)+1;
    				$germplasm = strtolower($germplasm);
    				$_data[$germplasm] = $genotypes[$index];
    			}
    		}
    		array_push($data, $_data);
    	}
    }

    drupal_json_output($data);
}
