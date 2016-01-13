#include "Server.h"

EthernetServer *Server;

void InitializeServer(){
	memset(&Server, 0, sizeof(Server));

	CreateConnection();

	CheckInternetConnection(true);
}

void CreateConnection(){
	Server = new EthernetServer(DEFAULT_PORT);

	Ethernet.begin(Arduino.Mac, Arduino.Ip, 1, Arduino.Gateway, Arduino.SubNetwork);

	Server->begin();

	Serial.print(F("Server IP: "));
  	Serial.println(Ethernet.localIP());
}

EthernetClient GetAvailableClient(){
	return Server->available();
}

void RestartServer(){
	Ethernet.begin(Arduino.Mac, Arduino.Ip, 1, Arduino.Gateway, Arduino.SubNetwork);

	Server->begin();

	Serial.print(F("Server restarted IP: "));
  	Serial.println(Ethernet.localIP());
}