#include "bmp.h"
#include "Touch.h"

/*.bmp类型图片文件的数据构成为
文件头：BMP文件以文件头开始，文件头的结构包括文件类型、文件大小、
        保留字段和图像数据的起始偏移量等信息。文件头的长度为14字节。
位图信息头：紧接着文件头的是位图信息头，它描述了图像的详细信息，
        包括图像宽度、高度、每像素位数、压缩方式等。位图信息头的长度为40字节。
调色板（Palette，可选项）：如果图像的每像素位数小于等于8位（即颜色索引的位数不超过8位），则会有一个调色板。
        调色板包含颜色索引表，用于映射到实际的颜色。调色板的大小取决于每像素位数，通常为2的位数次幂乘以颜色索引数目。
像素数据：紧接着文件头和位图信息头的是像素数据。像素数据按照从左到右、从下到上的顺序存储，每行的像素数据以4字节对齐（如果需要的话）。
        像素数据的格式取决于每像素位数和是否使用了调色板。通常情况下：
1、对于无调色板的真彩色图像（24位色深），每个像素由RGB三个字节（或四个字节，如果包含透明度信息）表示。
2、对于使用调色板的图像，每个像素用一个索引字节表示，通过调色板中的对应索引找到实际的RGB颜色值。*/

/*
    获取BMP图片的信息
    参数：BMP图片的路径
*/
BMP get_bmp_info(char *bmpname)
{
    int fd_bmp = open(bmpname, O_RDONLY);
    if (fd_bmp == -1)
    {
        perror("open bmp error");
        exit(1);
    }

    // 判断该文件是否为bmp文件,通过读取图片文件前两个字符信息
    char bm[2] = {0};
    read(fd_bmp, bm, 2);
    if (!(bm[0] == 'B' && bm[1] == 'M'))
    {
        printf("%s is not BMP file\n", bmpname);
        exit(1);
    }

    // 获取bmp图片的数据
    BMP bmpinfo;

    // 文件大小
    lseek(fd_bmp, 0x02, SEEK_SET);
    read(fd_bmp, &bmpinfo.size, 4);

    // 宽度和高度
    lseek(fd_bmp, 0x12, SEEK_SET);
    read(fd_bmp, &bmpinfo.width, 4);
    read(fd_bmp, &bmpinfo.height, 4);

    //色深，指每个像素的颜色深度，如1位、4位、8位、24位<-->0x00000018
    lseek(fd_bmp, 0x1c, SEEK_SET);
    read(fd_bmp, &bmpinfo.depth, 2);    

    //像素数组
    char* p=malloc(bmpinfo.size - 54);  //图片总大小 - 文件头大小
    lseek(fd_bmp ,0x36, SEEK_SET);
    read(fd_bmp, p,bmpinfo.size-54);
    bmpinfo.data = p;   //将所有像素数据写入像素数组当中

    close(fd_bmp);
    return bmpinfo;
}

/*
    功能：
        显示一张BMP图片,读取图片的像素数据并映射到屏幕上即可
    参数：
        (x, y) 图片从那个位置开始进行显示 x.y为图片的最左上角的坐标
        bmpname: 需要进行显示的图片的路径
*/
void lcd_draw_bmp(int x,int y,char *bmpname)
{
    BMP bmp=get_bmp_info(bmpname);

    //printf("bmpname=%s, size=%d, height = %d, depth = %d\n",bmpname, bmp.size, bmp.width, bmp.height, bmp.depth);
    
    //一行的有效字节数
    int line_types = bmp.width*bmp.depth / 8;

    //一行需要填充字节数
    int pad_types=(line_types % 4 == 0)? 0 : (4 - line_types % 4);

    //解析像素数组中的数据
    unsigned int color;
    unsigned char a,r,g,b;  //颜色分量

    char* p=bmp.data;
    for(int h=0; h < abs(bmp.height); h++)
    {
        for(int w=0; w < abs(bmp.width); w++)
        {
            //获取颜色分量,小端模式存储
            b=*(p++);
            g=*(p++);
            r=*(p++);
            a=(bmp.depth == 24)? 0:*(p++);
            //合成像素点
            color=a<<24 | r<<16 | g<<8 | b;

            //描点
            // width > 0 : 每一行的像素点从左往右存放
            // width < 0 : 每一行的像素点从右往左存放
            // height > 0: 每一列的像素点从下往上存放
            // height < 0: 每一列的像素点从上往下存放
            int m = x+w;      //横坐标  一行中的第几个像素点
            int n = y+bmp.height-1-h;        //纵坐标 第几行；屏幕是从上往下。
            lcd_draw_point(m, n, color);
        }
        
        p+=pad_types;
    }
}

/*自动播放电子相册*/
void atuo_photo()
{
    char *str[]={"1.bmp","2.bmp","3.bmp","4.bmp","5.jpg"};
    int n=10;
    while(n--)
    {
        for(int i=0;i<5;i++)
        {
            char temp[20]={0};
            strncat(temp,str[i],strlen(str[i])-4);
            strcat(temp,".bmp");
            if(strcmp(temp,str[i]) == 0)
            {
                lcd_draw_bmp(0,0,str[i]);   //打印bmp文件
            }
            else
            {
                lcd_draw_jpeg(0,0,str[i]);    //打印jpg文件
            }
            sleep(3);       //睡眠3s
            Clean_lcd();
        }
    }
}


