#include "sensor.h"    

extern int touch_fd;

// 存储点阵数据
char digits[10][16] = {
/*--  文字:  0  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
{0x00,0x00,0x00,0x18,0x24,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18,0x00,0x00},

/*--  文字:  1  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
{0x00,0x00,0x00,0x08,0x38,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x3E,0x00,0x00},

/*--  文字:  2  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
{0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x02,0x04,0x08,0x10,0x20,0x42,0x7E,0x00,0x00},

/*--  文字:  3  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
{0x00,0x00,0x00,0x3C,0x42,0x42,0x02,0x04,0x18,0x04,0x02,0x42,0x42,0x3C,0x00,0x00},

/*--  文字:  4  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
{0x00,0x00,0x00,0x04,0x0C,0x0C,0x14,0x24,0x24,0x44,0x7F,0x04,0x04,0x1F,0x00,0x00},

/*--  文字:  5  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
{0x00,0x00,0x00,0x7E,0x40,0x40,0x40,0x78,0x44,0x02,0x02,0x42,0x44,0x38,0x00,0x00},

/*--  文字:  6  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
{0x00,0x00,0x00,0x18,0x24,0x40,0x40,0x5C,0x62,0x42,0x42,0x42,0x22,0x1C,0x00,0x00},

/*--  文字:  7  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
{0x00,0x00,0x00,0x7E,0x42,0x04,0x04,0x08,0x08,0x10,0x10,0x10,0x10,0x10,0x00,0x00},

/*--  文字:  8  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
{0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x24,0x18,0x24,0x42,0x42,0x42,0x3C,0x00,0x00},

/*--  文字:  9  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
{0x00,0x00,0x00,0x38,0x44,0x42,0x42,0x42,0x46,0x3A,0x02,0x02,0x24,0x18,0x00,0x00}
};
 char guan[] = {
 /*--  文字:  光  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x01,0x00,0x21,0x08,0x11,0x08,0x09,0x10,0x09,0x20,0x01,0x00,0xFF,0xFE,0x04,0x40,
0x04,0x40,0x04,0x40,0x04,0x40,0x08,0x42,0x08,0x42,0x10,0x42,0x20,0x3E,0xC0,0x00
};
char qian[] = {
/*--  文字:  强  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x00,0xF9,0xFC,0x09,0x04,0x09,0x04,0x09,0xFC,0x78,0x20,0x40,0x20,0x43,0xFE,
0x42,0x22,0x7A,0x22,0x0B,0xFE,0x08,0x20,0x08,0x24,0x08,0x22,0x57,0xFE,0x20,0x02
};
char wen[] = {
/*--  文字:  温  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x00,0x23,0xF8,0x12,0x08,0x12,0x08,0x83,0xF8,0x42,0x08,0x42,0x08,0x13,0xF8,
0x10,0x00,0x27,0xFC,0xE4,0xA4,0x24,0xA4,0x24,0xA4,0x24,0xA4,0x2F,0xFE,0x00,0x00
};
char du[] = {
/*--  文字:  度  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x01,0x00,0x00,0x80,0x3F,0xFE,0x22,0x20,0x22,0x20,0x3F,0xFC,0x22,0x20,0x22,0x20,
0x23,0xE0,0x20,0x00,0x2F,0xF0,0x24,0x10,0x42,0x20,0x41,0xC0,0x86,0x30,0x38,0x0E
};
char shi[] = {
/*--  文字:  湿  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x00,0x27,0xF8,0x14,0x08,0x14,0x08,0x87,0xF8,0x44,0x08,0x44,0x08,0x17,0xF8,
0x11,0x20,0x21,0x20,0xE9,0x24,0x25,0x28,0x23,0x30,0x21,0x20,0x2F,0xFE,0x00,0x00
};
char qi[] = {
/*--  文字:  气  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x10,0x00,0x10,0x00,0x3F,0xFC,0x20,0x00,0x4F,0xF0,0x80,0x00,0x3F,0xF0,0x00,0x10,
0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x0A,0x00,0x0A,0x00,0x06,0x00,0x02
};
char ya[] = {
/*--  文字:  压  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x00,0x3F,0xFE,0x20,0x00,0x20,0x80,0x20,0x80,0x20,0x80,0x20,0x80,0x2F,0xFC,
0x20,0x80,0x20,0x80,0x20,0x90,0x20,0x88,0x20,0x88,0x40,0x80,0x5F,0xFE,0x80,0x00
};
char hai[] = {
/*--  文字:  海  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x01,0x00,0x21,0x00,0x11,0xFC,0x12,0x00,0x85,0xF8,0x41,0x08,0x49,0x48,0x09,0x28,
0x17,0xFE,0x11,0x08,0xE2,0x48,0x22,0x28,0x23,0xFC,0x20,0x08,0x20,0x50,0x00,0x20
};
char ba[] = {
/*--  文字:  拔  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x10,0x50,0x10,0x48,0x10,0x48,0x10,0x40,0xFB,0xFE,0x10,0x80,0x14,0x80,0x18,0xFC,
0x31,0x44,0xD1,0x44,0x11,0x28,0x11,0x28,0x12,0x10,0x12,0x28,0x54,0x44,0x21,0x82
};
char maohao[] = {
/*--  文字:  ：  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x30,0x00,0x30,0x00,0x00,0x00,0x30,0x00,0x30,0x00,0x00,0x00,0x00,0x00
};
char C[] = {
/*--  文字:  ℃  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x60,0x00,0x91,0xF4,0x96,0x0C,0x6C,0x04,0x08,0x04,0x18,0x00,0x18,0x00,0x18,0x00,
0x18,0x00,0x18,0x00,0x18,0x00,0x08,0x00,0x0C,0x04,0x06,0x08,0x01,0xF0,0x00,0x00
};
char L[] = {
/*--  文字:  l  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x10,0x70,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x7C,0x00,0x00
};
char U[] = {
/*--  文字:  u  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC6,0x42,0x42,0x42,0x42,0x46,0x3B,0x00,0x00
};
char X[] = {
/*--  文字:  x  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x76,0x24,0x18,0x18,0x18,0x24,0x6E,0x00,0x00
};
char baifenhao[] = {
/*--  文字:  %  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x44,0xA4,0xA8,0xA8,0xB0,0x54,0x1A,0x2A,0x2A,0x4A,0x44,0x00,0x00
};
char _P[] = {
/*--  文字:  P  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0xFC,0x42,0x42,0x42,0x42,0x7C,0x40,0x40,0x40,0x40,0xE0,0x00,0x00
};
char A[] = {
/*--  文字:  a  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x44,0x0C,0x34,0x44,0x4C,0x36,0x00,0x00
};
char M[] = {
/*--  文字:  m  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=8x16   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x49,0x49,0x49,0x49,0x49,0xED,0x00,0x00
};

//6818串口所对应的文件名
#define COM2 "/dev/ttySAC1"
#define COM3 "/dev/ttySAC2"
#define COM4 "/dev/ttySAC3"
int * p, blue = 0xff0000, black = 0xff0000, white = 0x00FFFFFF;

void display_bg(int x0, int y0,int x1, int y1 , int color)
{
    int i, j;
    for(i = x0; i < x1; i++)
    {
        for(j = y0; j < y1; j++)
        {
            point(j, i, color);
        }
    }    
}
void display_word(int color,int x0, int y0, char word[], int w, int h)
{
    int i, j, x, y;
    
    for(i = 0; i < w*h/8; i++)
    {
        for(j = 0; j < 8; j++)
        {
            if(word[i]>>(7-j) & 1 ==1)
            {
                x = i/(w/8) + x0;
                y = (i%(w/8))*8 + j + y0;
                point(y, x, color);
            }
        }
    }
}

void display_digit(int color, int x0, int y0, int number, int w, int h)
{
    int i, j, m = 0, a[100] = {0};
    if(number == 0)
    {
        display_word(blue, x0, y0, digits[0], w, h);
    }
    else
    {
        for(i = 0; number != 0; i++)
        {
            a[i] = number%10;
            number /= 10;
        }
        for(j = i - 1; j >= 0; j--)
        {
           // printf("%d\n", a[j]);    
            display_word(blue, x0, y0+m*8, digits[a[j]], w, h);
            m++;
        } 
    }
}


void display_picture(int x0, int y0, char file[])
{
    printf("%s\n", file);
    short int m;
    int bmp_fd, w, h;
    bmp_fd = open(file, O_RDONLY);
    
    if(bmp_fd == -1)
    {
        perror("open picture file error!");
        return;
    }
    
    lseek(bmp_fd, 0x12, SEEK_SET);
    read(bmp_fd, &w, 4);
    lseek(bmp_fd, 0x16, SEEK_SET);
    read(bmp_fd, &h, 4);    
    lseek(bmp_fd, 0x1C, SEEK_SET);
    read(bmp_fd, &m, 2);
   // printf("w = %d\n", w);
   // printf("h = %d\n", h);
   // printf("m = %d\n", m);
    char color_buf[w*h*m/8];
    lseek(bmp_fd, 54, SEEK_SET);
    read(bmp_fd, color_buf, w*h*m/8);
    
    int i, j, n = 0;
    for(i = h-1+x0; i >= x0; i--)
    {
        for(j = y0; j < w + y0; j++)
        {
            int color = color_buf[2+3*n] << 16 | color_buf[1+3*n] << 8 | color_buf[0+3*n];
            point(j, i, color);
            n++;
        }
    }
    
    close(bmp_fd);
}


int serial_init(char *file,int speed)
{
	/*
		打开串口文件
	*/
    int fd = open(file,O_RDWR);
    if(fd == -1)
    {
        perror("open serial error");
        return -1;
    }
	
    /*定义串口属性结构体*/
    struct termios myserial;
    memset(&myserial,0,sizeof(myserial));//清零
	
	/*设置控制模式 本地连接  使能接收*/
    myserial.c_cflag |= (CLOCAL | CREAD); 
    myserial.c_cflag &=  ~CSIZE; //清空数据位
    myserial.c_cflag &= ~CRTSCTS; //无硬件控制流
    myserial.c_cflag |= CS8; //数据位 8
    myserial.c_cflag &= ~CSTOPB; //停止位 1
    myserial.c_cflag &= ~PARENB; //不要校验

    /*设置波特率*/
	switch(speed)
	{
		case 9600:
			cfsetospeed(&myserial,B9600);
			cfsetispeed(&myserial,B9600);
			break;
		case 57600:
			cfsetospeed(&myserial,B57600);
			cfsetispeed(&myserial,B57600);
			break;
		case 115200:
			cfsetospeed(&myserial,B115200);
			cfsetispeed(&myserial,B115200);
			break;
	}
	
    /*刷新输出队列，清除正接收的数据*/
    tcflush(fd,TCIFLUSH);

    /*更改配置*/
    tcsetattr(fd,TCSANOW,&myserial);
	
    return fd;
}

