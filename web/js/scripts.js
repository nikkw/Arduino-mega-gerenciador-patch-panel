function ValidateIPaddress(inputText) {
    var ipformat = /^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/;
    return inputText.match(ipformat);
}

function createCookie(name,value,days) {
    if (days) {
        var date = new Date();
        date.setTime(date.getTime()+(days*24*60*60*1000));
        var expires = "; expires="+date.toGMTString();
    }
    else var expires = "";
    document.cookie = name+"="+value+expires+"; path=/";
}

function readCookie(name) {
    var nameEQ = name + "=";
    var ca = document.cookie.split(';');
    for(var i=0;i < ca.length;i++) {
        var c = ca[i];
        while (c.charAt(0)==' ') c = c.substring(1,c.length);
        if (c.indexOf(nameEQ) == 0) return c.substring(nameEQ.length,c.length);
    }
    return "";
}

function eraseCookie(name) {
    createCookie(name,"",-1);
}

function wClick(id){ 
	//click do botão 'alterar' no watchdog
	//monta um modal dinamicamente de acordo com o id do relay clicado
	modal = "<div class='modal fade' id='m" + id + "'>" +
      "<div class='modal-dialog'>" +
      "<div class='modal-content'>" +
      "<div class='modal-header'>" +
      "<button type='button' class='close' data-dismiss='modal' aria-label='Close'>" +
      "<span aria-hidden='true'>&times;</span>" +
      "</button>" +
      "<h4 class='modal-title'>Alterar IP porta " + (parseInt(id) + 1).toString() + "</h4>" +
      "</div>" +      
      "<div class='modal-body'>" +
      "<form>" +
      "<div class='form-group'>" +
      "<label id='ip'>Digite o IP</label>" +
      "<input type='text' class='form-control' id='i" + id + "' placeholder='IP'>" +
      "</div>" +
      "</form>" +
      "</div>" +
      "<div class='modal-footer'>" +
      "<button type='button' class='btn btn-default' data-dismiss='modal'>Fechar</button>" +
      "<button id='b" + id + "' type='submit' class='btn btn-primary' onClick='bClick(this.id)'>Salvar alterações</button>" +
      "</div>" +
      "</div>" +
      "</div>" +
      "</div>";

      $("div.modals" ).html(modal);

      a = "#m" + id;
      $(a).modal('show');
}

function bClick(id){
	id = id.replace('b', '');
	ip = $('#i' + id).val();

	if(!ip){
		$.notify("Preencha todos os campos", "error");
		return;
	}	

	if(!ValidateIPaddress(ip)){
		$.notify("Formato de IP incorreto", "error");
		return;
	}
		
	var args = btoa(id + ";" + ip);	
	var urlData = "[12;" +  args + "]";

	$.ajax({
        type: "GET",
        url: "/",
        async: true,
        data: urlData,

        success: function(data) { 

        	var d = data.split(":");

			if(d[1] == 1){
				$.notify("IP alterado com sucesso", "success");  
				$("#m" + id).modal('hide');
				$('#i' + id).val('');  						
				$('#w' + id).val(ip);
			}  				
			else{
				$.notify("Não foi possível alterar o IP", "error");
			}
        },
    });
}

