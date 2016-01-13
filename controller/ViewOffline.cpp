#include "ViewOffline.h"

void WriteMainPageOff(EthernetClient &client){
	WriteSuccessResponse(client);
	client.print(F(
	"<!DOCTYPE html>"
	"<html lang='pt-br'>"
	"<head>"
	"<meta http-equiv='refresh' content='60; url=/'>"
	"<meta charset='utf-8'>"
	"<title>Restrito</title>"

	"<style>"
	"li{"
	"display:inline;"
	"padding-right:30px;"
	"}"
	"button{"
	"height:40px;"
	"width:100px;"
	"color:#fff;"
	"}"
	".r{"
	"background-color:#d9534f;"
	"}"
	".g{"
	"background-color:#5cb85c;"
	"}"
	"</style>"	
	"<script>"
	"function restart(){"
	"window.location = '/?[13]';"
	"}"
	"</script>"
	"</head>"
	"<body>"
	"<ul>"
	"<a href='#' onClick='restart();'><li>Reiniciar todas as portas</li></a>"
	"<a href='?[10]'><li>Watchdog</li></a>"
	"<a href='?[8]'><li>Configurações</li></a>"
	"<a href='?[11]'><li>Sair</li></a>"
	"</ul>"
	));

	String aux;    
    String p;
    for (byte i = 0; i < MAX_RELAY; i++) {
        p = "<a href='/?[" + String(CODE_REVERSE_RELAY_STATUS) + ";" + String(i) + "]'>";
        client.print(p);

        if (Relay[i].State == RELAY_ON) {
          aux = "g";
        }
        else {
          aux = "r";
        }

        client.print("<button class='" + aux + "'>Porta " + String(i + 1) + "</button></a>");
    }

    client.print(F(
    "</body>"
	"</html>"
    ));
}

void WriteRestartPortsOff(EthernetClient &client){
	WriteSuccessResponse(client);
	client.print(F(
	"<head>"
	"<meta charset='utf-8'>"
	"</head>"
	"<h2>Reiniciando portas</h2>"	
	"<h3>Aguarde um momento, você será redirecionado</h3>"
	"<script>"
	"function get(u){"
	"var x=new XMLHttpRequest();"
	"x.open('GET',u,false);"
	"x.send();"
	"}"
	"get('/?[1]');"
	"setTimeout(function(){get('/?[2]');window.location='/';},5000);"
	"</script>"	
	));
}

void WriteWatchdogOff(EthernetClient &client){
	WriteSuccessResponse(client);

	client.print(F(	
	"<!DOCTYPE html>"
	"<html lang='pt-br'>"
	"<head>"
	"<meta http-equiv='refresh' content='60; url=/'>"
	"<meta charset='utf-8'>"
	"<title>Watchdog</title>"

	"<style>"
	"li{"
	"display: inline;"
	"padding-right:30px;"
	"}"		
	"</style>"

	"<script>"
	"function get(u){"		
	"var x=new XMLHttpRequest();"
	"x.open('GET',u,false);"
	"x.send();"
	"return x.responseText;"
	"}"	
	"function valid(i) {"
	"var ip = /^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/;"
	"return i.match(ip);"
	"}"
	"function chn(id){"
	"id = id.replace('p', '');"
	"var ip = prompt('Digite o novo IP:');"
	"if(ip != null){"
	"if(valid(ip)){"
	"var a = btoa(id + ';' + ip);"
	"var url = '[12;' +  a + ']';"
	"var r=get(url);"
	"r=r.split(':');"
	"if(r[1]==1){"
	"document.getElementById('t' + id).value = ip;"
	"alert('IP alterado com sucesso');"
	"}"
	"else{"
	"alert('Não foi possível alterar o IP');"
	"}"
	"}"
	"else{"
	"alert('Formato de IP incorreto');"
	"}"
	"}"
	"}"
	"</script>"
	"</head>"
	"<body>"
	"<ul>"
	"<a href='/'><li>Voltar para início</li></a>"
	"<a href='?[11]'><li>Sair</li></a>"
	"</ul>"
	));

	for(byte i = 0; i < MAX_RELAY; i++){
		String w = "Porta " + String(i + 1) + ":<br><input type='text' placeholder='" + GetIpStr(Arduino.PatchPanel.Port[i].Ip) + "' id='t" + String(i) + "' disabled><button id='p" + String(i) + "' onClick='chn(this.id);'>Alterar</button><br><br>";

		client.print(w);
	}

	client.print(F(
	"</body>"
	"</html>"
	));
}

