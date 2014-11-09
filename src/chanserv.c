/*
 *      chanserv.c - severin
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
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, alBoston,
 *      MA 02110-1301, USA.
 */

#include "main.h"

/********************************************************************/

/* global variables */
static cs_cmd *find_cs(const char *name);
ChanInfo *chans = NULL;
op *global_op_list = NULL;


static cs_cmd cs_cmds[] = {
	{ "ACC", cs_acc },
	{ "ADMIN", cs_admin },
	{ "ADMINOP", cs_adminop },
	{ "AKICK", cs_akick },
	{ "AOP", cs_aop },
	{ "DEADMINOP", cs_deadminop },
	{ "DEHALFOP", cs_dehalfop },
	{ "DEOWN", cs_deown },
	{ "DEVOICE", cs_devoice },
	{ "DEOP", cs_deop },
	{ "DROP", cs_drop },
	{ "GETPASS", cs_getpass },
	{ "HALFOP", cs_halfop },
	{ "HELP", NULL },
	{ "HOP", cs_hop },
	{ "IDENTIFY", cs_identify },
	{ "INFO", cs_info },
	{ "INVITE", cs_invite },
	{ "LIST", cs_list },
	{ "OP", cs_op },
	{ "OWN", cs_own },
	{ "OWNER", cs_cowner },
	{ "REGISTER", cs_register },
	{ "SET", cs_set },
	{ "SETPASS", cs_setpass },
	{ "SOP", cs_sop },
	{ "UOP", cs_uop },
	{ "VOICE", cs_voice },
	{ "VOP", cs_vop },
};
char *get_oline(int level) {
	static char *oline[] = {
		"",
		"",
		"Help operator",
		"IRC Operator",
		"Co Administrator",
		"Server Administrator",
		"Services Administrator",
		"Network Administrator"
	};
	return oline[level];
}

char *get_opacc(int level) {
	char *opacc[] = {
		NULL,
		"Uop",
		"Vop",
		"Hop",
		"Aop",
		"Sop",
		"Admin",
		"Owner",
		"Successor",
		"Founder"
	};
	return opacc[level];
}


void add_identifiedcs(user *u, char *channel) {
	struct cschans *uc = scalloc(sizeof(struct cschans), 1);
		uc->next = u->cschans;
		if (u->cschans)
			u->cschans->prev = uc;
		u->cschans = uc;
		uc->channel = channel;
		uc->level = CHAN_IDENTIFIED;
}
/********************************************************************/
/**
 * the main chanserv routine
 */
void chanserv(char *src, char *av) {
	int i = 0;
	char **uv = (char**) malloc(sizeof(char**) * 4096);
	char *pch = strtok(av, " ");
	cs_cmd *cs;
	user *u = finduser(src);
	while (pch != NULL) {
		uv[i] = sstrdup(pch);
		i++;
		pch = strtok(NULL, " ");
	}
	if ((cs = find_cs(uv[0]))) {
		if (cs->func)
			cs->func(src, i, uv);
	} else {
		notice(cs_name,src,CS_ERR_NOSUCHCMD,av);
		addlog(2, LOG_DBG_NS_UNKNOWN, ns_name, src, u->username, u->hostname,av);
	}
}

int cs_check_opwatch(char *chan,user *u) {
	if(!isregcs(chan)) {
		return 0;
	} else if(u->oper) {
		return 0;
	} else {
		ChanInfo *c = findchan(chan);
		if(cs_xop_get_level(u,c)>=AOP_LIST) {
			return 0;
		} else if(c->opwatch) {
			return 1;
		}
	}
	return 1;
}
void cs_check_successor(char *nick) {
	ChanInfo *c = chans;
	char **av = (char**)malloc(sizeof(char**)*sizeof(chans));
	int i = 0,j = 0;
	while(c) {
		if(stricmp(c->founder,nick)==0) {
			if((c->successor) && (stricmp(c->successor,"")!=0)) {
				strscpy(c->founder,c->successor,NICKMAX);
				c->successor = NULL;
			} else {
				av[i] = sstrdup(c->name);
				i++;
			}
		}
		c = c->next;
	}
	for(j=0;j<i;j++) {
		ChanInfo *cc = findchan(av[j]);
		delete_chan(cc);
	}
}
/********************************************************************/
/**
 * connect chanserv to the server
 */
extern int cs_connect(int sock) {
	int rc;
	char *nick = (char*) malloc(sizeof(char) * 256);
	sprintf(nick, "& %s 1 0 %s %s %s 0 +qdS * :%s\r\n", cs_name, s_user,
			s__host, s_name, cs_realname);
	rc = send(sock, nick, (int) strlen(nick), 0);
	return rc;
}


/********************************************************************/
/**
 * determine, why a user has access to a registered channel
 */
char *cs_get_why(user *u, ChanInfo *c) {
	int lvl = 0;
	int i = 0;
	char *why = (char*) malloc(sizeof(char*) * NICKMAX);
	return why;
}


