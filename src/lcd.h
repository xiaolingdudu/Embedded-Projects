#ifndef __LCD_H__
#define __LCD_H__
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h> 
#include <linux/input.h>
#include <string.h>

extern unsigned int* plcd ;//映射成功后是首地址
extern unsigned int* back_buffer;//一个后台buffer,用来改善频繁更改屏幕

//××××××××××××××××lcd 初始化××××××××××××××××××
void Lcd_Init();
//××××××××××××××××关闭lcd设备××××××××××××
void Lcd_close();

#endif // !__LCD_H__



