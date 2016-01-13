#ifndef __WATCHDOG_H__
#define __WATCHDOG_H__

#include "Main.h"

static const byte PING_DNS[4] PROGMEM = {4, 2, 2, 1}; //OpenDNS

#define WATCHDOG_WAIT_TIME               60L   //tempo para começar a pingar de novo após a porta ser reiniciada
#define WATCHDOG_CHECK_TIME              15L   //intervalo de tempo para os pings NAO COLOCAR MENOS QUE 15
#define WATCHDOG_PORT_RESTART_TIME       10L   //tempo para reiniciar a porta
#define WATCHDOG_MAX_PING_ERROR_COUNT     5L   //quantidade máxima de erros de ping
#define WATCHDOG_EXECUTE                 60L   //tempo que o watchdog volta a executar depois de receber um packet

#define CHECK_CONNECTION_TIME            15L   //intervalo de tempo para checar se há conexão com a internet
 
#define TIMER_INTERVAL                 1000L    //intervalo de tempos em que os timers sao chamados (em ms)

#define CLOCKS_PER_SEC                 1000L

void ProcessTimer();
void Watchdog();
void CheckInternetConnection(bool starting=false);

#endif