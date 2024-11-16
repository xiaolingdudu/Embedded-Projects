#ifndef _PROCESS2048_H_
#define _PROCESS2048_H_

#include"begin2048over.h"

/*位移操作通过获取--get_slipp--函数的返回值1(向左)、2(向右)、3(向上)、4(向下)实现*/
void process_(int sign);
/*向左移动*/
void move_a();
/*向右移动*/
void move_d();
/*向上移动*/
void move_w();
/*向下移动*/
void move_s();

#endif