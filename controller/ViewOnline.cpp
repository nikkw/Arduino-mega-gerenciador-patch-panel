#include "ViewOnline.h"

void WritePageHead(EthernetClient &client, String title, bool closeHead = true){
  client.print(F(

    "<!DOCTYPE HTML>"
    "<html lang='pt-br'>"
    "<head>"
    "<title>"

    ));

  client.print(title);

  client.print(F(

    "</title>"
    "<meta charset='utf-8'>"
    "<meta http-equiv='X-UA-Compatible' content='IE=edge'>"
    "<meta name='viewport' content='width=device-width, initial-scale=1'>"
    "<link href='http://arduino.blz.net.br/css/bootstrap.min.css' rel='stylesheet'>"
    "<link href='http://arduino.blz.net.br/css/style.css' rel='stylesheet'>" 
    ));

  if(closeHead){
    client.print(F("</head>"));
  }
}

void ClearCache(EthernetClient &client){
  client.print(F(

    "<script>document.execCommand('ClearAuthenticationCache', 'false');</script>"  //IE logoff
    "<script>try{"                                                                //mozila logoff
    "var agt=navigator.userAgent.toLowerCase();"
    "if (agt.indexOf(\"msie\") != -1) { document.execCommand(\"ClearAuthenticationCache\");}"
    "else{"
    "var xmlhttp = createXMLObject();"
    "xmlhttp.open(\"GET\",\"URL\",true,\"logout\",\"logout\");"
    "xmlhttp.send(\"\");"
    "xmlhttp.abort();"
    "}"
    "}catch(e){"
    "alert(\"Não foi possível fazer o logoff\");"
    "}"
    "function createXMLObject(){"
    "try{if(window.XMLHttpRequest){xmlhttp=new XMLHttpRequest();} else if(window.ActiveXObject){xmlhttp=new ActiveXObject(\"Microsoft.XMLHTTP\");}} catch (e) {xmlhttp=false;}"
    "return xmlhttp;"
    "}</script>"
    ));
}

void WriteSuccessResponse(EthernetClient &client){
  client.print(F(
        "HTTP/1.1 200 OK\n"
        "Content-Type: text/html\n"
        "Connection: keep-alive\n\n"
    ));
}

void WriteResponse(EthernetClient &client, bool success){
  WriteSuccessResponse(client);

  String aux = "_code: " + String(success) + "\n";

  client.print(aux);
}

void WriteLogoff(EthernetClient &client){
  client.print(F(
    "HTTP/1.1 401 Authorization Required\n"
    "Content-Type: text/html\n"
    "Connnection: close\n\n"
    ));

  WritePageHead(client, "Logout", false);
  ClearCache(client);
  client.print(F("</head>"));

  client.print(F(
    "<body>"
    "<h1>Você não está mais conectado</h1>"
    "<script>location.href='/';</script>"
    "</body>"
    "</html>"
    ));
}

void WriteLoginRequest(EthernetClient &client){

  client.print(F(
       "HTTP/1.1 401 Authorization Required\n"
       "WWW-Authenticate: Basic realm=\"Faca login para continuar\"\n"
        "Content-Type: text/html\n"
        "Connnection: close\n\n"
    ));

  WritePageHead(client, "Restrito");

  client.print(F(
    "<body>"
    "<h1 class=>Acesso não autorizado</h1>"
    "</body>"
    "</html>"
    ));
}

void Write404(EthernetClient &client){

  WriteSuccessResponse(client);
  WritePageHead(client, "Oops 404");

  client.print(F(
    "<body>"
    "<div class='container'>"
    "<div class='row'>"
    "<div class='col-md-12'>"
    "<div class='error-template'>"
    "<h1>Oops!</h1>"
    "<h2>404 Página não encontrada</h2>"  
    "<div class='error-actions'>"
    "<a href='/' class='btn btn-primary btn-lg'>Voltar para início </a>"
    "</div>"
    "</div>"
    "</div>"
    "</div>"
    "</body>"
    "</html>"
    ));
}

void WriteFooter(EthernetClient &client){
  client.print(F(
  "<footer class='footer'>"
   "<div class='container'>"
   "<p class='text-muted'>&copy; BLZ Soluções - Todos os direitos reservados.</p>"
   "</div>"
   "</footer>"
   ));
}

