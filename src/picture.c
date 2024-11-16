#include "picture.h"
#include "math.h"
//unsigned int* back_buffer = NULL;//一个后台buffer,用来改善频繁更改屏幕


//*************画点的函数********************
void point(int x, int y, unsigned int color) 
{
    if (x >= 0 && x < 800 && y >= 0 && y < 480) 
    {
        *(plcd + y * 800 + x) = color;
    }
}


//*****************添加背景颜色-color************
void display_bgm(int color) {
    int w =800,h=480;
    int x, y;
    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            point(x , y , color);
        }
    }
}

//××××××××××××××××××显示图片的函数×××××××
//1. 在相册中，不是lcd大小的图片需要居中
//2. 特定小的图片，不需要居中显示
//传入参数： 1. 图片名称 2. 坐标：xy 3. 是否需要居中显示
// choice ： 1--需要居中显示  0--不需要居中显示
void show_bmp(const char* filename, int x0,int y0,char choice)
{

    //1.打开bmp文件
    int bmp_fd = open(filename, O_RDONLY);
    if(-1 == bmp_fd)
    {
        perror("open bmp error");
        return;
    }
    //2. 判断是否是真的bmp文件
    unsigned char buf[2];
    read(bmp_fd,buf,2);
    if(buf[0]!=0x42 || buf[1]!= 0x4d)//如果开头不是BM 的ASCII码则不是BMP文件
    {
        printf("NOT a BMP !!\n");
        return ;
    }
    //3.读取图片数据
    int width,height,depth;
    lseek(bmp_fd,0x12,SEEK_SET);
    read(bmp_fd,&width,4);//四个字节--宽度
    read(bmp_fd,&height,4);//高度--可以继续往下读
    lseek(bmp_fd,0x1c,SEEK_SET);
    read(bmp_fd,&depth,4);//也可以是2个字节
    //只支持色深24和32
    if(!(depth == 24 || depth == 32))
    {
        printf("NOT Support!\n");
        return;
    }
    //printf("width = %d height = %d depth = %d \n", width,height,depth);
    //4.处理居中的情况
    if (1 == choice)//需要居中显示
    {
        display_bgm(0xFFFFFF);//居中显示需要将其他部分刷成其他颜色
        if(width<800||height<480)
        {
            x0 = (int)(800-width)/2;
            y0 = (int)(480-height)/2;
        }
    }

    //5.获取像素数组
    int line_valid_bytes = abs(width)*depth/8;//每一行像素数据的有效字节数
    int line_bytes;//每行的总字节数
    int laizi=0;
    if(line_valid_bytes%4)//不是四个整的字节
    {
        laizi = 4-line_valid_bytes%4;
    }
    line_bytes = line_valid_bytes+laizi;

    int total_bytes = line_bytes*abs(height);//整个像素数组的大小
    unsigned char *piexl = (unsigned char *)malloc(total_bytes);
    lseek(bmp_fd,54,SEEK_SET);
    read(bmp_fd,piexl,total_bytes);

    //6.使用像素数组画图
    unsigned char a,r,g,b;
    int color = 0;
    int i=0;
    for(int y=0; y<abs(height); y++)
    {
        for(int x=0;x<abs(width);x++)
        {
            //a  r  g  b  0xargb
            b=piexl[i++];
            g=piexl[i++];
            r=piexl[i++];
            if(depth == 32)
            {
                a=piexl[i++];
            }
            else
            {
                a=0;//透明的
            }
            color=(a<<24)|(r<<16)|(g<<8)|(b);
            //在屏幕上画点
            point(width>0?x0+x:x0+abs(width)-x-1,height>0?y0+abs(height)-y-1:y0+y,color);
        }
        i+=laizi;//在每一行的末尾添加赖子
    }
    //update_screen();
    free(piexl);
    close(bmp_fd);
}

//**************画一个方块*****************//
void Displaysql(int w, int h, int x0, int y0,unsigned int color)
{
	int x, y;
	for (y = 0; y < h; y++)
	{
		for (x = 0; x < w; x++)
		{
			point(x + x0, y + y0, color);
		}
	}
}

//*****************画一个圈*********************//
void Displaycir(int radios, int x0, int y0,unsigned int color)
{
	int x, y;
	for (y = y0-radios; y < y0+radios; y++)
	{
		for (x = x0-radios; x < x0+radios; x++)
		{
            if(sqrt(pow(x-x0,2)+pow(y-y0,2)) < radios)
            {
                point(x + x0, y + y0, color);
            }
		}
	}
}

