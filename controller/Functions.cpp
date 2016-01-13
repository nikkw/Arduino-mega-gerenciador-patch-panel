#include "Functions.h"

String GetIpStr(byte *ip){
	 return (String(ip[0]) + "." + String(ip[1]) + "." + String(ip[2]) + "." + String(ip[3]));
}

bool ChangeIP(String ip, byte* destIp){

	String value1 = StringSplit(ip, '.', 0);
	String value2 = StringSplit(ip, '.', 1);
	String value3 = StringSplit(ip, '.', 2);
	String value4 = StringSplit(ip, '.', 3);

	if(value1.length() > 0 && value2.length() > 0 && value3.length() > 0 && value4.length() > 0){
		byte dwIp[4];
		memset(&dwIp, 0, sizeof dwIp);

		dwIp[0] = value1.toInt();
		dwIp[1] = value2.toInt();
		dwIp[2] = value3.toInt();
		dwIp[3] = value4.toInt();

		memcpy(destIp, dwIp, sizeof dwIp);

		WriteConfigurations();	

		return true;
	}

	return false;
}

bool Ping(byte *ip){	
	ICMPPing ping(3, (uint16_t)random(0, 255)); 		
	ICMPEchoReply echo = ping(ip, 1);
	return echo.status == 0;
	/*
	byte sock = MAX_SOCK_NUM;
	byte result = -1;

	for (byte i = 0; i < MAX_SOCK_NUM; i++) {
    	uint8_t s = socketStatus(i);
    	if (s == SnSR::CLOSED || s == SnSR::FIN_WAIT || s == SnSR::CLOSE_WAIT) {
      		sock = i;
      		break;
    	}
  	}

  	if(sock != MAX_SOCK_NUM){
  		ICMPPing ping(sock, (uint16_t)random(0, 255)); 		
		ICMPEchoReply echo = ping(ip, 1);
		result = echo.status;
  	}

  	return result == 0;
  	*/
}

String StringIntersection(String response, char cIndex, char cFinal){
	byte index = response.indexOf(cIndex);
	byte final = response.indexOf(cFinal);

	if(index >= 0 && final >= 0){
		return response.substring(index+1, final);	
	}

	return "";	
}

String StringSplit(String data, char separator, byte index){
	byte found = 0;
  	char strIndex[] = {0, -1};
  	byte maxIndex = data.length()-1;

  	for(byte i = 0; i <= maxIndex && found <= index; i++){
  		if(data.charAt(i) == separator || i == maxIndex){
        	found++;
        	strIndex[0] = strIndex[1]+1;
        	strIndex[1] = (i == maxIndex) ? i + 1 : i;
    	}
  	}

  	return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}
