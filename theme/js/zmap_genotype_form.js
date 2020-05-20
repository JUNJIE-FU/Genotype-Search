$(document).ready(function(){
	$('#selected_nodes').css('display', 'none');
	var dataset = $('#edit-select-dataset').val();
	var zNodes, zTreeObj;
        var zTree_selected_nodes = new Array();

	$('#edit-select-dataset').change(function(){
		dataset = $('#edit-select-dataset').val();
		$.ajax({
	        url: "/api/genotype/retrive_germplasm/dataset/" + dataset,
	        type: "get",
	        dataType: "json",
	        success: function(data){
	            zTreeObj = $.fn.zTree.init($("#germplasms_tree"), setting, data);
	            fuzzySearch('germplasms_tree','#edit_germplasm_fuzzy_search',null,true); //初始化模糊搜索方法
	        }
    	});
	});
    /* --- ztree zmap-genotype tree init start --- */
    
    var setting = {
        check: {
            enable: true,
            chkStyle: "checkbox"
        },
        view: {
            nameIsHTML: true, //允许name支持html				
            selectedMulti: false
        },
        edit: {
            enable: false,
            editNameSelectAll: false
        },
        data: {
            simpleData: {
                enable: true
            }
        },
        treeNode: {
            open: false 
        },
        callback: {
            onCheck: zTreeOnCheck
        }
    };
    $.ajax({
        url: "/api/genotype/retrive_germplasm/dataset/" + dataset,
        type: "get",
        dataType: "json",
        success: function(data){
	            zTreeObj = $.fn.zTree.init($("#germplasms_tree"), setting, data);
	            fuzzySearch('germplasms_tree','#edit-germplasm-fuzzy-search',null,true); //初始化模糊搜索方法
        }
    });

    $('#edit-germplasm-fuzzy-search').click(function(e){
        $('#germplasms_tree').show();
        e.stopPropagation();
    });
    $('#germplasms_tree').click(function(e){
        $('#germplasms_tree').show();
        e.stopPropagation();
    });
    $('body').on('click',function(){
        $('#germplasms_tree').hide();
    });

    $('#zmap-genotype-form').submit(function(e){
        var selected_germplasms = zTree_selected_nodes.filter(function(v){return v != null && v != '';}).join().trim(',');
        $("input[name='selected_germplasms_hidden']").val(selected_germplasms);
    });

    function zTreeOnCheck(event, treeId, treeNode)
    {
        var treeObj = $.fn.zTree.getZTreeObj("germplasms_tree");
        var changedNodes = treeObj.getChangeCheckedNodes();
        $.each(changedNodes, function(index, item){
            item.checkedOld = item.checked;
        });
        $('#selected_nodes').css('display', 'block');
        var checkedNode;
        $.each(changedNodes, function(index, item){
	    if(item.isParent != true){
            	if (item.checked === true){
                	if(item.oldname){
                    		checkedNode = '<div id="'+ item.id +'" class="checked_node"><span>' + item.oldname + '</span></div>';
	                    	zTree_selected_nodes[parseInt(item.id)] = item.oldname; 
        	        } else {
                	    	checkedNode = '<div id="'+ item.id +'" class="checked_node"><span>' + item.name + '</span></div>';
	                    	zTree_selected_nodes[parseInt(item.id)] = item.name;
        	        }
                	$('#selected_nodes').append(checkedNode);
	        } else {
        	    	remove_id = '#' + item.id;
                	$('div').remove(remove_id);
	                zTree_selected_nodes.splice(parseInt(item.id), 1, null);
        	}
	    }
	});
        if($('.checked_node').length == 0){
            $('#selected_nodes').css('display', 'none');
        }
    }
});
