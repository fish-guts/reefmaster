#ifndef CHANNEL_H_
#define CHANNEL_H_

#include "struct.h"

void add_bot(char *chan, char *bot);
void add_status(channel *c,user *u,int status);
int is_bot_on_chan(char *botname,char *chan);
void chan_delete(channel *c);
void channel_add_ban(char *src,channel *c, char *mask);
void channel_remove_ban(char *src,channel *c, char *mask);
void check_status(channel *c,user *u);
void del_status(channel *c,user *u,int status);
void del_user(user *u,channel *c);
void del_bot(char *chan);
channel *findchannel(const char *chan);
void s_join(char *src, int ac, char **av);
void s_part(char *src, int ac, char **av);
int ison(channel *c, user *u);
int isop(channel *c,user *u);

#endif /*CHANNEL_H_*/
