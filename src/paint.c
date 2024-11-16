#include "paint.h"

int mode=0, color=0x0000ff, size=10;
int color_buf;

void InitCanve()
{
    Displaysql(800, 480, 0, 0, 0xffffff);
    //大小选择
    Displaycir(10, 20, 20, 0x000000);
    Displaycir(15, 45, 20, 0x000000);
    Displaycir(20, 80, 20, 0x000000);
    //颜色选择
    Displaycir(20, 120, 20, 0xff0000);
    Displaycir(20, 150, 20, 0x00ff00);
    Displaycir(20, 180, 20, 0x0000ff);
    //模式选择
    show_bmp("Draw1.bmp",480,25,0);
    show_bmp("draw2.bmp",530,25,0);
    show_bmp("draw3.bmp",580,25,0);
    show_bmp("draw4.bmp",750,25,0);
}

void PaintRun()
{
    //操作这个触摸屏 一般触摸屏的操作是不会死掉的  因此我们需要实现死循环
    struct input_event ev;//
    int flag = 0;//超时的flag
    float ev_x0,ev_y0,ev_x,ev_y,move_x,move_y;
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
        if(0x03 == ev.type)
        {
            if(0x00 == ev.code){
                move_x = ev.value * 800  / 1024 / 2;
            }
            if(0x01 == ev.code){
                move_y = ev.value * 480  / 600 / 2;
            }
            printf("%d %d\n", move_x, move_y);
            if(move_y>45){
                Displaycir(size, move_x, move_y, color);
            }
            //printf("我在绘画\n");
        }
        else if(0x01 == ev.type && BTN_TOUCH == ev.code && 0x00 == ev.value)//手抬起来
        {
            //printf("ev_x0:%d ev_y0:%d\n",ev_x0,ev_y0);
            //实现点击和方向判断
            if(ev_x0 == ev_x && ev_y0 == ev_y)//你的手没有动
            {
                printf("点击\n");
                //return;
            }
            if ((ev_x0 > 0 && ev_x0 < 30) && (ev_y0 > 0 && ev_y0 < 50))
            {
                size = 10;
                printf("小型\n");
            }
            if ((ev_x0 > 60 && ev_x0 < 90) && (ev_y0 > 0 && ev_y0 < 50))
            {
                size = 20;
                printf("中型\n");
            }
            if ((ev_x0 > 120 && ev_x0 < 150) && (ev_y0 > 0 && ev_y0 < 50))
            {
                size = 30;
                printf("大型\n");
            }
            if ((ev_x0 > 180 && ev_x0 < 210) && (ev_y0 > 0 && ev_y0 < 50))
            {
                color = 0xff0000;
                printf("红色\n");
            }
            if ((ev_x0 > 240 && ev_x0 < 270) && (ev_y0 > 0 && ev_y0 < 50))
            {
                color = 0x00ff00;
                printf("绿色\n");
            }
            if ((ev_x0 > 290 && ev_x0 < 320) && (ev_y0 > 0 && ev_y0 < 50))
            {
                color = 0x0000ff;
                printf("蓝色\n");
            }
            if ((ev_x0 > 410 && ev_x0 < 450) && (ev_y0 > 0 && ev_y0 < 80))
            {
                color = color_buf;
                printf("画图\n");
            }
            if ((ev_x0 > 460 && ev_x0 < 490) && (ev_y0 > 0 && ev_y0 < 70))
            {
                color_buf = color;
                printf("橡皮擦\n");
                color = 0xffffff;
            }
            if ((ev_x0 > 500 && ev_x0 < 530) && (ev_y0 > 0 && ev_y0 < 70))
            {
                InitCanve();
                printf("重置\n");
            }
            if ((ev_x0 > 650 && ev_x0 < 685) && (ev_y0 > 0 && ev_y0 < 70))
            {
                printf("退出\n");
                return;
            }
        }
    }
}
