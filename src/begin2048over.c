#include "begin2048over.h"

int data[4][4] = {0};
int count_zero() // 统计为0区域有多少，做判断结束条件
{
    int count = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (data[i][j] == 0)
                count++;
    return count;
}

int rand_2_4() // 产生3：7比列的4和2随机数
{
    srand((unsigned)time(NULL));
    return (rand() % 10) > 3 ? 2 : 4;
}

void da_ying() // 打印数组和游戏棋盘
{
    printf("——————————-——————————\n");
    for (int i = 0; i < 4; i++)
    {
        printf("|");
        for (int j = 0; j < 4; j++)
        {
            printf("%4d", data[i][j]);
            printf("|");
        }
        printf("\n");
        if (i < 3)
            printf("|————|————|————|————|\n");
        else
            printf("——————————-——————————\n");
    }
}

void produce_data(int (*data)[4]) // 该函数用来在空白区域产生数据
{
    srand((unsigned)time(NULL));
    unsigned int x = 0, y = 0, z = 0;
qushu:
    x = rand() % 16;
    y = x / 4;
    z = x % 4;
    if (*(*(data + y) + z) == 0)
    {
        *(*(data + y) + z) = rand_2_4();
        // da_ying();                  //调用打印函数，文字版
        daying_bmp(); // 调用图片显示函数，触摸版
        return;
    }
    else
        goto qushu;
}

void produce_data_0(int (*data)[4]) // 产生第一个数且不打印，因为2048初始化需产生两个数
{
    srand((unsigned)time(NULL));
    unsigned int x = 0, y = 0, z = 0;
qushu:
    x = rand() % 16;
    y = x / 4;
    z = x % 4;
    if (*(*(data + y) + z) == 0)
    {
        *(*(data + y) + z) = rand_2_4();
        return;
    }
    else
        goto qushu;
}

/************************************游戏结束条件******************************************/

int juice_()
{
    int count = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            if (data[i][j] == 2048)
                return 1; // 为1游戏胜利,可以改变2048的值降低难度
            if (data[i][j] == 0)
                count++;
        }
    if (count == 0)
    {
        int x = 0;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (data[i][j] == data[i][j + 1])
                    x++;
                if (data[j][i] == data[j + 1][i])
                    x++;
            }
        } // 判断是否有相邻相等的数值，如果有，继续游戏，没有则结束
        if (x == 0)
            return 0; // 为0游戏失败，结束游戏
    }
    else
        return 2; // 为2继续游戏
}

/*******************************显示图片***********************************/
void daying_bmp()
{
    char *str[] = {"0.bmp", "2.bmp", "4.bmp", "8.bmp", "16.bmp", "32.bmp", "64.bmp", "128.bmp", "256.bmp", "512.bmp", "1024.bmp", "2048.bmp"};
    
    int x0 = 0, y0 = 0;     //x0,y0为打印图片的起始点
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int n = data[i][j]; // n获取是str中的第几个元素
            if (n != 0)     //求出data[i][j]的对数值，对数值对应着str中的元素位置.
            {
                for (int n0 = 1;; n0++)
                {
                    n = n / 2;
                    if (n == 1)
                    {
                        n = n0;
                        break;
                    }
                }
            }
            lcd_draw_bmp(x0, y0, str[n]);
            x0 = x0 + 100;
            if (x0 == 400) // 改变起始值，显示下一张图片
            {
                x0 = 0;
                y0 = y0 + 100;
            }
        }
    }
}