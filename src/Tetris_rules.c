#include "Tetris_rules.h"

extern char tetris_data[400/40][800/40];

//俄罗斯方块长条类型旋转
void tetris_type1_revolve(testris_head* head)
{
    if(head->type!=1)
        return;      //类型有误
    int flag=1;     //用于判断是否能够旋转的标志位
    //判断当前长条是横向的还是纵向的
    if(head->first->i == head->first->next->i) //横向
    {
        int j0=(head->first->j + head->last->j)/2;
        int i0=head->first->i;
        for(int k=2;k>=-1;k--)
        {
            if(i0-k<0 || i0-k>9 || tetris_data[i0 - k][j0]!=0)
            {
                flag=0;
                break;
            }
        }
        if(flag==1) //能旋转
        {
            //printf("___%d___\n",__LINE__);
            //将当前位置方块清扫
            tetris_clean(head);
            testris_node* p=head->first;
            for(int k=2;k>=-1;k--)
            {
                p->i=i0 - k;
                p->j=j0;
                p=p->next;
            }
            tetris_type_draw(head);
        }
    }
    else if(head->first->j == head->first->next->j)
    {
        int i0=(head->first->i + head->last->i)/2+1;
        int j0=head->first->j;
        for(int k=1;k>=-2;k--)
        {
            if(j0-k<0 || j0-k>19 || tetris_data[i0][j0 - k]!=0)
            {
                flag=0;
                break;
            }
        }
        if(flag==1) //能旋转
        {
            //printf("___%d___\n",__LINE__);
            //将当前位置方块清扫
            tetris_clean(head);
            testris_node* p=head->first;
            for(int k=1;k>=-2;k--)
            {
                p->i=i0;
                p->j=j0 - k;
                p=p->next;
            }
            tetris_type_draw(head);
        }
    }
}

//俄罗斯方块楼梯类型旋转
void tetris_type3_revolve(testris_head* head)
{
    if(head->type!=3)
        return;      //类型有误
    int flag=1;     //用于判断是否能够旋转的标志位
    //判断当前楼梯是横向的还是纵向的
    if(head->first->i == head->first->next->i) //纵向
    {
        int i0=head->first->i;
        int j0=head->first->j;
        if(i0+1>9 || tetris_data[i0+1][j0+1]!=0)
            flag=0;
        if(flag==1)
        {
            //printf("___%d___\n",__LINE__);
            //将当前位置方块清扫
            tetris_clean(head);
            testris_node* p=head->first;
            p->i=i0-1;
            p->j=j0;
            p=p->next;
            p->i=i0;
            p->j=j0;
            p=p->next;
            p->i=i0;
            p->j=j0+1;
            p=p->next;
            p->i=i0+1;
            p->j=j0+1;
            tetris_type_draw(head);
        }
    }
    else if(head->first->j == head->first->next->j) //横向
    {
        int i0=head->first->next->i;
        int j0=head->first->next->j;
        if(i0-1<0 || j0+2>19 || tetris_data[i0-1][j0+1]!=0 ||tetris_data[i0-1][j0+2]!=0)
            flag=0;
        if(flag==1)
        {
            //printf("___%d___\n",__LINE__);
            //将当前位置方块清扫
            tetris_clean(head);
            testris_node* p=head->first;
            p->i=i0;
            p->j=j0;
            p=p->next;
            p->i=i0;
            p->j=j0+1;
            p=p->next;
            p->i=i0-1;
            p->j=j0+1;
            p=p->next;
            p->i=i0-1;
            p->j=j0+2;
            tetris_type_draw(head);
        }

    }

}


