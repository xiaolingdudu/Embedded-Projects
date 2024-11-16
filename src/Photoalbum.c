#include "Photoalbum.h"
/*
    提供一些文件夹的图片打印在显示屏上作为点击标识
*/
void offer_file_photo()
{
    char *str[10]={"album1.bmp","album2.bmp","album3.bmp","album4.bmp"};
    int x=0,y=0;
    for(int i=0;i<10;i++)
    {
        if(str[i] != NULL)
        {
            lcd_draw_bmp(x,y,str[i]);   //将代表文件夹的图片显示在屏幕上
            x=x+100;
            if(x>799)
            {
                x=0;
                y=y+60;
            }
        }
        else
            break;
    }
    lcd_draw_bmp(700,420,"quit.bmp");   //退出程序键
}

/*初始化链表头文件*/
list_photo* create_listhead()
{
    list_photo *listphoto=malloc(sizeof(list_photo));
    listphoto->first==NULL;
    listphoto->last==NULL;
    listphoto->n=0;
}

/*
    向链表中加入图片的名称信息
    参数：数组首地址，链表头文件
*/
void creative_list(list_photo* listphoto,char *str)
{
    photonode *new=malloc(sizeof(photonode));
    new->next=NULL;
    new->pre=NULL;
    strcpy(new->sign,str);

    if(listphoto->first==NULL)
    {
        listphoto->first=new;
        listphoto->last=new;
        new->next=listphoto->last;
        new->pre=listphoto->first;
    }
    else
    {
        listphoto->last->next=NULL;
        listphoto->first->pre=NULL;
        listphoto->last->next=new;
        new->pre=listphoto->last;
        new->next=listphoto->first;
        listphoto->first->pre=new;
        listphoto->last=new;
    }
    listphoto->n++;
}



/*获取某个文件夹中的照片文件*/
void get_photo_file(char *path,list_photo* listphoto)
{
    DIR *dir =opendir(path);
    if(dir==NULL)
    {
        perror("opendir error");
        exit(1);
    }
    struct dirent *dirp=NULL;
    while(dirp = readdir(dir))  //读取文件夹中的文件
    {
        struct stat st; //文件属性信息结构体
        char filename[100]={0};  //合成文件的相对路径
        sprintf(filename,"%s/%s",path,dirp->d_name);
        //获取文件信息
        int ret = lstat(filename,&st);
        if(ret==-1)
        {
            perror("lstat error");
            exit(1);
        }
        //如果是普通文件
        if(S_ISREG(st.st_mode))
        {
            char temp[100]={0};
            strcpy(temp,dirp->d_name);
            //如果是bmp文件或者jpg文件，将其写入链表
            if(strcmp( temp+strlen(dirp->d_name)-4,".bmp") == 0 || strcmp( temp+strlen(dirp->d_name)-4,".jpg") == 0)
                creative_list(listphoto,filename);
        }
        else if(S_ISDIR(st.st_mode))    //如果是目录文件
        {
            if(strcmp(dirp->d_name,".")!=0 && strcmp(dirp->d_name,"..")!=0)
            {
                get_photo_file(filename,listphoto); //递归
            }
        }
    }
}

/*
    判断照片为bmp格式还是jpg格式，并打印显示
    参数:   photonode*,文件信息在photonode的sign中;
*/
void judge_bmp_or_jpg(photonode* temp)
{
    char temp0[100]={0};
    strcpy(temp0,temp->sign);
    //printf("-----%d------\n",__LINE__);
    if(strcmp( temp0+strlen(temp->sign)-4,".bmp") == 0)
    {
        lcd_draw_bmp(0,0,temp->sign);
        //printf("-----%d------\n",__LINE__);
    }
    else if(strcmp( temp0+strlen(temp->sign)-4,".jpg") == 0)
    {
        lcd_draw_jpeg(0,0,temp->sign);
        //printf("-----%d------\n",__LINE__);
    }
    
}