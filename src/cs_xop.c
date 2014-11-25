/*
 * cs_xop.c
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

static char *acclist[] = { NULL, "Uop", "Vop", "Hop", "Aop", "Sop", "Successor", "Founder" };

void add_to_list(char *nick, char *chan, int level, char *addnick, int addlevel) {
	op *o = scalloc(sizeof(op),1);
	o->id = 0;
	o->level = level;
	o->nick = findnick(nick);
	o->chan = findchan(chan);
	o->addedby = sstrdup(addnick);
	o->addedbyacc = addlevel;
	o->addedon = time(NULL);
	o->next = global_op_list;
	if (global_op_list)
		global_op_list->prev = o;
	global_op_list = o;
}
/********************************************************************/
/**
 * cs AOP - handle the chanserv AOP command
 */
void cs_aop(char *src, int ac, char **av) {
	char *chan;
	char *nick;
	if (stricmp(av[2], "ADD") == 0) {
		if(ac<4) {
			notice(cs_name,src,CS_RPL_XOP_USAGE,"AOP <Channel> ADD <Nickname>");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"AOP ADD");
			return;
		}
		chan = av[1];
		nick = av[3];
		cs_xop_add(src, chan, AOP_LIST, nick);
		return;
	} else if (stricmp(av[2], "DEL") == 0) {
		if(ac<4) {
			notice(cs_name,src,CS_RPL_XOP_USAGE,"AOP <Channel> DEL <Nickname>");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"AOP DEL");
			return;
		}
		chan = av[1];
		nick = av[3];
		cs_xop_del(src, chan, AOP_LIST, nick);
		return;
	} else if (stricmp(av[2], "LIST") == 0) {
		if(ac<3) {
			notice(cs_name,src,CS_RPL_XOP_USAGE,"AOP <Channel> LIST");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"AOP LIST");
			return;
		}
		chan = av[1];
		cs_xop_list(src, chan, AOP_LIST);
		return;
	} else if (stricmp(av[2], "WIPE") == 0) {
		if(ac<3) {
			notice(cs_name,src,CS_RPL_XOP_USAGE,"AOP <Channel> LIST");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"AOP LIST");
			return;
		}
		chan = av[1];
		cs_xop_wipe(src, chan, AOP_LIST);
		return;
	} else {
		notice(cs_name,src,CS_ERR_NOSUCHCMD,av[2]);
		notice(cs_name,src,CS_ERR_XOP_USAGE,"AOP");
		notice(cs_name,src,CS_RPL_HLP,cs_name,"AOP");
		return;
	}
	return;
}
/********************************************************************/
/**
 * cs HOP - handle the chanserv HOP command
 */
void cs_hop(char *src, int ac, char **av) {
	char *chan;
	char *nick;
	if (stricmp(av[2], "ADD") == 0) {
		if(ac<4) {
			notice(cs_name,src,CS_RPL_XOP_USAGE,"HOP <Channel> ADD <Nickname>");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"HOP ADD");
			return;
		}
		chan = av[1];
		nick = av[3];
		cs_xop_add(src, chan, HOP_LIST, nick);
		return;
	} else if (stricmp(av[2], "DEL") == 0) {
		if(ac<4) {
			notice(cs_name,src,CS_RPL_XOP_USAGE,"HOP <Channel> DEL <Nickname>");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"HOP DEL");
			return;
		}
		chan = av[1];
		nick = av[3];
		cs_xop_del(src, chan, HOP_LIST, nick);
		return;
	} else if (stricmp(av[2], "LIST") == 0) {
		if(ac<3) {
			notice(cs_name,src,CS_RPL_XOP_USAGE,"HOP <Channel> LIST");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"HOP LIST");
			return;
		}
		chan = av[1];
		cs_xop_list(src, chan, HOP_LIST);
		return;
	} else if (stricmp(av[2], "WIPE") == 0) {
		if(ac<3) {
			notice(cs_name,src,CS_RPL_XOP_USAGE,"HOP <Channel> LIST");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"HOP LIST");
			return;
		}
		chan = av[1];
		cs_xop_wipe(src, chan, HOP_LIST);
		return;
	} else {
		notice(cs_name,src,CS_ERR_NOSUCHCMD,av[2]);
		notice(cs_name,src,CS_ERR_XOP_USAGE,"HOP");
		notice(cs_name,src,CS_RPL_HLP,cs_name,"HOP");
		return;
	}
	return;
}
/********************************************************************/
/**
 * cs SOP - handle the chanserv SOP command
 */
