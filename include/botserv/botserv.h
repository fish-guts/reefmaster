#ifndef BOTSERV_H_
#define BOTSERV_H_


#include "bs_add.h"
#include "bs_del.h"
#include "bs_dehalfop.h"
#include "bs_deop.h"
#include "bs_devoice.h"
#include "bs_getpass.h"
#include "bs_help.h"
#include "bs_identify.h"
#include "bs_info.h"
#include "bs_kick.h"
#include "bs_list.h"
#include "bs_msg.h"
#include "bs_op.h"
#include "bs_set.h"


extern bot *botlist;

void add_bot_to_chan(char *botname, char *chan);
void botserv(char *src, char *av);
extern int bs_connect(int sock);
void connect_bot(char *botname);
void connect_bots(void);
void delete_bot(char *botname);
void disconnect_bot(char *botname);
bot *findbot(const char *botname);
bot *findbot_onchan(char *botname,char *chan);
void load_bot(int id,char *botname, char *password, char *username, char *realname);
bot *register_bot(char *botname,char *password);
void remove_bot_from_chan(char *botname, char *chan);
bot *find_bot_by_id(unsigned int id);


#endif /*BOTSERV_H_*/