/********************************************************************/
/**
 * check whether the nick is the founder of the specified channel
 */
int cs_isfounder(char *nick, char *chan) {
	ChanInfo *c = findchan(chan);
	if (stricmp(nick, c->founder) == 0) {
		return 1;
	}
	return 0;
}
/********************************************************************/
/**
 * check wether the nick machtes an entry in the specified access list
 */
int cs_isonlist(char *nick, char *chan, int list) {
	op *o = global_op_list;
	if (global_op_list == NULL) {
		return 0;
	}
	while (o) {
		if (stricmp(chan, o->chan) == 0) {
			if (stricmp(nick, o->nick) == 0) {
				if (o->level < list)
					return 0;
				else if (o->level == list)
					return 1;
				else if (o->level > list) {
					return 2;
				}
			}
		}
		o = o->next;
	}
	return -1;
}
/********************************************************************/
/**
 * check wether the nick machtes an entry in the specified access list
 */
int cs_isonakicklist(char *mask, char *chan) {
	op *o = global_op_list;
	if (global_op_list == NULL) {
		return 0;
	}
	while (o) {
		if (stricmp(chan, o->chan) == 0) {
			if ((stricmp(mask, o->nick) == 0) && (o->level == AKICK_LIST)) {
				return 1;
			}
		}
		o = o->next;
	}
	return 0;
}
/********************************************************************/
/**
 * check whether the nick is the successor of the specified channel
 */
int cs_issuccessor(char *nick, char *chan) {
	ChanInfo *c = findchan(chan);
	if (c->successor) {
		if (stricmp(nick, c->successor) == 0) {
			return 1;
		}
	}
	return 0;
}

/********************************************************************/
/*
 * Deletes a channel when being dropped
 */
void delete_chan(ChanInfo *c) {
	if (c->prev)
		c->prev->next = c->next;
	else
		chans = c->next;
	if (c->next)
		c->next->prev = c->prev;
	free(c);
}
/********************************************************************/
/**
 * find the correct chanserv command
 */
static cs_cmd *find_cs(const char *name) {
	cs_cmd *cmd;
	for (cmd = cs_cmds; cmd->name-1; cmd++) {
		if (stricmp(name, cmd->name) == 0) {
			return cmd;
		}
	}
	return NULL;
}
/********************************************************************/
/**
 * find a registered channel in the chanserv table
 */
ChanInfo *findchan(const char *chan) {
	ChanInfo *c = chans;
	if (chans == NULL) {
		return NULL;
	}
	while (c && stricmp(c->name, chan) != 0) {
		c = c->next;
	}
	return c;
}
/********************************************************************/
/**
 * once a nick has been granted access to a channel, add it to the
 * counter
 */
void inc_list(ChanInfo *c, int list) {
	if (list == 1)
		c->uopcount++;
	else if (list == 2)
		c->vopcount++;
	else if (list == 3)
		c->hopcount++;
	else if (list == 4)
		c->aopcount++;
	else if (list == 5)
		c->sopcount++;
}
/********************************************************************/
/**
 * checks whether a user has successfully identified with a registered channel
 */
int isidentifiedcs(user *u, ChanInfo *c) {
	return -1;
}
/********************************************************************/
/**
 * add a channel to the chanserv table
 */
ChanInfo *register_chan(const char *src, char *name, char *pass, char *desc) {
	ChanInfo *c;
	c = scalloc(sizeof(ChanInfo), 1);
	strscpy(c->name, name, CHANMAX);
	strscpy(c->pass, pass, PASSMAX);
	strscpy(c->description, desc, DESCMAX);
	strscpy(c->founder, src, NICKMAX);
	c->akickcount = 0;
	c->aop_enabled = 1;
	c->uop_enabled = 1;
	c->vop_enabled = 1;
	c->hop_enabled = 1;
	c->sop_enabled = 1;
	c->keeptopic = cs_keeptopic;
	c->opwatch = cs_opwatch;
	if(c->opwatch)
		c->leaveops = 0;
	else
		c->leaveops = cs_leaveops;
	c->topiclock = cs_topiclock;
	if(cs_memolevel==0)
		c->memolevel = 1;
	else
		c->memolevel = cs_memolevel;
	c->autovop = cs_autovop;
	c->mlock = sstrdup(cs_mlock);
	c->next = chans;
	c->time_reg = time(NULL);
	if (chans)
		chans->prev = c;
	chans = c;
	return c;
}
/********************************************************************/
/**
 * write the nickname table to the database
 */
void save_chanserv_db(void) {
	db_save_chans(chans);
}
/********************************************************************/
/**
 * update the access table of the channels
 */
void update_xop_list(op *o) {
	o->next = global_op_list;
	if (global_op_list)
		global_op_list->prev = o;
	global_op_list = o;
}
/* EOF */
