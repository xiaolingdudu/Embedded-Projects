#include "gluttonous_snake_rules.h"

extern char data_str[440/20][560/20];

extern int stop_snake;

/*改变蛇的状态
参数为要移动到下一个点的数组下标
返回值: 0--正常
        1--表示蛇咬到自己或者撞墙结束游戏*/
int Snake_status(int i,int j, Head_snake* head)
{
    //越界撞墙
    if(i<0 || i==22 || j<0 || j==28)
    {
        if(i<0)    lcd_draw_bmp(20+j*20,20+i*20,"death4.bmp");
        if(i==22)    lcd_draw_bmp(20+j*20,20+i*20,"death2.bmp");
        if(j<0)    lcd_draw_bmp(20+j*20,20+i*20,"death3.bmp");
        if(j==28)    lcd_draw_bmp(20+j*20,20+i*20,"death1.bmp");
        return 1;   //游戏结束
    }
    //表示为蛇身
    if(data_str[i][j]==1)
    {
        //尾巴移走
        dele_snake(head);
        if(data_str[i][j]==1)
        {
            Creat_snake(head,i,j);
            return 1;   //结束游戏
        }
        Creat_snake(head,i,j);
        return 0;   //不结束
    }
    else if(data_str[i][j]==6)  //表示为食物球
    {
        //增长，只尾增
        Creat_snake(head,i,j);
        rand_str_data();    //刷新新的食物
    }
    else if(data_str[i][j]==0)  //正常移动
    {
        dele_snake(head);
        Creat_snake(head,i,j);
    }
    return 0;   //游戏继续
}

int tanchishe()
{
    //初始化屏幕
    int fd = open("/dev/fb0", O_RDWR);
    if (fd == -1)
    {
        perror("open error");
    }
    Lcd_init(fd);
    
again: 
    Clean_lcd();
    //初始化游戏界面
    lcd_draw_gluttonous_snake();
    Head_snake *head=creat_HeadSnake();
    rand_str_data();

    pthread_t pid;
    int ret=pthread_create(&pid,NULL,Move_snake,(void*)head);
    if(ret != 0)
    {
        errno=ret;
        perror("pthread_create error");
        exit(1);
    }

    lcd_draw_bmp(600,400,"stop.bmp");
    int temp=0;     //循环退出标志位
    //开始循环移动
    while(1)
    {
        //移动时有三种情况：前一格为空白地点，蛇不增长
        //前一格为所吃食物球，蛇增长一格
        //前一格为蛇自己的身体，咬到自己会结束游戏
        //前一格为墙壁，会撞墙结束游戏
        int i=head->last->i, j=head->last->j;
        switch(head->direction)
        {
            case 2: temp = Snake_status(i,j+1,head);
                break;
            case 3: temp = Snake_status(i,j-1,head);
                break;
            case 4: temp = Snake_status(i-1,j,head);
                break;
            case 5: temp = Snake_status(i+1,j,head);
                break;
            default: printf("数据有误：%d\n",head->direction);
                break;
        }
        if(temp==1)
            break;
        while(stop_snake)  //暂停时死循环等待
        {
            //usleep(100000);printf("stop\n");
        }
        usleep(250000);
    }
    ret=pthread_cancel(pid);
    printf("ret=%d\n",ret);

    ////跟新排名
    //Update_ranking(head);

    //释放链表空间
    clearn_all_snake(head);
    
    //显示退出游戏按键和重新开始按钮
    lcd_draw_bmp(600,320,"again.bmp");
    lcd_draw_bmp(600,400,"over.bmp");

    //游戏结束，选择退出游戏还是重新开始
    while(1)
    {
        int x,y;
        get_xy(&x,&y);
        exchang_data(&x,&y);
        if(x>600&&y>320&&y<400)
            goto again; //重新开始
        else if(x>600&&y>400&&y<480)
        {
            //Clean_lcd();
            break;
        }
    }

    //Lcd_uninit();
    return ;
}