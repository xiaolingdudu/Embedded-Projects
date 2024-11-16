#ifndef __GOBANG_TOUCH_H__
#define __GOBANG_TOUCH_H__

#include <stdio.h>
#include <linux/input.h> // 事件结构体的头文件
#include <stdlib.h>
#include "draw.h"
#include "judge.h"
#include "touch.h"
#include "lcd.h"
#include "menu.h"

extern int white_win_count;
extern int black_win_count;
extern int round1;

// 继续或退出的触摸判断
int Continue_or_quit(void);

// 游戏界面触摸
int Game_interface(void);

// 落子触摸
void Touch_function(char arr[][COL], const char *pathname4, const char *pathname5, const char *pathname6);

// 悔棋触摸
int Retract_chess(char arr[][COL], int x, int y, int a, int b, int c, int d, int *color, int *flag);

#endif