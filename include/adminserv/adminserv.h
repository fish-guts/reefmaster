#ifndef ADMINSERV_H_
#define ADMINSERV_H_

extern int as_connect(int sock);
void as_savedata(char *src,int ac,char **av);
void adminserv(char *src, char *av);

#endif /*ADMINSERV_H_*/
