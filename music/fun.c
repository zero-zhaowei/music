#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "fun.h"
#include "console.h"
int shizhong(LRC *pb)
{

    clear_screen();
    int time = 0;
    
    cusor_hide();
    cusor_moveto(30, 4);
    printf("简单爱");

    set_fg_color(COLOR_RED);
    cusor_moveto(25, 8);
    printf("%*s", -50, pb->lrc);

    cusor_moveto(25, 10);
    printf("%*s", -50, pb->next->lrc);

    cusor_moveto(25, 12);
    set_fg_color(COLOR_BLUE);
    printf("%*s", -50, pb->next->next->lrc);

    set_fg_color(COLOR_RED);
    cusor_moveto(25, 14);
    printf("%*s", -50, pb->next->next->next->lrc);

    cusor_moveto(25, 16);
    printf("%*s", -50, pb->next->next->next->next->lrc);



    //set_bg_color(COLOR_GREEN);
    while (pb!= NULL)
    {
        cusor_moveto(30, 2);
        printf("%02d:%02d ", time / 60, time % 60);

        if (time == pb->next->next->time)
        {
            // clear_screen();
            fflush(stdout);

            set_fg_color(COLOR_RED);
            cusor_moveto(25, 8);
            printf("%*s", -50, pb->lrc);

            cusor_moveto(25, 10);
            printf("%*s", -50, pb->next->lrc);

            cusor_moveto(25, 12);
            set_fg_color(COLOR_BLUE);
            printf("%*s", -50, pb->next->next->lrc);

            set_fg_color(COLOR_RED);
            cusor_moveto(25, 14);
            printf("%*s", -50, pb->next->next->next->lrc);

            cusor_moveto(25, 16);
            printf("%*s", -50, pb->next->next->next->next->lrc);

            pb = pb->next;

        }

        sleep(1);

        time++;
    }
    free(pb);
    pb = NULL;
    return 0;
}

//对前四行解析

// void printfour(char *str)
// {

//    int i=0;
//     char buf[4][128];
//     while (i<4)
//    {
//     sscanf(str[i],"%*4s %s",buf[i]);
//     printf("%s\n",buf[i]);
//     i++;
//    }

//     return;
// }

//从文件提取歌词首地址
char *geci(char *song, long *len)
{
    FILE *fp = fopen("简单爱.lrc", "r+");
    fseek(fp, 0, 2);
    *len = ftell(fp);
    // printf("len=%ld\n", *len);
    song = (char *)calloc(1, *len + 1);
    rewind(fp);
    fread(song, *len, 1, fp);
    //  printf("file=%s\n", song);
    fclose(fp);
    return song;
}

//切割歌词
int qiege(char *p, int i, char **msg_done)
{

    char *msg_str = p;

    i = 0;
    msg_done[i] = strtok(msg_str, "\r\n");
    while (msg_done[i] != NULL)
    {
        i++;
        msg_done[i] = strtok(NULL, "\r\n");
    }
    i = 0;
    //printf("进入切割\n");
    while (msg_done[i] != NULL)
    {

        //  printf("%s\n", msg_done[i]);
        i++;
    }

    return i - 1;
}

//解析

LRC *jiexi(int row, char **lrc)
{

    int i = 0;
    LRC *head = NULL;

    for (i = 4; i < row; i++)
    {
        char *p_lrc = lrc[i];
        while (*p_lrc == '[')
        {
            p_lrc += 10;
        }

        char *ps = lrc[i];
        while (*ps == '[')
        {
            int m = 0, s = 0;
            sscanf(ps, "[%d:%d", &m, &s);

            LRC tmp;
            tmp.time = m * 60 + s;
            strcpy(tmp.lrc, p_lrc);

            head = insert_link(head, tmp);
            //printf("head 的地址%p",head);
            ps += 10;
        }
    }
    return head;
}

//有序插入
LRC *insert_link(LRC *head, LRC tmp)
{
    LRC *pi = (LRC *)calloc(1, sizeof(LRC));

    *pi = tmp;
    pi->next = NULL;
    if (head == NULL)
    {
        head = pi;
        return head;
    }
    else
    {
        //寻找插入点的位置
        LRC *pf = head, *pb = head;
        while ((pb->time < pi->time) && (pb->next != NULL))
        {
            pf = pb;
            pb = pb->next;
        }
        //判断插入点的位置(前 中 尾)
        if (pb->time >= pi->time)
        {
            if (pb == head) //前
            {
                pi->next = head;
                head = pi;
            }
            else
            {
                pf->next = pi;
                pi->next = pb;
            }
        }
        else if (pb->next == NULL) //尾部
        {
            pb->next = pi;
        }
    }
    return head;
}

//链表的遍历
void bianli(const LRC *head)
{
    if (head == NULL)
    {
        return;
    }
    else
    {
        const LRC *pb = head;
        while (pb != NULL)
        {
            printf("%d %s\n", pb->time, pb->lrc);
            pb = pb->next;
        }
    }
}