$(function(){
	$('#buttonChangeIp').click(function(){
		var ip = $('#boxIp').val();

		if(!ip){
			$.notify("Preencha todos os campos", "error");
			return;
		}

		else if(!ValidateIPaddress(ip)){
			$.notify("Formato de IP inválido", "error");
			return;
		}

		var args = btoa(ip);
		var urlData = "[4;" +  args + "]";

		$.ajax({
            type: "GET",
            url: "/",
            async: true,
            data: urlData,

            success: function(data) { 

            	var d = data.split(":");

				if(d[1] == 1){
					createCookie("ip", ip);
					$.notify("Clique em aplicar modificações para completar", "warn");                
					$.notify("IP alterado com sucesso", "success");  
					$('#changeIp').modal('hide');
					$('#boxIp').val('');  						
				}  				
				else{
					$.notify("Não foi possível alterar o IP", "error");
				}
            },
        });
	});

	$('#buttonChangeGateway').click(function(){
		var gat = $('#boxGateway').val();

		if(!gat){
			$.notify("Preencha todos os campos", "error");
			return;
		}

		else if(!ValidateIPaddress(gat)){
			$.notify("Formato de gateway inválido", "error");
			return;
		}

		var args = btoa(gat);
		var urlData = "[5;" +  args + "]";

		$.ajax({
            type: "GET",
            url: "/",
            async: true,
            data: urlData,

            success: function(data) { 

            	var d = data.split(":");

				if(d[1] == 1){
					$.notify("Clique em aplicar modificações para completar", "warn");                
					$.notify("Gateway alterado com sucesso", "success");  
					$('#changeGateway').modal('hide');
					$('#boxGateway').val('');  						
				}  				
				else{
					$.notify("Não foi possível alterar gateway", "error");
				}
            },
        });
	});

	$('#buttonChangeSubNetwork').click(function(){
		var gat = $('#boxSubNetwork').val();

		if(!gat){
			$.notify("Preencha todos os campos", "error");
			return;
		}

		else if(!ValidateIPaddress(gat)){
			$.notify("Formato de máscara de sub rede inválido", "error");
			return;
		}

		var args = btoa(gat);
		var urlData = "[6;" +  args + "]";

		$.ajax({
            type: "GET",
            url: "/",
            async: true,
            data: urlData,

            success: function(data) { 

            	var d = data.split(":");

				if(d[1] == 1){
					$.notify("Clique em aplicar modificações para completar", "warn");                
					$.notify("Máscara de sub rede alterado com sucesso", "success");         
					$('#changeSubNetwork').modal('hide');
					$('#boxSubNetwork').val('');  						
				}  				
				else{
					$.notify("Não foi possível alterar a máscara de sub rede", "error");
				}
            },
        });
	});

	$('#buttonChangePass').click(function(){

		var oldPass = $('#boxOldPass').val();
		var newPass1 = $('#boxNewPass1').val();
		var newPass2 = $('#boxNewPass2').val();

		if(!oldPass || !newPass1 || !newPass2){
			$.notify("Preencha todos os campos", "error");
			return;
		}

		else if(newPass1 != newPass2){
			$.notify("As senhas são diferentes", "error");
			return;
		}

		if(newPass1.length < 4 || newPass1.length > 16){
			$.notify("A senha deve ter entre 4 e 16 caracteres", "error");
			return;
		}

		//encode: btoa
		//decode: atob

		var args = btoa(oldPass + ";" + newPass1 + ";" + newPass2);
		var urlData = "[7;" +  args + "]";

		$.ajax({
            type: "GET",
            url: "/",
            async: true,
            data: urlData,

            success: function(data) { 	

            	var d = data.split(":");

				if(d[1] == 1){
					$.notify("Senha alterada com sucesso", "success");

					$('#changePass').modal('hide');

					$('#boxOldPass').val('');
					$('#boxNewPass1').val('');
					$('#boxNewPass2').val('');
				}            	
				else{
					$.notify("Senha informada incorreta", "error");
				}
            }
        });
	});
	
	$('ul.navbar-left li.restart-all').click(function(e){
		waitingDialog.show("Reiniciando");

		var urlData = "[1]";
		var success = false;

		$.ajax({
            type: "GET",
            url: "/",
            async: true,
            data: urlData,

            success: function(data) { 	

            	var d = data.split(":");

				if(d[1] == 1){
					success = true;	
				}            	
            }
        });

		setTimeout(function () {

			urlData = "[2]";
			success = false;

			$.ajax({
	            type: "GET",
	            url: "/",
	            async: false,
	            data: urlData,

	            success: function(data) { 	

	            	var d = data.split(":");

					if(d[1] == 1){
						success = true;	
					}            	
	            }
	        });

			waitingDialog.hide();

			window.location = '/';
		}, 5000)		
	});

	$('ul.navbar-right li.apply').click(function(e){
		waitingDialog.show("Aplicando modificações");

		var urlData = "[9]";

		$.ajax({
            type: "GET",
            url: "/",
            async: true,
            data: urlData,
        });

		setTimeout(function () {

			waitingDialog.hide();		

			var ip = readCookie("ip");			

			if(ip != ""){
				eraseCookie("ip");
				window.location = 'http://' + ip + '/?[8]';
			}
			else{
				window.location = '/?[8]';
			}	
		}, 4000)		
	});	
})


