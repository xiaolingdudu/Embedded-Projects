#ifndef __PAINT_H__
#define __PAINT_H__

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <linux/input.h>
#include "touch.h"
#include "picture.h"
#include "lcd.h"

void InitCanve(void);
void PaintRun(void);


#endif
