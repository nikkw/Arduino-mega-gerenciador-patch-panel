#ifndef __SERVER_H__
#define __SERVER_H__

#include "Main.h"

#define DEFAULT_PORT 80

extern EthernetServer *Server;

void InitializeServer();
void CreateConnection();
EthernetClient GetAvailableClient();
void RestartServer();

#endif