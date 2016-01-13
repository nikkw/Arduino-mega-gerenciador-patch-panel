#include "Main.h"

void Main(){
	Serial.begin(DEFAULT_SPEED);
	InitializePushButton();
	InitializeArduino();			
	InitializeRelays();	
	InitializeServer();	
}

void Loop(){
    ProcessTimer();
	ProcessClientMessage();  
}