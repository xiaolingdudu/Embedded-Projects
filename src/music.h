#ifndef __MUSIC_H__
#define __MUSIC_H__

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <linux/input.h>
#include <pthread.h>
#include "touch.h"
#include "play_video.h"
#include "picture.h"
extern int music_i;
extern pthread_t thread_slip, thread_pic, thread_music,thread_eMusic_albums_touch;
void * playmusic(void *arg);
//音乐播放初始化，成功返回0 ，失败返回其他
int MusicInit();
void eMusic_albums(void);
#endif