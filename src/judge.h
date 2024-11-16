#ifndef __JUDGE_H__
#define __JUDGE_H__

#define ROW 10
#define COL 10

void Arr_Init(char arr[ROW][COL]);      //对记录数据的数组进行初始化
int IsWin(char board[ROW][COL], int row, int col, int a, int b); //判断胜负
int judge_final_win(char a,int b);//判断最终胜利
#endif