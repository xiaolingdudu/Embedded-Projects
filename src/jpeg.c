#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "jpeglib.h"
#include "bmp.h"
/*
    功能: 
        进行jpeg图片的显示
    参数:
        需要进行显示的jpeg图片的路径
*/
int lcd_draw_jpeg(int x0,int y0,char* jpeg_name)
{
	/*
	１.　分配并初始化一个jpeg解压对象
	*/
	struct jpeg_decompress_struct dinfo; //定义了一个jpeg的解压对象
	
	struct jpeg_error_mgr jerr; //定义一个错误变量
	dinfo.err = jpeg_std_error(&jerr);
		
	jpeg_create_decompress(&dinfo); //初始化这个解压对象

	/*
	2. 指定要解压缩的图像文件
	
	*/
	FILE *infile;
	infile = fopen(jpeg_name, "r");
	if (infile == NULL)
	{
		perror("fopen error");
		return -1;
	}

	jpeg_stdio_src(&dinfo, infile); //为解压对象dinfo指定要解压的文件

	/*
	3. 调用jpeg_read_header()获取图像信息

	*/
	jpeg_read_header(&dinfo, TRUE);

	/*
	4. 设置jpeg解压缩对象dinfo的一些参数，可采用默认参数
	*/


	/*
	5.调用jpeg_start_decompress()启动解压过程
	jpeg_start_decompress(&dinfo); 
	调用jpeg_start_decompress(&dinfo);函数之后，JPEG解压对象dinfo中下面这几个成员变量
	将会比较有用：
	output_width:  图像的输出宽度
	output_height：　图像的输出高度
	output_component：　每个像素的分量数，也即字节数，3/4字节
		在调用jpeg_start_decompress(&dinfo); 之后往往需要为解压后的扫描线上的所有像素点分配存储空间，
	output_width * output_components(一行的字节数，output_height行)

	*/

	jpeg_start_decompress(&dinfo); 


	unsigned char *buffer = malloc(dinfo.output_width * dinfo.output_components);

	/*
	６.　读取一行或者多行扫描线数据并处理，通常的代码是这样的：
	
	//output_scanline表示扫描的总行数
	//output_height表示图像的总行数
	while (dinfo.output_scanline < dinfo.output_height)
	{
		jpeg_read_scanlines(&dinfo, &buffer, 1);

		//deal with scanlines . RGB/ARGB
	}
	*/

	//output_scanline表示扫描的总行数
	//output_height表示图像的总行数
	while (dinfo.output_scanline < dinfo.output_height)
	{
		jpeg_read_scanlines(&dinfo, &buffer, 1); //dinfo.output_scanline + 1

		//deal with scanlines . RGB/ARGB
		int x; //一行的像素点数量

		char *p = buffer;
		for (x = 0; x < dinfo.output_width; x++)
		{
			unsigned char r, g, b, a = 0;
			int color;
			if (dinfo.output_components == 3)
			{
				r = *p++;
				g = *p++;
				b = *p++;
			} else if (dinfo.output_components == 4)
			{
				a = *p++;
				r = *p++;
				g = *p++;
				b = *p++;
			}
			color = (a << 24) | (r << 16) | (g << 8) |(b) ;

			//LCD_DrawPoint(x, dinfo.output_scanline - 1 ,  color); 
			int m=x0+x;
			int n=y0+dinfo.output_scanline - 1;
            //lcd_draw_point(x, dinfo.output_scanline - 1, color);
			lcd_draw_point(m, n, color);
		}
	}

	/*
	7. 调用　jpeg_finish_decompress()完成解压过程
	*/
	jpeg_finish_decompress(&dinfo);



	/*
	８.调用jpeg_destroy_decompress()释放jpeg解压对象dinfo
	jpeg_destroy_decompress(&dinfo);
	
	
	*/
	jpeg_destroy_decompress(&dinfo);
	free(buffer);
	fclose(infile);

	return 0;
}
