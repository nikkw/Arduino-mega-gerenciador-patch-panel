#include "Relay.h"

st_Relay Relay[MAX_RELAY];

void InitializeRelays(){
	memset(&Relay, 0, sizeof(Relay));

	for(byte i = 0; i < MAX_RELAY; i++){
		Relay[i].Port = pgm_read_byte_near(RelayPorts + i);
		Relay[i].State = RELAY_ON;
		pinMode(Relay[i].Port, OUTPUT);		
	}

	TurnOnAllRelays();
}

void SetRelayStatus(byte relayPos, byte status, bool watchdog){
	if(relayPos >= 0 && relayPos < MAX_RELAY){
		if(status == RELAY_ON || status == RELAY_OFF){
			if(!watchdog){
				Relay[relayPos].State = status;
			}
			else{
				Relay[relayPos].State = RELAY_ON;
			}
			
			digitalWrite(Relay[relayPos].Port, status);
		}		
	}
}

void ReverseRelayStatus(byte relayPos){
	SetRelayStatus(relayPos, !Relay[relayPos].State);
}

void TurnOnAllRelays(){
	for(byte i = 0; i < MAX_RELAY; i++){
		SetRelayStatus(i, RELAY_ON);
	}
}

void TurnOffAllRelays(){
	for(byte i = 0; i < MAX_RELAY; i++){
		SetRelayStatus(i, RELAY_OFF);
	}
}