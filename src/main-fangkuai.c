#include "Tetris_initial.h"
#include "Tetris_rules.h"
#include <pthread.h>
#include "Touch1.h"

enum Event_tetris{event_0,event_again,event_break,event_Normal_End};

extern char tetris_data[400/40][800/40];
testris_head* head=NULL;
int tetris_start=0;     //判断游戏是否开始标志位
int score=0;    //得分
enum Event_tetris tetris_event=event_0; //点击进程的事件标志位，用于区分退出和重新开始

pthread_t pth_id;   //自由下降线程ID

//判断是否有一以上行满了，清除满的区域，并将剩余区域移动至末尾
//返回值为得分，清除一行+10分
int judge_get_score();

//俄罗斯方块自由下降的线程函数
void* tetris_free_fall()
{
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);  //设置线程可以取消
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    //int* process_Out=(int*)process_out;
    int move_flag=1;    //移动标志位
    while(1)
    {
        if(tetris_start!=0) //表示游戏开始
        {
            if(head==NULL)  //表示还没有生成俄罗斯方块类型
            {
                //printf("链表空间为空，重新生成数据__%d__\n",__LINE__);
                head=rand_tetris();  //随机产生一种俄罗斯方块
            }
            else
                move_flag = Down_tetris(head);  //自由下降
            if(move_flag==0)    //已经不可下降了
            {
                int flag_full=0;    //判断数组是否满了的标志位
                //1.将数值写入数组
                testris_node* p=head->first;
                while (p)
                {
                    if(tetris_data[p->i][p->j]!=0)  //说明剩余位置已经不足以放置新的俄罗斯方块了
                        flag_full=1;    
                    tetris_data[p->i][p->j]=p->sign;
                    p=p->next;
                }
                if(flag_full)
                {
                    tetris_type_draw(head);
                    tetris_start=0; //游戏结束
                    tetris_event = event_Normal_End;    //游戏正常结束事件
                    break;
                }
                //2.消除链表空间
                head=clear_tetris_list(head);
                //3.将标志位重新置为1
                move_flag=1;
                score += judge_get_score();
                //printf("score = %d\n",score);
                draw_juxing(0,0,80,16,0xff36648b);      //显示当前得分
                Lcd_Number1(0,0,0xff000000,score,5,12);
            }
            usleep(500000);
        }
        ////else表示游戏未开始或者游戏暂停

        //if(*process_Out)      //使用传参让进程结束
        //    pthread_exit(NULL);
    }
    head=clear_tetris_list(head);
    lcd_draw_bmp(300,0,"./continue.bmp");
    lcd_draw_bmp(400,0,"./again.bmp");
    lcd_draw_bmp(500,0,"./break.bmp");
    draw_juxing(600,0,200,60,0xff36648b);
}

//获取点击事件的进程
void *get_xy_touch_event()
{
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);  //设置线程可以取消
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    int x,y;
    while(1)
    {
        get_xy(&x,&y);
        exchang_data(&x,&y);    //获取点击坐标
        if(tetris_start==0)     //暂停
        {
            if(x>300 &&x<360 && y<60)   //点击开始/继续游戏
            {
                lcd_draw_bmp(300,0,"./pause.bmp");
                lcd_draw_bmp(400,0,"./revolve.bmp");    //旋转方块
                lcd_draw_bmp(500,0,"./left.bmp");       //左移
                lcd_draw_bmp(600,0,"./right.bmp");      //右移
                lcd_draw_bmp(700,0,"./speed_down.bmp"); //快速下降
                tetris_start=1;
            }
            if(x>400 && x<460&&y<60)    //重新开始
            {
                Tetris_init();  //用初始化将内部的区块刷新
                //显示按键
                lcd_draw_bmp(300,0,"./pause.bmp");
                lcd_draw_bmp(400,0,"./revolve.bmp");    //旋转方块
                lcd_draw_bmp(500,0,"./left.bmp");       //左移
                lcd_draw_bmp(600,0,"./right.bmp");      //右移
                lcd_draw_bmp(700,0,"./speed_down.bmp"); //快速下降
                //回收开启的进程
                head=clear_tetris_list(head);   //2.消除链表空间
                pthread_cancel(pth_id);
                pthread_join(pth_id,NULL);
                printf("tetris_free_fall回收了\n");
                tetris_start=1;
                for(int i=0;i<10;i++)
                    for(int j=0;j<20;j++)
                        tetris_data[i][j]=0;
                tetris_event=event_again; //事件1，表示为需要重新创建一个自由下降的线程
            }
            if(x>500 && x<560 && y<60)
            {
                tetris_event=event_break;     //事件2，表示为需要退出游戏
                break;
            }
        }
        else if(tetris_start==1)     //游戏开始的情况
        {
            if(x>300 &&x<360 && y<60)   //点击暂停
            {
                //暂停后跟换操作界面
                lcd_draw_bmp(300,0,"./continue.bmp");
                lcd_draw_bmp(400,0,"./again.bmp");
                lcd_draw_bmp(500,0,"./break.bmp");
                draw_juxing(600,0,60,60,0xff36648b);
                draw_juxing(700,0,60,60,0xff36648b);
                tetris_start=0;
            }
            else if(x>400 &&x<460 && y<60)       //旋转
                Revolve_tetris(head);
            else if(x>500 &&x<560 && y<60)       //左移动
                Left_tetris(head);
            else if(x>600 &&x<660 && y<60)       //右移
                Right_tetris(head);
            else if(x>700 &&x<760 && y<60)       //快速下降
                tetris_speed_down(head);       
        }
    }
}

