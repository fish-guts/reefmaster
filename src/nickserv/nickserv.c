/*
 *      nickserv.c - severin
 *
 *      Copyright (c) 2014 Severin Mueller <severin.mueller@reefmaster.org>
 *
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

#include "main.h"

/* global vars */

/* timeout list */
static struct timeout {
	struct timeout *next, *prev;
	user *u;
	timer *to;
	int type;
} *my_timeouts;

/* list containing a the registered nicknames */
NickInfo *nicklist = NULL;
static ns_cmd *find_ns(const char *name);


/********************************************************************/
/* function prototypes */

static void add_ns_timeout(user *u, int type, time_t delay);
static void force_identify(user *u, int from_timeout);
static void del_ns_timeout(user *u, int type);
static void release(user *u, int from_timeout);
static void rem_ns_timeout(user *u, int type);
static void timeout_collide(timer *t);
static void timeout_collide_tl(timer *t);
static void timeout_release(timer *t);


/* all the nickserv commands */
ns_cmd ns_cmds[] = {
	{ "ACC", ns_acc },
	{ "ACCESS", ns_access_cmd },
	{ "AUTH", ns_auth },
	{ "DROP", ns_drop },
	{ "INFO", ns_info },
	{ "GETPASS", ns_getpass },
	{ "GHOST", ns_ghost },
	{ "HELP" , ns_help },
	{ "IDENTIFY", ns_identify },
	{ "LIST", ns_list },
	{ "LISTCHANS", ns_listchans },
	{ "NOTIFY", ns_notify },
	{ "REGISTER", ns_register },
	{ "RELEASE", ns_release },
	{ "SET", ns_set },
	{ "SETPASS", ns_setpass }
};


/********************************************************************/
/**
 * starts a timer, depending on the type
 */
static void add_ns_timeout(user *u, int type, time_t delay) {
	timer *to;
	struct timeout *t;
	void (*timeout_routine)(timer *);
	if (type == TO_COLLIDE_TL)
		timeout_routine = timeout_collide_tl;
	else if (type == TO_COLLIDE)
		timeout_routine = timeout_collide;
	else if (type == TO_RELEASE)
		timeout_routine = timeout_release;
	else
		return;
	to = add_timeout(delay, timeout_routine, 0);
	to->data = u;
	t = smalloc(sizeof(*t));
	t->next = my_timeouts;
	my_timeouts = t;
	t->prev = NULL;
	t->u = u;
	t->to = to;
	t->type = type;
}
/********************************************************************/
/**
 * remove any timer if a user quits
 */
void cancel_user(user *u) {
	del_ns_timeout(u, TO_COLLIDE);
}
/********************************************************************/
/**
 * starts a timer, giving the user 60 seconds to identify for the nickname. nick will changed if the user fails to do so
 */
static void force_identify(user *u, int from_timeout) {
	char newnick[NICKMAX];
	long int buf = 0;
	double x = RAND_MAX + 1.0;
	char *nick = u->nick;
	/* create a random guest name */
	buf = 1 + rand() * (99999 / x);
	snprintf(newnick, sizeof(newnick), "Guest%ld", buf);

	if (!from_timeout) {
		del_ns_timeout(u, TO_COLLIDE);
	}

	if (from_timeout > 0) {
		notice(ns_name, u->nick, NS_RPL_PLZ_NOTIMELEFT);
	}
	/* change the nick */
	svsnick(u->nick, newnick, time(NULL));
	ns_enforce(nick);
	add_ns_timeout(u, TO_RELEASE, ns_release_time);
}
/********************************************************************/
/**
 *  stop an existing timer
 */
static void del_ns_timeout(user *u, int type) {
	struct timeout *t, *t2;
	t = my_timeouts;
	while (t) {
		if ((t->u == u) && (t->type == type)) {
			t2 = t->next;
			if (t->next) {
				t->next->prev = t->prev;
			}
			if (t->prev) {
				t->prev->next = t->next;
			} else {
				my_timeouts = t->next;
			}
			del_timeout(t->to);
			free(t);
			t = t2;
		} else {
			t = t->next;
		}
	}
}
/********************************************************************/
/**
 * delete a nickname from the list.
 */
