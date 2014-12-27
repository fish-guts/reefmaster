#ifndef OPERSERV_H_
#define OPERSERV_H_

#include "os_oper.h"


extern operuser *opers;

void delete_oper(char *nick);
operuser *findoper(const char *src);
extern int os_connect(int sock);
void announce_oper(char *oper,int lvl);
void operserv(char *src, char *av);

#endif /*OPERSERV_H_*/
