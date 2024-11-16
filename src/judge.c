#include "judge.h"
//数组初始化
void Arr_Init(char arr[ROW][COL])
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			arr[i][j] = ' ';//将当前位置设置为空格字符
		}
	}
}

//判断胜负
int IsWin(char board[ROW][COL], int row, int col, int a, int b)
{
	int zcount = 0;//记录白棋连续的棋子数量
	int fcount = 0;//记录黑棋连续的棋子数量
	
	//判断横向是否连续,我们判断以落子点为中心的左边4个和右边四个加上自己落子位置，总共九个位置
	for (int i = -4; i <= 4; i++)
	{
		//检查列位置是否在有效范围内  
		if (b + i >= 0 && b + i < col)
		{
			//如果当前位置是玩家w的棋子，增加连续数量，重置玩家b的连续数量 
			if (board[a][b + i] == 'w')
			{
				zcount++;
				fcount = 0;
			}
			//如果当前位置是玩家b的棋子，增加连续数量，重置玩家w的连续数量
			else if (board[a][b + i] == 'b')
			{
				fcount++;
				zcount = 0;
			}
			else //既不等于1，又不是等于0，说明该位置为空空格，两者都清零
			{
				fcount = 0;
				zcount = 0;
				continue;
			}
		}
		//如果玩家w连续五个棋子，返回1表示白方赢得游戏
		if (zcount == 5)
		{
			return 1;
		}
		//如果玩家b连续五个棋子，返回-1表示黑方赢得游戏 
		if (fcount == 5)
		{
			return -1;
		}
	}

	//判断垂直方向是否连续
	for (int i = -4; i <= 4; i++)
	{
		if (a + i >= 0 && a + i < col)
		{
			if (board[a + i][b] == 'w')
			{
				zcount++;
				fcount = 0;
			}
			else if (board[a + i][b] == 'b')
			{
				fcount++;
				zcount = 0;
			}
			else
			{
				fcount = 0;
				zcount = 0;
				continue;
			}
		}
		if (zcount == 5)
		{
			return 1;
		}
		if (fcount == 5)
		{
			return -1;
		}
	}

	//从左上往右下斜方向判断是否连续
	for (int i = -4; i <= 4; i++)
	{
		//检查行和列位置是否都在有效范围内  
		if (a + i >= 0 && a + i < col && b + i >= 0 && b + i < col)
		{
			if (board[a + i][b + i] == 'w')
			{
				zcount++;
				fcount = 0;
			}
			else if (board[a + i][b + i] == 'b')
			{
				zcount = 0;
				fcount++;
			}
			else
			{
				zcount = 0;
				fcount = 0;
				continue;
			}
		}
		if (zcount == 5)
		{
			return 1;
		}
		if (fcount == 5)
		{
			return -1;
		}
	}

	//从右上往左下斜方向判断是否连续
	for (int i = -4; i <= 4; i++)
	{
		//检查行和列位置是否都在有效范围内
		if (a + i >= 0 && a + i < col && b - i >= 0 && b - i < col)
		{
			if (board[a + i][b - i] == 'w')
			{
				zcount++;
				fcount = 0;
			}
			else if (board[a + i][b - i] == 'b')
			{
				zcount = 0;
				fcount++;
			}
			else
			{
				zcount = 0;
				fcount = 0;
				continue;
			}
		}
		if (zcount == 5)
		{
			return 1;
		}
		if (fcount == 5)
		{
			return -1;
		}
	}
}

//判断最终的胜利
int judge_final_win(char a,int b)
{
	//如果玩家是w且得分大于等于3，则返回1表示白方赢得游戏  
	if(a=='w'&&b>=3)
	{
		return 1;
	}
	//如果玩家是b且得分大于等于3，则返回-1表示黑方赢得游戏  
	else if(a=='b'&&b>=3)
	{
		return -1;
	}
	//其他情况返回0表示游戏继续进行或没有赢家 
	return 0;
}