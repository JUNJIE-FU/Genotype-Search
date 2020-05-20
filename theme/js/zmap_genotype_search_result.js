$(document).ready(function(){
	var dataset = Drupal.settings.zmap_genotype.dataset ? Drupal.settings.zmap_genotype.dataset : '';
	var germplasms = Drupal.settings.zmap_genotype.germplasms ? Drupal.settings.zmap_genotype.germplasms : '';
	var pos_chr = Drupal.settings.zmap_genotype.chr ? Drupal.settings.zmap_genotype.chr : '';
	var pos_start = Drupal.settings.zmap_genotype.start ? Drupal.settings.zmap_genotype.start : '';
	var pos_end = Drupal.settings.zmap_genotype.end ? Drupal.settings.zmap_genotype.end : '';
	if(!dataset){
		$('#messagebox').html('Dataset should be provided.');
	}
	if(!germplasms){
		$('#messagebox').html('Germplasm should be provided.');
	}
	if(!pos_chr){
		$('#messagebox').html('Chr should be provided.');
	}
	if(!pos_start){
		$('#messagebox').html('Start position should be provided.');
	}
	if(!pos_end){
		$('#messagebox').html('End position should be provided.');
	}

	var germplasms_arr = germplasms.split(',');
	var tab_columns = [
		{title:"Position", field:"position"},
		{title:"ID", field:"snpid", sorter:"string"},
		{title:"REF", field:"ref", sorter:"string"},
		{title:"ALT", field:"alt", sorter:"string"}
	];
	function formatter_function(cell, formatterParams){
		var data = cell.getValue();
		if(data == '0|0'){
			$(cell.getElement()).css({"background-color":"#FBB4AE"});
		} else if(data == '1|1'){
			$(cell.getElement()).css({"background-color":"#B3CDE3"});
		} else if(data == '0|1'){
			$(cell.getElement()).css({"background-color":"#CCEBC5"});
		} else {
			$(cell.getElement()).css({"background-color":"#D9D9D9"});
		}
		return cell.getValue();
	}
	
	$.each(germplasms_arr, function(index, item){
		var _item = item.toLowerCase();
		var _column = { title:item, field:_item, formatter:formatter_function };
		tab_columns.push(_column);
	});
	var genotypes_result_table = new Tabulator('#genotype_search_result', {
		columns: tab_columns, 
		layout:"fitData",
		pagination:"local",
		paginationSize:20, 
		tooltipsHeader:true
	});

	var genotypes_result;
	var genotypes_result_api = "/api/genotype/result/dataset/" + dataset + "/germplasms/" + germplasms + "/chr/" + pos_chr + "/start/" + pos_start + "/end/" + pos_end;
	$.ajax({
		url: genotypes_result_api,
		type: "get",
		dataType: "json",
		async: false,
		success: function(data){
		        current_dataset = '<p id="current_dataset">Current Dataset: <b>' + dataset + '</b></p>';	
			$(current_dataset).insertBefore('#genotype_search_result');
			genotypes_result_table.setData(data);
		}
	});
	
	/*
	$('#genotypes_download').click(function(){
		genotypes_result_table.download('csv', 'zeamap_genotypes_result.csv');
	});
	*/
});
