#include "menu.h"

//选择模式函数
int Select_Mode(const char *pathname1)
{
    //打印游戏封面
    Show_pictures(0, 0, "wuziqi_1.bmp");

    //调用Game_interface函数，当点击玩家对战返回1，退出游戏返回0
    return Game_interface();
}