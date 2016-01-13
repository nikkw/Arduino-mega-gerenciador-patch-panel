#include "Client.h"

void ProcessClientMessage(){
	EthernetClient client = GetAvailableClient();	

	if(client){		

		String line1;

		for(byte i = 0; i < MAX_LINE; i++){
			char c = client.read();

			if(c == '\n'){
				break;
			}	

			line1 += c;
		}

		const auto packetId = GetPacketId(line1);

		if(packetId > MAX_CODE){
			if(InSession.InternetConnection){
				Write404(client);
			}
			else{
				Write404Off(client);
			}
		}
		
		//in session packets
		else if(packetId == CODE_TURN_OFF_ALL_RELAYS){
			TurnOffAllRelays();
			WriteResponse(client, true);	
		}

		else if(packetId == CODE_TURN_ON_ALL_RELAYS){
			TurnOnAllRelays();
			WriteResponse(client, true);	
		}
		
		else if(packetId == CODE_REVERSE_RELAY_STATUS){
			String arg = GetArgument(line1, 1);
			if(arg != ""){
				byte relay = arg.toInt();
				if(relay >= 0 && relay < MAX_RELAY){
					ReverseRelayStatus(relay);
					client.print(F("<script>window.location = '/';</script>"));				
				}
			}
		}

		else if(packetId == CODE_CHANGE_IP){
			String plain = "[" + b64_decode_string(GetArgument(line1, 1)) + "]";

			String ip = GetArgument(plain, 0);

			bool success = ChangeIP(ip, Arduino.Ip);

			WriteResponse(client, success);
		}

		else if(packetId == CODE_CHANGE_GATEWAY){
			String plain = "[" + b64_decode_string(GetArgument(line1, 1)) + "]";

			String ip = GetArgument(plain, 0);

			bool success = ChangeIP(ip, Arduino.Gateway);
			
			WriteResponse(client, success);
		}

		else if(packetId == CODE_CHANGE_SUBNETWORK){
			String plain = "[" + b64_decode_string(GetArgument(line1, 1)) + "]";

			String ip = GetArgument(plain, 0);

			bool success = ChangeIP(ip, Arduino.SubNetwork);

			WriteResponse(client, success);
		}

		else if(packetId == CODE_CHANGE_PASS){
			String plain = "[" + b64_decode_string(GetArgument(line1, 1)) + "]";

			String oldPass = GetArgument(plain, 0);
			String newPass1 = GetArgument(plain, 1);
			String newPass2 = GetArgument(plain, 2);	

			bool success = false;

			if(oldPass == Arduino.Pass){
				if(newPass1 == newPass2){
					if(newPass1.length() >= 4 && newPass1.length() <= sizeof Arduino.Pass){				
						
						char pass[sizeof Arduino.Pass];
						memset(pass, 0, sizeof pass);
						newPass1.toCharArray(pass, newPass1.length() + 1);
						
						strncpy(Arduino.Pass, pass, sizeof Arduino.Pass); 

						WriteConfigurations();

						success = true;						
					}
				}
			}

			WriteResponse(client, success);
		}	

		else if(packetId == CODE_WATCHDOG){
			if(InSession.InternetConnection){
				WriteWatchdog(client);
			}
			else{
				WriteWatchdogOff(client);
			}
		}

		else if(packetId == CODE_WATCHDOG_CHANGE_IP){

			String plain = "[" + b64_decode_string(GetArgument(line1, 1)) + "]";

			byte relay = GetArgument(plain, 0).toInt();
			String ip = GetArgument(plain, 1);

			bool success = false;

			if(relay >= 0 && relay < MAX_RELAY){
				success = ChangeIP(ip, Arduino.PatchPanel.Port[relay].Ip);
			}

			WriteResponse(client, success);				
		}

		else if(packetId == CODE_SETTINGS){
			if(InSession.InternetConnection){
				WriteSettings(client);
			}
			else{
				WriteSettingsOff(client);
			}			
		}

		else if(packetId == CODE_RESTART){
			RestartServer();
		}

		else if(packetId == CODE_RESTART_PORTS_OFFLINE){
			WriteRestartPortsOff(client);			
		}

		else if(packetId == CODE_LOGOFF){
			WriteLogoff(client);
		}

		else if(packetId == CODE_RESTART_OFFLINE){
			WriteRestartOff(client);
		}		

		else{ //off session packets		

			String response;
			static const String match = F("Authorization: Basic");
			bool flag = false;
			uint16_t index = 0;
			uint16_t final = 0;

			for(uint16_t i = 0; i < MAX_RESPONSE_SIZE; i++){
				char c = client.read();

				response += c;

				if(response.indexOf(match) >= 0 && !flag){
					flag = true;
					index = i+2;
				}

				if(flag && c == '\n'){
					final = i;
					break;
				}
			}

			if(index > 0 && final > 0 && flag){
				String hash = response.substring(index, final);

				String dec = b64_decode_string(hash);

				String arduino = String(Arduino.User) + ":" + String(Arduino.Pass);
				
				if(dec == arduino){
					if(InSession.InternetConnection){
						WriteMainPage(client);
					}
					else{
						WriteMainPageOff(client);
					}
				}
				else{
					WriteLoginRequest(client);
				}
			}
			else{
				WriteLoginRequest(client);
			}
		}

		InSession.LastReceivedPacketClock = millis();				
		client.stop();
	}
}