void cs_sop(char *src, int ac, char **av) {
	char *chan;
	char *nick;
	if (stricmp(av[2], "ADD") == 0) {
		if(ac<4) {
			notice(cs_name,src,CS_RPL_XOP_USAGE,"SOP <Channel> ADD <Nickname>");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"SOP ADD");
			return;
		}
		chan = av[1];
		nick = av[3];
		cs_xop_add(src, chan, SOP_LIST, nick);
		return;
	} else if (stricmp(av[2], "DEL") == 0) {
		if(ac<4) {
			notice(cs_name,src,CS_RPL_XOP_USAGE,"SOP <Channel> DEL <Nickname>");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"SOP DEL");
			return;
		}
		chan = av[1];
		nick = av[3];
		cs_xop_del(src, chan, SOP_LIST, nick);
		return;
	} else if (stricmp(av[2], "LIST") == 0) {
		if(ac<3) {
			notice(cs_name,src,CS_RPL_XOP_USAGE,"SOP <Channel> LIST");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"SOP LIST");
			return;
		}
		chan = av[1];
		cs_xop_list(src, chan, SOP_LIST);
		return;
	} else if (stricmp(av[2], "WIPE") == 0) {
		if(ac<3) {
			notice(cs_name,src,CS_RPL_XOP_USAGE,"SOP <Channel> LIST");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"SOP LIST");
			return;
		}
		chan = av[1];
		cs_xop_wipe(src, chan, SOP_LIST);
		return;
	} else {
		notice(cs_name,src,CS_ERR_NOSUCHCMD,av[2]);
		notice(cs_name,src,CS_ERR_XOP_USAGE,"SOP");
		notice(cs_name,src,CS_RPL_HLP,cs_name,"SOP");
		return;
	}
	return;
}
/********************************************************************/
/**
 * cs UOP - handle the chanserv UOP command
 */
void cs_uop(char *src, int ac, char **av) {
	char *chan;
	char *nick;
	if (stricmp(av[2], "ADD") == 0) {
		if(ac<4) {
			notice(cs_name,src,CS_RPL_XOP_USAGE,"UOP <Channel> ADD <Nickname>");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"UOP ADD");
			return;
		}
		chan = av[1];
		nick = av[3];
		cs_xop_add(src, chan, UOP_LIST, nick);
		return;
	} else if (stricmp(av[2], "DEL") == 0) {
		if(ac<4) {
			notice(cs_name,src,CS_RPL_XOP_USAGE,"UOP <Channel> DEL <Nickname>");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"UOP DEL");
			return;
		}
		chan = av[1];
		nick = av[3];
		cs_xop_del(src, chan, UOP_LIST, nick);
		return;
	} else if (stricmp(av[2], "LIST") == 0) {
		if(ac<3) {
			notice(cs_name,src,CS_RPL_XOP_USAGE,"UOP <Channel> LIST");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"UOP LIST");
			return;
		}
		chan = av[1];
		cs_xop_list(src, chan, UOP_LIST);
		return;
	} else if (stricmp(av[2], "WIPE") == 0) {
		if(ac<3) {
			notice(cs_name,src,CS_RPL_XOP_USAGE,"UOP <Channel> LIST");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"UOP LIST");
			return;
		}
		chan = av[1];
		cs_xop_wipe(src, chan, UOP_LIST);
		return;
	} else {
		notice(cs_name,src,CS_ERR_NOSUCHCMD,av[2]);
		notice(cs_name,src,CS_ERR_XOP_USAGE,"UOP");
		notice(cs_name,src,CS_RPL_HLP,cs_name,"UOP");
		return;
	}
	return;
}

