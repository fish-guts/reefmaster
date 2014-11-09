#ifndef BOTSERV_H_
#define BOTSERV_H_

extern bot *botlist;

void bot_add_chan(bot *b,char *chan);
void bot_del_chan(bot *b,char *chan);
void botserv(char *src, char *av);
void bs_add(char *src,int ac,char **av);
extern int bs_connect(int sock);
bot *findbot(const char *botname);
bot *findbot_onchan(char *chan);
bot *register_bot(char *botname,char *password);
void connect_bot(char *botname);

#endif /*BOTSERV_H_*/
