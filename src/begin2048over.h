#ifndef _BEGIN2048OVER_H_
#define _BEGIN2048OVER_H_

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include "bmp.h"

/*统计为0区域有多少，做判断结束条件*/
int count_zero();

/*该函数用来在空白区域产生数据*/
void produce_data(int (*data)[4]);

/*初始化第一个数，并且不打印*/
void produce_data_0(int (*data)[4]);  

/*产生3：7比列的4和2随机数*/
int rand_2_4();

/*打印数组和游戏棋盘*/
void da_ying();

/*
    游戏结束判断函数
    返回值:     
        为1游戏胜利
        为2继续游戏
        为0游戏失败
*/
int juice_();

/*
    2048图片显示
*/
void daying_bmp();

#endif