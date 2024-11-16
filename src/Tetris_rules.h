#ifndef __TETRIS_RULES_H__
#define __TETRIS_RULES_H__

#include "Tetris_initial.h"

//俄罗斯方块长条类型旋转
void tetris_type1_revolve(testris_head* head);

//俄罗斯方块楼梯类型旋转
void tetris_type3_revolve(testris_head* head);

//俄罗斯方块楼梯类型旋转
void tetris_type4_revolve(testris_head* head);

//俄罗斯方块左拐楼梯类型旋转
void tetris_type5_revolve(testris_head* head);

//旋转俄罗斯方块，参数：
//      head：为存储俄罗斯方块的链表
void Revolve_tetris(testris_head* head);

//左移俄罗斯方块，参数：
//      head：为存储俄罗斯方块的链表
void Left_tetris(testris_head* head);

//右移俄罗斯方块，参数：
//      head：为存储俄罗斯方块的链表
void Right_tetris(testris_head* head);

//俄罗斯方块正常下移，参数：
//      head：为存储俄罗斯方块的链表
//      返回值：1为可以并且已经移动了，0表示不可移动
int Down_tetris(testris_head* head);

//快速下降到底部
void tetris_speed_down(testris_head* head);

#endif