//获取校验和
char get_BCC(char *cmd)
{
	char BCC = 0;
	int i;
	for(i = 0;i < cmd[0] - 2;i++)
	{
		//BCC = BCC ^ cmd[i];
		BCC ^= cmd[i];
	}
	
	return ~BCC;
}

/*
	防碰撞
	
*/

void CascAnticollRfidCmd(int fd)
{
	char cmd[8] = {0};
	cmd[0] = 0x08;
	cmd[1] = 0x02;
	cmd[2] = 0x42;
	cmd[3] = 0x02;
	cmd[4] = 0x93;//使用ALL模式
	cmd[5] = 0x00;
	cmd[6] = get_BCC(cmd);
	cmd[7] = 0x03;
	//将这个命令发送给rfid 
	write(fd,cmd,cmd[0]);
	
	//稍微延时一会 0.1s
	usleep(100000);
	
	//收rfid的回应
	unsigned char buf[10] = {0};
	int r = read(fd,buf,10);
	if(r == 10)
	{		
		if(buf[2] == 0)
		{
			int getUID  = buf[4] | buf[5] << 8 | buf[6] << 16 | buf[7] << 24;
			printf("getUID = %x\n",getUID);
		}
	}
	else
	{
		perror("read CascAnticollRfidCmd error");
	}
	
	
}

