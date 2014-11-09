#ifndef IRC_H_
#define IRC_H_

void ban(char *src,char *target,char *chan);
void chatops(char *src,char *msg,...);
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
void hop(char *src,char *target,char *chan);
void invite(char *src,char *target,char *chan);
void kick(char *src,char *target,char *chan,char *reason);
void mode(const char *src,char *target,char *modes,char *chan);
void notice(const char *src,char *dest,char *msg, ...);
void pong(void);
void quit(char *nick);
void s_kill(const char *src,char *dest,char *reason);
void s_send(char *cmd, ...);
void svs2mode(const char *src,char *target,char *modes,char *chan);
void svsmode(const char *src,char *target,char *modes,char *chan);
void svsnick(char *src,char *newnick,time_t t);
void voice(char *src,char *target,char *chan);
void wallops(char *src,char *msg,...);


#endif /*IRC_H_*/
