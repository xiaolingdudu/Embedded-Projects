#include "camera.h"
#include "picture.h"
typedef struct
{
    char *start;
    size_t length;
} buffer_t;

buffer_t buffer[4]; // 映射所需的素材缓存在数组中
buffer_t current;   // 保存当前输出的一帧

//int *plcd;  // 用于存储屏幕缓冲区的首地址,以便后续对屏幕进行读写操作
int *lcd_p; // 指向屏幕缓冲区的特定位置
int lcd_fd; // 用于存储屏幕设备文件的文件描述符

void *lcd_init()
{
    lcd_fd = open("/dev/fb0", O_RDWR);
    if (lcd_fd == -1)
    {
        perror("open lcd_file error\n");
        return MAP_FAILED;
    }
    plcd = (int *)mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, lcd_fd, 0);
    return plcd;
}

int uninit_lcd()
{
    close(lcd_fd);
    if (munmap(lcd_p, 800 * 480 * 4) == -1)
    {
        return -1;
    }
    return 0;
}

unsigned int sign3 = 0;
//YUYV转rgb
int yuyv2rgb(int y, int u, int v)
{
    unsigned int pixel24 = 0;
    unsigned char *pixel = (unsigned char *)&pixel24;
    int r, g, b;
    static int ruv, guv, buv;
    if (sign3)
    {
        sign3 = 0;
        ruv = 1159 * (v - 128);
        guv = 380 * (u - 128) + 813 * (v - 128);
        buv = 2018 * (u - 128);
    }
    r = (1164 * (y - 16) + ruv) / 1000;
    g = (1164 * (y - 16) - guv) / 1000;
    b = (1164 * (y - 16) + buv) / 1000;
    if (r > 255)
        r = 255;
    if (g > 255)
        g = 255;
    if (b > 255)
        b = 255;
    if (r < 0)
        r = 0;
    if (g < 0)
        g = 0;
    if (b < 0)
        b = 0;
    pixel[0] = r;
    pixel[1] = g;
    pixel[2] = b;
    return pixel24;
}

//YUYV转rgb（调用yuyv2rgb函数）
int yuyv2rgb0(unsigned char *yuv, unsigned char *rgb, unsigned int width, unsigned int height)
{
    unsigned int in, out;
    int y0, u, y1, v;
    unsigned int pixel24;
    unsigned char *pixel = (unsigned char *)&pixel24;
    unsigned int size = width * height * 2;
    for (in = 0, out = 0; in < size; in += 4, out += 6)
    {
        y0 = yuv[in + 0];
        u = yuv[in + 1];
        y1 = yuv[in + 2];
        v = yuv[in + 3];
        sign3 = 1;
        pixel24 = yuyv2rgb(y0, u, v);
        rgb[out + 0] = pixel[0];
        rgb[out + 1] = pixel[1];
        rgb[out + 2] = pixel[2];
        pixel24 = yuyv2rgb(y1, u, v);
        rgb[out + 3] = pixel[0];
        rgb[out + 4] = pixel[1];
        rgb[out + 5] = pixel[2];
    }
    return 0;
}


int camera_flag=0;

