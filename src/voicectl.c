#include "common.h"
#include "voicectl.h"
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
//

//#define REC_CMD  "./arecord -d4 -c1 -r16000 -traw -fS16_LE cmd.pcm"
#define REC_CMD  "arecord -d3 -c1 -r16000 -traw -fS16_LE cmd.pcm"
#define PCM_FILE "./cmd.pcm"
/* -d：录音时长（duration）
-c：音轨（channels）
-r：采样频率（rate）
-t：封装格式（type）
-f：量化位数（format） */

void catch (int sig)
{
	if (sig == SIGPIPE)
	{
		printf("killed by SIGPIPE\n");
		exit(0);
	}
}

int voicectl(char *ip)
{
	int openflag;
	signal(SIGPIPE, catch);
	// 初始化TCP客户端套接字，用于连接到语音识别服务器(即ubuntu)
	int sockfd_tcp = init_tcp_socket(ip);
	// 初始化本地UDP套接字
	int sockfd_udp = init_udp_socket();

	int id_num = -1; // 识别后的指令id
	while (1)
	{
		// 1，调用arecord来录一段音频
		printf("please to start REC in 3s...\n");

		// 在程序中执行一条命令  “录音的命令”
		system(REC_CMD);

		// 2，将录制好的PCM音频发送给语音识别引擎
		send_pcm(sockfd_tcp, PCM_FILE);

		// 3，等待对方回送识别结果（字符串ID）
		xmlChar* id = wait4id(sockfd_tcp);
		if (id == NULL)
		{
			continue;
		}
		id_num = atoi((char*)id);


		//if (id_num == 1001)
		//{
		//	system("madplay -Q hu_tao_paint.mp3");//画板

		//	InitCanve();
		//	PaintRun();
		//	show_bmp("Desktop_bmp.bmp", 0, 0, 1);
		//	show_bmp("hutao.bmp", 20, 245, 0);
		//	/* 函数 */
		//	printf("1001\n");

		//}
		//if (id_num == 1000)
		//{
		//	show_bmp("hutao.bmp", 20, 245, 0);
		//	system("madplay -Q hu_tao_start.mp3");//开始
		//	/* 函数 */

		//	printf("1000\n");
		//	break;

		//}
		//if (id_num == 1002)
		//{
		//	system("madplay -Q hu_tao_photo.mp3");//相册
		//	/* 函数 */
		//	eMusic_albums();
		//	show_bmp("Desktop_bmp.bmp", 0, 0, 1);
		//	show_bmp("hutao.bmp", 20, 245, 0);
		//	printf("1002\n");
		//	break;
		//}
		//if (id_num == 1003)
		//{
		//	system("madplay -Q hu_tao_camera.mp3");//监控
		//	camera_Run();
		//	show_bmp("Desktop_bmp.bmp", 0, 0, 1);
		//	show_bmp("hutao.bmp", 20, 245, 0);
		//	/* 函数 */
		//	printf("1003\n");
		//	break;
		//}
		//if (id_num == 1004)
		//{
		//	system("madplay -Q hu_tao_game.mp3");//2048

		//	show_bmp("hutao.bmp", 20, 245, 0);
		//	/* 函数 */
		//	printf("1004\n");
		//	break;
		//}
		//if (id_num == 1005)
		//{
		//	system("madplay -Q hu_tao_no.mp3");//我帅不帅
		//	/* 函数 */

		//	show_bmp("hutao.bmp", 20, 245, 0);
		//	printf("1005\n");
		//	break;
		//}
		//if (id_num == 1006)
		//{
		//	system("madplay -Q hu_tao_game.mp3");//五子棋
		//	/* 函数 */
		//	GobangRun();
		//	show_bmp("Desktop_bmp.bmp", 0, 0, 1);
		//	show_bmp("hutao.bmp", 20, 245, 0);
		//	printf("1006\n");
		//	break;
		//}
		//if (id_num == 1007)
		//{
		//	system("madplay -Q hu_tao_vidio.mp3");//视频播放器
		//	/* 函数 */
		//	InitVideo();
		//	VideoRun();
		//	show_bmp("Desktop_bmp.bmp", 0, 0, 1);
		//	show_bmp("hutao.bmp", 20, 245, 0);
		//	printf("1007\n");
		//	break;
		//}
		//if (id_num == 1008)
		//{
		//	system("madplay -Q hu_tao_end.mp3");//结束

		//	printf("1008\n");
		//	show_bmp("Desktop_bmp.bmp", 0, 0, 1);
		//	//show_bmp("hutao.bmp",20,245,0);
		//	return 0;
		//	break;
		//}
		//if (id_num == 1009)
		//{
		//	system("madplay -Q hu_tao_sensor.mp3");//结束
		//	InitSensor();
		//	SensorRun();
		//	show_bmp("Desktop_bmp.bmp", 0, 0, 1);
		//	show_bmp("hutao.bmp", 20, 245, 0);
		//	printf("1009\n");
		//	break;
		//}

		switch (id_num)
		{	
		case 1000:
			openflag = 1;
			show_bmp("hutao.bmp", 20, 245, 0);
			system("madplay -Q hu_tao_start.mp3");//开始
			/* 函数 */

			printf("1000\n");
			break;
		case 1001:
			if (openflag == 1)
			{
			system("madplay -Q hu_tao_paint.mp3");//画板

			InitCanve();
			PaintRun();
			show_bmp("Desktop_bmp.bmp", 0, 0, 1);
			show_bmp("hutao.bmp", 20, 245, 0);
			/* 函数 */
			printf("1001\n");
			}
		break;
		case 1002:
			if (openflag == 1)
			{
			system("madplay -Q hu_tao_photo.mp3");//相册
			/* 函数 */
			eMusic_albums();
			show_bmp("Desktop_bmp.bmp", 0, 0, 1);
			show_bmp("hutao.bmp", 20, 245, 0);
			printf("1002\n");
			}
			break;
		case 1003:
			if (openflag == 1)
			{
			system("madplay -Q hu_tao_camera.mp3");//监控
			camera_Run();
			show_bmp("Desktop_bmp.bmp", 0, 0, 1);
			show_bmp("hutao.bmp", 20, 245, 0);
		/* 函数 */
			printf("1003\n");
			}
			break;
		case 1004:
			if (openflag == 1)
			{
			system("madplay -Q hu_tao_game.mp3");//2048
			you_2048();
			show_bmp("Desktop_bmp.bmp", 0, 0, 1);
			/* 函数 */
			printf("1004\n");
			}
			break;
		case 1005:
			if (openflag == 1)
			{
			system("madplay -Q hu_tao_no.mp3");//我帅不帅
			/* 函数 */

			show_bmp("Desktop_bmp.bmp", 0, 0, 1);
			printf("1005\n");
			}
			break;
		case 1006:
			if (openflag == 1)
			{
			system("madplay -Q hu_tao_game.mp3");//五子棋
		/* 函数 */
			GobangRun();
			show_bmp("Desktop_bmp.bmp", 0, 0, 1);
			show_bmp("hutao.bmp", 20, 245, 0);
			printf("1006\n");
			}
			break;
		case 1007:
			if (openflag == 1)
			{
			system("madplay -Q hu_tao_vidio.mp3");//视频播放器
		/* 函数 */
			InitVideo();
			VideoRun();
			show_bmp("Desktop_bmp.bmp", 0, 0, 1);
			show_bmp("hutao.bmp", 20, 245, 0);
			printf("1007\n");
			}
			break;
		case 1008:
			if (openflag == 1)
			{
			system("madplay -Q hu_tao_end.mp3");//结束
			openflag = 0;
			printf("1008\n");
			show_bmp("Desktop_bmp.bmp", 0, 0, 1);
			//show_bmp("hutao.bmp",20,245,0);
			return 0;
			}	
			break;
	//打开传感器!id(1009);
		case 1009:
			if (openflag == 1)
			{
			system("madplay -Q hu_tao_sensor.mp3");//结束
			InitSensor();
			SensorRun();
			show_bmp("Desktop_bmp.bmp", 0, 0, 1);
			show_bmp("hutao.bmp", 20, 245, 0);
			printf("1009\n");
			}
			break;
		default:
			if (openflag == 1)
			{
			system("mplayer hu_tao_no.mp3");
			}		
			break;
		}
		
		
		printf("recv id: %d \n", id_num);
		// udp发送数据给接收端, 接收端收到数据id后，再决定执行什么功能
		send_id(sockfd_udp, id_num);
		
	}

	return 0;
}
