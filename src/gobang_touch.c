#include "gobang_touch.h"


//悔棋投降触摸
int Retract_chess(char arr[][COL], int x, int y, int a, int b, int c, int d, int *color, int *flag)
{

    //和棋
    if (x > 500 && y > 130 && y < 230)
    {
        printf("00000\n");
        return 2;
    }
    else if (x > 500 && y > 250 && y < 345)
    {
        if (*flag == 1)
        {
            printf("1111\n");
            Display_retract_false(a, b);
            arr[c][d] = ' ';
            *color = -1;
            (*flag)--;
            printf("flag:=%d", flag);
            return 0;
        }
    }
    else if (x > 500 && y > 350 && y < 424)
    {
        if (*color == 1) //白棋胜利
        {
            return 1;
        }
        else if (*color == -1)//黑棋胜利
        {
            return -1;
        }
    }
}

//触摸下子功能
void Touch_function(char arr[][COL], const char *pathname4, const char *pathname5, const char *pathname6) // 触摸功能
{
	////如果黑棋胜利次数和白棋胜利次数之和大于等于5，则重置胜利次数
    if (black_win_count + white_win_count >= 5)
    {
        black_win_count = 0;
        white_win_count = 0;
    }
    int count = 0;//初始化计数器
    int flag = 0;//初始化标志位
    int ret = 0;//初始化返回值
    FILE *abs_screen = fopen("/dev/input/event0", "r");
    if (abs_screen == NULL)//如果打开失败
        exit(0);//则退出程序

    //定义一个结构体input_event，用来获取事件的
    struct input_event ev;
    int x = 0, y = 0;//初始化触摸点的坐标
    int board_x = 0, board_y = 0;//初始化棋盘上的坐标
    int color = 1;//初始化棋子的颜色，这里假设为白棋（值为1）  
    //循环读取
    while (1)
    {
        int size = fread(&ev, sizeof(ev), 1, abs_screen);
        if (size == 0)//如果读取失败或没有事件可读
            continue; //则继续下一次循环，不执行下面的代码

        // 判断事件类型
        if (ev.type == EV_ABS) // 绝对事件
        {
            // 获取X轴的数值
            if (ev.code == ABS_X)
            {
                x = ev.value * 0.78;
            }
        }
        if (ev.type == EV_ABS) // 绝对事件
        {
            // 获取Y轴的数值
            if (ev.code == ABS_Y)
            {
                y = ev.value * 0.78;
            }
        }

        //判断压感（按下时ev.value为1，抬起时为0）
        if (ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0)
        {
			//判断触摸点是否在棋盘区域内
            if (x >= 36 && x <= 450 && y >= 24 && y <= 456)
            {
                if (x >= 36 && y > 24 && x <= 450 && y <= 456)
                {
					//对x坐标和y坐标进行修正，确保它们是棋盘格子的整数倍，以便更精确地定位棋子位置
                    if (x % 48 > 24)
                    {
                        x = x - x % 48 + 48;
                    }
                    else
                    {
                        x = x - x % 48;
                    }
                    if (y % 48 > 24)
                    {
                        y = y - y % 48 + 48;
                    }
                    else
                    {
                        y = y - y % 48;
                    }
                }
				//打印当前触摸点的坐标，用于调试或显示
                printf("x:%d,y:%d\n", x, y);
                if (color == 1 && arr[(y - 1) / 48][(x - 16) / 48] == ' ')
                {
					//记录下棋的坐标和当前的颜色（白棋）  
                    board_x = x;
                    board_y = y;
                    flag = 1;//设置标志位，表示正在下棋或即将下棋  
                    arr[(y - 1) / 48][(x - 16) / 48] = 'w';//在棋盘上放置白棋
                    LCD_play_chess(x + 16, y, &color, arr[(y - 1) / 48][(x - 16) / 48]);
                    count++; //下棋计数加一，用于记录已经下了多少步棋  
                }
                else if (color == -1 && arr[(y - 1) / 48][(x - 16) / 48] == ' ')
                {
                    board_x = x;
                    board_y = y;
                    flag = 1;
                    arr[(y - 1) / 48][(x - 16) / 48] = 'b';
                    LCD_play_chess(x + 16, y, &color, arr[(y - 1) / 48][(x - 16) / 48]);
                    count++;
                }

                if (arr[(y - 1) / 48][(x - 16) / 48] == 'w')
                {
					//调用函数判断白棋是否胜利
                    if (IsWin(arr, ROW, COL, (y - 1) / 48, (x - 16) / 48) == 1)
                    {
                        //如果白棋胜利，打印消息，增加胜利计数和回合数，并在LCD上显示胜利信息，等待2秒后显示胜利的图片，再等待3秒后判断是否结束游戏 
                        printf("white win!\n");
                        white_win_count++;
                        round1++;
                        LCD_Dispaly_white_Recording_Board(white_win_count);
                        sleep(2);
                        Show_pictures(0, 0, pathname4); // 白棋胜利
                        sleep(3);
                        int ret1 = judge_final_win(arr[(y - 1) / 48][(x - 16) / 48], white_win_count);
                        if (ret1 == 1)
                        {
                            goto loop1;
                        }
                        break;
                    }
                }
                else if (arr[(y - 1) / 48][(x - 16) / 48] == 'b')
                {
					 //调用函数判断黑棋是否胜利 
                    if (IsWin(arr, ROW, COL, (y - 1) / 48, (x - 16) / 48) == -1)
                    {
                        printf("black win!\n");
                        black_win_count++;
                        round1++;
                        LCD_Dispaly_Black_Recording_Board(black_win_count);
                        sleep(2);
                        Show_pictures(0, 0, pathname5); // 黑棋胜利
                        sleep(3);
                        int ret1 = judge_final_win(arr[(y - 1) / 48][(x - 16) / 48], black_win_count);
                        if (ret1 == -1)
                        {
                            goto loop2;
                        }
                        break;
                    }
                }
                //如果已经下完所有棋子，判断是否平局，并打印相关信息，增加回合数，然后退出循环
                if (count == ROW * COL)
                {
                    printf("平局\n");
                    round1++;
                    break;
                }
                printf("%c %d %d \n", arr[(y - 1) / 48][(x - 16) / 48], (y - 1) / 48, (x - 16) / 48);
            }

            if (x > 500)
                ret = Retract_chess(arr, x, y, board_x + 16, board_y, (board_y - 1) / 48, (board_x - 16) / 48, &color, &flag);
            //如果回退函数返回值为2，表示棋局和棋
			if (ret == 2)
            {
                printf("draw/tie in chess or other board games!\n");
                Show_pictures(0, 0, pathname6); //和棋
                sleep(2);
                break;//退出当前循环
            }
            else if (ret == 1 && count > 5)
            {

                printf("black win!\n");
                Show_pictures(0, 0, pathname5);//黑棋胜利
                sleep(2);
                break;//退出当前循环
            }
            else if (ret == -1 && count > 5)
            {
                printf("white win!\n");
                Show_pictures(0, 0, pathname4);//白棋胜利
                sleep(2);
                break;//退出当前循环
            }
		//如果白棋胜利次数达到3次或者黑棋胜利次数达到3次，直接退出循环
        loop1:
        loop2:
            if (white_win_count >= 3 || black_win_count >= 3)
            {
                break;//退出当前循环
            }
        }
    }
    
}

