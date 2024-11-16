#include "play_video.h"


void InitVideo()
{
    Displaysql(800, 480, 0, 0, 0xFF9933);
    show_bmp("three.bmp", 30, 10,0);
    show_bmp("chicken.bmp", 30, 250,0);
    show_bmp("man.bmp", 400, 10,0);

    show_bmp("tip.bmp", 480, 300,0);
    show_bmp("draw4.bmp", 750, 400,0);
}

void * PlayVideo(void * argv)
{	
	pthread_detach(pthread_self());

	char video_buf[128] = {0};
    int video_i = (int)argv;
    while (1)
	{
		system("killall -9 mplayer");//保证别的madplay死掉
        sprintf(video_buf,"mplayer %d.mp4",video_i);
        printf("%s\n",video_buf);
        system(video_buf);
		sleep(1);
	}
}

void VideoRun()
{
    pthread_t VideoPlay;
    struct input_event ev;//
    int flag = 0,play = 0;//超时的flag
    int ev_x0,ev_y0,ev_x,ev_y;

    int ret = 0;

    while(1)
    {
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
                return ;//返回一个错误的方向
            }
            continue;
        }
        flag = 0;
        //将数据打印出来看看
        //printf("type:%d code:%d value:%d\n",ev.type,ev.code,ev.value);
        //获取坐标
        if(EV_ABS == ev.type)//接下来的数据就是坐标
        {
            if(REL_X == ev.code)//x轴
            {
                ev_x = ev.value;
            }
            else if(REL_Y == ev.code)//y轴
            {
                ev_y = ev.value;
            }
        }
        if(0x01 == ev.type && BTN_TOUCH == ev.code && 0x01 == ev.value)//手按下去的时候
        {
            ev_x0 = ev_x * 800 / 1200;
            ev_y0 = ev_y * 480 / 600;
        }
        else if(0x01 == ev.type && BTN_TOUCH == ev.code && 0x00 == ev.value)//手抬起来
        {
            printf("ev_x0:%d ev_y0:%d\n",ev_x0,ev_y0);
            //实现点击和方向判断
            if(ev_x0 == (ev_x * 800 / 1200) && ev_y0 == (ev_y * 480 / 600))//你的手没有动
            {
                printf("点击\n");
                if(play == 1)
                {
                    printf("视频结束\n");
                    pthread_cancel(VideoPlay);
                    system("killall -9 mplayer");
                    InitVideo();
                    play = 0;
                }
            }
            if ((ev_x0 > 10 && ev_x0 < 300) && (ev_y0 > 0 && ev_y0 < 200))
            {
                if(play == 0)
                {
                    printf("播放新宝岛\n");   
                    play = 1;
                    ret = pthread_create(&VideoPlay, NULL,PlayVideo, (void *)1);//创建一个线程去执行thread_function1函数，并且传递的参数为NULL
                    if (ret != 0)
                    {
                        printf("pthread1 create error:%d\n",ret );
                        sleep(1);
                    }
                }
            }
            if ((ev_x0 > 340 && ev_x0 < 620) && (ev_y0 > 0 && ev_y0 < 200))
            {
                if(play == 0)
                {
                    printf("播放鸡你太美\n");
                    play = 1;
                    ret = pthread_create(&VideoPlay, NULL,PlayVideo, (void *)3);//创建一个线程去执行thread_function1函数，并且传递的参数为NULL
                    if (ret != 0)
                    {
                        printf("pthread1 create error:%d\n",ret );
                        sleep(1);
                    }
                }
            }
            if ((ev_x0 > 10 && ev_x0 < 300) && (ev_y0 > 250 && ev_y0 < 470))
            {
                if(play == 0)
                {
                    printf("播放科目三\n");
                    play = 1;
                    ret = pthread_create(&VideoPlay, NULL,PlayVideo, (void *)2);//创建一个线程去执行thread_function1函数，并且传递的参数为NULL
                    if (ret != 0)
                    {
                        printf("pthread1 create error:%d\n",ret );
                        sleep(1);
                    }
                }
            }
            if ((ev_x0 > 600 && ev_x0 < 680) && (ev_y0 > 400 && ev_y0 < 470))
            {
                if(play == 0)
                {
                    printf("退出\n");
                    break;//可能会出问题
                }
            }
            
        }
    }
}