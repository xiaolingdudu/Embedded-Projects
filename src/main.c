#include <stdio.h>
#include "picture.h"
#include "lcd.h"
#include "touch.h"
#include "music.h"
#include "login.h"
#include "paint.h"
#include "camera.h"
#include "play_video.h"
#include "intelligent_voice.h"
#include "sensor.h"
#include "gobang.h"
#include "voicectl.h"

void App_Run(int argc, char* argv[])  // 修改：接受 argc 和 argv 作为参数
{
    int App_ID = 0;
    while (1)
    {
        App_ID = desktop_touch();

        switch (App_ID)
        {
        case PhotoAlbum:  /* 电子音乐相册 */
            eMusic_albums();
            show_bmp("Desktop_bmp.bmp", 0, 0, 1);
            break;
        case Monitor:  /* 监控 */
            camera_Run();
            show_bmp("Desktop_bmp.bmp", 0, 0, 1);
            break;
        case DrawingBoard:  /* 画板 */
            InitCanve();
            PaintRun();
            show_bmp("Desktop_bmp.bmp", 0, 0, 1);
            break;
        case Vdieo:  /* 视频 */
            InitVideo();
            VideoRun();
            show_bmp("Desktop_bmp.bmp", 0, 0, 1);
            break;
        case intelligent_voice:  /* 语音通讯 */
            voicectl(argv[1]);  // 使用传入的 argv
            show_bmp("Desktop_bmp.bmp", 0, 0, 1);
            break;
        case Sensor:  /* 传感器 */
            InitSensor();
            SensorRun();
            show_bmp("Desktop_bmp.bmp", 0, 0, 1);
            break;
        case Gobang:  /* 五子棋 */
            GobangRun();
            show_bmp("Desktop_bmp.bmp", 0, 0, 1);
            break;
        case Tan:  /* 贪吃蛇 */
            tanchishe();
            show_bmp("Desktop_bmp.bmp", 0, 0, 1);
            break;
        case Fang:  /* 2048 */
            you_2048();
            show_bmp("Desktop_bmp.bmp", 0, 0, 1);
            break;
        default:
            break;
        }
    }
}

void login_run()
{
    while (1)
    {
        TouchPoint touch_pos = Get_TouchPosition(); // 获取触摸位置
        int result = show_hua(touch_pos.x * 800 / 1024);  // 触摸位置转换
        if (result == 1)
        {
            printf("解锁完成,请你在显示屏处输入正确的密码\n");
            break;
        }
    }
}

void password_run()
{
    while (1)
    {
        if (unlock_passward())  // 密码输入界面
        {
            printf("密码正确,可以开始使用APP了\n");
            break;
        }
    }
}

int main(int argc, char* argv[])
{
    Lcd_Init();  // LCD 初始化
    touch_evntInit();  // 触摸事件初始化
    TouchPoint point;
    show_bmp("lockx.bmp", 0, 0, 1);  // 解锁前的界面

    // 需要使用密码解锁的话，取消注释以下行
    // login_run();
    password_run();  // 密码验证

    while (1)
    {
        show_bmp("Desktop_bmp.bmp", 0, 0, 1);
        App_Run(argc, argv);  // 将 argc 和 argv 传递给 App_Run
    }

    Lcd_close();
    Close_Touchfd();
    return 0;
}
