#ifndef _INTELLIGENT_VOICE_H__
#define _INTELLIGENT_VOICE_H__

#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "camera.h"
//#include "Gobang.h"
#include "lcd.h"
#include "music.h"
#include "paint.h"
#include "play_video.h"
#include "sensor.h"
#include "touch.h"
#include "Gobang.h"

int Voice_ClientRun(char *ip, char *port);
void TcpInit(const char *ipaddr, unsigned short port);
int function(void);

#endif