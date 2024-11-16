#ifndef __TETRIS_INITIAL_H__
#define __TETRIS_INITIAL_H__

#include "lcds.h"
#include "bmp.h"
#include <unistd.h>
//初始化俄罗斯方块的棋盘
void Tetris_init();

typedef struct testris_node{
    char i;     //数组行列
    char j;     
    char sign;  //存储方块具体值，用于区分颜色
    struct testris_node* next;
}testris_node;      //俄罗斯方块数据类型

typedef struct testris_head{
    testris_node* first;
    testris_node* last;
    int type;   //用于区分类型
    int num;
}testris_head;  //头结点


//产生一个俄罗斯方块结点
testris_node* creat_node(int i,int j,int sign);

//产生第一类俄罗斯方块链表，长条,输入为方块颜色属性
testris_head* creat_1_type(int sign);

//产生第二类俄罗斯方块链表，正方形,输入为方块颜色属性
testris_head* creat_2_type(int sign);

//产生第二类俄罗斯方块链表，正方形,输入为方块颜色属性
testris_head* creat_3_type(int sign);

//产生第二类俄罗斯方块链表，正方形,输入为方块颜色属性
testris_head* creat_4_type(int sign);

//产生第二类俄罗斯方块链表，正方形,输入为方块颜色属性
testris_head* creat_5_type(int sign);

//随机产生一个俄罗斯方块类型并随机它的颜色
testris_head* rand_tetris();

//俄罗斯方块清除函数，用于刷新当前俄罗斯类型方块所在区域
void tetris_clean(testris_head* head);

//给俄罗斯方块上色--显示俄罗斯方块
void tetris_type_draw(testris_head* head);

//销毁链表，释放空间
testris_head* clear_tetris_list(testris_head* head);

//绘制整个数组中的方块
void tetris_shuzu_draw();

#endif