#ifndef __LOGIN_H__
#define __LOGIN_H_

#include <stdio.h>
//*************目的是为了提供一个明确的布尔类型*************
#include <stdbool.h>//数据类型 bool 以及两个预定义的常量 true 和 false

#define UNLOCK_WORD_LEN         6           /* 密码长度 */
#define UNLOCK_PASSWORD         "000000"    /* 解锁密码 */

//#define UNLOCK_WALLPAPER_PATH   "./data/unlock/unlock_wallpaper.bmp"  /* 壁纸 */

#define UNLOCK_WALLPAPER_PATH   "password.bmp"
#define UNLOCK_FEEDBACK_PATH    "click.bmp"  /* 按键反馈效果图 */

/* 文字属性----------------------------- */
#define UNLOCK_TEXT_COLOR       0x000000FF  /* 字体颜色——蓝色 */
#define UNLOCK_TEXT_START_X     400         /* 输入密码回显的起始x坐标 */ 
#define UNLOCK_TEXT_START_Y     53          /* 输入密码回显的起始y坐标 */ 

/* 反馈图片相对于按键的偏移(为了显示效果好一点才加的这个东西) */
#define UNLOCK_FB_DELTA_X       (-10)
#define UNLOCK_FB_DELTA_Y       (-10)
/* 按键-------------------------------- */
/* 键值------ */
typedef enum UNLOCK_KEY
{
    UNLOCK_0,
    UNLOCK_1,
    UNLOCK_2,
    UNLOCK_3,
    UNLOCK_4,
    UNLOCK_5,
    UNLOCK_6,
    UNLOCK_7,
    UNLOCK_8,
    UNLOCK_9,  
    UNLOCK_CONFIRM,
    UNLOCK_BS,
    UNLOCK_NONE     /* 无键值 */
}UNLOCK_KEY;

/* 按键坐标范围---*/
/* 确认键 */
#define UNLOCK_CONFIRM_X_START  90
#define UNLOCK_CONFIRM_X_END    170
#define UNLOCK_CONFIRM_Y_START  340
#define UNLOCK_CONFIRM_Y_END    420

/* 返回键 "BackSpace" */
#define UNLOCK_BS_X_START       300
#define UNLOCK_BS_X_END         380
#define UNLOCK_BS_Y_START       340
#define UNLOCK_BS_Y_END         420

/* 0 */
#define UNLOCK_0_X_START        195
#define UNLOCK_0_X_END          275
#define UNLOCK_0_Y_START        340
#define UNLOCK_0_Y_END          420

/* 1 */
#define UNLOCK_1_X_START        90
#define UNLOCK_1_X_END          170
#define UNLOCK_1_Y_START        240
#define UNLOCK_1_Y_END          320

/* 2 */
#define UNLOCK_2_X_START        195
#define UNLOCK_2_X_END          275
#define UNLOCK_2_Y_START        240
#define UNLOCK_2_Y_END          320

/* 3 */
#define UNLOCK_3_X_START        300
#define UNLOCK_3_X_END          380
#define UNLOCK_3_Y_START        240
#define UNLOCK_3_Y_END          320

/* 4 */
#define UNLOCK_4_X_START        90
#define UNLOCK_4_X_END          170
#define UNLOCK_4_Y_START        140
#define UNLOCK_4_Y_END          220

/* 5 */
#define UNLOCK_5_X_START        195
#define UNLOCK_5_X_END          275
#define UNLOCK_5_Y_START        140
#define UNLOCK_5_Y_END          220

/* 6 */
#define UNLOCK_6_X_START        300
#define UNLOCK_6_X_END          380
#define UNLOCK_6_Y_START        140
#define UNLOCK_6_Y_END          220

/* 7 */
#define UNLOCK_7_X_START        90
#define UNLOCK_7_X_END          170
#define UNLOCK_7_Y_START        45
#define UNLOCK_7_Y_END          125

/* 8 */
#define UNLOCK_8_X_START        195
#define UNLOCK_8_X_END          275
#define UNLOCK_8_Y_START        45
#define UNLOCK_8_Y_END          125

/* 9 */
#define UNLOCK_9_X_START        300
#define UNLOCK_9_X_END          380
#define UNLOCK_9_Y_START        45
#define UNLOCK_9_Y_END          125


//************滑动进度条******************
//参数：触摸点x的值
//返回值：成功返回1 失败返回0 
int show_hua(int t_x);

/**
 * @brief 获取按键键值（辅助函数）
 * 
 * @param x 输入坐标
 * @param y 输入坐标
 * @return UNLOCK_KEY 返回键值
 */
static UNLOCK_KEY unlock_GetKey(int x, int y);

//*************密码解锁界面*****************
// 返回值--ture or false 只有解锁完成才会返回ture
bool unlock_passward();

#endif