void WriteScripts(EthernetClient &client){

    client.print(F(

     "<script src='http://arduino.blz.net.br/js/jquery.min.js'></script>"     
     "<script src='http://arduino.blz.net.br/js/bootstrap.min.js'></script>"
     "<script src='http://arduino.blz.net.br/js/notify.js'></script>"
     "<script src='http://arduino.blz.net.br/js/loading.js'></script>"
     "<script src='http://arduino.blz.net.br/js/scripts.js'></script>"
     ));  
}

void WriteMainPage(EthernetClient &client){
  WriteSuccessResponse(client);
  WritePageHead(client, "Restrito", false);

  client.print(F("<meta http-equiv='refresh' content='60; url=/'>"));
  client.print(F("</head>"));

  client.print(F(
    "<body>"            

    "<nav class='navbar navbar-default navbar'>"
    "<div class='container'>"
    "<ul class='nav navbar-nav navbar-right'>"    
    ));

    String a = "<li><a href='?[" + String(CODE_WATCHDOG) + "]'>Watchdog</a></li>";
    client.print(a);

    a = "<li><a href='?[" + String(CODE_SETTINGS) + "]'>Configurações</a></li>";
    client.print(a);

    String auxx = "<li><a href='?[" + String(CODE_LOGOFF) + "]'>Sair</a></li>";
    client.print(auxx);

    client.print(F(
    "</ul>"         
    "<ul class='nav navbar-nav navbar-left'>"
    ));

    String restart = "<li class='restart-all'><a href='#'>Reiniciar todas portas</a></li>";

    client.print(restart);

    client.print(F(
    "</ul>"       

    "</div>"
    "</nav>"
                                  
    "<div class='container main'>"                  
    "<div class='page-header'>"                             
    "<h1>Controlador</h1>"
   
    "</div>"                    
    ));
    
    String aux;    
    String p;
    for (byte i = 0; i < MAX_RELAY; i++) {
        p = "<a href='/?[" + String(CODE_REVERSE_RELAY_STATUS) + ";" + String(i) + "]'>";
        client.print(p);

        if (Relay[i].State == RELAY_ON) {
          aux = "success";
        }
        else {
          aux = "danger";
        }

        client.print("<button type='button' class='btn btn-" + aux + " btn-door'> Porta " + String(i + 1) + "</button></a>");
    }

    client.println(F(
       "</div>"
       ));
       
       WriteFooter(client);

       WriteScripts(client);

       client.print(F(    
       "</body>"
       "</html>"
        ));
}

void WriteWatchdog(EthernetClient &client){
  WriteSuccessResponse(client);
  WritePageHead(client, "Watchdog", false);
  client.print(F("<meta http-equiv='refresh' content='120; url=/?[10]'>"));
  client.print(F("</head>")); 

  client.print(F(
      "<nav class='navbar navbar-default navbar'>"
      "<div class='container'>"
      "<ul class='nav navbar-nav navbar-right'>"
      ));

      String a = "<li><a href='?[" + String(CODE_LOGOFF) + "]'>Sair</a></li>";
      client.print(a);      

      client.print(F(
      "</ul>"         
      "<ul class='nav navbar-nav navbar-left'>"
      "<li><a href='/'>Voltar para início</a></li>"
      "</ul>"       
      "</div>"
      "</nav>"      
      "<div class='container settings'>"                  
      "<div class='page-header'>"                             
      "<h5 class='pull-right' style='color:#ff0000;'>O Watchdog fica em modo de espera enquanto alguém acessa a interface</h5>"
      "<h1>Watchdog</h1>"
      "</div>"
      "<div class='modals'></div>"     
      "<div class=items>"      
      ));

  for(byte i = 0; i < MAX_RELAY; i++){
    client.print(F(
      "<div class='row settings-item'>"
      "<label class='label-settings'>Porta "));

    client.print(String(i + 1));

    client.print(F(
      "</label>"
      "<form class='form-inline'>"
      "<input type='text' class='form-control box-settings' id='"
      ));

    client.print("w" + String(i));

    client.print(F(
      "' placeholder='"
    ));
    client.print(GetIpStr(Arduino.PatchPanel.Port[i].Ip));
     client.print(F(
      "' disabled>"      
      "<button type='button' data-toggle='modal' data-target='#' class='btn btn-primary' id='"
      ));

     client.print(String(i));

     client.print(F(
       "' onClick='wClick(this.id)'>Alterar</button>"
      "</form>"
      "</div>"
      ));   
  }

  client.print(F(
      "</div>"
      "</div>"
      ));

      WriteFooter(client);
      WriteScripts(client);

      client.print(F(
      "</body>"
      "</html>"
      ));
}

