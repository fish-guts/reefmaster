#ifndef STRUCT_H_
#define STRUCT_H_

#include <time.h>

#define NICKMAX 33
#define CHANMAX 33
#define PASSMAX 33
#define DESCMAX 2048

typedef struct _accesslist accesslist;
typedef struct _auth auth;
typedef struct _botinfo bot;
typedef struct _as_cmd as_cmd;
typedef struct _bs_cmd bs_cmd;
typedef struct _op op;
typedef struct _chanacc chanacc;
typedef struct _akick akick;
typedef struct _chaninfo ChanInfo;
typedef struct _channel channel;
typedef struct _command com;
typedef struct _cs_cmd cs_cmd;
typedef struct _irc_command irc_cmd;
typedef struct _ns_cmd ns_cmd;
typedef struct _cs_xop_check xop_check;
typedef struct _user user;
typedef struct _oper operline;
typedef struct _nickinfo NickInfo;
typedef struct _timeout_ timer;
typedef struct _notify_text ntext;
typedef struct _notify notify;
typedef struct _targettype targettype;

struct _auth
{
	auth *next, *prev;
	int type;
	char *target;
	char *sender;
	time_t date;
	int status;
};

struct _botinfo {
	bot *next,*prev;
	char *name;
	char *password;
	char *username;
	char *realname;
	char **chanlist;
	int chancount;
};
struct _channel
{
	channel *next, *prev;
	int ucnt,ops,hops,vops,uops,owners,pus;
	char *modes;
	char *name;
	char *topic;
	char *key;
    struct chanusers 
    {
		struct chanusers *next, *prev;
		user *u;
    } *users;	
	
};
struct _op {
	op *prev,*next;
	char *nick;
	char *chan;
	int level;
	time_t addedon;
	char *addedby;
	int addedbyacc;
	char *reason;
};

struct _chaninfo {
	ChanInfo *prev, *next;
	char name[CHANMAX];
	char pass[PASSMAX];
	char description[DESCMAX];
	time_t time_reg;
	int akickcount;
	int aop_enabled;
	int uopcount;
	int vopcount;
	int hopcount;
	int aopcount;
	int sopcount;
	int admincount;
	int ownercount;
	char *bot;
	char founder[NICKMAX];
	int hop_enabled;
	char *mlock;
	int restricted;
	int sop_enabled;
	char *successor;
	char topic[2048];
	int topiclock;
	int uop_enabled;
	int keeptopic;
	int autovop;
	int memolevel;
	int leaveops;
	int opwatch;
	char *url;
	int vop_enabled;
	char **accesslist;
	char accesscount;
};

struct _akick {
	akick *prev, *next;
	char *mask;
	char *reason;
	char *addedby;
	char *addedbyacc;
	time_t addedon;
};
struct _bs_cmd
{
	const char *name;
	void (*func)(char *src,int ac,char **av);
};
struct _cs_cmd
{
	const char *name;
	void(*func)(char *src,int ac, char **av);
};
struct _ns_cmd
{
	const char *name;
	void (*func)(char *src,int ac,char **av);
};
struct _as_cmd
{
	const char *name;
	void (*func)(char *src,int ac,char **av);
};
struct _irc_command
{
    const char *name;
    void (*func)(char *source, int ac, char **av);
};
struct _notify_text
{
    int name;
    char *text;
};
struct _nickinfo {
    NickInfo *next, *prev;
    int id;
    int auth_chan;
    int auth_notify;
    unsigned int authcount;
    accesslist *al;
    unsigned short channelcount;
    char *email;
    int enforced;
    int hidemail;
    char *last_realname;
    time_t last_seen;
    const char *last_usermask;
    unsigned short memomax;
    int mforward;
    char *mforward_to;
    char *mlock;
    short mnotify;
    char nick[NICKMAX];
    int noop;
    notify *notifylist;
    int nomemo;
    char pass[PASSMAX];
    int protect;
    long reserved[4];
    time_t time_reg;
    char *url;
    auth *authlist;
};
struct _accesslist {
	accesslist *prev, *next;
	char *mask;
};
struct _notify {
	notify *prev, *next;
	NickInfo *nick;
};
struct _timer {
    timer *next, *prev;
    time_t settime, timeout;
    int repeat;	
    void (*code)(timer *);
    void *data;
};
struct _targettype {
	targettype *prev,*next;
	int id;
	char *name;
};
struct _user 
{
	user *next;
	user *prev;
	char  nick[32];
	char   *username;
	char   *hostname;
	char   *realname;
	char   *server;
	char   *modes;
	time_t  signon;
	int     oper;
	char   *mode;
    short   pw_cnt;
    time_t  pw_time;
    time_t  lastmemo;	
    time_t  lastnickreg;
    time_t  lastchanreg;
    time_t  flood_time;      
    int flood_level1;
    int flood_level2;
    int nick_count;
    int chan_count;
    struct usernicks {
    	struct usernicks *next, *prev;
    	char *nick;
    	int level;
    } *usernicks;
    struct cschans {
    	struct cschans *next, *prev;
    	char *channel;
    	int level;
    } *cschans;
    struct userchans 
    {
		struct userchans *next, *prev;
		channel *chan;
		int status;
    } *chans;
    struct u_acc 
    {
    	char *nick;
    	int level;
    } *acc; 
};
struct _timeout_ {
    timer *next, *prev;
    user *u;
    time_t settime, timeout;
    int repeat;
    void (*code)(timer *);
    void *data;
    int type;
};

#endif /*STRUCT_H_*/
