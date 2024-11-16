#ifndef __CANERRA_H__
#define __CANERRA_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/videodev2.h>
#include <netinet/in.h>        //  TCP/IP协议所需头文件
#include <sys/socket.h>
#include "touch.h"
#include "lcd.h"
//monitor 主函数
void camera_Run();


#endif