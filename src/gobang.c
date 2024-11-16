#include "Gobang.h"

const char *arr1[10];
//定义全局变量，记录白棋的胜利次数 
int white_win_count = 0;
//定义全局变量，记录黑棋的胜利次数 
int black_win_count = 0;
//定义全局变量，用于记录游戏回合次数
int round1 = 0;

void game_continue(pathname path)
{
    char arr[ROW][COL] = {0};
    Arr_Init(arr);                    //初始化字符数组
    LCD_board_dispaly();              //LCD棋盘打印
    Show_pictures(496, 0, "wuziqi_7.bmp"); //打印计分板
    LCD_Dispaly_Black_Recording_Board(black_win_count);
    LCD_Dispaly_white_Recording_Board(white_win_count);
    Show_pictures(496, 70, "wuziqi_2.bmp"); //显示右边功能框
    Touch_function(arr, "wuziqi_4.bmp", "wuziqi_5.bmp","wuziqi_6.bmp"); //执行落子程序
}

//相关路径
void game(pathname path)
{
	//定义一个二维字符数组，用于存储棋盘上的字符
    char arr[ROW][COL] = {0};
    Arr_Init(arr);       //初始化字符数组
    LCD_board_dispaly(); //LCD棋盘打印
	//调用Show_pictures函数，显示计分板（初始状态）  
    Show_pictures(496, 0, "wuziqi_7.bmp");
	//循环显示右边功能框图片，从高度70开始逐渐向上移动  
    for (int i = 200; i >= 70; i--)
    {
        Show_pictures(496, i, "wuziqi_2.bmp"); //显示右边功能框
    }
	//执行落子程序
    Touch_function(arr, "wuziqi_4.bmp", "wuziqi_5.bmp","wuziqi_6.bmp");

loop1:
    //打印是否继续游戏的图片
    Show_pictures(0, 0, "wuziqi_3.bmp");
	//调用Continue_or_quit函数，判断是否继续游戏
    if (Continue_or_quit())
    {
		//如果继续游戏，则调用game_continue函数并检查游戏轮次或胜利次数，根据条件跳转到不同的标签位置 
        game_continue(path);
        if (round1 >= 5 || white_win_count >= 3 || black_win_count >= 3)
        {
            goto loop2;
        }
        goto loop1;
    }
loop2:
    //重置胜利次数变量
    white_win_count = 0;
    black_win_count = 0;
    close(lcd_fd); //关闭LCD_fd
}

void test(int *x, pathname path)
{
	//使用switch语句根据用户选择的游戏模式调用不同的函数
    switch (*x = Select_Mode("wuziqi_1.bmp"))
    {
    case ONE://如果选择模式为1，则调用game函数开始游戏 
        game(path);
        break;
		
    case ZERO://如果选择模式为0，则显示结束屏幕并退出游戏
        Show_End_Screen();
        printf("退出游戏\n");
        break;
    }
}


//*****五子棋主函数*********//
void GobangRun()
{
    int x;
    pathname path;
    do
    {
        test(&x, path);
    }
    while (x);
    return ;

}