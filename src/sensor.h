#ifndef _SENSOR_H_
#define _SENSOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include "picture.h"
#include <pthread.h>
#include <linux/input.h>
#include "lcd.h"
#include "touch.h"
void InitSensor(void);
int SensorRun(void);

#endif