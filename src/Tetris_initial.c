#include "Tetris_initial.h"
#include <stdlib.h>
#include <time.h>

char tetris_data[400/40][800/40]={0};   //确定游戏数组大小

//初始化俄罗斯方块的棋盘
void Tetris_init()
{
    draw_juxing(0,0,800,480,0xff36648b);   //内部颜色
    draw_juxing(0,60,800,10,0xFFEEB422);    //边界
    draw_juxing(0,470,800,10,0xFFEEB422);
    lcd_draw_bmp(300,0,"./continue.bmp");   //继续/开始游戏    
    lcd_draw_bmp(400,0,"./again.bmp");      //重新开始界面
    lcd_draw_bmp(500,0,"./break.bmp");      //退出游戏
}

//产生一个俄罗斯方块结点
testris_node* creat_node(int i,int j,int sign)
{
    testris_node* p1=(testris_node*)malloc(sizeof(testris_node));
    p1->i=i;
    p1->j=j;
    p1->sign=sign;
    p1->next=NULL;
    return p1;
}

//产生第一类俄罗斯方块链表，长条,输入为方块颜色属性
testris_head* creat_1_type(int sign)
{
    testris_head* head=(testris_head*)malloc(sizeof(testris_head));
    head->first=NULL;
    head->last=NULL;
    head->type=1;
    head->num=4;
    srand((unsigned)time(NULL));
    int flag=rand()%2;
    if(flag==0) //生成竖条
    {
        for(int i=0;i<4;i++)
        {
            testris_node* new=creat_node(5,i,sign);
            if(head->first==NULL)
                head->first=head->last=new;
            else
            {
                head->last->next=new;
                head->last=new;
            }
        }
    }
    else    //横条
    {
        for(int i=3;i<7;i++)
        {
            testris_node* new=creat_node(i,0,sign);
            if(head->first==NULL)
                head->first=head->last=new;
            else
            {
                head->last->next=new;
                head->last=new;
            }
        }
    }
    return head;
}

//产生第二类俄罗斯方块链表，正方形,输入为方块颜色属性
testris_head* creat_2_type(int sign)
{
    testris_head* head=(testris_head*)malloc(sizeof(testris_head));
    head->first=NULL;
    head->last=NULL;
    head->type=2;
    head->num=4;
    for(int i=0;i<4;i++)
    {
        testris_node* new=creat_node(i<2? 4:5, i==0? 0:i%2, sign);  //i==0? 0:i%2排除i为0的情况，i为0不可取余
        if(head->first==NULL)
            head->first=head->last=new;
        else
        {
            head->last->next=new;
            head->last=new;
        }
    }
    return head;
}

//产生第三类俄罗斯方块链表，楼梯,输入为方块颜色属性
testris_head* creat_3_type(int sign)
{
    testris_head* head=(testris_head*)malloc(sizeof(testris_head));
    head->first=NULL;
    head->last=NULL;
    head->type=3;
    head->num=4;
    srand((unsigned)time(NULL));
    int flag=rand()%2;
    if(flag==1)
    {
        testris_node* new=creat_node(4,0,sign);     //第一个方块
        head->first=head->last=new;
        new=creat_node(5,0,sign);       //第二个方块
        head->last->next=new;
        head->last=new;
        new=creat_node(5,1,sign);       //第三个方块
        head->last->next=new;
        head->last=new;
        new=creat_node(6,1,sign);
        head->last->next=new;           //第四个方块
        head->last=new;
    }
    else
    {
        testris_node* new=creat_node(5,0,sign);     //第一个方块
        head->first=head->last=new;
        new=creat_node(5,1,sign);       //第二个方块
        head->last->next=new;
        head->last=new;
        new=creat_node(4,1,sign);       //第三个方块
        head->last->next=new;
        head->last=new;
        new=creat_node(4,2,sign);
        head->last->next=new;           //第四个方块
        head->last=new;
    }
    return head;
}

//产生第四类俄罗斯方块链表，右侧拐杖,输入为方块颜色属性
testris_head* creat_4_type(int sign)
{
    testris_head* head=(testris_head*)malloc(sizeof(testris_head));
    head->first=NULL;
    head->last=NULL;
    head->type=4;
    head->num=4;
    testris_node* new=creat_node(4,0,sign);     //第一个方块
    head->first=head->last=new;
    int i=0;
    while(i<3)
    {
        new=creat_node(4+i,1,sign);
        i++;
        head->last->next=new;
        head->last=new;
    }
    return head;
}

