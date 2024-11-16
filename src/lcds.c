#include "lcds.h"
#include "word.h"


// lcd.h
extern unsigned int* plcd;  // 声明外部变量
// lcd.h
extern void display_word();


//unsigned int *plcd = NULL; // 映射标志位
int fd = -1;

/*****************基础close、write、lseek函数的使用*********************/
/*用白色作为清屏*/
void Clean_lcd()
{
    // lseek(fd, 0, SEEK_SET);
    unsigned int color = 0xffffffff;
    for (int i = 0; i < 800 * 480; i++)
        // write(fd, &color, 4);
        *(plcd + i) = color;
}

/*清除正方形范围的空间
输入：x、y起始位置，w、h为宽高、color为清屏颜色
0xffffffff为白色
*/
void Clean_lcd_part(int x,int y,int w,int h,unsigned int color)
{
    // lseek(fd, 0, SEEK_SET);
    for (int i = x; i <= x+w; i++)
    {
        for(int j = y; j <= y+h; j++)
        {
            *(plcd + (800*(j-1))+i) = color;
        }
    }
    
}

/*用write函数向屏幕中写入数据*/
void Write_lcd(int fd, int color)
{
    for (int i = 0; i < 800 * 480; i++)
        write(fd, &color, 4);
}

/*使用三种颜色刷新显示屏*/
void shuaxing_write_lcd(int fd)
{
    int color = 0xffff00ff;
    int color1 = 0xffff0000;
    int color2 = 0xff00ff00;
    int n = 10;
    while (n--) // 每隔3s刷屏
    {
        Write_lcd(fd, color);
        lseek(fd, 0, SEEK_SET);
        sleep(3);

        Write_lcd(fd, color1);
        lseek(fd, 0, SEEK_SET);
        sleep(3);

        Write_lcd(fd, color2);
        lseek(fd, 0, SEEK_SET);
        sleep(3);
    }
}

/********************内存映射相关函数********************/

/*打开映射*/
void Lcd_init(int fd)
{
    plcd = mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (plcd == MAP_FAILED)
    {
        perror("mmap error");
    }
}

/*解除映射*/
void Lcd_uninit()
{
    munmap(plcd, 800 * 480 * 4);
}

/*画点函数*/
void lcd_draw_point(int x, int y, unsigned int color)
{
    if (x >= 0 && x < 800 && y >= 0 && y < 480)
        *(plcd + y * 800 + x) = color;
}

/*画横线函数*/
void lcd_draw_line(int y, unsigned int color)
{
    for (int i = 0; i < 800; i++)
        lcd_draw_point(i, y, color);
}

/*画竖线函数*/
void lcd_draw_line1(int x,unsigned int color)
{
    for(int i=0;i<480;i++)
        lcd_draw_point(x,i,color);
}

/*画平面函数*/
void lcd_draw_plane(unsigned int color)
{
    for (int i = 0; i < 800 * 480; i++)
        *(plcd + i)=color;
}

/*画线段
  参数: x1、y1起始坐标
        x2、y2终点坐标
*/
void lcd_draw_segment(int x1,int y1,int x2,int y2)
{
    float k=(float)(x1-x2)/(y1-y2);     //转化为小数
    float b=y1-k*x1;
    
    int temp=x1>x2? x1:x2;
    for(int i=x1>x2? x2:x1; i<=temp; i++)
    {
        int j=i*k+b;    //y=kx+b 一元一次方程
        lcd_draw_point(i,j,0xff000000);
    }    
}

/*画矩形函数*/
void draw_juxing()
{

    int x1, x2, y1, y2;
    unsigned int color = 0xffff0000; // 红色
    Clean_lcd();                     // 刷新屏幕

    printf("请输入要画矩形的x1:");
    scanf("%d", &x1);
    printf("请输入要画矩形的x2:");
    scanf("%d", &x2);
    printf("请输入要画矩形的y1:");
    scanf("%d", &y1);
    printf("请输入要画矩形的y2:");
    scanf("%d", &y2);

    int i0 = (x1 > x2) ? x1 : x2;
    int j0 = (y1 > y2) ? y1 : y2;
    for (int i = (x1 < x2) ? x1 : x2; i < i0; i++)
    {
        for (int j = (y1 < y2) ? y1 : y2; j < j0; j++)
        {
            lcd_draw_point(i, j, color);
        }
    }
}

