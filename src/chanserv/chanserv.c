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

/* global variables */
static cs_cmd *find_cs(const char *name);
ChanInfo *chans = NULL;
op *global_op_list = NULL;


cs_cmd cs_cmds[] = {
	{ "ACC", cs_acc },
	{ "ADMIN", cs_admin },
	{ "AKICK", cs_akick },
	{ "AOP", cs_aop },
	{ "COP", cs_cop },
	{ "DEADMIN", cs_deadmin },
	{ "DEHALFOP", cs_dehalfop },
	{ "DEOWN", cs_deown },
	{ "DEVOICE", cs_devoice },
	{ "DEOP", cs_deop },
	{ "DROP", cs_drop },
	{ "GETPASS", cs_getpass },
	{ "HALFOP", cs_halfop },
	{ "HELP", cs_help },
	{ "HOP", cs_hop },
	{ "IDENTIFY", cs_identify },
	{ "INFO", cs_info },
	{ "INVITE", cs_invite },
	{ "LIST", cs_list },
	{ "MKICK", cs_mkick },
	{ "MDEOP", cs_mdeop },
	{ "OP", cs_op },
	{ "OWN", cs_own },
	{ "QOP", cs_qop },
	{ "REGISTER", cs_register },
	{ "SET", cs_set },
	{ "SETPASS", cs_setpass },
	{ "SOP", cs_sop },
	{ "UOP", cs_uop },
	{ "UNBAN", cs_unban },
	{ "VOICE", cs_voice },
	{ "VOP", cs_vop }
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
		"Cop",
		"Qop",
		"Successor",
		"Founder",
		"Services Administrator"
	};

	return opacc[level];
}

/********************************************************************/
/**
 * add a channel identification to a user
 */
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
	while (pch != NULL) {
		uv[i] = sstrdup(pch);
		i++;
		pch = strtok(NULL, " ");
	}

	if ((cs = find_cs(uv[0]))) {
		if (cs->func) {
			cs->func(src, i, uv);
		}
	} else {
		notice(cs_name,src,CS_ERR_NOSUCHCMD, uv[0]);
		notice(cs_name,src,NS_RPL_HLP_MAIN,cs_name);
		return;
	}
}

/********************************************************************/
/**
 * check whether a registered channel has opwatch enabled
 * deop unauthorized users if opped
 */
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

/********************************************************************/
/**
 * check for a successor if the founder's nickname is dropped
 * the successor will then become the founder and no
 * successor is set
 */
void cs_check_successor(char *nick) {
	op *o = global_op_list;
	while(o) {
		ChanInfo *c = findchan(o->chan->name);
		if(stricmp(o->nick->nick,nick)==0) {
			if(o->level==ACCESS_FND) {
				if(c->successor) {
					c->founder = c->successor;
					c->successor = -1;
				} else {
					delete_chan(c);
					mode(s_name, c->name, "-r", NULL);
				}
			} else if(o->level==ACCESS_SUC) {
				c->successor = -1;
			}
		}
		remove_from_list(o);
		o = o->next;
	}
}

/********************************************************************/
/**
 * reverse the topic if topiclock is enabled and changed by
 * a user below the required level
 */
void cs_check_topiclock(char *src,channel *cl,char *oldtopic) {
	if(isservice(src)) {
		return;
	}
	user *u = finduser(src);
	if(!u)
		return;
	if(!isregcs(cl->name)) {
		return;
	}
	ChanInfo *c = findchan(cl->name);
	if(c->topiclock>0) {
		if(cs_xop_get_level(u,c)<c->topiclock) {
			cl->topic = sstrdup(oldtopic);
			topic(cs_name,cl->name,cl->topic_user,cl->topic_time,oldtopic);
			return;
		}
	}
}
/********************************************************************/
/**
 * connect chanserv to the server
 */
extern int cs_connect(int sock) {
	int rc;
	char *nick = (char*) malloc(sizeof(char) * 256);
	sprintf(nick,SNICK, cs_name, s_user,
			s__host, s_name, cs_realname);
	rc = send(sock, nick, (int) strlen(nick), 0);
	return rc;
}


/********************************************************************/
/**
 * determine, why a user has access to a registered channel
 */
char *cs_get_why(user *u, ChanInfo *c) {
	usernick *un = u->usernicks;
	while(un) {
		op *o = global_op_list;
		while(o) {
			if((stricmp(c->name,o->chan->name)==0) && (stricmp(un->n->nick,o->nick->nick)==0)) {
				return un->n->nick;
			}
			o  = o->next;
		}
		un = un->next;
	}
	return NULL;
}

/********************************************************************/
/**
 * remove all op entries of a dropped nick
 */
void cs_drop_nick(char *nick) {
	op *o = global_op_list;
	while(o) {
		if(stricmp(o->nick->nick,nick)==0) {
			remove_from_list(o);
		}
		o = o->next;
	}
}


/********************************************************************/
/**
 * check whether the nick is the founder of the specified channel
 */
int cs_isfounder(int nick_id, char *chan) {
	ChanInfo *c = findchan(chan);
	if (nick_id == c->founder) {
		return 1;
	}
	return 0;
}
/********************************************************************/
/**
 * check wether the nick machtes an entry in the specified access list
 */
int cs_isonlist(char *nick, char *chan, int list, int move) {
	if (global_op_list == NULL) {
		return 0;
	}
	op *o = global_op_list;
	while (o) {
		if (stricmp(chan, o->chan->name) == 0) {
			if (stricmp(nick, o->nick->nick) == 0) {
				if (o->level == list) {
					return 0;
				} else {
					if(move==1) {
						return o->level;
					} else {
						return -1;
					}
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
	ChanInfo *c = findchan(chan);
	akick *ak = c->akicklist;
	if (!ak) {
		return 0;
	}
	while (ak) {
		if (stricmp(mask, ak->mask) == 0) {
			return 1;
		}
		ak = ak->next;
	}
	return 0;
}
/********************************************************************/
/**
 * check whether the nick is the successor of the specified channel
 */
int cs_issuccessor(int nick_id, char *chan) {
	ChanInfo *c = findchan(chan);
	if(c->successor > 0) {
		if(nick_id == c->successor) {
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
 * find a channel using the specified id
 */
ChanInfo *find_chan_by_id(unsigned int id) {
	ChanInfo *c = chans;
	while(c) {
		if(c->id == id) {
			return c;
		}
		c = c->next;
	}
	return NULL;
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
	c->founder = findnick(src)->id;
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
	c->id = max_cs_id++;
	if (chans)
		chans->prev = c;
	chans = c;
	return c;
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
