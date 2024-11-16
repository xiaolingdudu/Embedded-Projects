#ifndef __GLUTTONOUS_SNAKE_H__
#define __GLUTTONOUS_SNAKE_H__

#include "lcds.h"
#include "bmp.h"
#include <stdlib.h>
#include <time.h>

//初始化贪吃蛇的游戏界面
void lcd_draw_gluttonous_snake();

//随机产生贪吃蛇要吃的球
void rand_str_data();      //产生数组中的随机数

//贪吃蛇以双向链表的形式连接
//因此需要构造带头结点的链表结构
typedef struct Node{
    char i;     //数组行
    char j;     //数组列
    struct Node* next;  //指向前一个
}Node;

typedef struct Head_snake{
    Node* first;    //蛇尾
    Node* last;     //蛇头
    int direction;  //记录当前蛇移动方向,即确保蛇不能直接往回移动
    int num;        //蛇的长度
}Head_snake;

//生成贪吃蛇的头
Head_snake* creat_HeadSnake();

//清空链表空间
void clearn_all_snake(Head_snake* head);

//跟新贪吃蛇的历史排名
void Update_ranking(Head_snake* head);

#endif