//俄罗斯方块右拐类型旋转
void tetris_type4_revolve(testris_head* head)
{
    if(head->type!=4)
        return;
    int flag=1;
    //printf("__fi=%d__fj=%d__li=%d__lj=%d__\n",head->first->i,head->first->j,head->last->i,head->last->j);
    //  O
    //OOO
    if(head->first->i + 2 == head->last->i && head->first->j + 1 == head->last->j)
    {
        int i0=head->first->i+1;
        int j0=head->first->j+1;
        if(tetris_data[i0][j0-1] !=0 || j0+1>19 || tetris_data[i0][j0+1]!=0 || tetris_data[i0-1][j0+1]!=0)
            flag=0;
        if(flag==1)
        {
            //将当前位置方块清扫
            tetris_clean(head);
            testris_node* p=head->first;
            p->i=i0-1;  p->j=j0+1;
            p=p->next;
            p->i=i0;    p->j=j0+1;
            p=p->next;
            p->i=i0;    p->j=j0;
            p=p->next;
            p->i=i0;    p->j=j0-1;
            tetris_type_draw(head);
        }
    }
    //O
    //O
    //OO
    else if(head->first->i + 1 == head->last->i && head->first->j == head->last->j + 2)
    {
        //printf("___%d___\n",__LINE__);
        int i0=head->first->i+1;
        int j0=head->first->j-1;
        if(tetris_data[i0-1][j0] !=0 || i0+1>9 || tetris_data[i0+1][j0]!=0 || tetris_data[i0+1][j0+1]!=0)
            flag=0;
        if(flag==1)
        {
            //将当前位置方块清扫
            tetris_clean(head);
            testris_node* p=head->first;
            p->i=i0+1;  p->j=j0+1;
            p=p->next;
            p->i=i0+1;  p->j=j0;
            p=p->next;
            p->i=i0;    p->j=j0;
            p=p->next;
            p->i=i0-1;  p->j=j0;
            tetris_type_draw(head);
        }
    }
    //OOO
    //O
    else if(head->first->i == head->last->i + 2 && head->first->j == head->last->j + 1)
    {
        //printf("___%d___\n",__LINE__);
        int i0=head->first->i-1;
        int j0=head->first->j-1;
        if(j0-1<0 || tetris_data[i0][j0-1]!=0 || tetris_data[i0+1][j0-1]!=0 ||tetris_data[i0][j0+1]!=0)
            flag=0;
        if(flag==1)
        {
            //将当前位置方块清扫
            tetris_clean(head);
            testris_node* p=head->first;
            p->i=i0+1;  p->j=j0-1;
            p=p->next;
            p->i=i0;    p->j=j0-1;
            p=p->next;
            p->i=i0;    p->j=j0;
            p=p->next;
            p->i=i0;    p->j=j0+1;
            tetris_type_draw(head);
        }
    }
    //OO
    // O
    // O
    else if(head->first->i - 1 == head->last->i && head->first->j + 2 == head->last->j)
    {
        //printf("___%d___\n",__LINE__);
        int i0=head->first->i-1;
        int j0=head->first->j+1;
        if(i0-1<0 || j0-1<0 || tetris_data[i0+1][j0]!=0 || tetris_data[i0-1][j0-1]!=0 ||tetris_data[i0-1][j0]!=0)
            flag=0;
        if(flag==1)
        {
            //将当前位置方块清扫
            tetris_clean(head);
            testris_node* p=head->first;
            p->i=i0-1;  p->j=j0-1;
            p=p->next;
            p->i=i0-1;  p->j=j0;
            p=p->next;
            p->i=i0;    p->j=j0;
            p=p->next;
            p->i=i0+1;  p->j=j0;
            tetris_type_draw(head);
        }
    }
}

//俄罗斯方块左拐楼梯类型旋转
void tetris_type5_revolve(testris_head* head)
{
    if(head->type!=5)
        return;
    int flag=1;
    //printf("__fi=%d__fj=%d__li=%d__lj=%d__\n",head->first->i,head->first->j,head->last->i,head->last->j);
    //O  
    //OOO
    if(head->first->i - 2 == head->last->i && head->first->j + 1 == head->last->j)
    {
        int i0=head->first->i-1;
        int j0=head->first->j+1;
        if(tetris_data[i0-1][j0-1] !=0 || j0+1>19 || tetris_data[i0][j0+1]!=0 || tetris_data[i0][j0-1]!=0)
            flag=0;
        if(flag==1)
        {
            //将当前位置方块清扫
            tetris_clean(head);
            testris_node* p=head->first;
            p->i=i0-1;  p->j=j0-1;
            p=p->next;
            p->i=i0;    p->j=j0-1;
            p=p->next;
            p->i=i0;    p->j=j0;
            p=p->next;
            p->i=i0;    p->j=j0+1;
            tetris_type_draw(head);
        }
    }
    //OO
    //O
    //O
    else if(head->first->i + 1 == head->last->i && head->first->j +2 == head->last->j)
    {
        //printf("___%d___\n",__LINE__);
        int i0=head->first->i+1;
        int j0=head->first->j+1;
        if(tetris_data[i0-1][j0] !=0 || i0+1>9 || tetris_data[i0+1][j0]!=0 || tetris_data[i0-1][j0+1]!=0)
            flag=0;
        if(flag==1)
        {
            //将当前位置方块清扫
            tetris_clean(head);
            testris_node* p=head->first;
            p->i=i0-1;  p->j=j0+1;
            p=p->next;
            p->i=i0-1;  p->j=j0;
            p=p->next;
            p->i=i0;    p->j=j0;
            p=p->next;
            p->i=i0+1;  p->j=j0;
            tetris_type_draw(head);
        }
    }
    //OOO
    //  O
    else if(head->first->i == head->last->i - 2 && head->first->j == head->last->j + 1)
    {
        int i0=head->first->i+1;
        int j0=head->first->j-1;
        if(j0-1<0 || tetris_data[i0][j0-1]!=0 || tetris_data[i0+1][j0+1]!=0 ||tetris_data[i0][j0+1]!=0)
            flag=0;
        if(flag==1)
        {
            //将当前位置方块清扫
            tetris_clean(head);
            testris_node* p=head->first;
            p->i=i0+1;  p->j=j0+1;
            p=p->next;
            p->i=i0;    p->j=j0+1;
            p=p->next;
            p->i=i0;    p->j=j0;
            p=p->next;
            p->i=i0;    p->j=j0-1;
            tetris_type_draw(head);
        }
    }
    // O
    // O
    //OO
    else if(head->first->i - 1 == head->last->i && head->first->j - 2 == head->last->j)
    {
        int i0=head->first->i-1;
        int j0=head->first->j-1;
        if(i0-1<0 || j0-1<0 || tetris_data[i0+1][j0]!=0 || tetris_data[i0+1][j0-1]!=0 ||tetris_data[i0-1][j0]!=0)
            flag=0;
        if(flag==1)
        {
            //将当前位置方块清扫
            tetris_clean(head);
            testris_node* p=head->first;
            p->i=i0+1;  p->j=j0-1;
            p=p->next;
            p->i=i0+1;  p->j=j0;
            p=p->next;
            p->i=i0;    p->j=j0;
            p=p->next;
            p->i=i0-1;  p->j=j0;
            tetris_type_draw(head);
        }
    }
}


