#ifndef _LCDS_H_
#define _LCDS_H_

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/mman.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
// lcd.h
extern unsigned int* plcd;  // 声明外部变量
// lcd.h
extern void display_word();

/*用白色作为清屏*/
void Clean_lcd();

/*清除正方形范围的空间
输入：x、y起始位置，w、h为宽高、color为清屏颜色
0xffffffff为白色
*/
void Clean_lcd_part(int x,int y,int w,int h,unsigned int color);

/*
    用write函数向屏幕中写入数据
    参数：文件标识符fd、颜色数据color
*/
void Write_lcd(int fd, int color);

/*使用三种颜色刷新显示屏*/
void shuaxing_write_lcd(int fd);

/*打开映射*/
void Lcd_init(int fd);

/*解除映射*/
void Lcd_uninit();

/*画点函数*/
void lcd_draw_point(int x,int y,unsigned int color);

/*画横线函数*/
void lcd_draw_line(int y,unsigned int color);

/*画竖线函数*/
void lcd_draw_line1(int x,unsigned int color);

/*画线段
  参数: x1、y1起始坐标
        x2、y2终点坐标
*/
void lcd_draw_segment(int x1,int y1,int x2,int y2);

/*画平面函数*/
void lcd_draw_plane(unsigned int color);

/*画矩形函数*/
void draw_juxing();

/*画圆函数*/
void draw_circle(int x, int y, int r, unsigned int color);

/*画爱心：爱心函数---> (x^2 + y^2 - 1)^3 - x^2 * y^3 = 0 */
void draw_aixing();

/*画太极函数*/
void draw_taiji();

/*
    功能:
        显示一个字符
    参数：
        (x0, y0): 在第y0行的第x0个像素点开始进行字符显示
        w:字符的宽   h: 字符的高
        color: 字符的颜色
        word: 需要进行显示的字符的像素点取模数组
*/
void display_word(int x0,int y0,int w,int h,unsigned int color,char *word);

/*
    功能：显示数字
    参数：(x0,y0):在第几行第几个像素点开始进行数字显示
        color：字符颜色
        data: 为需要显示的数字；len：为数字长度(不够会舍弃，有余留空白)
*/
void Lcd_Number(int x0, int y0, int color, int data, int len);

void Lcd_Number1(int x0, int y0, int color, int data, int len, int gap);
/*屏幕显示普通字符串函数,
    参数：(x0,y0)起始坐标，gap为两个字符的间距,建议选择16或12，值越小字符越紧凑
        color：字符颜色
        str：字符串首地址*/
void Lcd_string_size(int x0, int y0, int color, char* str, int gap);

/*
    使用display_word函数,打印游戏结束
    参数：color---字体颜色
*/
void useing_word(unsigned int color);

/*  打印楚河汉界
    参数：color---字体颜色
*/
void useing_word_chuhe(unsigned int color);

/*
打印棋盘所需汉字；
输入：1为红方、2为黑方、3为和棋
*/
void useing_word_player(int data);

#endif