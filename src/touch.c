#include "touch.h"



//*********触摸事件初始化*********
int touch_fd;//屏幕设备
void touch_evntInit(void)
{
    // int fd = open(TOUCH_PATH,O_RDONLY);//只读打开
    // if(fd<0)
    // {
    //     perror("open fail");
    //     return 0;
    // }
    touch_fd=open(TOUCH_PATH,O_RDONLY);
    if(touch_fd<0)
    {
        perror("open touch_fd fail");
        return ;
    }
}

//************获取触摸方向*********
//返回值：触摸方向，具体定义在宏定义处
int Get_TouchDirection(void)
{
    struct input_event ev;
    int x_start=-1,y_start=-1;	//坐标的初值
    int x_end = -1,y_end = -1;    //坐标终点
    int flag=0;
    while(1)
    {
        //2.不停地从文件中读取数据
        int r=read(touch_fd, &ev, sizeof(struct input_event));
        if(sizeof(ev)!=r)//等待响应--如果当时没反应，可以容忍，进行等待
        {
            usleep(10);
            flag++;
            if(flag>=10)
            {
                perror("read ev error");
                break;
            }
            continue;
        }
        flag=0;
        //3.解析数据
        if(ev.type == EV_ABS)   //触摸事件 
        {
            if(ev.code == ABS_X)
            {
                if (-1 == x_start)        //x轴
                {
                    x_start = ev.value;	//起点
                }
                x_end = ev.value;      //终点
                
            }
            if(ev.code == ABS_Y)		//y轴
            {
                if (-1 == y_start)
                {
                    y_start = ev.value;
                }
                y_end = ev.value;      //终点
                
            }
            if(ev.code ==ABS_PRESSURE && ev.value == 0)
            {
                if(x_start != -1 && y_start != -1)
                {
                    break;
                }
            }
        }
        
        if(ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0)   //当检测到触摸屏被释放（即触摸结束）时，退出当前的触摸检测循环。
        {
            if(x_start != -1 && y_start != -1)
            {
                return Touch_Click;
            }
        }

        if (abs(x_end - x_start) > (y_end - y_start))
        {
            if (x_end - x_start > 0)
            {
                return Touch_Right;
            }
            else
            {
                return Touch_Left;
            }
            
        }
        if (abs(x_end - x_start) < (y_end - y_start))
        {
            if (y_end - y_start > 0)
            {
                return Touch_Down;
            }
            else
            {
                return Touch_Up;
            }
            
        }
    }
    
    //打印坐标
    printf("%d , %d\n", x_end, y_start);   
}

//**************获取触摸位置--可以识别长按****
//*****************获取触摸点位置*********
// 返回值是上面的一个TouchPOint的结构体，
//xy为触摸点的位置，原始坐标--未处理lcd与触摸屏大小不一样的问题
//is_long_press为是否长按，0--未长按  1--长按
TouchPoint Get_TouchPosition()
{
    TouchPoint point = {-1, -1, 0};  // 初始化 x, y 和 is_long_press
    struct input_event ev;
    int start_time = 0;  // 用于记录开始触摸的时间
    int current_time = 0;  // 用于记录当前时间
    const int LONG_PRESS_THRESHOLD = 2000;  // 定义长按的时间阈值（假设是2秒）
    int flag=0;
    while(1) //有疑问
    {
        int r = read(touch_fd, &ev, sizeof(struct input_event));
        if(sizeof(ev) != r) {
            usleep(10);
            flag++;
            if(flag >= 10) {
                perror("read ev error");
                break;
            }
            continue;
        }
        flag = 0;
        if(ev.type == EV_ABS) 
        {   usleep(1000);
            if(ev.code == ABS_X) 
            {
                point.x = ev.value;
            }
            if(ev.code == ABS_Y) 
            {
                point.y = ev.value;
            }
        }
        if(ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0) 
        {
            point.is_long_press = 0;  // 重置长按标志位
            break;
        }

        if(point.x !=-1&& point.y !=-1)
        {
            // 检查是否长按
            if (start_time == 0) 
            {
                start_time = current_time;  // 记录开始触摸的时间
            } 
            else 
            {
                if ((current_time - start_time) >= LONG_PRESS_THRESHOLD) 
                {
                    point.is_long_press = 1;  // 设置长按标志位为1
                }
            }
            printf("Touch Position: (%d, %d %d)\n", point.x, point.y, point.is_long_press);
            return point;
        }
    }
}


