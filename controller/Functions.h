#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "Main.h"

String GetIpStr(byte *ip);
bool ChangeIP(String ip, byte* destIp);
bool Ping(byte *ip);
String StringIntersection(String response, char cIndex, char cFinal);
String StringSplit(String data, char separator, byte index);

#endif