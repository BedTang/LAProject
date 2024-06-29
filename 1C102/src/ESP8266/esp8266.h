#ifndef __ESP8266_H
#define __ESP8266_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ls1c102.h"



char* esp8266_check_cmd(char *str);
char esp8266_send_cmd(char *cmd,char *ack,uint16_t waittime);
void esp8266_start_trans(void);
char esp8266_send_data( char *ack1,char *ack2, uint16_t waittime);

#ifdef __cplusplus
}
#endif

#endif