//×××××关闭触摸屏××××××
void Close_Touchfd()
{
    close(touch_fd);
}


// 在桌面上时的获取具体实施app的函数
// 返回APP的ID
int desktop_touch()
{
    TouchPoint desktop_point;
    desktop_point = Get_TouchPosition();
    desktop_point.x=desktop_point.x*0.78;
    desktop_point.y=desktop_point.y*0.8;
    //tc.x*800/1024,tc.y*480/600
     printf("DesktoppointX :%d\n", desktop_point.x);
     printf("desktop_point.is_long_press: %d\n", desktop_point.is_long_press);
    switch (desktop_point.is_long_press)
    {
    case 1://长按的话--什么都不做
        break;
    
    case 0://短按则打开该APP
        //相册按键
        if ((desktop_point.x > PhotoAlbum_X_START )&& (desktop_point.y > PhotoAlbum_Y_START)&& 
            (desktop_point.x<PhotoAlbum_X_END)&& (desktop_point.y<PhotoAlbum_Y_END))
            {
                
                printf("PhotoAlbum APP started...\n");
                return PhotoAlbum;
            }
        //监控
        else if ((desktop_point.x>Monitor_X_START)&& (desktop_point.x<Monitor_X_END)&&
            (desktop_point.y>Monitor_Y_START)&&(desktop_point.y<Monitor_Y_END))
        {
            
            printf("Monitor APP started...\n");
            return Monitor;
        }
        // 画板
        else if ((desktop_point.x>DrawingBoard_X_START)&&(desktop_point.x<DrawingBoard_X_END)&&
            (desktop_point.y>DrawingBoard_Y_START)&&(desktop_point.y<DrawingBoard_Y_END))
            {
                
                printf("DrawingBoard APP started...\n");
                return DrawingBoard;
            }
        // 视频
        else if ((desktop_point.x>Vdieo_X_START)&&(desktop_point.x<Vdieo_X_END)&&
            (desktop_point.y>Vdieo_Y_START)&&(desktop_point.y<Vdieo_Y_END))
            {
                
                printf("Vdieo APP started...\n");
                return Vdieo;
            }
        // 智能语音intelligent_voice
        else if ((desktop_point.x>Intelligent_voice_X_START)&&(desktop_point.x<intelligent_voice_X_END)&&
            (desktop_point.y>Intelligent_voice_Y_START)&&(desktop_point.y<intelligent_voice_Y_END))
            {
                
                printf("intelligent_voice APP started...\n");
                return intelligent_voice;
            }
        // 传感器
        else if ((desktop_point.x>Sensor_X_START)&&(desktop_point.x<Sensor_X_END)&&
            (desktop_point.y>Sensor_Y_START)&&(desktop_point.y<Sensor_Y_END))
            {
                
                printf("Sensor APP started...\n");
                return Sensor;
            }
        // 五子棋
        else if ((desktop_point.x>Gobang_X_START)&&(desktop_point.x<Gobang_X_END)&&
            (desktop_point.y>Gobang_Y_START)&&(desktop_point.y<Gobang_Y_END))
            {
                
                printf("Gobang APP started...\n");
                return Gobang;
            }
        else if ((desktop_point.x > Tan_X_START) && (desktop_point.x < Tan_X_END) &&
            (desktop_point.y > Tan_Y_START) && (desktop_point.y < Tan_Y_END))
             {

            printf("Tan APP started...\n");
            return Tan;
            }
        else if ((desktop_point.x > Fang_X_START) && (desktop_point.x < Fang_X_END) &&
            (desktop_point.y > Fang_Y_START) && (desktop_point.y < Fang_Y_END))
            {

            printf("Tan APP started...\n");
            return Fang;
               }
        break;

    default:
        //return 0;
        break;
    }
}
//camera 界面的触摸函数


