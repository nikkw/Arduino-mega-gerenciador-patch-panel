#ifndef __VIEW_ONLINE_H__
#define __VIEW_ONLINE_H__

#include "Main.h"

void WritePageHead(EthernetClient &client, String title, bool closeHead);
void ClearCache(EthernetClient &client);
void WriteSuccessResponse(EthernetClient &client);
void WriteResponse(EthernetClient &client, bool success);
void WriteLogoff(EthernetClient &client);
void WriteLoginRequest(EthernetClient &client);
void Write404(EthernetClient &client);
void WriteScripts(EthernetClient &client);
void WriteMainPage(EthernetClient &client);
void WriteWatchdog(EthernetClient &client);
void WriteSettings(EthernetClient &client);

#endif
