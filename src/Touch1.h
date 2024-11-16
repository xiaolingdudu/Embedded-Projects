#ifndef _TOUCH1_H_
#define _TOUCH1_H_

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h> 
#include <linux/input.h>
#include <math.h>


/*
    功能：
        获取手指离开触摸屏时的触摸点的坐标
    参数:
        (x, y)用来保存触摸点的坐标
*/
void get_xy(int* x, int* y);
/*
    换算1024*600的触摸屏为800*480的显示屏.
    主要服务于点击触摸事件，---get_xy---便于精准定位，
*/
void exchang_data(int *x,int *y);

/*
    屏幕滑动函数
    参数：(*x,*y)用于在滑动操作当中获取点击操作的坐标
    返回值: 1->左滑
            2->右滑
            3->上滑
            4->下滑
            0->不是滑动操作，为点击操作
*/
int get_slipp(int* x,int* y);

#endif