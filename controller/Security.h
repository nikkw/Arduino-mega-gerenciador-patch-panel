#ifndef __SECURITY_H__
#define __SECURITY_H__

#include "Main.h"

int ap_base64decode_len(const char *bufcoded, int buflen);
int ap_base64decode(char *bufplain, const char *bufcoded, int buflen);
int ap_base64decode_binary(unsigned char *bufplain, const char *bufcoded, int buflen);
int ap_base64encode_len(int len);
int ap_base64encode(char *encoded, const char *string, int len);
int ap_base64encode_binary(char *encoded, const unsigned char *string, int len);
char *b64_encode(char *buf, int len);
String b64_encode_string(String buf);
char *b64_decode(char *buf);
String b64_decode_string(String buf);

#endif