#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>
#include "console.h"
#include "fun.h"
#include "start_mplayer.h"


long len=0;
int i=0;
char *song=NULL;
const struct LRC *ge=NULL;
char *qie=NULL;
int main(int argc, char const *argv[])
{
    char *msg_done[128] = {NULL};
    LRC *head = NULL;

    

    //读取歌词到堆区空间
    char *ret=geci(song,&len);
    //切割
    int qie=qiege(ret,i,msg_done);

    //定义结构体，逐行解析歌词
    head=jiexi(qie,msg_done);

    //遍历链表
    //printf("aaa%p\n",head);
    //bianli(head);


    //打开文件
    mplayer_play("./简单爱.mp3");


    //生成时钟
    shizhong(head);
   
    return 0;
}

