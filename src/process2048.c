#include "process2048.h"

extern int data[4][4];
void process_(int sign)  //位移操作通过获取--get_slipp--函数的返回值1(向左)、2(向右)、3(向上)、4(向下)实现
{
    switch (sign)
    {
        case 1 :
            move_a();
            printf("左移成功\n");
            break;
        case 2 :
            move_d();
            printf("右移成功\n");
            break;
        case 3 :
            move_w();
            printf("上移成功\n");
            break;
        case 4 : 
            move_s();
            printf("下移成功\n");
            break;
        default:
            printf("移动不成功\n");
            break;
    }
    return;
}
void move_a()   //判断左滑动
{
    int x=0;
    int data1[4][4]={0};
    int y=0,z=0;
    for(int i=0;i<4;i++)
    {
        for(int j=0,j1;j<3;j++)
        {
            j1=j+1;
    xun:    if(data[i][j1]==0&&j1<3) 
            {
                j1++;
                goto xun;
            }
            if(data[i][j]==data[i][j1]&&data[i][j]!=0)   //寻找能相加的两个数
            {
                data[i][j]=data[i][j]+data[i][j1];
                data[i][j1]=0;
                y++;                                    //数合并则必须要跟新游戏状态，搭配 --->line 54
            }
        }

        int count=0;
        for(int j=0;j<4;j++)
        {
            if(data[i][j]!=0) data1[i][count++]=data[i][j];
        }

        for(int j=0;j<4;j++)
        {
            if(data[i][j]!=data1[i][j])   //通过比较两个数组的元素是否相等，判断数组是否完全相等
                y++;                      //不完全相等则能移动，搭配 --->line 54
            data[i][j]=data1[i][j];
        }
    }
    if(y!=0)
    {
        produce_data(data);
        return;
    }   //如果y==4，数组不跟新数据，证明向a方向无法移动
    else return;
}

void move_d()   //判断右滑动
{
    int x=0;
    int data1[4][4]={0};
    int y=0,z=0;
    for(int i=0;i<4;i++)
    {
        for(int j=3,j1;j>0;j--)
        {
            j1=j-1;
    xun:    if(data[i][j1]==0&&j1>0) 
            {
                j1--;
                goto xun;
            }
            if(data[i][j]==data[i][j1]&&data[i][j]!=0)
            {
                data[i][j]=data[i][j]+data[i][j1];
                data[i][j1]=0;
                y++;
            }
        }
        int count=3;
        for(int j=3;j>=0;j--)
        {
            if(data[i][j]!=0) data1[i][count--]=data[i][j];
        }
        for(int j=3;j>=0;j--)
        {
            if(data[i][j]!=data1[i][j])
                y++;
            data[i][j]=data1[i][j];
        }
    }
    if(y!=0)
        produce_data(data);   //如果y==4，数组不跟新数据，证明向a方向无法移动
}

void move_w()   //判断右滑动
{
    int x=0;
    int data1[4][4]={0};
    int y=0,z=0;
    for(int i=0;i<4;i++)
    {
        for(int j=0,j1;j<3;j++)
        {
            j1=j+1;
    xun:    if(data[j1][i]==0&&j1<3) 
            {
                j1++;
                goto xun;
            }
            if(data[j][i]==data[j1][i]&&data[j][i]!=0)
            {
                data[j][i]=data[j][i]+data[j1][i];
                data[j1][i]=0;
                y++;
            }
        }
        int count=0;
        for(int j=0;j<4;j++)
        {
            if(data[j][i]!=0) data1[count++][i]=data[j][i];
        }
        for(int j=0;j<4;j++)
        {
            if(data[j][i]!=data1[j][i])
                y++;
            data[j][i]=data1[j][i];
        }
    }
    if(y!=0)
        produce_data(data);   //如果y==4，数组不跟新数据，证明向a方向无法移动
}
void move_s()   //判断右滑动
{
    int x=0;
    int data1[4][4]={0};
    int y=0,z=0;
    for(int i=0;i<4;i++)
    {
        for(int j=3,j1;j>0;j--)
        {
            j1=j-1;
    xun:    if(data[j1][i]==0&&j1>0) 
            {
                j1--;
                goto xun;
            }
            if(data[j][i]==data[j1][i]&&data[j][i]!=0)
            {
                data[j][i]=data[j][i]+data[j1][i];
                data[j1][i]=0;
                y++;
            }
        }
        int count=3;
        for(int j=3;j>=0;j--)
        {
            if(data[j][i]!=0) data1[count--][i]=data[j][i];
        }
        for(int j=3;j>=0;j--)
        {
            if(data[j][i]!=data1[j][i])
                y++;
            data[j][i]=data1[j][i];
        }
    }
    if(y!=0)
        produce_data(data);   //如果y==4，数组不跟新数据，证明向a方向无法移动
}