/********************************************************************/
/**
 * cs VOP - handle the chanserv VOP command
 */
void cs_vop(char *src, int ac, char **av) {
	char *chan;
	char *nick;
	if (stricmp(av[2], "ADD") == 0) {
		if(ac<4) {
			notice(cs_name,src,CS_RPL_XOP_USAGE,"VOP <Channel> ADD <Nickname>");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"VOP ADD");
			return;
		}
		chan = av[1];
		nick = av[3];
		cs_xop_add(src, chan, VOP_LIST, nick);
		return;
	} else if (stricmp(av[2], "DEL") == 0) {
		if(ac<4) {
			notice(cs_name,src,CS_RPL_XOP_USAGE,"VOP <Channel> DEL <Nickname>");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"VOP DEL");
			return;
		}
		chan = av[1];
		nick = av[3];
		cs_xop_del(src, chan, VOP_LIST, nick);
		return;
	} else if (stricmp(av[2], "LIST") == 0) {
		if(ac<3) {
			notice(cs_name,src,CS_RPL_XOP_USAGE,"VOP <Channel> LIST");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"VOP LIST");
			return;
		}
		chan = av[1];
		cs_xop_list(src, chan, VOP_LIST);
		return;
	} else if (stricmp(av[2], "WIPE") == 0) {
		if(ac<3) {
			notice(cs_name,src,CS_RPL_XOP_USAGE,"VOP <Channel> LIST");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"VOP LIST");
			return;
		}
		chan = av[1];
		cs_xop_wipe(src, chan, VOP_LIST);
		return;
	} else {
		notice(cs_name,src,CS_ERR_NOSUCHCMD,av[2]);
		notice(cs_name,src,CS_ERR_XOP_USAGE,"VOP");
		notice(cs_name,src,CS_RPL_HLP,cs_name,"VOP");
		return;
	}
	return;
}

/********************************************************************/
/**
 * input of a chanserv SOP/AOP/UOP/HOP/VOP command - add a nick to the
 * specified list of the specified channel
 */
