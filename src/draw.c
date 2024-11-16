#include "draw.h"

extern unsigned int* plcd;

// 显示一个像素点
//posx和posy为像素点的坐标，color为像素点的颜色值
void lcd_draw_pixel(int posx, int posy, int color)
{
	//判断像素点坐标是否在LCD屏幕范围内
    if (posx >= 0 && posx < 800 && posy >= 0 && posy < 480)
		//在对应位置写入颜色值
        *(plcd + posy * 800 + posx) = color;
}
// 初始化lcd屏幕
// void lcd_init()
// {
//     //打开lcd设备文件
//     lcd_fd = open(LCD_PATH, O_RDWR);
//     if (lcd_fd == -1)//如果打开失败
//     {
//         perror("open lcd failed");
//         return;
//     }
//     //读取lcd屏幕的当前信息
//     struct fb_var_screeninfo lcd_info;//定义结构体变量，用于存储lcd屏幕信息
//     ioctl(lcd_fd, FBIOGET_VSCREENINFO, &lcd_info);//通过ioctl函数获取lcd屏幕信息

//     //将lcd内存映射到进程的地址空间中，使得可以直接读写lcd内存 
//     int mem_size = lcd_info.xres * lcd_info.yres * (lcd_info.bits_per_pixel / 8);
// 	//计算内存大小 
//     lcd_fp = mmap(NULL, mem_size, PROT_READ | PROT_WRITE, MAP_SHARED, lcd_fd, 0);
// 	//映射内存
//     if (lcd_fp == MAP_FAILED)//如果映射失败 
//     {
//         perror("mmap failed");
//         close(lcd_fd);
//         lcd_fd = -1;//设置lcd设备文件为-1，表示打开失败  
//         exit(0);
//     }
//     return;
// }
// 打印棋盘上初始的五个点
void DisPlay_Five_point(void)
{
	//初始化lcd屏幕
    lcd_init();
	//定义五个点的坐标
    int x0 = 144 + 16, y0 = 144;
    int x1 = 336 + 16, y1 = 144;
    int x2 = 240 + 16, y2 = 240;
    int x3 = 144 + 16, y3 = 336;
    int x4 = 336 + 16, y4 = 336;
	//在每个点周围绘制一个圆形图案（通过判断像素点是否在圆内，然后绘制黑色像素）
    for (int w = x0 - 48; w < x0 + 48; w++)//w循环控制圆的宽度  
    {
        for (int h = y0 - 48; h < y0 + 48; h++) //h循环控制圆的高度  
        {
			//判断当前像素点是否在圆x0，y0内
            if ((w - x0) * (w - x0) + (h - y0) * (h - y0) <= 25)//圆的半径是25像素
                lcd_draw_pixel(w, h, 0x000000); //在圆内绘制黑色像素点 
        }
    }
	//同理，为其他四个点绘制圆形图案 
    for (int w = x1 - 48; w < x1 + 48; w++)
    {
        for (int h = y1 - 48; h < y1 + 48; h++)
        {
            if ((w - x1) * (w - x1) + (h - y1) * (h - y1) <= 25)
                lcd_draw_pixel(w, h, 0x000000);
        }
    }
    for (int w = x2 - 48; w < x2 + 48; w++)
    {
        for (int h = y2 - 48; h < y2 + 48; h++)
        {
            if ((w - x2) * (w - x2) + (h - y2) * (h - y2) <= 25)
                lcd_draw_pixel(w, h, 0x000000);
        }
    }
    for (int w = x3 - 48; w < x3 + 48; w++)
    {
        for (int h = y3 - 48; h < y3 + 48; h++)
        {
            if ((w - x3) * (w - x3) + (h - y3) * (h - y3) <= 25)
                lcd_draw_pixel(w, h, 0x000000);
        }
    }
    for (int w = x4 - 48; w < x4 + 48; w++)
    {
        for (int h = y4 - 48; h < y4 + 48; h++)
        {
            if ((w - x4) * (w - x4) + (h - y4) * (h - y4) <= 25)
                lcd_draw_pixel(w, h, 0x000000);
        }
    }
    close(lcd_fd);
}
////打印棋盘
//void lcd_draw_board()
//{
//    for (int h = 0; h < 480; h++) //打印棋盘的横线
//    {
//        for (int w = 0; w < 496; w++)//打印棋盘的列
//        {
//			 //为棋盘的每个格子绘制一个像素点，颜色为0xa42d00（一种黄色）
//            lcd_draw_pixel(w, h, 0xa42d00);
//            //如果在棋盘的边界位置，则绘制黑色像素点
//            if (w <= 16)
//            {
//                lcd_draw_pixel(w, h, 0x000000);
//            }
//			//如果行h是48的倍数，表示到达一个新的横线，则绘制黑色像素点作为分隔线  
//            if (h % 48 == 0)
//            {
//                lcd_draw_pixel(w, h, 0x000000);//分隔线为黑色 
//            }
//        }
//    }
//    for (int w = 0; w < 496; w++) // 打印棋盘的竖线
//    {
//        for (int h = 0; h < 480; h++)
//        {
//			//如果列w是48的倍数加32，表示到达一个新的竖线，则绘制黑色像素点作为分隔线  
//            if ((w + 32) % 48 == 0)
//            {
//                lcd_draw_pixel(w, h, 0x000000);
//            }
//        }
//    }
//	//在绘制完棋盘后，显示五个初始点
//    DisPlay_Five_point();
//}
// 
// 
// 
// 
// // 定义棋盘和线条颜色
#define BOARD_COLOR 0xffffff   // 棋盘的颜色（黄褐色）
#define LINE_COLOR  0x000000   // 线条颜色（黑色）
#define CELL_SIZE   48         // 每个格子的大小为48像素
#define BOARD_WIDTH 496        // 棋盘宽度
#define BOARD_HEIGHT 480       // 棋盘高度

