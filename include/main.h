#ifndef MAIN_H_
#define MAIN_H_

#include "sqlite.h"


#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <wait.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <setjmp.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <regex.h>



#include "serverprotocol.h"
#include "channel.h"
#include "chanserv/chanserv.h"
#include "commands.h"
#include "config.h"
#include "database.h"
#include "functions.h"
#include "help.h"
#include "irc.h"
#include "log.h"
#include "constants.h"
#include "nickserv/nickserv.h"
#include "operserv/operserv.h"
#include "sock.h"
#include "user.h"
#include "botserv/botserv.h"
#include "adminserv/adminserv.h"

/* global vars */ 
int mainsock;
char inick[64];
time_t last_check;

/* Function prototypes */

void print_msg(char *msg, ...);
int  load_app(void);
void start_app(void);
void print_welcome_msg(void);
void create_files(void);

/* Definitions */

#define LOAD_OK 0
#define ERRCODE_0 0x900A001
#define ERRCODE_1 0x900A002
#define CMD_ARR_SIZE 5
#define IRCSERVER s_name;
#define IRCBUF_SIZE 100000
#define TO_COLLIDE	0
#define TO_RELEASE	1
#define TO_COLLIDE_TL 2
#define CONFIG_OK 0
#define CONFIG_FAIL -2
#define CONFIG_COK -1
#define STRMAX 33
#define STRMAX2 64
#define STRMAX3 128

#define UOP			0x0001
#define OP			0x0002
#define VOP			0x0004
#define HOP			0x0008
#define AOP			0x0016
#define ADMIN		0x0032
#define OWNER		0x0064



#define IDENTIFIED	0x0001
#define HASACCESS	0x0002

#define DEBUG 1
#define ERROR 2
#define WARN 3

#define NICK_ACCESS 	1
#define NICK_IDENTIFIED 2
#define NICK_OPER		3

#define CHAN_IDENTIFIED 1

#define REG_NO_PROTECT 		1
#define REG_NORMAL_PROTECT 	2
#define REG_HIGH_PROTECT 	3

#define AUTH_NOTIFY	0
#define AUTH_UOP	1
#define AUTH_VOP	2
#define AUTH_HOP	3
#define AUTH_AOP	4
#define AUTH_SOP	5
#define AUTH_SUCC	6
#define AUTH_FOUND	7

#define ACCESS_UOP		1
#define ACCESS_VOP		2
#define ACCESS_HOP		3
#define ACCESS_AOP		4
#define ACCESS_SOP		5
#define ACCESS_SUC  	6
#define ACCESS_FND		7
#define ACCESS_FND_FULL	8
#define ACCESS_SRA		9

#define NOTIFY_ONLINE 2
#define NOTIFY_OFFLINE 4


/* database Files */

#define CONFIG_FILE 	"services.conf"
#define DB				"db/services.db"

/* service status flags */

int ns_status;
int cs_status;
int bs_status;
int os_status;
int as_status;

/* other things */

time_t next_save;
int save_interval;

/* These are the variables set by the config file */

/* Block "services" */
char *s_address;
char *s_cycle_message;
char *s_description;
int   s_flag;
char *s__host;
int   s_keeplogfiles;
char *s_log;
char *s_motd;
char *s_name;
int   s_PassAction;
int   s_PassLimit;
int   s_PassTimeout;
char *s_password;
char *s_pid;
int   s_port;
int   s_StrictPassword;
char *s_unreal;
char *s_user;

/* Block "nickserv" */
int   ns_admin;
int   ns_delay;
int   ns_enabled;	
int   ns_expiry;
char *ns_name;
char *ns_realname;
int   ns_autoaccess;
int   ns_usage_access;
int   ns_sendmemo;
int   ns_maxlist;
int   ns_operonly;
int   ns_access_max;
int   ns_spass;
int   ns_gpass; 
char *ns_enforcer;
int   ns_release_time;
int	  ns_noop;
int   ns_high_protect;
int   ns_hide_email; 
int   ns_no_memo; 
int   ns_auth_channel; 
int   ns_auth_notify; 
int   ns_mnotify;
char *ns_mlock;

/* Block "chanserv" */
int   cs_admin_access;
int   cs_akick_add;
int   cs_akick_del;
int   cs_akick_list;
int   cs_akick_wipe;
int   cs_aop_add;
int   cs_aop_del;
int   cs_aop_list;
int   cs_aop_wipe;
int   cs_hop_add;
int   cs_hop_del;
int   cs_hop_list;
int   cs_hop_wipe;
int   cs_vop_add;
int   cs_vop_del;
int   cs_vop_list;
int   cs_vop_wipe;
int   cs_uop_add;
int   cs_uop_del;
int   cs_uop_list;
int   cs_uop_wipe;
int   cs_enabled;
char *cs_name; 
char *cs_realname;
int   cs_delay; 
int   cs_sops_max; 
int   cs_aops_max;
int   cs_hops_max; 
int   cs_vops_max; 
int   cs_uops_max; 
int   cs_akicks_max;
int   cs_sop_add;
int   cs_sop_del;
int   cs_sop_list;
int   cs_sop_wipe;
int   cs_maxlist;
int   cs_regaccess; 
int   cs_operonly; 
int   cs_spass; 
int   cs_gpass;
int   cs_mkick_access;
int   cs_mdeop_access;
int   cs_memolevel;
int   cs_autovop;
char *cs_mlock;
int   cs_opwatch; 
int   cs_keeptopic; 
int   cs_leaveops; 
int   cs_secret; 
int   cs_restricted; 
int   cs_topiclock; 
int   cs_private; 
int   cs_cmd_op;
int   cs_cmd_kick;
int   cs_cmd_ban;
int   cs_cmd_invite;
int   cs_cmd_mkick;


int   cs_set_opwatch_access;
int   cs_set_leaveops_access;
int   cs_set_keeptopic_access;
int   cs_set_topiclock_access;
int   cs_set_restricted_access;
int   cs_set_memolevel_access;
int   cs_set_desc_access;
int   cs_set_password_access;
int   cs_set_successor_access;
int   cs_set_founder_access;
int   cs_set_bot_access;
int   cs_set_mlock_access;


/* Block "operserv" */
int   os_enabled;
char *os_name; 
char *os_realname; 
int   os_on_oper; 
int   os_on_mode; 
int   os_on_akill; 
int   os_on_sgline; 
int   os_on_skline;
int   os_on_szline; 
int   os_on_sqline; 
int   os_on_kick; 
int   os_on_list; 
int   os_on_kill; 
int   os_akill_expiry;
int   os_sgline_expiry;
int   os_skline_expiry;
int   os_szline_expiry;
int   os_sqline_expiry;

int   os_can_akill;
int   os_can_chghost;
int   os_can_global;
int   os_can_local;
int   os_can_kill;
int   os_can_chatops;
int   os_can_sgline;
int   os_can_sqline;
int   os_can_skline;
int   os_can_szline;
char  *os_vhost;

int os_access_flag;


/* Block "botserv" */
int   bs_enabled;
char *bs_name; 
char *bs_realname; 
int   bs_access_add;
int   bs_access_del;
int   bs_access_list;
int   bs_access_set;
int   bs_access_getpass;
int   bs_access_setpass;


/* Block "adminserv" */
int   as_enabled;
char *as_name; 
char *as_realname; 
int   as_access_flag; 

#endif /*MAIN_H_*/
