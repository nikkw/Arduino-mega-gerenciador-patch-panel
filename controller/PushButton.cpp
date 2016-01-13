#include "PushButton.h"

void InitializePushButton(){
	pinMode(PushButtonPort, INPUT);

	byte state = analogRead(PushButtonPort);

	if(state == 0){
		SetDefaultConfigurations();
	}
}