/*
	这个函数是对rfid进行请求的
	成功返回0  失败返回-1
*/
int RequestRfidCmd(int fd)
{
	unsigned char cmd[7] = {0};
	cmd[0] = 0x07;
	cmd[1] = 0x02;
	cmd[2] = 0x41;
	cmd[3] = 0x01;
	cmd[4] = 0x52;//使用ALL模式
	cmd[5] = get_BCC(cmd);
	cmd[6] = 0x03;
	//将这个命令发送给rfid 
	write(fd,cmd,cmd[0]);
	
	//稍微延时一会 0.1s
	usleep(1000000);
	
	//等待rfid的回应
	char buf[8] = {0};
	int r = read(fd,buf,8);
	if(r == 8)
	{
		if(buf[2] == 0)//请求成功
		{	
			switch(buf[4])
			{
				case 0x04:
					printf("S50\n");
					break;
				case 0x02:
					printf("S70\n");
					break;
			}
			
			return 0;
		}
		return -1;
		
	}
	else
	{
		perror("请求失败\n");
		//将蜂鸣器弄的不响
		
		return -1;
	}
}


/*
	这个函数的功能是为了给rfid发送使能命令 
	并且专注这个rfid的返回信息
	fd:是你的初始化好了的串口
	成功返回0 失败返回-1
*/
int SendEnableCmd(int fd)
{
	unsigned char cmd[6] = {0};
	cmd[0] = 0x06;
	cmd[1] = 0x01;
	cmd[2] = 0x41;
	cmd[3] = 0x00;
	cmd[4] = get_BCC(cmd);
	cmd[5] = 0x03;
	
	//将这个命令发送给rfid 
	write(fd,cmd,cmd[0]);
	
	//稍微延时一会 0.1s
	usleep(100000);
	
	
	//等你的rfid回你的信息
	char buf[18] = {0};
	int r = read(fd,buf,18);
	//printf("%d %d\n",r,buf[2]);
	if(18 == r)//这样你才叫得到了完整信息
	{
		if(buf[2] == 0)//这样才叫准备好了
		{
			printf("yes\n");
			return 0;
		}		
		return -1;
	}	
	else
	{
        printf("SendEnableCmd read r = %d\n",r);
		perror("read error");
		return -1;
	}
}

