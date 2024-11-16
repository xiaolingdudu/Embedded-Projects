#ifndef _BMP_H_
#define _BMP_H_

#include "lcds.h"

//BMP图片信息结构体
typedef struct bmp_info{
    int size;       //图片大小
    int width;      //图片宽度
    int height;     //图片高度
    short depth;    //图片的色深
    char* data;     //指向像素素组
}BMP;

/*
    获取BMP图片的信息
    参数：BMP图片的路径
*/
BMP get_bmp_info(char *bmpname);

/*
    功能：
        显示一张BMP图片
    参数：
        (x, y) 图片从那个位置开始进行显示 x.y为图片的最左上角的坐标
        bmpname: 需要进行显示的图片的路径
*/
void lcd_draw_bmp(int x,int y,char *bmpname);

/*
    自动播放电子相册
    更改其中的数组更改内容
*/
void atuo_photo();

/*
    功能: 
        进行jpeg图片的显示
    参数:
        需要进行显示的jpeg图片的路径
*/
int lcd_draw_jpeg(int x0, int y0, char* jpeg_name);

#endif