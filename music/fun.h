
#pragma once
typedef struct lrc{
    int time;
    char lrc[256];

    struct lrc *next;
}LRC;

extern int shizhong();
extern char *geci(char *song ,long *len);
extern int qiege(char *p, int i, char **msg_done);
extern void mplayer_play(char * song_path);
extern LRC *insert_link(LRC *head,LRC tmp);
extern LRC *jiexi(int row, char **lrc );
//extern void printfour(char **str);