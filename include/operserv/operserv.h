#ifndef OPERSERV_H_
#define OPERSERV_H_

#include "os_akill.h"
#include "os_chatops.h"
#include "os_chghost.h"
#include "os_global.h"
#include "os_help.h"
#include "os_kill.h"
#include "os_local.h"
#include "os_oper.h"
#include "os_sgline.h"
#include "os_skline.h"
#include "os_sqline.h"
#include "os_szline.h"

extern operuser *opers;
extern akill *akills;

void delete_oper(char *nick);
operuser *findoper(const char *src);
extern int os_connect(int sock);
void announce_oper(char *oper,int lvl);
void operserv(char *src, char *av);

#endif /*OPERSERV_H_*/
