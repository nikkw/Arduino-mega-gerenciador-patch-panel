#include "Timer.h"

void ProcessTimer(){
	static uint32_t timer = millis();

	if((millis() - timer) >= TIMER_INTERVAL){

		Watchdog();
		CheckInternetConnection();
		
		timer = millis(); 
	}
}

void Watchdog(){
	uint32_t t = millis();
	
	//watchdog funcionar apenas quando ninguem está acessando a interface
	if(InSession.LastReceivedPacketClock != 0){
		if((t - InSession.LastReceivedPacketClock) >= WATCHDOG_EXECUTE * CLOCKS_PER_SEC){	
			InSession.LastReceivedPacketClock = 0;
		}
		else{
			bool flag = false;

			//só vai pausar a execução do watchdog quando tiver nenhuma porta reiniciando
			for(byte i = 0; i < MAX_RELAY; i++){
				if(InSession.Watchdog.Port[i].Restart){
					flag = true;
					break;
				}
			}
			
			InSession.Watchdog.Execute = flag;
		}				
	}
	else{
		InSession.Watchdog.Execute = true;
	}

	if(InSession.Watchdog.Execute){		
		for(byte i = 0; i < MAX_RELAY; i++){

			if(Relay[i].State == RELAY_OFF){
				continue;
			}

			auto ip = Arduino.PatchPanel.Port[i].Ip;

			if(ip[0] != 0){ //se a porta tiver configurada			

				//verifica se ja passou WATCHDOG_WAIT_TIME após reiniciar uma porta
				//senao, o ping nao acontece até acabar esse tempo
				if(!InSession.Watchdog.Port[i].Restart && InSession.Watchdog.Port[i].Clock != 0){
					if((t - InSession.Watchdog.Port[i].Clock) < WATCHDOG_WAIT_TIME * CLOCKS_PER_SEC){					
						continue;
					}
					else{
						InSession.Watchdog.Port[i].Clock = 0;
					}		
				}			

				static uint32_t timer[MAX_RELAY];								

				//testa cada porta com um ping
				//se a quantidade de erros for maior que WATCHDOG_MAX_PING_ERROR_COUNT
				//seta para que essa porta seja reiniciada
				if((t - timer[i]) >= WATCHDOG_CHECK_TIME * CLOCKS_PER_SEC && !InSession.Watchdog.Port[i].Restart){				

					timer[i] = t; 

					if(!Ping(ip)){

						InSession.Watchdog.Port[i].ErrorCount ++;

						if(InSession.Watchdog.Port[i].ErrorCount >= WATCHDOG_MAX_PING_ERROR_COUNT){

							InSession.Watchdog.Port[i].ErrorCount = 0;						
							InSession.Watchdog.Port[i].Off = false;						
							InSession.Watchdog.Port[i].Restart = true;
							continue;
						}
					}
					else{
						InSession.Watchdog.Port[i].ErrorCount = 0;	
					}									
				}

				//verifica se tem alguma porta para reiniciar
				//se tiver alguma, irá desligar a porta
				//depois de WATCHDOG_PORT_RESTART_TIME segundos irá ligar novamente
				if(InSession.Watchdog.Port[i].Restart){				

					if(!InSession.Watchdog.Port[i].Off){								
						InSession.Watchdog.Port[i].Off = true;
						InSession.Watchdog.Port[i].Clock = t;
						SetRelayStatus(i, RELAY_OFF, true);
					}
					else{
						if((t - InSession.Watchdog.Port[i].Clock) >= WATCHDOG_PORT_RESTART_TIME * CLOCKS_PER_SEC){					
							InSession.Watchdog.Port[i].Restart = false;
							InSession.Watchdog.Port[i].Off = false;
							InSession.Watchdog.Port[i].Clock = t;
							SetRelayStatus(i, RELAY_ON);
						}
					}
				}
			}
		}	
	}
}

void CheckInternetConnection(bool starting){
	static uint32_t lastCheckClock = millis();

	if((millis() - lastCheckClock) >= CHECK_CONNECTION_TIME * CLOCKS_PER_SEC || starting){				
		static byte ip[sizeof PING_DNS];
		memcpy_P(&ip[0], &PING_DNS[0], sizeof ip);

		InSession.InternetConnection = Ping(ip);
		
		lastCheckClock = millis();
	}
}