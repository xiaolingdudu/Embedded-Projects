/*
 * @Description: 
 * @Version: 1.0
 * @Autor: 李慧宁-Huining Li777
 * @Date: 2023-12-22 15:03:15
 * @LastEditors: 李慧宁-Huining Li777
 * @LastEditTime: 2023-12-28 16:56:04
 */
#ifndef __PICTURE_H__
#define __PICTURE_H_

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h> 
#include <linux/input.h>
#include <string.h>
#include "lcd.h"
#include "touch.h"
#include <pthread.h>
#include "music.h"
//*************画点的函数********************
void point(int x, int y, unsigned int color) ;
//*****************添加背景颜色-color************
void display_bgm(int color);
//××××××××××××××××××显示图片的函数×××××××
//1. 在相册中，不是lcd大小的图片需要居中
//2. 特定小的图片，不需要居中显示
//传入参数： 1. 图片名称 2. 坐标：xy 3. 是否需要居中显示
// choice ： 1--需要居中显示  0--不需要居中显示
void show_bmp(const char* filename, int x0,int y0,char choice);
//****************特效相关函数***************//
void Displaysql(int w, int h, int x0, int y0, unsigned int color);
void Displaycir(int radios, int x0, int y0,unsigned int color);
void DisplayNo(int width, int height, int x0, int y0, unsigned int *color);
void DisplayDelay(int width, unsigned int *color);
void DisplayCircle(int width, int height, int x0, int y0, unsigned int *color);
void DisplayBmpPicVideo(const char *pic, int state);

int ShowPicture(void);
#endif // !__PICTURE_H_