//游戏界面触摸
int Game_interface(void)
{
    //打开LCD屏文件
    // FILE *screen_file = fopen("/dev/input/event0", "r");
    // if (screen_file == NULL)
    // {
    //     printf("open screen_file error\n");
    //     return -1;
    // }
    struct input_event ev;//定义输入事件结构体
    int x = 0, y = 0;
    while (1)//无限循环，持续读取输入事件 
    {
        int flag;
        //我们想获取坐标值  那么就是从这个文件里面读取内容
        int r = read(touch_fd,&ev,sizeof(ev));
        if(sizeof(ev) != r)//读出问题出来了
        {
            usleep(10);
            flag++;
            if(10 <= flag)
            {
                //超时太多了  不行了
                perror("read ev error");
                return 0;//返回一个错误的方向
            }
            continue;
        }
        //判断事件类型
        if (ev.type == EV_ABS)
        {
            //获取X轴的数值
            if (ev.code == ABS_X)
            {
                x = ev.value * 0.78;
            }
        }
        if (ev.type == EV_ABS)
        {
            //获取Y轴的数值
            if (ev.code == ABS_Y)
            {
                y = ev.value * 0.78;
            }
        }
        if (ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0)//如果事件类型是按键事件，并且是触摸屏按下的事件（值为0） 
        {
            if (x >= 300 && x <= 450 && y >= 130 && y <= 200)
            {
                return ONE;//在第一个区域内触摸，返回ONE 
            }
            if (x >= 300 && x <= 450 && y >= 250 && y <= 320)
            {
                return TWO;//在第二个区域内触摸，返回TWO  
            }
            else if (x >= 300 && x <= 450 && y >= 370 && y <= 420)
            {
                return ZERO;//在第三个区域内触摸，返回ZERO
            }
        }
    }
}

int Continue_or_quit(void)
{
    // 打开LCD屏文件
    // FILE *screen_file = fopen("/dev/input/event0", "r");
    // if (screen_file == NULL)
    // {
    //     printf("open screen_file error\n");
    //     return -1;
    // }

    struct input_event ev;
    int x = 0, y = 0;
    while (1)
    {
        int flag;
        int r = read(touch_fd,&ev,sizeof(ev));
        if(sizeof(ev) != r)//读出问题出来了
        {
            usleep(10);
            flag++;
            if(10 <= flag)
            {
                //超时太多了  不行了
                perror("read ev error");
                return 0;//返回一个错误的方向
            }
            continue;
        }
        // 判断事件类型
        if (ev.type == EV_ABS)
        {
            // 获取X轴的数值
            if (ev.code == ABS_X)
            {
                x = ev.value * 0.78;
            }
        }
        if (ev.type == EV_ABS)
        {
            // 获取Y轴的数值
            if (ev.code == ABS_Y)
            {
                y = ev.value * 0.78;
            }
        }

        if (ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0)
        {
            if (x > 90 && x < 250)
            {
                return 1;
            }
            else if (x > 500 && x < 670)
            {
                return 0;
            }
        }
    }
}