void WriteSettings(EthernetClient &client){
  
    WriteSuccessResponse(client);
    WritePageHead(client, "Configuracoes", false); 

    client.print(F("<meta http-equiv='refresh' content='120; url=/?[8]'>"));
    client.print(F("</head>"));

    client.print(F(
      "<body>"

      "<div class='modal fade' id = 'changeIp'>"
      "<div class='modal-dialog'>"
      "<div class='modal-content'>"
      "<div class='modal-header'>"
      "<button type='button' class='close' data-dismiss='modal' aria-label='Close'>"
      "<span aria-hidden='true'>&times;</span>"
      "</button>"
      "<h4 class='modal-title'>Alterar IP</h4>"
      "</div>"      
      "<div class='modal-body'>"
      "<form>"
      "<div class='form-group'>"
      "<label id='ip'>Digite o novo endereço de IP</label>"
      "<input type='text' class='form-control' id='boxIp' placeholder='IP'>"
      "</div>"
      "</form>"
      "</div>"
      "<div class='modal-footer'>"
      "<button type='button' class='btn btn-default' data-dismiss='modal'>Fechar</button>"
      "<button id='buttonChangeIp' type='submit' class='btn btn-primary'>Salvar alterações</button>"
      "</div>"
      "</div>"
      "</div>"
      "</div>"  

      "<div class='modal fade' id = 'changeGateway'>"
      "<div class='modal-dialog'>"
      "<div class='modal-content'>"
      "<div class='modal-header'>"
      "<button type='button' class='close' data-dismiss='modal' aria-label='Close'>"
      "<span aria-hidden='true'>&times;</span>"
      "</button>"
      "<h4 class='modal-title'>Alterar Gateway</h4>"
      "</div>"      
      "<div class='modal-body'>"
      "<form>"
      "<div class='form-group'>"
      "<label id='ip'>Digite o novo gateway:</label>"
      "<input type='text' class='form-control' id='boxGateway' placeholder='Gateway'>"
      "</div>"
      "</form>"
      "</div>"
      "<div class='modal-footer'>"
      "<button type='button' class='btn btn-default' data-dismiss='modal'>Fechar</button>"
      "<button id='buttonChangeGateway' type='submit' class='btn btn-primary'>Salvar alterações</button>"
      "</div>"
      "</div>"
      "</div>"
      "</div>"  

      "<div class='modal fade' id = 'changeSubNetwork'>"
      "<div class='modal-dialog'>"
      "<div class='modal-content'>"
      "<div class='modal-header'>"
      "<button type='button' class='close' data-dismiss='modal' aria-label='Close'>"
      "<span aria-hidden='true'>&times;</span>"
      "</button>"
      "<h4 class='modal-title'>Alterar máscara de sub rede</h4>"
      "</div>"      
      "<div class='modal-body'>"
      "<form>"
      "<div class='form-group'>"
      "<label id='ip'>Digite a nova máscara de sub rede:</label>"
      "<input type='text' class='form-control' id='boxSubNetwork' placeholder='Máscara de sub rede'>"
      "</div>"
      "</form>"
      "</div>"
      "<div class='modal-footer'>"
      "<button type='button' class='btn btn-default' data-dismiss='modal'>Fechar</button>"
      "<button id='buttonChangeSubNetwork' type='submit' class='btn btn-primary'>Salvar alterações</button>"
      "</div>"
      "</div>"
      "</div>"
      "</div>"  

      "<div class='modal fade' id = 'changePass'>"
      "<div class='modal-dialog'>"
      "<div class='modal-content'>"
      "<div class='modal-header'>"
      "<button type='button' class='close' data-dismiss='modal' aria-label='Close'>"
      "<span aria-hidden='true'>&times;</span>"
      "</button>"
      "<h4 class='modal-title'>Alterar senha</h4>"
      "</div>"      
      "<div class='modal-body'>"
      "<form>"                   
      "<div class='form-group'>"
      "<label id='labelOldPass'>Digite a senha antiga</label>"                   
      "<input type='password' class='form-control' id='boxOldPass' placeholder='Senha antiga'></div>"
      "<div class='form-group'>"
      "<label id='labelOldPass'>Digite a nova senha</label>"                   
      "<input type='password' class='form-control' id='boxNewPass1' placeholder='Nova senha'></div>"
      "<div class='form-group'>"
      "<label id='labelOldPass'>Confirme a nova senha</label>"                   
      "<input type='password' class='form-control' id='boxNewPass2' placeholder='Confirmação'></div>"                  
      "</form></div>"
      "<div class='modal-footer'>"
      "<button type='button' class='btn btn-default' data-dismiss='modal'>Fechar</button>"
      "<button id='buttonChangePass' type='submit' class='btn btn-primary'>Salvar alterações</button>"
      "</div>"
      "</div>"
      "</div>"
      "</div>"  

      "<nav class='navbar navbar-default navbar'>"
      "<div class='container'>"
      "<ul class='nav navbar-nav navbar-right'>"    
      ));

      String auxx = "<li class='apply'><a href='#'>Aplicar modificações</a></li>";
      client.print(auxx);

      auxx = "<li><a href='?[" + String(CODE_LOGOFF) + "]'>Sair</a></li>";
      client.print(auxx);      

      client.print(F(
      "</ul>"         
      "<ul class='nav navbar-nav navbar-left'>"
      "<li><a href='/'>Voltar para início</a></li>"
      "</ul>"       
      "</div>"
      "</nav>"

      "<div class='container settings'>"                  
      "<div class='page-header'>"                             

      "<h5 class='pull-right' style='color:#ff0000;'>Após fazer alterações, clique em <b>aplicar modificações</b></h5>"
      "<h1>Configurações</h1>"

      "</div>"     

      "<div class=items>"
      ));

      //IP
      client.print(F(
      "<div class='row settings-item'>"
      "<label class='label-settings'>IP:</label>"
      "<form class='form-inline'>"
      "<input type='text' class='form-control box-settings' id='boxSettingsIp' placeholder='"
      ));      

      client.print(GetIpStr(Arduino.Ip));

      client.print(F(
      "' disabled>"      
      "<button type='button' data-toggle='modal' data-target='#changeIp' class='btn btn-primary'>Alterar</button>"
      "</form>"
      "</div>" 
      ));     
      //IP

      //GATEWAY
      client.print(F(
      "<div class='row settings-item'>"
      "<label class='label-settings'>Gateway:</label>"
      "<form class='form-inline'>"
      "<input type='text' class='form-control box-settings' id='boxSettingsGateway' placeholder='"
      ));      

      client.print(GetIpStr(Arduino.Gateway));

      client.print(F(
      "' disabled>"      
      "<button type='button' data-toggle='modal' data-target='#changeGateway' class='btn btn-primary'>Alterar</button>"
      "</form>"
      "</div>" 
      ));     
      //GATEWAY

      //SUB NETWORK
      client.print(F(
      "<div class='row settings-item'>"
      "<label class='label-settings'>Máscara de sub rede:</label>"
      "<form class='form-inline'>"
      "<input type='text' class='form-control box-settings' id='boxSettingsSubNetwork' placeholder='"
      ));      

      client.print(GetIpStr(Arduino.SubNetwork));

      client.print(F(
      "' disabled>"      
      "<button type='button' data-toggle='modal' data-target='#changeSubNetwork' class='btn btn-primary'>Alterar</button>"
      "</form>"
      "</div>" 
      ));   
      //SUB NETWORK

      //PASSWORD
      client.print(F(
      "<div class='row settings-item'>"
      "<label class='label-settings'>Senha:</label>"
      "<form class='form-inline'>"
      "<input type='text' class='form-control box-settings' id='boxSettingsPass' placeholder='"
      ));      

      client.print(F("********"));

      client.print(F(
      "' disabled>"      
      "<button type='button' data-toggle='modal' data-target='#changePass' class='btn btn-primary'>Alterar</button>"
      "</form>"
      "</div>" 
      ));   
      //PASSWORD
      
      client.print(F(
      "</div>"
      "</div>"
      ));

      WriteFooter(client);
      WriteScripts(client);

      client.print(F(
      "</body>"
      "</html>"
      ));
}
