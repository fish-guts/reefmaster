#ifndef CHANSERV_H_
#define CHANSERV_H_


#include "cs_acc.h"
#include "cs_admin.h"
#include "cs_adminop.h"
#include "cs_akick.h"
#include "cs_xop.h"
#include "cs_drop.h"
#include "cs_getpass.h"
#include "cs_halfop.h"
#include "cs_help.h"
#include "cs_identify.h"
#include "cs_info.h"
#include "cs_invite.h"
#include "cs_list.h"
#include "cs_mdeop.h"
#include "cs_mkick.h"
#include "cs_op.h"
#include "cs_own.h"
#include "cs_register.h"
#include "cs_set.h"
#include "cs_setpass.h"
#include "cs_unban.h"
#include "cs_voice.h"

#define UOP_LIST 1
#define VOP_LIST 2
#define HOP_LIST 3
#define AOP_LIST 4
#define SOP_LIST 5
#define COP_LIST 6
#define QOP_LIST 7
#define SUCCESSOR_ACC 8
#define SUCCESSOR 9
#define FOUNDER_ACC 10
#define FOUNDER  11
#define FULLFOUNDER  12
#define AKICK_LIST 999

#define UOP_STR "Uop"
#define VOP_STR "Vop"
#define HOP_STR "Hop"
#define AOP_STR "Aop"
#define SOP_STR "Sop"
#define COP_STR "Cop"
#define QOP_STR "Qop"
#define SUCCESSOR_STR "Successor"
#define FOUNDER_STR "Founder"

extern op *global_op_list;
extern ChanInfo *chans;



void add_identifiedcs(user *u, char *channel);
void chanserv(char *src,char *av);
void cs_check_successor(char *nick);
int cs_check_opwatch(char *chan,user *u);
void cs_check_topiclock(char *src,channel *cl,char *oldtopic);
extern int cs_connect(int sock);
void cs_drop_nick(char *nick);
char *cs_get_why(user *u,ChanInfo *c);
int cs_isfounder(int nick_id,char *chan);
int cs_isonakicklist(char *mask, char *chan);
int cs_isonlist(char *nick,char *chan,int list, int move);
int cs_issuccessor(int nick_id,char *chan);
void cs_op(char *src, int ac, char **av);
void delete_chan(ChanInfo *c);
ChanInfo *findchan(const char *chan);
ChanInfo *find_chan_by_id(unsigned int id);
char *get_oline(int level);
char *get_opacc(int level);
int isidentifiedcs(user *u, ChanInfo *c);
ChanInfo *register_chan(const char *src,char *name,char *pass,char *desc);
void remove_from_chan_list(char *nick,ChanInfo *c,op *o);
void update_xop_list(op *o);



#endif /*CHANSERV_H_*/
