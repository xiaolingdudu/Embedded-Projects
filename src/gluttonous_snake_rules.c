#include "gluttonous_snake_rules.h"

extern char data_str[440/20][560/20];

int stop_snake=0;   //使用全局变量作为暂停操作锁死主函数蛇的运动

//链表尾插，改变蛇头的位置
void Creat_snake(Head_snake* head,int i,int j)
{
    Node* new=malloc(sizeof(Node));
    data_str[i][j]=head->direction; //新的头需要继承方向
    new->i=i;
    new->j=j;
    new->next=NULL;     //尾增
    if(head->first==NULL)   //没有结点的情况
    {
        head->first=head->last=new;
    }
    else
    {
        head->last->next=new;
        //将原本的尾部，也就是蛇头位置的值改为1，变为蛇身体
        data_str[head->last->i][head->last->j]=1;
        lcd_draw_bmp(20+head->last->j*20, 20+head->last->i*20, "1_tan.bmp");
        
        //改变贪吃蛇的头
        head->last=head->last->next; 
    }
    char buf[8];
    sprintf(buf,"%d_tan.bmp",data_str[head->last->i][head->last->j]);
    lcd_draw_bmp(20+head->last->j*20, 20+head->last->i*20, buf);
    head->num++;
}

/*头删，蛇移动看作头往前一步，尾步少去一节
在该游戏当中*/
void dele_snake(Head_snake* head)
{
    if(head->first==NULL)
        return ;
    data_str[head->first->i][head->first->j]=0; 
    //相应的将像素位置清除
    Clean_lcd_part(20+head->first->j*20, 20+head->first->i*20, 20, 20, 0xffffffff);
    if(head->first->next==NULL)
    {
        free(head->first);
        head->last=NULL;
        head->first=NULL;
    }
    else
    {
        Node* p=head->first;
        head->first=head->first->next;
        p->next=NULL;
        free(p);    //消除空间
        //printf("--delesnake--%d---\n",__LINE__);
    }
    head->num--;
}

//触摸操作贪吃蛇换方向的函数,线程函数
void *Move_snake(void* head)
{
    //设置为分离模式，将不考虑线程的返回值
    pthread_detach(pthread_self());
    int x=0,y=0;
    Head_snake* p=(Head_snake*)head;
    int temp;
    while(1)
    {
        //获取滑动方向,或者双击坐标
        temp=get_slipp(&x,&y);   //1--左滑，2--右滑，3--上滑，4--下滑
        //direction值为 2--右移，3--左移，4--上移，5--下移
        
        if(temp>0)  //表示为滑动操作
        {
            if(p->direction==2)
            {
                if(temp==3) p->direction=4;
                else if(temp==4)    p->direction=5;    
            }
            else if(p->direction==3)    //当前为向左移动
            {
                if(temp==3) p->direction=4;
                else if(temp==4)    p->direction=5;    
            }
            else if(p->direction==4)
            {
                if(temp==1) p->direction=3;
                else if(temp==2)    p->direction=2;    
            }
            else if(p->direction==5)
            {
                if(temp==1) p->direction=3;
                else if(temp==2)    p->direction=2;    
            }
        }
        else if(temp==0)    //点击操作
        {
            exchang_data(&x,&y);
            if(x>600 && y>400)
            {
                if(stop_snake==0)   //双击暂停
                {
                    stop_snake=1;
                    printf("__暂停中__%d__\n",__LINE__);
                    //Clean_lcd_part(600,400,200,80,0xffffffff);    //运行段错误
                    lcd_draw_bmp(600,400,"no_stop.bmp");
                }
                else                //双击继续
                {    
                    stop_snake=0;
                    lcd_draw_bmp(600,400,"stop.bmp");
                }
            }
        }
        
        //滑动之后延时0.02s防止误操作
        usleep(20000);       
    }
}