void delete_nick(NickInfo *n) {
	if (n->prev) {
		n->prev->next = n->next;
	} else {
		nicklist = n->next;
	}

	if (n->next) {
		n->next->prev = n->prev;
	}

	free(n);
}
/********************************************************************/
/**
 * Call the correct function
 */
static ns_cmd *find_ns(const char *name) {
	ns_cmd *cmd;
	for (cmd = ns_cmds; cmd->name-1; cmd++) {
		if (stricmp(name, cmd->name) == 0) {
			return cmd;
		}
	}
	return NULL;
}
/********************************************************************/
/**
 * find a channel auth request in the nickname's auth list
 */
int findauth_chan(char *src, char *nick, char *chan, int level) {
	return 0;
}
/********************************************************************/
/**
 * find a notify auth request in the nickname's auth list
 */
auth *findauth_notify(char *src, char *nick) {
	NickInfo *n = findnick(nick);
	if(!n) {
		return NULL;
	}
	auth *a = n->authlist;
	if (n->authlist == NULL) {
		return NULL;
	}
	while (a) {
		if((stricmp(src,nick)==0) && (a->type==AUTH_NOTIFY)) {
			return a;
		}
		a = a->next;
	}
	return NULL;
}
/********************************************************************/
/**
 * Locates a user structure for user information
 */
NickInfo *findnick(const char *src) {
	NickInfo *n = nicklist;
	while (n && stricmp(n->nick, src) != 0) {
		n = n->next;
	}
	return n;
}
/********************************************************************/
/**
 * find a nickname using the specified id
 */
NickInfo *find_nick_by_id(int id) {
	NickInfo *n = nicklist;
	while(n) {
		if(n->id == id) {
			return n;
		}
		n = n->next;
	}
	return NULL;
}
/********************************************************************/
/**
 * checks whether a user has successfully identified with a
 * registered nickname
 */
int isidentified(user *u, char *nick) {
	if(u->oper>=ns_admin)
		return 1;
	usernick *un;
	un = u->usernicks;
	while(un) {
		if ((stricmp(un->n->nick,nick)==0) && (un->level==NICK_IDENTIFIED)) {
			return 1;
		}
		un = un->next;
	}
	return 0;
}

/********************************************************************/
/**
 *  the main nickserv routine
 */
void nickserv(char *src, char *av) {
	int i = 0;
	char **uv = (char**) malloc(sizeof(char**) * 4096);
	char *pch = strtok(av, " ");
	ns_cmd *ns;
	while (pch != NULL) {
		uv[i] = sstrdup(pch);
		i++;
		pch = strtok(NULL, " ");
	}
	if ((ns = find_ns(uv[0]))) {
		if (ns->func) {
			ns->func(src, i, uv);
		}
	} else {
		notice(ns_name,src,NS_ERR_NOSUCHCMD, uv[0]);
		notice(ns_name,src,NS_RPL_HLP_MAIN,ns_name);
		return;
	}
}/********************************************************************/
/**
 * connect nickserv to server
 */
extern int ns_connect(int sock) {
	char *nick = (char*) malloc(sizeof(char) * 1024);
	sprintf(nick, SNICK, ns_name, s_user,
			s__host, s_name, ns_realname);
	int rc = send(sock, nick, (int) strlen(nick), 0);
	free(nick);
	return rc;

}

/********************************************************************/
/**
 * check whether the joining user u is in a registered nickname's
 * notify list and send a message if so.
 */
void ns_checknotify(user *u, int mode) {
	if(!isreg(u->nick)) {
		return;
	}
	NickInfo *n2 = nicklist;
	while(n2) {
		notify *no = n2->notifylist;
		while(no) {
			if(stricmp(no->nick->nick,u->nick)==0) {
				if(finduserbynick(n2->nick)) {
					if(mode==NOTIFY_ONLINE) {
						notice(ns_name,n2->nick,"\2%s\2 is now online!",u->nick);
						return;
					} else if (mode==NOTIFY_OFFLINE) {
						notice(ns_name,n2->nick,"\2%s\2 is now offline!",u->nick);
						return;
					}
				}
			}
			no = no->next;
		}
		n2 = n2->next;
	}
}
/********************************************************************/
/**
 * check for existing auth requests
 */
