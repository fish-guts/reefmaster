#ifndef IRC_H_
#define IRC_H_

void addserverban(char type,char *user,char *host,char *reason,int timestamp);
void ban(char *src,const char *target,char *chan);
void chatops(char *src,char *msg,...);
int check_valid_nickname(char *nick);
void deadmin(char *src,char *target,char *chan);
void dehop(char *src,char *target,char *chan);
void deop(char *src,char *target,char *chan);
void deowner(char *src,char *target,char *chan);
void devoice(char *src,char *target,char *chan);
void do_admin(char *src,char *target,char *chan);
void do_join(char *src,char *chan);
void do_op(char *src,char *target,char *chan);
void do_owner(char *src,char *target,char *chan);
void do_part(char *src,char *chan,char *msg);
void gline(char *user,char *host,char *reason,int timestamp);
void globops(char *src,char *msg,...);
void hop(char *src,char *target,char *chan);
void invite(char *src,char *target,char *chan);
void kick(char *src,const char *target,char *chan,char *reason);
void kline(char *user,char *host,char *reason,int time);
void mode(const char *src,const char *target,char *modes,char *chan);
void notice(const char *src,char *dest,char *msg, ...);
void pong(void);
void quit(char *nick);
void s_kill(const char *src,char *dest,char *reason);
void s_send(char *cmd, ...);
void svs2mode(const char *src,char *target,char *modes,char *chan);
void svsmode(const char *src,char *target,char *modes,char *chan);
void svsnick(char *src,char *newnick,time_t t);
void topic(char *src, char *chan,char *nick,time_t timestamp,char *topic);
void voice(char *src,char *target,char *chan);
void wallops(char *src,char *msg,...);
void zline(char *user, char *host, char *reason, int timestamp);

#endif /*IRC_H_*/
