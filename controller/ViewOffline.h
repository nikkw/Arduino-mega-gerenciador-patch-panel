#ifndef __VIEW_OFFLINE_H__
#define __VIEW_OFFLINE_H__

#include "Main.h"

void WriteMainPageOff(EthernetClient &client);
void WriteRestartPortsOff(EthernetClient &client);
void WriteWatchdogOff(EthernetClient &client);
void WriteSettingsOff(EthernetClient &client);
void WriteRestartOff(EthernetClient &client);
void Write404Off(EthernetClient &client);

#endif