void ns_check_auth(user *u) {
	NickInfo *n = findnick(u->nick);
	if(has_open_auth(n)) {
		notice(ns_name,u->nick,NS_AUTH_RPL_OPEN);
	}
	return;
}
/********************************************************************/
/**
 * checks for a password
 */
int ns_checkpass(char *src, char *pass) {
	NickInfo *n = findnick(src);
	if (stricmp(pass, n->pass)) {
		return 1;
	}
	return 0;
}
/********************************************************************/
/**
 * takes over a nickname, if not identified for it properly. After
 * 60 seconds, the nick will be released
 */
void ns_enforce(char *src) {
	char buf[1024];
	sprintf(buf, "NICK %s %lu 1 %s %s %s :%s Nickname Enforcement\r\n", src,time(NULL), ns_enforcer, s__host, s_name, ns_name);
	addlog(1, ns_name, LOG_DBG_ENFORCING, src);
	NickInfo *n = findnick(src);
	n->enforced = 1;
	send(mainsock, buf, strlen(buf), 0);
	return;
}


/********************************************************************/
/**
 * check whether the user has entered multiple wrong passwords
 */
void ns_passlimit(user *u) {
	if (u->oper >= 1)
		return;
	else {
		switch (s_PassAction) {
		/* kill the user */
		case 1:
			s_kill(ns_name, u->nick, NS_ERR_TOOMANYPASS);
			rem_ns_timeout(u, TO_COLLIDE);
			break;
		/* kline the user */
		case 2:
			kline(ns_name,"*",u->hostname,"Too many wrong password attemps. Try again in 30 Minutes",30);
			break;
		/* gline the user */
		case 3:
			gline(ns_name,"*",u->hostname,"Too many wrong password attemps. Try again in 30 Minutes",30);
			break;
		default:
			break;
		}
	}
}

/********************************************************************/
/**
 * remove the timers if a service-held nickname was released
 */
static void release(user *u, int from_timeout) {
	if (!from_timeout) {
		del_ns_timeout(u, TO_COLLIDE);
	}
	del_ns_timeout(u, TO_COLLIDE_TL);
	del_ns_timeout(u, TO_RELEASE);
	quit(u->nick);
}
/********************************************************************/
/**
 * remove the timers if the user has successfully
 * identified for their nickname
 */
static void rem_ns_timeout(user *u, int type) {
	struct timeout *t, *t2;
	t = my_timeouts;
	while (t) {
		if (t->u == u && t->type == type) {
			t2 = t->next;
			if (t->next) {
				t->next->prev = t->prev;
			}

			if (t->prev) {
				t->prev->next = t->next;
			} else {
				my_timeouts = t->next;
			}
			free(t);
			t = t2;
		} else {
			t = t->next;
		}
	}
}
/********************************************************************/
/**
 * add a timer if a user occupies a registered nickname
 */
static void timeout_collide(timer *t) {
	user *u = t->data;
	rem_ns_timeout(u, TO_COLLIDE);
	add_ns_timeout(u, TO_RELEASE, ns_release_time);
	force_identify(u, 1);
}
/********************************************************************/
/**
 * this timer gives the user 60 seconds to identify for their nickname
 */
static void timeout_collide_tl(timer *t) {
	user *u = t->data;
	rem_ns_timeout(u, TO_COLLIDE_TL);
	if ((u = finduser(u->nick)) == NULL)
		return;
	add_ns_timeout(u, TO_COLLIDE, 30);
	notice(ns_name, u->nick, NS_RPL_PLZ_30SECSLEFT);
}
/********************************************************************/
/**
 * remove a timer
 */
static void timeout_release(timer *t) {
	user *u = t->data;
	rem_ns_timeout(u, TO_RELEASE);
	release(u, 1);
}

/********************************************************************/
/**
 * add a nick identification (password or access to a user)
 */