void cs_xop_add(char *src, char *chan, int list, char *nick) {
	int alist[] = { 0, cs_uop_add, cs_vop_add, cs_hop_add, cs_aop_add, cs_sop_add };
	if(!isregcs(chan)) {
		notice(cs_name,src,CS_ERR_NOTREG,chan);
		return;
	}
	if(!isreg(nick)) {
		notice(cs_name,src,NS_ERR_NOTREG,nick);
		return;
	}
	int listacc = 0;
	ChanInfo *c = findchan(chan);
	if ((listacc = cs_xop_get_level(finduser(src),c)) < alist[list]) {
		notice(cs_name, src, CS_ERR_XOP_HIGHERACCESS, get_opacc(alist[list]));
		return;
	}
	int existing_level = cs_isonlist(nick,chan,list,1);
	NickInfo *n = findnick(nick);
	if(existing_level==0) {
		notice(cs_name,src,CS_ERR_XOP_ALREADYONLIST,nick,acclist[list],chan);
		return;
	} else if(cs_isfounder(nick,chan)) {
		notice(cs_name,src,CS_ERR_XOP_FOUNDERCANNOTADD,nick,chan,acclist[list]);
		return;
	} else if(cs_issuccessor(nick,chan)) {
		notice(cs_name,src,CS_ERR_XOP_FOUNDERCANNOTADD,nick,chan,acclist[list]);
		return;
	} else if(existing_level>0) {
		if((n->auth_chan) && (list>existing_level)) {
			add_auth_entry(nick,chan,list,src,listacc);
			return;
		}
		move_in_list(nick,chan,list,existing_level,src,listacc);
		notice(cs_name,src,CS_RPL_XOP_MOVED,nick,acclist[existing_level], acclist[list],chan);
		return;
	} else {
		if((n->auth_chan) && (list>existing_level)) {
			add_auth_entry(nick,chan,list,src,listacc);
			return;
		}
		notice(cs_name,src,CS_RPL_XOP_ADDED,nick,acclist[list],chan);
		add_to_list(nick,chan,list,src,listacc);
	}
}
auth *find_auth_entry(char *nick,char *chan) {
	NickInfo *n = findnick(nick);
	auth *a = n->authlist;
	if (n->authlist == NULL) {
		return NULL;
	}
	while (a) {
		if(stricmp(a->target,chan)==0) {
			return a;
		}
		a = a->next;
	}
	return NULL;
}
void add_auth_entry(char *nick,char *chan,int list,char *src,int listacc) {
	NickInfo *n = findnick(nick);
	if(find_auth_entry(nick,chan)) {
		notice(cs_name,src,CS_RPL_ATH_ALREADYSENT,nick);
		return;
	} else {
		auth*a = scalloc(sizeof(auth), 1);
		a->next = n->authlist;
		if (n->authlist)
			n->authlist->prev = a;
		n->authlist = a;
		a->type = list;
		a->target = sstrdup(chan);
		a->sender = sstrdup(src);
		a->date = time(NULL);
		a->status = 0;
		a->acclevel = listacc;
		notice(cs_name,src,CS_RPL_XOP_AUTH_REQUIRED,nick);
		if(list<AUTH_SUCC) {
			notice(cs_name,src,CS_RPL_XOP_AUTH_SENT_XOP,nick,acclist[list],chan);
		} else {
			notice(cs_name,src,CS_RPL_XOP_AUTH_SENT_SF,nick,acclist[list],chan);
		}
		notice(cs_name,src,CS_RPL_XOP_AUTH_SENT_END,nick);
		user *u = finduser(nick);
		if (u) {
			notice(ns_name, nick, NS_RPL_ATH_TEXT_NOTIFY, src);
		}
		return;
	}
}
/********************************************************************/
/**
 * input of a chanserv SOP/AOP/UOP/HOP/VOP command - remove a nick
 * from specified list of the specified channel
 */
void cs_xop_del(char *src, char *chan, int list, char *nick) {
	int addacc;
	int add[] =
			{ 0, cs_uop_del, cs_vop_del, cs_hop_del, cs_aop_del, cs_sop_del };
	user *u = finduser(src);
	if (!isregcs(chan)) {
		notice(cs_name, src, CS_ERR_NOTREG, chan);
		return;
	}
	ChanInfo *c = findchan(chan);
	if (!isreg(nick)) {
		notice(cs_name, src, NS_ERR_NOTREG, nick);
		return;
	}
	if ((addacc = cs_xop_get_level(u, c)) < add[list]) {
		notice(cs_name, src, CS_ERR_XOP_HIGHERACCESS, get_opacc(add[list]));
		return;
	}
	int existing_level = cs_isonlist(nick, chan, list,0);
	if (existing_level < 0) {
		notice(cs_name, src, CS_ERR_XOP_NOTONLIST, nick, get_opacc(list), chan);
		return;
	}
	op *o = find_list_entry(nick,chan,list);
	remove_from_list(o);
	notice(cs_name,src,CS_RPL_XOP_DELETED,nick,get_opacc(list),chan);
	return;
}
/********************************************************************/
/**
 * check the level a nick has to the specified channel
 */
int cs_xop_get_level(user *u, ChanInfo *c) {
	if(u->oper>cs_admin_access) {
		return ACCESS_SRA;
	}
	usernick *un = u->usernicks;
	int level = 0;
	while(un) {
		if(un->level==1)
			level = get_access_for_nick(c,un->n) -1;
		else
			level = get_access_for_nick(c,un->n);
		un = un->next;
	}
	return level;
}
/********************************************************************/
/**
 * input of a chanserv SOP/AOP/UOP/HOP/VOP command - list all the nicks
 * that have the specified access to the specified channel
 *
 */
