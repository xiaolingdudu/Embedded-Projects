#ifndef _GOBANG_H_
#define _GOBANG_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "menu.h"
#include "gobang_touch.h"

// const char *arr1[10];
// //定义全局变量，记录白棋的胜利次数 
// int white_win_count = 0;
// //定义全局变量，记录黑棋的胜利次数 
// int black_win_count = 0;
// //定义全局变量，用于记录游戏回合次数
// int round1 = 0;

//定义一个结构体类型，用于存储游戏相关的路径信息
typedef struct pathname
{
    char str1[10]; //封面路径
    char str2[10]; //棋盘右边的投降悔棋图片路径
    char str3[10]; //是否继续的图片路径
    char str4[10]; //白棋获胜
    char str5[10]; //黑棋获胜
    char str6[10]; //和棋
    char str7[10]; //计分板
    int count;
} pathname;

void GobangRun();



#endif // !_GOBANG_H_
