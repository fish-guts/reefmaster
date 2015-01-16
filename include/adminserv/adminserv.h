#ifndef ADMINSERV_H_
#define ADMINSERV_H_

#include "as_savedata.h"
#include "as_squit.h"


extern int as_connect(int sock);
void as_savedata(char *src,int ac,char **av);
void adminserv(char *src, char *av);

#endif /*ADMINSERV_H_*/