// 打印棋盘
void lcd_draw_board()
{
    // 遍历棋盘的每个像素点
    for (int h = 0; h < BOARD_HEIGHT; h++) // 打印横线
    {
        for (int w = 0; w < BOARD_WIDTH; w++) // 打印竖线
        {
            // 绘制默认的棋盘格子颜色
            lcd_draw_pixel(w, h, BOARD_COLOR);

            // 绘制横向分隔线：每隔CELL_SIZE个像素（即每个格子的边缘）
            if (h % CELL_SIZE == 0)
            {
                lcd_draw_pixel(w, h, LINE_COLOR);
            }

            // 绘制纵向分隔线：每隔CELL_SIZE个像素
            if (w % CELL_SIZE == 0)
            {
                lcd_draw_pixel(w, h, LINE_COLOR);
            }

            // 绘制棋盘的左边界（前16个像素）
            if (w < 16)
            {
                lcd_draw_pixel(w, h, LINE_COLOR);
            }
        }
    }

    // 在绘制完棋盘后，显示五个初始点
    DisPlay_Five_point();
}

//下子打印函数，用于在棋盘上放置棋子并显示其颜色
void LCD_play_chess(int x, int y, int *color, char arr)
{
    lcd_init();
    //根据传入的字符（b或w）判断是黑棋还是白棋，并相应地绘制棋子  
    if (arr == 'b')//b代表黑棋，颜色为黑色 
    {
        for (int w = x - 48; w < x + 48; w++)//在棋子的周围绘制一个圆形区域（半径为48像素）为黑色  
        {
            for (int h = y - 48; h < y + 48; h++)
            {
                if ((w - x) * (w - x) + (h - y) * (h - y) <= 125)//根据圆心和半径判断像素点是否在圆内  
                {

                    lcd_draw_pixel(w, h, 0x000000);//在圆内绘制黑色像素点，表示放置了黑棋
                    *color *= -1;//更新颜色状态，表示已经放置了黑棋，下次放置白棋
                }
            }
        }
    }
    else if (arr == 'w')//w代表白棋，颜色为白色
    {
        for (int w = x - 48; w < x + 48; w++)//在棋子的周围绘制一个圆形区域（半径为48像素）为白色  
        {
            for (int h = y - 48; h < y + 48; h++)
            {
                if ((w - x) * (w - x) + (h - y) * (h - y) <= 125)
                {

                    lcd_draw_pixel(w, h, 0xffffff);
                    *color *= -1;
                }
            }
        }
    }
}
// 显示游戏选项范围
void Show_Game_Options(void)
{
    lcd_init();
	//在指定的坐标范围内绘制黑色像素点，形成游戏选项的背景框 
    for (int h = 200; h < 285; h++)
    {
        for (int w = 90; w < 250; w++)
        {
            lcd_draw_pixel(w, h, 0x000000);//绘制黑色像素点 
        }
        //在另一指定的坐标范围内绘制黑色像素点，形成另一个背景框
        for (int h = 200; h < 285; h++)
        {
            for (int w = 500; w < 670; w++)
            {
                lcd_draw_pixel(w, h, 0x000000);
            }
        }
    }
    close(lcd_fd);
}
// 打印结束画面
void Show_End_Screen(void)
{
    lcd_init();
	//打印全屏的黑色，表示游戏的结束画面 
    for (int h = 0; h < 480; h++) // 打印横行
    {
        for (int w = 0; w < 800; w++)
        {
            lcd_draw_pixel(w, h, 0x000000);//绘制黑色像素点
        }
    }
    close(lcd_fd);
}
//打印图
void Show_pictures(int posx, int posy, const char *str)
{
    //lcd_init();
	
    int pic_id = open(str, O_RDONLY);//打开指定的图片文件，只读方式
    if (pic_id == -1)//如果打开失败
    {
        perror("open picture failed");//打印错误信息
        return;
    }
    //定义一个4字节的空间去存储读取到的数据
    unsigned char data[4] = {0};
    read(pic_id, data, 2);
    //判断是否为BMP图片
    if (data[0] != 0x42 || data[1] != 0x4d)
	{
        puts("this picture not bmp file!");
        return;
	}
    //读取像素数组的偏移量数据
    lseek(pic_id, 0x0a, SEEK_SET);//定位到文件的0x0A位置 
    read(pic_id, data, 4);//读取4字节数据
    //数据还原，取决大小端模式，得到像素数组的偏移量  
    int offset = data[3] << 24 | data[2] << 16 | data[1] << 8 | data[0];
    
	//读取图片宽度，该数据位于文件的0x12位置，4字节长度  
    lseek(pic_id, 0x12, SEEK_SET);
    read(pic_id, data, 4);
    //数据还原，取决大小端模式，得到图片的宽度
    int width = data[3] << 24 | data[2] << 16 | data[1] << 8 | data[0];
    
	//读取图片高度，紧接着宽度数据后面，4字节长度
    read(pic_id, data, 4);
    //数据还原，取决大小端模式，得到图片的高度
    int height = data[3] << 24 | data[2] << 16 | data[1] << 8 | data[0];
    
	//读取色深，该数据位于文件的0x1C位置，2字节长度
    lseek(pic_id, 0x1c, SEEK_SET);
    read(pic_id, data, 2);
    //数据还原，取决大小端模式，得到图片的色深（每像素的位数）  
    int depth = data[1] << 8 | data[0];
    
	printf("宽度：%d,高度：%d,色深：%d\n", width, height, depth);
    //偏移到像素数组的位置
    lseek(pic_id, offset, SEEK_SET);//定位到像素数组的开始位置  
    
	//计算填充字节数，因为BMP图片的每行像素数据需要是4的倍数，不足的话需要填充  
    int fills = 0;
    
	if ((width * depth / 8) % 4)  //如果每行像素数据的字节数不是4的倍数  
    {  
        fills = 4 - (width * depth / 8) % 4;  //计算需要填充的字节数  
    }  
  
    //实际一行的字节数，包括填充的字节数  
    int real_width = width * depth / 8 + fills;  
  
    //计算出像素数组的大小，即实际一行的字节数乘以图片的高度（绝对值）  
    int pixel_array_size = real_width * abs(height);  
  
    //获取像素数组的数据，malloc分配相应大小的内存空间  
    unsigned char *color_point = malloc(sizeof(char) * pixel_array_size);  
    printf("像素数组大小%d\n", pixel_array_size);  //打印像素数组的大小  
    if (color_point == NULL)  //如果内存分配失败  
    {  
        printf("error !!!!!!!!!!!!!\n");  //打印错误信息  
    }

    read(pic_id, color_point, pixel_array_size);
    //显示图片
    int i = 0;
    for (int h = 0; h < abs(height); h++)
    {
        for (int w = 0; w < width; w++)
        {
            unsigned char a, r, g, b;
            b = color_point[i++];
            g = color_point[i++];
            r = color_point[i++];
            a = depth == 24 ? 0 : color_point[i++];
            //整合颜色
			//将颜色值整合为一个32位的整数，格式为ARGB
            int color = a << 24 | r << 16 | g << 8 | b;
			//在LCD上画一个像素，位置由x和y确定，颜色为上面整合的颜色值
            lcd_draw_pixel(w + posx, ((height < 0) ? h : height - 1 - h) + posy, color);
        }
        // 每一行结束跳过填充字节
        i = i + fills;}//更新到下一个需要绘制的像素的位置，同时考虑了可能的填充字节  
    //释放内存
	free(color_point);
    close(pic_id);
}

