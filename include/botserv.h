#ifndef BOTSERV_H_
#define BOTSERV_H_


#include "bs_add.h"
#include "bs_del.h"


extern bot *botlist;

void add_bot_to_chan(char *botname, char *chan);
void botserv(char *src, char *av);
extern int bs_connect(int sock);
void connect_bot(char *botname);
void delete_bot(char *botname);
void disconnect_bot(char *botname);
bot *findbot(const char *botname);
bot *findbot_onchan(char *botname,char *chan);
bot *get_botlist(void);
bot *register_bot(char *botname,char *password);
void remove_bot_from_chan(char *botname, char *chan);


#endif /*BOTSERV_H_*/
