#ifndef __GLUTTONOUS_SNAKE_RULES_H__
#define __GLUTTONOUS_SNAKE_RULES_H__

#include "gluttonous_snake_initial.h"
#include "Touch1.h"
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

//链表尾插，改变蛇头的位置
void Creat_snake(Head_snake* head,int i,int j);

/*头删，蛇移动看作头往前一步，尾步少去一节
在该游戏当中*/
void dele_snake(Head_snake* head);

//触摸操作贪吃蛇换方向的函数,线程函数
void *Move_snake(void* head);


#endif // !__GLUTTONOUS_SNAKE_RULES_H__