/*画圆函数*/
void draw_circle(int x, int y, int r, unsigned int color)
{
    for (int i = x - r; i < x + r; i++)
    {
        for (int j = y - r; j < y + r; j++)
        {
            if (sqrt(pow(x - i, 2) + pow(y - j, 2)) < r)
                lcd_draw_point(i, j, color);
        }
    }
}

/*画爱心：爱心函数---> (x^2 + y^2 - 1)^3 - x^2 * y^3 = 0 ,该函数改变1的值进行放大，改成25，放大25倍*/
void draw_aixing()
{
    int color=0xffff0000;
    int x=100,y=50,r=50;
    for(int i=x-r;i<x+r;i++)
    {
        for(int j=y-r;j<y+r;j++)    //倒叙打印
        {
            int i0=x-i,j0=y-j;
            if(pow( (i0*i0+j0*j0-300) ,3) < i0*i0*j0*j0*j0)
            {
                lcd_draw_point(i,j,color);
                //printf("i=%d,j=%d\n",i,j);
            }
        }
    }
}

/*画太极函数*/
void draw_taiji()
{
    int x = 400, y = 240; // 确定圆心位于正中心
    unsigned int color1 = 0xff000000;
    unsigned int color2 = 0xffffffff;
    int r = 100;
    lcd_draw_plane(0xff00ffff);
    for (int i = x - r; i < x + r; i++)
    {
        for (int j = y - r; j < y + r; j++)
        {
            if (sqrt(pow(i - x, 2) + pow(j - y, 2)) < r)
            {
                if (i < 400)
                    lcd_draw_point(i, j, color1);
                else
                    lcd_draw_point(i, j, color2);
            }
        }
    } // 左黑色大圈，右红色大圈
    int r1 = 50;
    for (int i = x - r1; i < x + r1; i++)
    {
        for (int j = y - r; j < y + r; j++)
        {
            if (j < 240) // 上半区域
            {
                if (sqrt(pow(i - x, 2) + pow(j - (y - r1), 2)) < r1) // 圆心向上移动了50
                {
                    if (i < 400)
                        lcd_draw_point(i, j, color2);
                }
            }
            else
            {
                if (sqrt(pow(i - x, 2) + pow(j - (y + r1), 2)) < r1) // 圆心向上移动了50
                {
                    if (i >= 400)
                        lcd_draw_point(i, j, color1);
                }
            }
        }
    }
    int r2 = r1 / 4;    //小圆半径
    draw_circle(x, y - r1, r2, color1);
    draw_circle(x, y + r1, r2, color2);
}

/*
    功能:
        显示一个字符
    参数：
        (x0, y0): 在第y0行的第x0个像素点开始进行字符显示
        w:字符的宽   h: 字符的高
        color: 字符的颜色
        word: 需要进行显示的字符的像素点取模数组
*/
//void display_word(int x0, int y0, int w, int h, unsigned int color, char *word)
//{
//    int x, y;                           // 表示需要显示的像素的坐标
//    for (int i = 0; i < w * h / 8; i++) // 循环次数为数组里面的元素个数，遍历数组
//    {
//        for (int j = 0; j < 8; j++) // 进行bit遍历
//        {
//            if (word[i] & (1 << (7 - j))) // 从高位开始向低位遍历
//            {
//                y = i / (w / 8);
//                x = i % (w / 8) * 8 + j;
//            }
//            lcd_draw_point(x0 + x, y0 + y, color);
//        }
//    }
//}