void add_nick_with_access(user *u, NickInfo *n, int type) {
	usernick *un = scalloc(sizeof(usernick), 1);
	un->next = u->usernicks;
	if (u->usernicks) {
		u->usernicks->prev = un;
	}
	u->usernicks = un;
	un->n = n;
	un->level = type;
}
/********************************************************************/
/**
 * check whether the joining user uses a registered nickname, and
 * react accordingly.
 *
 */
void validate_user(user *u) {
	char *mask = (char*) malloc(sizeof(char*) * 128);
	sprintf(mask, "%s@%s", u->username, u->hostname);
	if (isreg(u->nick)) {
		/* sets mode +r if the user has already identified for this nick */
		if (isidentified(u, u->nick)) {
			svs2mode(s_name, u->nick, "+r 0", NULL);
			return;
		}
		if (!isidentified(u, u->nick)) {
			svs2mode(s_name, u->nick, "-r 0", NULL);
		}
		/* checks whether the usermask matches an entry in the nickname's access list*/
		if (ismatch(u, mask)) {
			add_nick_with_access(u,findnick(u->nick),NICK_ACCESS);
			return;
		}
		/* stop here, if the nick has the override flag (see config for more details) */
		if (u->oper >= ns_admin) {
			return;
		}
		notice(ns_name, u->nick, NS_RPL_PLZ_IDENTIFY0);
		/* issue a warning, that this nick is taken - nick will not be changed though (no protection) */
		if (isreg(u->nick) == 1) {
			notice(ns_name, u->nick, NS_RPL_PLZ_IDENTIFY1, ns_name);
		} else if (isreg(u->nick) == 2) {
			/* user has 60 seconds to identify (normal protection) */
			notice(ns_name, u->nick, NS_RPL_PLZ_IDENTIFY1, ns_name);
			notice(ns_name, u->nick, NS_RPL_PLZ_IDENTIFY2);
			add_ns_timeout(u, TO_COLLIDE_TL, 30);
		} else if (isreg(u->nick) == 3) {
			/* nick is changed immediately (agressive protection) */
			notice(ns_name, u->nick, NS_RPL_PLZ_IDENTIFY3);
			notice(ns_name, u->nick, NS_RPL_PLZ_IDENTIFY4, ns_name);
			add_ns_timeout(u, TO_RELEASE, ns_release_time);
			force_identify(u, 0);
		}
	} else {
		del_ns_timeout(u, TO_COLLIDE);
		del_ns_timeout(u, TO_COLLIDE_TL);
	}
	return;
}
/********************************************************************/
/**
 * delete a running timer
 */
void remove_timeout(user *u, int type) {
	del_ns_timeout(u, type);
}
/********************************************************************/
/**
 * adds a new nickname to the nickserv table
 */
NickInfo *register_nick(const char *src, const char *password,char *email) {
	user *u = finduser(src);
	NickInfo *n;
	char *usermask = (char*) malloc(sizeof(char*) * 1024);
	sprintf(usermask, "%s@%s", u->username,u->hostname);
	n = scalloc(sizeof(NickInfo), 1);
	if (!src) {
		src = "";
	}
	strscpy(n->nick, src, NICKMAX);
	strscpy(n->pass, password, PASSMAX);
	n->email = sstrdup(email);
	n->nomemo = ns_no_memo;
	n->auth_chan = ns_auth_channel;
	n->auth_notify = ns_auth_notify;
	n->protect = ns_high_protect;
	n->hidemail = ns_hide_email;
	n->noop = ns_noop;
	n->last_realname = sstrdup(u->realname);
	n->last_seen = time(NULL);
	n->time_reg = time(NULL);
	n->last_usermask = sstrdup(usermask);
	n->mforward = 0;
	if (ns_autoaccess) {
		ns_access_add_mask(n,usermask);
	}
	n->next = nicklist;
	if (nicklist)
		nicklist->prev = n;
	nicklist = n;
	return n;
}

/**
 * add a nick the user's list of nick they identified for
 */
void add_identified(user *u, char *nick) {
	usernick *un = scalloc(sizeof(usernick), 1);
	un->next = u->usernicks;
	if (u->usernicks) {
		u->usernicks->prev = un;
	}
	u->usernicks = un;
	un->n = findnick(nick);
	un->level = NICK_IDENTIFIED;
}
/* EOF */