//**********camera主函数***************//
void camera_Run()
{
    lcd_init();
    display_bgm(0x00000000);
    // 打开摄像头
    int fd_v4l2 = open("/dev/video7", O_RDWR);
    if (fd_v4l2 == -1)
    {
        perror("open error");
        exit(-1);
    }
    // 获取功能参数
    struct v4l2_capability cap = {};
    int res = ioctl(fd_v4l2, VIDIOC_QUERYCAP, &cap);
    if (res == -1)
    {
        perror("ioctl cap");
        exit(-1);
    }
    // 先确定摄像头功能可以使用
    if (cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)
    {
        printf("is a capture device!\n");
    }
    else
    {
        printf("is not a capture device!\n");
        exit(-1);
    }
    // 获取摄像头支持的格式
    struct v4l2_fmtdesc fmt = {};
    fmt.index = 0;
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE; // 获取摄像头格式
    while ((res = ioctl(fd_v4l2, VIDIOC_ENUM_FMT, &fmt)) == 0)
    {
        printf("pixformat = %c %c %c %c,description = %s\n",
                fmt.pixelformat & 0xff,
                (fmt.pixelformat >> 8) & 0xff,
                (fmt.pixelformat >> 16) & 0xff,
                (fmt.pixelformat >> 24) & 0xff,
                fmt.description);
        fmt.index++;
    }
    // 设置采集通道
    int index = 0; // 使用通道0
    res = ioctl(fd_v4l2, VIDIOC_S_INPUT, &index);
    if (res == -1)
    {
        perror("ioctl_s_input");
        exit(-1);
    }
    // 设置摄像头采集格式
    struct v4l2_format format = {};
    format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    format.fmt.pix.width =800;//640
    format.fmt.pix.height = 480;
    format.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV; // YUYV
    format.fmt.pix.field = V4L2_FIELD_NONE;
    res = ioctl(fd_v4l2, VIDIOC_S_FMT, &format);
    if (res == -1)
    {
        perror("ioctl s_fmt");
        exit(-1);
    }
    // 申请缓存空间
    struct v4l2_requestbuffers req = {};
    req.count = 4;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;
    res = ioctl(fd_v4l2, VIDIOC_REQBUFS, &req);
    if (res == -1)
    {
        perror("ioctl reqbufs");
        exit(-1);
    }
    // 分配映射入队
    size_t i, max_len = 0;
    for (i = 0; i < 4; i++)
    {
        struct v4l2_buffer buf = {};
        buf.index = i; // 0~3展现4帧图片
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        res = ioctl(fd_v4l2, VIDIOC_QUERYBUF, &buf);
        if (res == -1)
        {
            perror("ioctl querybuf");
            exit(-1);
        }
        // 判读并记录最大长度，以适配各个图帧
        if (buf.length > max_len)
            max_len = buf.length;
        // 映射
        buffer[i].length = buf.length;
        buffer[i].start = mmap(NULL, buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, fd_v4l2, buf.m.offset);
        if (buffer[i].start == MAP_FAILED)
        {
            perror("mmap");
            exit(-1);
        }
        // 入队
        res = ioctl(fd_v4l2, VIDIOC_QBUF, &buf);
        if (res == -1)
        {
            perror("ioctl qbuf");
            exit(-1);
        }
    }
    // 申请临时缓冲区
    current.start = malloc(max_len);
    if (current.start == NULL)
    {
        perror("malloc");
        exit(-1);
    }
    // 启动摄像头
    enum v4l2_buf_type buf_type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    res = ioctl(fd_v4l2, VIDIOC_STREAMON, &buf_type);
    if (res == -1)
    {
        perror("ioctl streamon");
        exit(-1);
    }
    // 延时
    sleep(1);
    // RGB缓冲区
    char rgb[640 * 480 * 3];
    
    pthread_t thread_camera_touch;
    if (pthread_create(&thread_camera_touch,NULL,camera_touch,NULL) != 0)
	{
		perror("camera_touch_task create fail");
		return ;
	}
    // 采集数据
    while (1)
    {   
        printf("%d\n",camera_flag);

        if(camera_flag==0)
        {
        struct v4l2_buffer buf = {};
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        // 出队
        res = ioctl(fd_v4l2, VIDIOC_DQBUF, &buf);
        if (res == -1)
        {
            perror("ioctl dqbuf");
        }
        // 拷贝数据
        memcpy(current.start, buffer[buf.index].start, buf.bytesused);
        current.length = buf.bytesused;
        // 入队
        res = ioctl(fd_v4l2, VIDIOC_QBUF, &buf);
        if (res == -1)
        {
            perror("ioctl qbuf");
        }
        // YUYV转RGB
        yuyv2rgb0(current.start, rgb, 640, 480);
        // 显示LCD
        int x, y;
        for (y = 0; y < 480; y++)
        {
            for (x = 0; x < 640; x++)
            {
                point(x,y,rgb[3 * (y*640 + x)] << 16 | rgb[3 * (y*640 + x) + 1] << 8 | rgb[3 * (y*640 + x) + 2]);
                //*(plcd + y*800 + x) = rgb[3 * (y*640 + x)] << 16 | rgb[3 * (y*640 + x) + 1] << 8 | rgb[3 * (y*640 + x) + 2];
            }
        }
        }
        else
        {
            camera_flag=0;
            pthread_cancel(thread_camera_touch);
            //printf("123\n");
            break;
        }
    }
    
    // 关闭摄像头采集
    buf_type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    res = ioctl(fd_v4l2, VIDIOC_STREAMOFF, &buf_type);
    if (res == -1)
    {
        perror("ioctl streamoff");
        exit(-1);
    }
    // 解除映射
    for (i = 0; i < 4; i++)
    {
        munmap(buffer[i].start, buffer[i].length);
    }
    free(current.start);
    sleep(1); // 延时一下
    close(fd_v4l2);
    //uninit_lcd();
}

