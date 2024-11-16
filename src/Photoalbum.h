#ifndef _PHOTOALBUM_H_
#define _PHOTOALBUM_H_

#include "bmp.h"
#include "jpeglib.h"
#include "Touch1.h"
#include <dirent.h>

typedef struct photonode{
    char sign[100];          //存储照片信息
    struct photonode *pre;
    struct photonode *next;
}photonode;

typedef struct LIST_photo{
    photonode *first;
    photonode *last;
    int n;          //n记录照片的数量;
}list_photo;

/*
    提供一些文件夹的图片打印在显示屏上作为点击标识
*/
void offer_file_photo();

/*获取某个文件夹中的照片文件*/
void get_photo_file(char *path,list_photo *listphoto);

/*初始化链表头文件*/
list_photo* create_listhead();

/*
    向链表中加入图片的名称信息
    参数：数组首地址，链表头文件
*/
void creative_list(list_photo* listphoto,char *str);

/*
    判断照片为bmp格式还是jpg格式，并打印显示
    参数:   photonode*,文件信息在photonode的sign中;
*/
void judge_bmp_or_jpg(photonode* temp);

#endif