void InitSensor()
{
    show_bmp("beauty.bmp", 0, 0,0);
    show_bmp("draw4.bmp", 750, 400,0);
    Displaysql(200, 150, 90, 160, 0xffffff);
}


/* 进程部分 */

void * yanwu(void *arg)
{
    pthread_detach(pthread_self());

    int fd = serial_init(COM2, 9600);
    int fd1 = open("/dev/pwm", O_RDWR);
    int ret;
    char beep_ctrl[1];

    if(fd == -1)
    {
        perror("serial_init error!\n");
        return (void *)-1;
    }
    if(fd1 == -1)
    {
        perror("open /dev/pwm error!\n");
        return (void *)-1;
    }
    
    while(1)
    {
        char w_buf[9] = {0xFF, 0X01, 0x86, 0, 0, 0, 0, 0, 0x79};
        write(fd, w_buf, 9);
        usleep(1000);
        char r_buf[9];
        int r = read(fd, r_buf, 9);
        if(r == 9 && r_buf[0] == 0xff && r_buf[1] == 0x86)
        {
            int n = r_buf[2]<<8 | r_buf[3];
            printf("n = %d\n", n);
            if(n > 138)
            {
                printf("蜂鸣器\n");
                beep_ctrl[0] = 1;  //不响
                ret = write(fd1,beep_ctrl,sizeof(beep_ctrl));
                if( ret == -1)
                {
                    perror("write");
                }
                sleep(1);
                
                beep_ctrl[0] = 0; 	//响
                ret = write(fd1,beep_ctrl,sizeof(beep_ctrl));
                if( ret == -1)
                {
                    perror("write");
                }
                sleep(1);
            }
            else
            {
                beep_ctrl[0] = 0; 	//响
                ret = write(fd1,beep_ctrl,sizeof(beep_ctrl));
                if( ret == -1)
                {
                    perror("write");
                }
            }
        }
        
        sleep(1);
    }
    
    //close(fd1);
    close(fd);
    return 0;
}