//产生第五类俄罗斯方块链表，左侧拐杖,输入为方块颜色属性
testris_head* creat_5_type(int sign)
{
    testris_head* head=(testris_head*)malloc(sizeof(testris_head));
    head->first=NULL;
    head->last=NULL;
    head->type=5;
    head->num=4;
    testris_node* new=creat_node(6,0,sign);     //第一个方块
    head->first=head->last=new;
    int i=0;
    while(i<3)
    {
        new=creat_node(6-i,1,sign);
        i++;
        head->last->next=new;
        head->last=new;
    }
    return head;
}

//随机产生一个俄罗斯方块类型并随机它的颜色
testris_head* rand_tetris()
{
    srand((unsigned)time(NULL));
    int sign=rand()%5+1;      //12345分别对应红黄蓝紫青
    testris_head* head=NULL;
    switch (rand()%5)
    {
        case 0:head = creat_1_type(sign);
            break;
        case 1:head = creat_2_type(sign);
            break;
        case 2:head = creat_3_type(sign);
            break;
        case 3:head = creat_4_type(sign);
            break;
        case 4:head = creat_5_type(sign);
            break;
        default:
            break;
    }
    return head;
}

//俄罗斯方块清除函数，用于刷新当前俄罗斯类型方块所在区域
void tetris_clean(testris_head* head)
{
    testris_node* p=head->first;
    while(p)
    {
        draw_juxing(p->j*40, 70+p->i*40, 40, 40, 0xff36648b);
        p=p->next;
    }
}

//给俄罗斯方块上色--显示俄罗斯方块
void tetris_type_draw(testris_head* head)
{
    testris_node* p=head->first;
    unsigned int color=0;
    switch (head->first->sign)
    {
        case 1: color=0xffff0000;
            break;
        case 2: color=0xFFFFFB05;
            break;
        case 3: color=0xff0000ff;
            break;
        case 4: color=0xFFA105FF;
            break;
        case 5: color=0xFF05FFB9;
            break;
        default:
            break;
    }
    while(p)
    {
        draw_juxing(p->j*40, p->i*40+70, 40, 2, 0xffffffff);    //白色包边
        draw_juxing(p->j*40+2, p->i*40+70+2, 40-4, 40-4, color);
        draw_juxing(p->j*40, p->i*40+70+38, 40, 2, 0xffffffff);    //白色包边
        draw_juxing(p->j*40, p->i*40+70, 2, 40, 0xffffffff);    //白色包边
        draw_juxing(p->j*40+38, p->i*40+70, 2, 40, 0xffffffff);    //白色包边
        p=p->next;
    }
}

//销毁链表，释放空间
testris_head* clear_tetris_list(testris_head* head)
{
    if(head==NULL)
        return NULL;
    testris_node* p=head->first;
    while(head->first==NULL)
    {
        head->first=head->first->next;
        p->next=NULL;
        free(p);
        p=head->first;
    }
    free(head);
    if(head==NULL)
        printf("为空\n");
    return NULL;
}

//绘制整个数组中的方块
void tetris_shuzu_draw()
{
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<20;j++)
        {
            unsigned int color;
            switch (tetris_data[i][j])
            {
                case 1: color=0xffff0000;
                    break;
                case 2: color=0xFFFFFB05;
                    break;
                case 3: color=0xff0000ff;
                    break;
                case 4: color=0xFFA105FF;
                    break;
                case 5: color=0xFF05FFB9;
                    break;
                default:    draw_juxing(j*40, i*40+70, 40, 40, 0xff36648b);    //涂成背景色
                    break;
            }
            if(tetris_data[i][j]!=0)
            {
                draw_juxing(j*40, i*40+70, 40, 2, 0xffffffff);    //白色包边
                draw_juxing(j*40+2, i*40+70+2, 40-4, 40-4, color);
                draw_juxing(j*40, i*40+70+38, 40, 2, 0xffffffff);    //白色包边
                draw_juxing(j*40, i*40+70, 2, 40, 0xffffffff);    //白色包边
                draw_juxing(j*40+38, i*40+70, 2, 40, 0xffffffff);    //白色包边
            }
        }
    }
}



















