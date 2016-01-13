#ifndef __MAIN_H__
#define __MAIN_H__

#include <SPI.h>
#include <Ethernet.h>
#include <ICMPPing.h>
#include <EEPROM.h>

#define MAX_RELAY 10
#define DEFAULT_SPEED 9600

#include "IO.h"
#include "Relay.h"
#include "Arduino.h"
#include "Timer.h"
#include "Server.h"
#include "Client.h"
#include "Parser.h"
#include "ViewOnline.h"
#include "ViewOffline.h"
#include "Security.h"
#include "PushButton.h"
#include "Functions.h"

void Main();
void Loop();

#endif