/***************** 特效部分 ******************/
//****************普通特效******************
void DisplayNo(int width, int height, int x0, int y0, unsigned int *color)
{
	int x, y, i = 0;
	for (y = height - 1 + y0; y >= y0; y--)
	{
		for (x = x0; x < x0 + width; x++)
		{
            point(x, y, color[i++]); 
			//*(plcd + y * 800 + x) = color[i++];
		}		
	}
}
//********************* 区块特效*****************//
void DisplayDelay(int width, unsigned int *color)
{
	int x, y, num;

	for (int i = 3; i > 0; i--)
	{
		for (int j = 0; j < 5; j++)
		{
			for (y = (i * 160) - 1; y >= (i - 1) * 160; y--)
			{
				for (x = j * 160; x < (j + 1) * 160; x++)
				{
					num = y * width + x;
                    point(x, y, color[num]) ;
					//*(plcd + y * 800 + x) = color[num];
				}		
			}
			usleep(5 * 1000 * 10);
		}
	}

}

//*********** 圆圈特效  ******************//
void DisplayCircle(int width, int height, int x0, int y0,unsigned int* color)
{
	int radios = 0, MaxRadios;
	int x, y, i = 0;

	if(800 - x0 >= 400){
		x = 800 - x0;
	}
	else{
		x = x0;
	}

	if(480 - x0 >= 240){
		y = 480 - y0;
	}
	else{
		y = y0;
	}

	MaxRadios = (int)sqrt(pow(x, 2) + pow(y, 2)) + 1;
	printf("中心点离屏幕最远距离为：%d\n", MaxRadios);

	while (radios <= MaxRadios+50)
	{
		i = 0;
		for (y = height - 1; y >= 0; y--)
		{
			for (x = 0; x < width; x++)
			{
				if(sqrt(pow((x-x0), 2) + pow((y-y0), 2)) < radios){
					//*(plcd + y * 800 + x) = color[i];
                    point(x, y, color[i]) ;
				}
				i++;
			}
		}
		radios += 100;
		usleep(100);
	}
}



//*******************特效图片显示函数********//
void DisplayBmpPicVideo(const char *pic, int state)
{
	int fd = open(pic, O_RDONLY);
	if (-1 == fd)
	{
		perror("open error");
		return;
	}
	//判断这个图片是不是真的bmp文件
	int width, height, depth=0;
	//读取宽度，将偏移量偏移到宽度
	lseek(fd, 0x12, SEEK_SET);
	read(fd, &width, 4);
	read(fd, &height, 4);

	lseek(fd, 0x1c, SEEK_SET);//色深
	read(fd, &depth, 2);
	//数组比较大最好采用动态分配
	int n = (4 - width * (depth / 8) % 4) % 4;
	unsigned char* colorbuf = malloc((width * (depth / 8) + n) * height);
	unsigned int* colordata = malloc(width * height * sizeof(unsigned int));
	//将像素数组读到再说 偏移过头部就是像素数组
	lseek(fd, 0x36, SEEK_SET);
	read(fd, colorbuf, (width * (depth / 8) + n) * height);

	//拿到每一个像素点的argb
	unsigned char c_a=0, c_r, c_b ,c_g;
	unsigned int color;
	int i = 0,j = 0;
	int x, y;
	for (y = height - 1; y >= 0; y--)
	{
		for (x = 0; x < width; x++)
		{
			c_b = colorbuf[i++];
			c_g = colorbuf[i++];
			c_r = colorbuf[i++];
			if(32==depth)
				c_a = colorbuf[i++];
			colordata[j++] = c_a << 24 | c_r << 16 | c_g << 8 | c_b;
		}
		i += n;//每次走完一行就要跳过n个字节
	}

	switch (state)
	{
	case 1:
		DisplayNo(width, height, (800 - width)/2, (480 - height)/2, colordata);
	break;
	case 2:
		DisplayDelay(width, colordata);
	break;
	case 3:
		DisplayCircle(width,height, 400, 240, colordata);
	break;
	default:
		
	break;
	}

	free(colorbuf);
	free(colordata);


	close(fd);
}

TouchDir dir;

int ShowPicture()
{
	DisplayBmpPicVideo("./photo_1.bmp", 1);
	while (1)
	{
		printf("mode:%d\n",dir);
		switch (dir)
		{
			case TouchUp:
				DisplayBmpPicVideo("./photo_1.bmp", 1);
			break;
			case TouchDown:
				Displaysql(800, 480, 0, 0, 0xffffff);
				DisplayBmpPicVideo("./photo_2.bmp",1);
			break;
			case TouchLeft:
				DisplayBmpPicVideo("./photo_3.bmp",2);
			break;
			case TouchRight:
				DisplayBmpPicVideo("./photo_4.bmp",3);
			break;
            case TouchClick://点击切换歌曲
                music_i++;
                if(music_i > 4)
                {
                    music_i = 1;
                }
                system("killall -9 madplay");
            break;
			case TouchExit:
				//eMusic_albums_touch_flag=0;
				printf("exit the eMusic_albums......\n");
				//取消所有的线程
				pthread_cancel(thread_slip);
				pthread_cancel(thread_music);
				return 1;
			break;
			default:
				printf("保持原状\n");
			break;
		}
		dir = TouchOther;
		sleep(1);
	}
}




