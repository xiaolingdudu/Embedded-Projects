#ifndef __PLAY_VIDEO_H__
#define __PLAY_VIDEO_H__

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <linux/input.h>
#include "picture.h"
#include "touch.h"
#include "music.h"
void InitVideo(void);
void VideoRun();
void *PlayVideo(void *argv);

#endif