void * rfid(void *arg)
{
    pthread_detach(pthread_self());
    //初始化串口
	int fd = serial_init(COM4,9600);
	printf("fd = %d\n",fd);
	//给我们的rfid发送使能命令 打开你的rfid这个设备
	//自己写一个函数 来实现命令的发送
	
	
	int r = SendEnableCmd(fd);
	if(r != 0)//失败了
	{
        printf("SendEnableCmd error\n");
	}
	
	while(1)
	{
		//发送请求
		r = RequestRfidCmd(fd);
		if(r == 0)//请求成功
		{
			//防碰撞
			CascAnticollRfidCmd(fd);
			printf("你好我是小草神\n");
            show_bmp("green.bmp", 450, 10,0);
            sleep(1);
            InitSensor();
        }
	}
}

void * gy_39(void *arg)
{
/*    
	发送的信息：
		开发板发送给传感器的指令格式：帧头+指令+校验和(8bit)
		帧头和校验和是用来“验证身份”的
		指令才是用来表达此次通信的目的
		各占一个字节，共三个字节
		帧头：0xa5
		指令：
				只请求光照： 10000001 -> 0x81
				只请求温湿度气压海拔：10000010 -> 0x82
				两种都请求：10000011 -> 0x83
		检验和：
				等于帧头加上指令，只保存低8位
			0xa5 + 0x81  -> 0x26
*/

    pthread_detach(pthread_self());

    char led_ctrl[2];
    int fd1 = open("/dev/led_drv",O_RDWR);
    if(fd1 < 0)
	{
		printf("open led_drv failed\n");
		return (void*)-1;
	}
    int fd = serial_init(COM3, 9600);
    int m = 2;
    char w_buf[][3] ={{0xa5, 0x81, 0x26}, {0xa5, 0x82, 0x27}, {0xa5, 0x83, 0x28}};
    int Lux = 0, T = 0, P = 0, Hum = 0, H = 0;
    int t,r,ret;
    char r_buf[24];
    while (1)
    {

        t = write(fd, w_buf[m], 3);
        // printf("%d\n", t);
        usleep(1000);
        r = read(fd, r_buf, 24);

        if (r == 9 && r_buf[2] == 0x15)
        {
            Lux = (r_buf[4] << 24 | r_buf[5] << 16 | r_buf[6] << 8 | r_buf[7]) / 100;
        }
        else if (r == 15 && r_buf[2] == 0x45)
        {
            T = (r_buf[4] << 8 | r_buf[5]) / 100;
            P = (r_buf[6] << 24 | r_buf[7] << 16 | r_buf[8] << 8 | r_buf[9]) / 100;
            Hum = (r_buf[10] << 8 | r_buf[11]) / 100;
            H = (r_buf[12] << 8 | r_buf[13]) / 100;
        }
        else if (r == 24)
        {
            Lux = (r_buf[4] << 24 | r_buf[5] << 16 | r_buf[6] << 8 | r_buf[7]) / 100;
            T = (r_buf[13] << 8 | r_buf[14]) / 100;
            P = (r_buf[15] << 24 | r_buf[16] << 16 | r_buf[8] << 8 | r_buf[9]) / 100;
            Hum = (r_buf[10] << 8 | r_buf[11]) / 100;
            H = (r_buf[12] << 8 | r_buf[13]) / 100;
        }
        printf("Lux = %d, T = %d, P = %d, Hum = %d, H = %d\n", Lux, T, P, Hum, H);
        sleep(1);

        if (Lux < 6)
        {
            led_ctrl[1] = 9;  //D9
            led_ctrl[0] = 1; //on
            ret = write(fd1,led_ctrl,sizeof(led_ctrl));
            
            if( ret != 2)
            {
                perror("write");
            }
            sleep(1);
        }
        else
        {
            led_ctrl[1] = 9; //D9
            led_ctrl[0] = 0; //off
            
            ret = write(fd1,led_ctrl,sizeof(led_ctrl));
            
            if( ret != 2)
            {
            
                perror("write");
            }
            sleep(1);
    }
        display_word(black, 170, 100, guan, 16, 16);
        display_word(black, 170, 116, qian, 16, 16);
        display_word(black, 170, 132, maohao, 16, 16);
        display_bg(170, 148, 186, 164, white);
        display_digit(blue, 170, 148, Lux, 8, 16);
        display_word(blue, 170, 169, L, 8, 16);
        display_word(blue, 170, 177, U, 8, 16);
        display_word(blue, 170, 185, X, 8, 16);

        display_word(black, 196, 100, wen, 16, 16);
        display_word(black, 196, 116, du, 16, 16);
        display_word(black, 196, 132, maohao, 16, 16);
        display_bg(196, 148, 218, 172, white);
        display_digit(blue, 196, 148, T, 8, 16);
        display_word(blue, 196, 169, C, 16, 16);

        display_word(black, 222, 100, shi, 16, 16);
        display_word(black, 222, 116, du, 16, 16);
        display_word(black, 222, 132, maohao, 16, 16);
        display_bg(222, 148, 238, 182 + 100, white);
        display_digit(blue, 222, 148, Hum, 8, 16);
        display_word(blue, 222, 174, baifenhao, 8, 16);

        display_word(black, 248, 100, qi, 16, 16);
        display_word(black, 248, 116, ya, 16, 16);
        display_word(black, 248, 132, maohao, 16, 16);
        display_bg(248, 148, 264, 209 + 50, white);
        display_digit(blue, 248, 148, P, 8, 16);
        display_word(blue, 248, 193, _P, 8, 16);
        display_word(blue, 248, 201, A, 8, 16);

        display_word(black, 272, 100, hai, 16, 16);
        display_word(black, 272, 116, ba, 16, 16);
        display_word(black, 272, 132, maohao, 16, 16);
        display_bg(272, 148, 288, 177 + 100, white);
        display_digit(blue, 272, 148, H, 8, 16);
        display_word(blue, 272, 169, M, 8, 16);
    }
    
    close(fd);
    //return 0;
}