//旋转俄罗斯方块，参数：
//      head：为存储俄罗斯方块的链表
void Revolve_tetris(testris_head* head)
{
    if(head==NULL)
        return;
    switch (head->type)
    {
    case 1: tetris_type1_revolve(head);     //长条
        break;
    case 3: tetris_type3_revolve(head);     //楼梯
        break;
    case 4: tetris_type4_revolve(head);     //右拐
        break;
    case 5: tetris_type5_revolve(head);     //左拐
        break;
    default:                //正方型和其他类型无需旋转
        break;
    }
}


//左移俄罗斯方块，参数：
//      head：为存储俄罗斯方块的链表
void Left_tetris(testris_head* head)
{
    if(head==NULL)
        return;
    testris_node* p=head->first;
    int flag=1;     //标志位判断移动后是否越界
    while(p)
    {
        //判断不越界且每一个格子左侧为空
        if(p->i + 1 >9 || tetris_data[p->i + 1][p->j] != 0)    
        {
            flag=0;
            break;
        }
        p=p->next;
    }
    if(flag==1)     //可以左移
    {
        //将当前位置方块清扫
        tetris_clean(head);
        p=head->first;
        while(p)
        {
            p->i += 1;
            p=p->next;
        }
        tetris_type_draw(head);
    }
}

//右移俄罗斯方块，参数：
//      head：为存储俄罗斯方块的链表
void Right_tetris(testris_head* head)
{
    if(head==NULL)
        return;
    testris_node* p=head->first;
    int flag=1;     //标志位判断移动后是否越界
    while(p)
    {
        //判断不越界且每一个格子右侧为空
        if(p->i - 1 < 0 || tetris_data[p->i - 1][p->j] != 0)    
        {
            flag=0;
            break;
        }
        p=p->next;
    }
    if(flag==1)     //可以右移
    {
        //将当前位置方块清扫
        tetris_clean(head);
        p=head->first;
        while(p)
        {
            p->i -= 1;
            p=p->next;
        }
        //显示移动后位置的俄罗斯方块
        tetris_type_draw(head);
    }
}

//俄罗斯方块正常下移，参数：
//      head：为存储俄罗斯方块的链表
//      返回值：1为可以并且已经移动了，0表示不可移动
int Down_tetris(testris_head* head)
{
    if(head==NULL)
        return 0;
    testris_node* p=head->first;
    int flag=1;     //标志位判断移动后是否越界
    while(p)
    {
        //判断不越界且每一个格子下侧为空
        if(p->j + 1 > 19 || tetris_data[p->i][p->j+1] != 0)    
        {
            flag=0;
            break;
        }
        p=p->next;
    }
    if(flag==1)     //可以下移
    {
        //将当前位置方块清扫
        tetris_clean(head);
        p=head->first;
        while(p)
        {
            p->j += 1;
            p=p->next;
        }
        //显示移动后位置的俄罗斯方块
        tetris_type_draw(head);
        return 1;
    }
    else    return 0;
}

//快速下降到底部
void tetris_speed_down(testris_head* head)
{
    if(head==NULL)
        return;
    int num=head->num;
    int num0=0;
    while(1)
    {
        testris_node* p=head->first;
        while(p)
        {
            if(p->j+1 < 20 && tetris_data[p->i][p->j+1]==0)
                num0++;
            p=p->next;
        }
        if(num0!=num)
            break;
        else    
        {
            num0=0;     //记录的数据清零
            //将所有方块往下移动一次
            tetris_clean(head);
            p=head->first;
            while(p)
            {
                p->j += 1 ;
                p=p->next;
            }
            tetris_type_draw(head);
        }
    }
}