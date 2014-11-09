#ifndef CHANNEL_H_
#define CHANNEL_H_

#include "struct.h"

void add_status(channel *c,user *u,int status);
void chan_delete(channel *c);
void check_status(channel *c,user *u);
void del_status(channel *c,user *u,int status);
void del_user(user *u,channel *c);

channel *findchannel(const char *chan);
void s_join(char *src, int ac, char **av);
void s_part(char *src, int ac, char **av);
int ison(channel *c, user *u);
int isop(channel *c,user *u);

#endif /*CHANNEL_H_*/