int SensorRun()
{
    struct input_event ev;//
    int flag = 0;//超时的flag
    int ev_x0,ev_y0,ev_x,ev_y,move_x,move_y;


    pthread_t task_yanwu,task_rfid,task_gy39;
    if(pthread_create(&task_yanwu, NULL, (void *)yanwu, NULL) == -1)
    {
        perror("fail to create pthread task_yanwu\n");
        return -1;
    }
    if(pthread_create(&task_rfid, NULL, (void *)rfid, NULL) == -1)
    {
        perror("fail to create pthread task_rfid\n");
        return -1;
    }
    if(pthread_create(&task_gy39, NULL, (void *)gy_39, NULL) == -1)
    {
        perror("fail to create pthread task_rfid\n");
        return -1;
    }
    while (1)
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
                return 0;//返回一个错误的方向
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
            //printf("ev_x0:%d ev_y0:%d\n",ev_x0,ev_y0);
            //实现点击和方向判断
            if(ev_x0 == (ev_x * 800 / 1200) && ev_y0 == (ev_y * 480 / 600))//你的手没有动
            {
                printf("点击\n");
                //return;
            }
            if ((ev_x0 > 600 && ev_x0 < 680) && (ev_y0 > 400 && ev_y0 < 470))
            {

                printf("退出\n");
                pthread_cancel(task_yanwu);
                pthread_cancel(task_rfid);
                pthread_cancel(task_gy39);
                break;
                //exit(1);
            }
        }
    }
    
    return 0;
}