void cs_xop_list(char *src, char *chan, int list) {
	int listacc;
	static char *addedby_lvl[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "\2ServiceRootAdmin\2" };
	int alist[] = { 0, cs_uop_list, cs_vop_list, cs_hop_list, cs_aop_list, cs_sop_list };
	user *u = finduser(src);
	if (!isregcs(chan)) {
		notice(cs_name, src, CS_ERR_NOTREG, chan);
		return;
	}
	ChanInfo *c = findchan(chan);

	if ((listacc = cs_xop_get_level(u, c)) < alist[list]) {
		notice(cs_name, src, CS_ERR_XOP_HIGHERACCESS, get_opacc(alist[list]));
		return;
	}
	op *o = global_op_list;
	int i = 0;
	char str[128];
	notice(cs_name, src, CS_RPL_XOP_LIST_BEGIN, get_opacc(list), chan);
	while (o) {
		if (stricmp(chan, o->chan->name) == 0) {
			if (o->level == list) {
				strftime(str, 100, "%d/%m/%Y %T %Z", localtime(&o->addedon));
				notice(cs_name, src, CS_RPL_XOP_LIST, i + 1, o->nick->nick,
						addedby_lvl[o->addedbyacc], o->addedby, str);
				i++;
			}
		}
		o = o->next;
	}
	if ((i > 1) || (i == 0)) {
		notice(cs_name, src, CS_RPL_XOP_LIST_COMPLETE1, i);
	} else {
		notice(cs_name, src, CS_RPL_XOP_LIST_COMPLETE2);
	}
}
/********************************************************************/
/**
 * input of a chanserv SOP/AOP/UOP/HOP/VOP command - remove all the
 * nicks from the specified list of the specified channel
 */
void cs_xop_wipe(char *src, char *chan, int list) {
	int wipeacc;
	int wipe[] = { 0, cs_uop_wipe, cs_vop_wipe, cs_hop_wipe, cs_aop_wipe,cs_sop_wipe };
	user *u = finduser(src);
	if (!isregcs(chan)) {
		notice(cs_name, src, CS_ERR_NOTREG, chan);
		return;
	}
	ChanInfo *c = findchan(chan);
	if ((wipeacc = cs_xop_get_level(u, c)) < wipe[list]) {
		notice(cs_name, src, CS_ERR_XOP_HIGHERACCESS, get_opacc(wipe[list]));
		return;
	}
	int i = 0;
	op *o = global_op_list;
	while (o) {
		if (stricmp(chan, o->chan->name) == 0) {
			if (o->level == list) {
				i++;
				remove_from_list(o);
			}
		}
		o = o->next;
	}

	if (i == 1)
		notice(cs_name, src, CS_RPL_XOP_WIPED1, get_opacc(list), chan);
	else
		notice(cs_name, src, CS_RPL_XOP_WIPED2, get_opacc(list), chan, i);
	return;
}
op *find_list_entry(char *nick,char *chan,int level) {
	op *o = global_op_list;
	while (o) {
		if((stricmp(o->nick->nick, nick) ==0) && (stricmp(o->chan->name, chan) ==0) && (o->level == level)) {
			return o;
		}
		o = o->next;
	}
	return NULL;
}
int get_access_for_nick(ChanInfo *c, NickInfo *n) {
	op *o = global_op_list;
	while(o) {
		notice(cs_name,"Fish-Guts","%s->%s: %i",o->chan->name,o->nick->nick,o->level);
		if((o->nick->id==n->id) && (stricmp(c->name,o->chan->name)==0)) {
			return o->level;
		}
		o = o->next;
	}
	return 0;
}
void move_in_list(char *nick, char *chan, int level, int existing_level, char *addnick, int addlevel) {
	op *o = find_list_entry(nick,chan,existing_level);
	o->level = level;
	o->addedby = sstrdup(addnick);
	o->addedbyacc = addlevel;
	o->addedon = time(NULL);
}

void remove_from_list(op *o) {
	if (o->prev)
		o->prev->next = o->next;
	else
		global_op_list = o->next;
	if (o->next)
		o->next->prev = o->prev;
	free(o);
}
