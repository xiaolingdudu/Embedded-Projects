#include "music.h"

pthread_t thread_slip, thread_pic, thread_music,thread_eMusic_albums_touch;
int music_i = 1;


//开一个线程去播放音乐
void * playmusic(void *arg)
{
    //让其分离
    pthread_detach(pthread_self());

    char music_buf[128] = {0};
    while(1)
    {
        system("killall -9 madplay");//保证别的madplay死掉
        sprintf(music_buf,"madplay -Q %d.MP3",music_i);
        printf("%s\n",music_buf);
        system(music_buf);
        sleep(1);
        //music_i++;
        //if(music_i > 2)
            //music_i = 1;
    }

}
//音乐播放初始化，成功返回0 ，失败返回其他
int MusicInit()
{
    pthread_t thread;
    if(pthread_create(&thread,NULL,playmusic,NULL) != 0)
    {
        perror("play music error");
        return -2;
    }
    return 0;
}

void eMusic_albums(void)
{
    	/* 电子相册 */

	if (pthread_create(&thread_music,NULL,playmusic,NULL) != 0)
	{
		perror("PlayMusic_task create fail");
		return ;
	}
	if (pthread_create(&thread_slip,NULL,GetState,NULL) != 0)
	{
		perror("GetState_task create fail");
		return ;
	}
	// if (pthread_create(&thread_pic,NULL,ShowPicture,NULL) != 0)
	// {
	// 	perror("ShowPicture_task create fail");
	// 	return ;
	// }
    // if (pthread_create(&thread_eMusic_albums_touch,NULL,eMusic_albums_touch,NULL) != 0)
	// {
	// 	perror("thread_eMusic_albums_touch create fail");
	// 	return ;
	// }
    int exit_flag = 0;
    while (1)
    {
        exit_flag = ShowPicture();
        if (exit_flag==1)
        {
            exit_flag=0;
            system("killall madplay");
            return ;
        }
    }
    
}