int fangkuai()
{
    int fd=open("/dev/fb0",O_RDWR);
    if(fd==-1)
    {
        perror("open fail");
        return 0;
    }
    Lcd_init(fd);
    Clean_lcd();

    //初始化游戏界面
    Tetris_init();

    score=0;    //得分
    int ret=pthread_create(&pth_id,NULL,tetris_free_fall,NULL);
    if(ret!=0)
    {
        perror("pthread_create error");
        exit(1);
    }

    pthread_t pth_id_touch;     //点击事件的线程ID
    //创建线程
    ret=pthread_create(&pth_id_touch,NULL,get_xy_touch_event,NULL);
    if(ret!=0)
    {
        perror("pthread_create error");
        exit(1);
    }
    
    while(tetris_event!=event_break)
    {
        if(tetris_event==event_again)   //重新开始事件
        {
            score=0;    //得分
            ret=pthread_create(&pth_id,NULL,tetris_free_fall,NULL);
            if(ret!=0)
            {
                perror("pthread_create error");
                exit(1);
            }
            tetris_event=event_0;
        }
        else if(tetris_event==event_Normal_End) //游戏正常结束事件
        {
            //为了确保游戏正常结束时，点击线程不可在阻塞点击操作位置，因此，直接将线程回收，重新开启线程。
            pthread_cancel(pth_id_touch);
            pthread_join(pth_id_touch,NULL);
            printf("touch回收了\n");
            //创建线程
            ret=pthread_create(&pth_id_touch,NULL,get_xy_touch_event,NULL);
            if(ret!=0)
            {
                perror("pthread_create error");
                exit(1);
            }
            tetris_event=event_0;      //恢复事件为一般事件
        }
    }

    for(int i=0;i<10;i++)  
    {
        for(int j=0;j<20;j++)
            printf("%d ",tetris_data[i][j]);
        printf("\n");
    }    
    //回收开启的进程
    pthread_cancel(pth_id);
    pthread_join(pth_id,NULL);
    pthread_cancel(pth_id_touch);
    pthread_join(pth_id_touch,NULL);
    printf("----退出了\n");

    //Lcd_uninit();
    close(fd);
    return;
}

//判断是否有一以上行满了，清除满的区域，并将剩余区域移动至末尾
//返回值为得分，清除一行+10分
int judge_get_score()
{
    int score=0;
    int flag=1;
    
    for(int j=0;j<20;j++)
    {
        for(int i=0;i<10;i++)
        {
            if(tetris_data[i][j]==0)
            {
                flag=0;
                break;
            }
        }
        if(flag==1) //需要清除
        {
            score+=10;
            for(int i=0;i<10;i++)
            {
                for(int j0=j;j0>0;j0--)
                {
                    tetris_data[i][j0]=tetris_data[i][j0-1];
                }
                tetris_data[i][0]=0;
            }
            tetris_shuzu_draw();    //跟新数组当中的值
        }
        flag=1;     //重新置为1，进入下一层判断
    }
    
    return score;
}