void WriteSettingsOff(EthernetClient &client){
	WriteSuccessResponse(client);

	client.print(F(
	"<!DOCTYPE html>"
	"<html lang='pt-br'>"
	"<head>"
	"<meta charset='utf-8'>"
	"<title>Configurações</title>"

	"<style>"
	"li{"
	"display: inline;"
	"padding-right:30px;}"

	"</style>"

	"<script>"
	"function createCookie(e,t,i){if(i){var o=new Date;o.setTime(o.getTime()+24*i*60*60*1e3);var a='; expires='+o.toGMTString()}else var a='';document.cookie=e+'='+t+a+'; path=/'}"
	"function get(u){"	
	"var x=new XMLHttpRequest();"
	"x.open('GET',u,false);"
	"x.send();"
	"return x.responseText;}"	
	"function valid(i){"
	"var ip = /^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/;"
	"return i.match(ip);}"

	"function cPass(){"
	"var pass = prompt('Digite a senha antiga');"
	"if(pass != null){"
	"var new1 = prompt('Digite a nova senha');"
	"if(new1 != null){"
	"var new2 = prompt('Confirme a nova senha');"
	"if(new2 != null){"
	"if(new1 == new2){"
	"if(new1.length >= 4 && new1.length <= 16){"
	"var a = btoa(pass + ';' + new1 + ';' + new2);"
	"var url = '[7;' +  a + ']';"
	"var r = get(url);"
	"r = r.split(':');"
	"if(r[1] == 1){"
	"alert('Senha alterada com sucesso');}"
	"else{"
	"alert('Não foi possível alterar a senha');}}"
	"else{"
	"alert('A senha deve conter entre 4 e 16 caracteres');}}"
	"else{"
	"alert('A senha e a confirmação estão diferentes');}}}}}"
	

	"function cIp(id){"
	"var ip = prompt('Digite o novo valor');"
	"if(ip != null){"
	"if(valid(ip)){"
	"var code = ['4','5','6'];"
	"if(id >= 0 && id < 3){"
	"var a = btoa(ip);"
	"var url = '[' + code[id] + ';' +  a + ']';"
	"var r = get(url);"
	"r=r.split(':');"
	"if(r[1]==1){"
	"if(id==0){createCookie('ip', ip);}"
	//"document.getElementById('t' + id).value = ip;"
	"alert('Alteração feita com sucesso. Clique em aplicar modificações para completar');}"
	"else{"
	"alert('Não foi possível completar a alteração');}}"
	"else{"
	"alert('Não foi possível completar a alteração');}}"
	"else{"
	"alert('Formato de IP incorreto');}}}"

	"</script>"
	"</head>"
	"<body>"
	"<ul>"
	"<a href='/'><li>Voltar para início</li></a>"
	"<a href='?[14]'><li>Aplicar modificações</li></a>"
	"<a href='?[11]'><li>Sair</li></a>"
	"</ul>"

	"<h4 style='color:red;'>Após fazer alterações, clique em aplicar modificações</h4>"

	"IP:<br> <input type='text' placeholder='"
	));
	
	client.print(GetIpStr(Arduino.Ip));

	client.print(F(
	"' id='t0' disabled> <button id='0' onClick='cIp(this.id);'>Alterar</button><br><br>"	
	"Gateway:<br> <input type='text' placeholder='"
	));

	client.print(GetIpStr(Arduino.Gateway));

	client.print(F(
	"' id='t1' disabled> <button id='1' onClick='cIp(this.id);'>Alterar</button><br><br>"
	"Máscara de sub rede:<br> <input type='text' placeholder='"
	));

	client.print(GetIpStr(Arduino.SubNetwork));

	client.print(F(
	"' id='t2' disabled> <button id='2' onClick='cIp(this.id);'>Alterar</button><br><br>"
	"Senha:<br> <input type='text' placeholder='********' id='t3' disabled> <button id='3' onClick='cPass();'>Alterar</button><br><br>"
	"</body>"
	"</html>"
	));
}

void WriteRestartOff(EthernetClient &client){
	WriteSuccessResponse(client);
	client.print(F(
	"<!DOCTYPE html>"
	"<html lang='pt-br'>"
	"<head>"
	"<meta charset='utf-8'>"
	"<title>Aplicando modificações</title>"
	"</head>"
	"<body>"
	"<h2>Aplicando modificações</h2>"	
	"<h3>Aguarde um momento, você será redirecionado</h3>"

	"<script>"
	"function createCookie(e,t,o){if(o){var r=new Date;r.setTime(r.getTime()+24*o*60*60*1e3);var i='; expires='+r.toGMTString()}else var i='';document.cookie=e+'='+t+i+'; path=/'}function readCookie(e){for(var t=e+'=',o=document.cookie.split(';'),r=0;r<o.length;r++){for(var i=o[r];' '==i.charAt(0);)i=i.substring(1,i.length);if(0==i.indexOf(t))return i.substring(t.length,i.length)}return''}function eraseCookie(e){createCookie(e,'',-1)}"

	"function get(u){"
	"var x=new XMLHttpRequest();"
	"x.open('GET',u,true);"
	"x.send();"
	"}"

	"get('/?[9]');"

	"setTimeout(function () {"
	"var ip = readCookie('ip');"		

	"if(ip != ''){"
	"eraseCookie('ip');"
	"window.location = 'http://' + ip + '/?[8]';"
	"}"
	"else{"
	"window.location = '/?[8]';"
	"}"
	"}, 3000)"

	"</script>"	
	"</body>"
	"</html>"
	));
}

void Write404Off(EthernetClient &client){
	WriteSuccessResponse(client);

	client.print(F(
	"<!DOCTYPE html>"
	"<html lang='pt-br'>"
	"<head>"
	"<meta charset='utf-8'>"
	"<title>404</title>"
	"</head>"
	"<body>"
	"<h2>Página não encontrada</h2>"	
	"<h3>Aguarde um momento, você será redirecionado</h3>"

	"<script>"

	"setTimeout(function () {"
	"window.location = '/';"
	"}, 2000)"

	"</script>"	
	"</body>"
	"</html>"
	));


}