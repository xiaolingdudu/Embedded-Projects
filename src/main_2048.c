////#include "Photoalbum.h"
//#include "process2048.h"
//#include "Touch1.h"
//
//extern int data[4][4];  //2048游戏的数组
//extern unsigned int *plcd;
//extern int fd;
//int you_2048()
//{
//    fd = open("/dev/fb0", O_RDWR);
//    if (fd == -1)
//    {
//        perror("open error");
//    }
//    Lcd_init(fd);
//    Clean_lcd(); // 先清屏
//    produce_data_0(data);
//    produce_data(data);
//    int sign;
//    while(1)
//    {
//        sign=get_slipp1();
//        int juice=juice_();
//        if(juice==0)
//        {
//            printf("游戏结束,你失败了\n");
//            lcd_draw_bmp(0,0,"gameover.bmp");
//            Lcd_uninit();
//            close(fd);
//            return 0;
//        }
//        else if(juice==1)
//        {
//            printf("游戏成功，你赢了\n");
//            lcd_draw_bmp(0,0,"gameover.bmp");
//            break;
//        }                                 //循环结束条件
//        process_(sign);
//        
//    }
//    int sum=0;
//    for(int i=0;i<4;i++)
//        for(int j=0;j<4;j++)
//            sum=sum+data[i][j];
//    printf("你的得分是%d\n",sum);
//    
//    //Lcd_uninit();
//    close(fd);
//
//    return ;
//}

#include "process2048.h"
#include "Touch1.h"

extern int data[4][4];  // 2048游戏的数组
extern unsigned int* plcd;
extern int fd;

int you_2048()
{
    while (1)  // 外层循环，用于重新开始游戏的功能
    {
        fd = open("/dev/fb0", O_RDWR);
        if (fd == -1)
        {
            perror("open error");
            return -1;
        }

        Lcd_init(fd);
        Clean_lcd(); // 先清屏
        produce_data_0(data);  // 初始化数据
        produce_data(data);    // 随机产生一个2或4

        int sign;

        while (1)  // 游戏主循环
        {
            sign = get_slipp1();  // 获取用户滑动方向或点击
            int juice = juice_();  // 判断游戏状态
            if (juice == 0)
            {
                printf("游戏结束,你失败了\n");
                lcd_draw_bmp(0, 0, "gameover.bmp");

                // 询问用户是否重新开始
                int choice = get_user_choice();
                if (choice == 1)
                {
                    // 重新开始游戏
                    break;  // 跳出当前游戏循环，重新开始外层循环
                }
                else
                {
                    // 退出游戏
                    //Lcd_uninit();
                    close(fd);
                    return;
                }
            }
            else if (juice == 1)
            {
                printf("游戏成功，你赢了\n");
                lcd_draw_bmp(0, 0, "gameover.bmp");

                // 询问用户是否重新开始
                int choice = get_user_choice();
                if (choice == 1)
                {
                    // 重新开始游戏
                    break;  // 跳出游戏循环，重新开始外层循环
                }
                else
                {
                    // 退出游戏
                    Lcd_uninit();
                    close(fd);
                    return 0;
                }
            }

            // 检查用户是否点击了重新开始或退出
            if (sign == 5)  // 右上角点击，重新开始
            {
                printf("重新开始游戏\n");
                break;  // 跳出当前游戏循环，重新开始外层循环
            }
            else if (sign == 6)  // 右下角点击，退出游戏
            {
                printf("退出游戏\n");
                //Lcd_uninit();
                close(fd);
                return ;
            }

            // 处理滑动操作
            process_(sign);

            // 计算当前得分（可以放在这里随时显示得分）
            int sum = 0;
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                    sum += data[i][j];
            printf("当前得分: %d\n", sum);
        }

        close(fd);  // 关闭文件描述符，准备重新开始或退出
    }

    return 0;
}

int get_user_choice()
{
    printf("请选择: 右上角点击重新开始，右下角点击退出\n");

    int choice;
    while (1)
    {
        choice = get_slipp1();  // 通过触摸屏获取用户输入

        if (choice == 5)
        {
            printf("你选择了重新开始\n");
            return 1;  // 返回重新开始信号
        }
        else if (choice == 6)
        {
            printf("你选择了退出\n");
            return 2;  // 返回退出信号
        }
        else
        {
            printf("无效选择，请点击右上角或右下角\n");
        }
    }
}