//悔棋重新打印该部分的棋盘
//清除指定位置周围的24x24区域内的LCD内容，并将该区域外的位置设置为黑色  
//参数x和y指定了清除的起始位置  
void Display_retract_false(int x, int y)
{
    lcd_init();
    //循环遍历指定区域的每个像素，并清除它们  
    for (int w = x - 24; w < x + 24; w++)
    {
        for (int h = y - 24; h < y + 24; h++)
        {
            lcd_draw_pixel(w, h, 0xa42d00);
        }
    }
    //在指定位置画一个黑色的垂直线
    for (int w = x - 24; w < x + 24; w++)
    {
        lcd_draw_pixel(w, y, 0x000000);
    }
    //在指定位置画一个黑色的水平线 
    for (int h = y - 24; h < y + 24; h++)
    {
        lcd_draw_pixel(x, h, 0x000000);
    }

    close(lcd_fd);
}
//初始化LCD并打印棋盘，然后关闭LCD连接 
void LCD_board_dispaly(void)
{
    //lcd_init();       //LCD初始化
    lcd_draw_board(); //打印棋盘
    //close(lcd_fd);
}
//打印记录版的得分
//根据count的值显示黑方的得分或状态在LCD上 
void LCD_Dispaly_Black_Recording_Board(int count)
{
    if (count == 1)
    {
        Show_pictures(560, 15, "wuziqi_8.bmp");
    }
    else if (count == 2)
    {
        Show_pictures(560, 15, "wuziqi_9.bmp");
    }
    else if (count == 3)
    {
        Show_pictures(560, 15, "wuziqi_10.bmp");
    }
    else if (count == 4)
    {
        Show_pictures(560, 15, "wuziqi_11.bmp");
    }
    else if (count == 5)
    {
        Show_pictures(560, 15, "wuziqi_12.bmp");
    }
}
//根据count的值显示白方的得分或状态在LCD上，与上一个函数类似，但位置不同
void LCD_Dispaly_white_Recording_Board(int count)
{
    if (count == 1)
    {
        Show_pictures(705, 20, "wuziqi_8.bmp");
    }
    else if (count == 2)
    {
        Show_pictures(705, 15, "wuziqi_9.bmp");
    }
    else if (count == 3)
    {
        Show_pictures(705, 15, "wuziqi_10.bmp");
    }
    else if (count == 4)
    {
        Show_pictures(705, 15, "wuziqi_11.bmp");
    }
    else if (count == 5)
    {
        Show_pictures(705, 15, "wuziqi_12.bmp");
    }
}