/*
    功能：显示数字
    参数：(x0,y0):在第几行第几个像素点开始进行数字显示
        color：字符颜色
        data: 为需要显示的数字；len：为数字长度(不够会舍弃，有余留空白)
*/
void Lcd_Number(int x0, int y0, int color, int data, int len)
{
    int flag=0;   //flag用于记录数字是否为负数
    if(data<0)
        flag=1;
    data=abs(data);
    int temp=0;
    int i;
    for(i=1; i<=len; i++)   //循环次数为数字数字长度
    {
        if(data==0) break;  //值为0退出
        temp=data%10;
        display_word(x0+16*(len-i),y0,16,20,color,Number_size16[temp]);     //调用显示字符的函数
        data=data/10;
    }
    //显示‘-’号
    if(flag)
    {
        display_word(x0+16*(len-i), y0, 16, 20,color, Number_size16[10]);
    }
}

/*
    功能：显示数字
    参数：(x0,y0):在第几行第几个像素点开始进行数字显示
        color：字符颜色
        data: 为需要显示的数字；len：为数字长度(不够会舍弃，有余留空白)
        gap:为数字间隔，建议选择16或12，值越小字符越紧凑
*/
void Lcd_Number1(int x0, int y0, int color, int data, int len, int gap)
{
    int flag = 0;   //flag用于记录数字是否为负数
    if (data < 0)
        flag = 1;
    data = abs(data);
    int temp = 0;
    int i;
    for (i = 1; i <= len; i++)   //循环次数为数字数字长度
    {
        if (data == 0) break;  //值为0退出
        temp = data % 10;
        display_word(x0 + gap * (len - i), y0, 16, 20, color, Number_size16[temp]);     //调用显示字符的函数
        data = data / 10;
    }
    //显示‘-’号
    if (flag)
    {
        display_word(x0 + 16 * (len - i), y0, 16, 20, color, Number_size16[10]);
    }
}

/*屏幕显示普通字符串函数,
    参数：(x0,y0)起始坐标，gap为两个字符的间距,建议选择16或12，值越小字符越紧凑
        color：字符颜色
        str：字符串首地址*/
void Lcd_string_size(int x0, int y0, int color, char* str, int gap)
{
    int i=0,x;
    while(str[i])   //遇到'\0'时结束
    {
        x=x0+16*i;
        if(x > 784) //800-16,大于时，剩下的空间不至于显示一个宽16的字符
            break;
        //printf("-%c--%d---\n",str[i],str[i]-' ');
        //该函数使用的字库间隔有点宽，x坐标间隔可以改为12使字符更好
        display_word(x0+gap*i,y0,16,20,color,Size_ascll16[str[i]-' ']);
        i++;
    }
}

/*
    使用display_word函数的中间函数,打印游戏结束
    参数：color---字体颜色
*/
void useing_word(unsigned int color)
{
    int x0, y0;
    /*
    printf("请输入开始打印字符的x坐标:");
    scanf("%d", &x0);
    printf("请输入开始打印字符的y坐标:");
    scanf("%d", &y0);
    */
   //数组大小48*48/8；
    x0 = 500;
    y0 = 140;
    int w = 48, h = 48;
    char *str[] = {word, word1, word2, word3}; // 用来存储字符矩阵的数组的首地址名称
    for (int i = 0; i < 4; i++)
    {
        display_word(x0, y0 + i * 50, w, h, color, str[i]);
    }
}

//打印楚河汉界
void useing_word_chuhe(unsigned int color)
{
    int x0=60,y0=225;
    int w=40,h=37;
    char*str[]={word4,word5,word6,word7};
    for(int i=0;i<2;i++)
    {
        display_word(x0+i*80 , y0, w, h, color, str[i]);
    }
    color=0xff000000;
    for(int i=2;i<4;i++)
    {
        display_word(x0+i*80 , y0, w, h, color, str[i]);
    }
}

/*
打印棋盘所需汉字；
输入：1为红方、2为黑方、3为和棋
*/
void useing_word_player(int data)
{
    if(data==1)         //打印红方
    {
        display_word(400,220,40,37,0xffff0000,word8);
        display_word(440,220,40,37,0xffff0000,word10);
    }
    else if(data==2)    //打印黑方
    {
        display_word(400,220,40,37,0xff000000,word9);
        display_word(440,220,40,37,0xff000000,word10);
    }
    else if(data==3)    //打印和棋
    {
        display_word(500,200,40,37,0xffA1A1A1,word11);
        display_word(500,240,40,37,0xffA1A1A1,word12);
    }
}


