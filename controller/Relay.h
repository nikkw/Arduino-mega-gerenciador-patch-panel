#ifndef __RELAY_H__
#define __RELAY_H__

#include "Main.h"

#define RELAY_ON HIGH
#define RELAY_OFF LOW

static const byte RelayPorts[MAX_RELAY] PROGMEM = {3, A4, 5, 6, 7, 8, 9, A0, A1, A2};

typedef struct {
  byte Port;
  byte State;
} st_Relay;

extern st_Relay Relay[MAX_RELAY];

void InitializeRelays();
void SetRelayStatus(byte relayPos, byte status, bool watchdog=false);
void ReverseRelayStatus(byte RelayPos);
void TurnOnAllRelays();
void TurnOffAllRelays();

#endif