void* camera_touch(void* argv)
{
    TouchPoint camera_touch= {-1, -1, 0};
    while (1)
    {
        camera_touch = Get_TouchPosition();
        camera_touch.x=camera_touch.x*800/1024;
        camera_touch.y=camera_touch.y*480/600;
        printf("%d %d\n", camera_touch.x, camera_touch.y);
        if ((camera_touch.x >650 )&& (camera_touch.y > 0)&& 
                (camera_touch.x<1000)&& (camera_touch.y<60))
                {
                    
                    printf("exit the monitor...\n");
                    camera_flag = 1;
                }
        else
        {
            camera_flag = 0;
        }
    }
    
}

//**************获取触摸方向2****************//
//获取触摸屏方向
TouchDir GetTouchDir(void)
{
    //操作这个触摸屏 一般触摸屏的操作是不会死掉的  因此我们需要实现死循环
    struct input_event ev;//
    int flag = 0;//超时的flag
    int ev_x0,ev_y0,ev_x,ev_y;
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
                return TouchError;//返回一个错误的方向
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
            ev_x0 = ev_x;
            ev_y0 = ev_y;
        }
        else if(0x01 == ev.type && BTN_TOUCH == ev.code && 0x00 == ev.value)//手抬起来
        {
            printf("%d %d %d %d\n",ev_x0,ev_y0,ev_x,ev_y);
            //实现点击和方向判断
            if(ev_x0 == ev_x && ev_y0 == ev_y)//你的手没有动
            {
                printf("点击\n");
                if(ev_x0 >=900&&ev_y0<=100)
                {
                    return TouchExit;
                }
                return TouchClick;
            }
            else//滑动 滑动就会有方向
            {
                if(ev_x > ev_x0 && abs(ev_x - ev_x0) > abs(ev_y - ev_y0))
                {
                    printf("右滑\n");
                    return TouchRight;
                }
                else if(ev_x < ev_x0 && abs(ev_x - ev_x0) > abs(ev_y - ev_y0))
				{
					printf("左滑\n");
					// music_i = 2;
					// system("killall -9 madplay");
					return TouchLeft;
				}
				else if(ev_y > ev_y0 && abs(ev_x - ev_x0) < abs(ev_y - ev_y0))
				{
					printf("下滑\n");
					// music_i = 3;
					// system("killall -9 madplay");
					return TouchDown;
				}
				else if(ev_y < ev_y0 && abs(ev_x - ev_x0) < abs(ev_y - ev_y0))
				{
					printf("上滑\n");
					// music_i = 4;
					// system("killall -9 madplay");
					return TouchUp;
				}
                else
                {
                    return TouchOther;
                }
            }
        }

    }
}


// //*************音乐相册的退出************//
// void *eMusic_albums_touch(void * argv)
// {
//     TouchPoint eMusic_albums_touch= {-1, -1, 0};
//     eMusic_albums_touch = Get_TouchPosition();
//     eMusic_albums_touch.x=eMusic_albums_touch.x*800/1024;
//     eMusic_albums_touch.y=eMusic_albums_touch.y*480/600;
//     while(1)
//     {
//         if ((eMusic_albums_touch.x >650 )&& (eMusic_albums_touch.y > 0)&& 
//             (eMusic_albums_touch.x<1000)&& (eMusic_albums_touch.y<60))
//             {
//                 eMusic_albums_touch_flag=0;
//                 printf("exit the eMusic_albums......\n");
//                 //取消所有的线程
//                 pthread_cancel(thread_slip);
//                 pthread_cancel(thread_music);
//                 pthread_cancel(thread_pic);
//                 pthread_cancel(thread_eMusic_albums_touch);
                
//             }
//     }
// }



extern TouchDir dir;

void * GetState(void * argv)
{
	pthread_detach(pthread_self());

	while(1)
	{
		dir = GetTouchDir();
		sleep(1);
	}
}



//销毁触摸屏
void DestoryTouch(void)
{
    close(touch_fd);
}

