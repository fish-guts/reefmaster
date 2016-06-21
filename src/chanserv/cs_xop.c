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

static char *acclist[] = { NULL, "Uop", "Vop", "Hop", "Aop", "Sop", "Cop", "Qop", "Successor", "Founder" };
static char *chan_access_level[] = {
		"0", // Disabled
		"1", // Uop
		"2", // Vop
		"3", // Hop
		"4", // Aop
		"5", // Sop
		"6", // Cop
		"7", // Qop
		"8", // Successor
		"9", // Founder identified for nick
		"10", // Full founder (identified for chan)
		"\2ServiceRootAdmin\2" // SRA
};

/********************************************************************/
/**
 * if the target nick has authorization for channel lists enabled
 * add an auth entry
 */
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
		notice(cs_name,src,CS_XOP_RPL_AUTH_REQUIRED,nick);
		if(list<AUTH_SUCC) {
			notice(cs_name,src,CS_XOP_RPL_AUTH_SENT_XOP,nick,acclist[list],chan);
		} else {
			notice(cs_name,src,CS_XOP_RPL_AUTH_SENT_SF,nick,acclist[list],chan);
		}
		notice(cs_name,src,CS_XOP_RPL_AUTH_SENT_END,nick);
		user *u = finduser(nick);
		if (u) {
			notice(ns_name, nick, NS_AUTH_RPL_TEXT_CHAN, src,acclist[list],chan);
		}
		return;
	}
}

/********************************************************************/
/**
 * add an access entry to the global op list
 */
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
			notice(cs_name,src,CS_XOP_RPL_USAGE,"AOP <Channel> ADD <Nickname>");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"AOP ADD");
			return;
		}
		chan = av[1];
		nick = av[3];
		if(findchan(chan)->aop_count>=cs_aops_max) {
			notice(cs_name,src,CS_XOP_ERR_LIMIT,"Aop",cs_aops_max,chan);
			return;

		}
		cs_xop_add(src, chan, AOP_LIST, nick);

		return;
	} else if (stricmp(av[2], "DEL") == 0) {
		if(ac<4) {
			notice(cs_name,src,CS_XOP_RPL_USAGE,"AOP <Channel> DEL <Nickname>");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"AOP DEL");
			return;
		}
		chan = av[1];
		nick = av[3];
		cs_xop_del(src, chan, AOP_LIST, nick);
		return;
	} else if (stricmp(av[2], "LIST") == 0) {
		if(ac<3) {
			notice(cs_name,src,CS_XOP_RPL_USAGE,"AOP <Channel> LIST");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"AOP LIST");
			return;
		}
		chan = av[1];
		cs_xop_list(src, chan, AOP_LIST);
		return;
	} else if (stricmp(av[2], "WIPE") == 0) {
		if(ac<3) {
			notice(cs_name,src,CS_XOP_RPL_USAGE,"AOP <Channel> LIST");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"AOP LIST");
			return;
		}
		chan = av[1];
		cs_xop_wipe(src, chan, AOP_LIST);
		return;
	} else {
		notice(cs_name,src,CS_ERR_NOSUCHCMD,av[2]);
		notice(cs_name,src,CS_XOP_ERR_USAGE,"AOP");
		notice(cs_name,src,CS_RPL_HLP,cs_name,"AOP");
		return;
	}
	return;
}

/********************************************************************/
/**
 * cs COP - handle the chanserv COP command
 */
void cs_cop(char *src, int ac, char **av) {
	char *chan;
	char *nick;
	if (stricmp(av[2], "ADD") == 0) {
		if(ac<4) {
			notice(cs_name,src,CS_XOP_RPL_USAGE,"COP <Channel> ADD <Nickname>");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"COP ADD");
			return;
		}
		chan = av[1];
		nick = av[3];
		if(findchan(chan)->cop_count>=cs_cops_max) {
			notice(cs_name,src,CS_XOP_ERR_LIMIT,"Cop",cs_cops_max,chan);
			return;

		}
		cs_xop_add(src, chan, COP_LIST, nick);
		return;
	} else if (stricmp(av[2], "DEL") == 0) {
		if(ac<4) {
			notice(cs_name,src,CS_XOP_RPL_USAGE,"COP <Channel> DEL <Nickname>");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"COP DEL");
			return;
		}
		chan = av[1];
		nick = av[3];
		cs_xop_del(src, chan, COP_LIST, nick);
		return;
	} else if (stricmp(av[2], "LIST") == 0) {
		if(ac<3) {
			notice(cs_name,src,CS_XOP_RPL_USAGE,"COP <Channel> LIST");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"COP LIST");
			return;
		}
		chan = av[1];
		cs_xop_list(src, chan, COP_LIST);
		return;
	} else if (stricmp(av[2], "WIPE") == 0) {
		if(ac<3) {
			notice(cs_name,src,CS_XOP_RPL_USAGE,"COP <Channel> WIPE");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"COP WIPE");
			return;
		}
		chan = av[1];
		cs_xop_wipe(src, chan, COP_LIST);
		return;
	} else {
		notice(cs_name,src,CS_ERR_NOSUCHCMD,av[2]);
		notice(cs_name,src,CS_XOP_ERR_USAGE,"COP");
		notice(cs_name,src,CS_RPL_HLP,cs_name,"COP");
		return;
	}
	return;
}

/********************************************************************/
/**
 * cs QOP - handle the chanserv QOP command
 */
void cs_qop(char *src, int ac, char **av) {
	char *chan;
	char *nick;
	if (stricmp(av[2], "ADD") == 0) {
		if(ac<4) {
			notice(cs_name,src,CS_XOP_RPL_USAGE,"QOP <Channel> ADD <Nickname>");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"QOP ADD");
			return;
		}
		chan = av[1];
		nick = av[3];
		if(findchan(chan)->qop_count>=cs_qops_max) {
			notice(cs_name,src,CS_XOP_ERR_LIMIT,"Qop",cs_qops_max,chan);
			return;

		}
		cs_xop_add(src, chan, QOP_LIST, nick);
		return;
	} else if (stricmp(av[2], "DEL") == 0) {
		if(ac<4) {
			notice(cs_name,src,CS_XOP_RPL_USAGE,"QOP <Channel> DEL <Nickname>");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"QOP DEL");
			return;
		}
		chan = av[1];
		nick = av[3];
		cs_xop_del(src, chan, QOP_LIST, nick);
		return;
	} else if (stricmp(av[2], "LIST") == 0) {
		if(ac<3) {
			notice(cs_name,src,CS_XOP_RPL_USAGE,"QOP <Channel> LIST");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"QOP LIST");
			return;
		}
		chan = av[1];
		cs_xop_list(src, chan, QOP_LIST);
		return;
	} else if (stricmp(av[2], "WIPE") == 0) {
		if(ac<3) {
			notice(cs_name,src,CS_XOP_RPL_USAGE,"QOP <Channel> LIST");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"QOP LIST");
			return;
		}
		chan = av[1];
		cs_xop_wipe(src, chan, QOP_LIST);
		return;
	} else {
		notice(cs_name,src,CS_ERR_NOSUCHCMD,av[2]);
		notice(cs_name,src,CS_XOP_ERR_USAGE,"QOP");
		notice(cs_name,src,CS_RPL_HLP,cs_name,"QOP");
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
			notice(cs_name,src,CS_XOP_RPL_USAGE,"HOP <Channel> ADD <Nickname>");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"HOP ADD");
			return;
		}
		chan = av[1];
		nick = av[3];
		if(findchan(chan)->hop_count>=cs_hops_max) {
			notice(cs_name,src,CS_XOP_ERR_LIMIT,"Hop",cs_aops_max,chan);
			return;
		}
		cs_xop_add(src, chan, HOP_LIST, nick);
		return;
	} else if (stricmp(av[2], "DEL") == 0) {
		if(ac<4) {
			notice(cs_name,src,CS_XOP_RPL_USAGE,"HOP <Channel> DEL <Nickname>");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"HOP DEL");
			return;
		}
		chan = av[1];
		nick = av[3];
		cs_xop_del(src, chan, HOP_LIST, nick);
		return;
	} else if (stricmp(av[2], "LIST") == 0) {
		if(ac<3) {
			notice(cs_name,src,CS_XOP_RPL_USAGE,"HOP <Channel> LIST");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"HOP LIST");
			return;
		}
		chan = av[1];
		cs_xop_list(src, chan, HOP_LIST);
		return;
	} else if (stricmp(av[2], "WIPE") == 0) {
		if(ac<3) {
			notice(cs_name,src,CS_XOP_RPL_USAGE,"HOP <Channel> LIST");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"HOP LIST");
			return;
		}
		chan = av[1];
		cs_xop_wipe(src, chan, HOP_LIST);
		return;
	} else {
		notice(cs_name,src,CS_ERR_NOSUCHCMD,av[2]);
		notice(cs_name,src,CS_XOP_ERR_USAGE,"HOP");
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
			notice(cs_name,src,CS_XOP_RPL_USAGE,"SOP <Channel> ADD <Nickname>");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"SOP ADD");
			return;
		}
		chan = av[1];
		nick = av[3];
		if(findchan(chan)->sop_count>=cs_sops_max) {
			notice(cs_name,src,CS_XOP_ERR_LIMIT,"Sop",cs_sops_max,chan);
			return;

		}
		cs_xop_add(src, chan, SOP_LIST, nick);
		return;
	} else if (stricmp(av[2], "DEL") == 0) {
		if(ac<4) {
			notice(cs_name,src,CS_XOP_RPL_USAGE,"SOP <Channel> DEL <Nickname>");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"SOP DEL");
			return;
		}
		chan = av[1];
		nick = av[3];
		cs_xop_del(src, chan, SOP_LIST, nick);
		return;
	} else if (stricmp(av[2], "LIST") == 0) {
		if(ac<3) {
			notice(cs_name,src,CS_XOP_RPL_USAGE,"SOP <Channel> LIST");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"SOP LIST");
			return;
		}
		chan = av[1];
		cs_xop_list(src, chan, SOP_LIST);
		return;
	} else if (stricmp(av[2], "WIPE") == 0) {
		if(ac<3) {
			notice(cs_name,src,CS_XOP_RPL_USAGE,"SOP <Channel> LIST");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"SOP LIST");
			return;
		}
		chan = av[1];
		cs_xop_wipe(src, chan, SOP_LIST);
		return;
	} else {
		notice(cs_name,src,CS_ERR_NOSUCHCMD,av[2]);
		notice(cs_name,src,CS_XOP_ERR_USAGE,"SOP");
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
			notice(cs_name,src,CS_XOP_RPL_USAGE,"UOP <Channel> ADD <Nickname>");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"UOP ADD");
			return;
		}
		chan = av[1];
		nick = av[3];
		if(findchan(chan)->uop_count>=cs_uops_max) {
			notice(cs_name,src,CS_XOP_ERR_LIMIT,"Uop",cs_uops_max,chan);
			return;

		}
		cs_xop_add(src, chan, UOP_LIST, nick);
		return;
	} else if (stricmp(av[2], "DEL") == 0) {
		if(ac<4) {
			notice(cs_name,src,CS_XOP_RPL_USAGE,"UOP <Channel> DEL <Nickname>");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"UOP DEL");
			return;
		}
		chan = av[1];
		nick = av[3];
		cs_xop_del(src, chan, UOP_LIST, nick);
		return;
	} else if (stricmp(av[2], "LIST") == 0) {
		if(ac<3) {
			notice(cs_name,src,CS_XOP_RPL_USAGE,"UOP <Channel> LIST");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"UOP LIST");
			return;
		}
		chan = av[1];
		cs_xop_list(src, chan, UOP_LIST);
		return;
	} else if (stricmp(av[2], "WIPE") == 0) {
		if(ac<3) {
			notice(cs_name,src,CS_XOP_RPL_USAGE,"UOP <Channel> LIST");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"UOP LIST");
			return;
		}
		chan = av[1];
		cs_xop_wipe(src, chan, UOP_LIST);
		return;
	} else {
		notice(cs_name,src,CS_ERR_NOSUCHCMD,av[2]);
		notice(cs_name,src,CS_XOP_ERR_USAGE,"UOP");
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
			notice(cs_name,src,CS_XOP_RPL_USAGE,"VOP <Channel> ADD <Nickname>");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"VOP ADD");
			return;
		}
		chan = av[1];
		nick = av[3];
		if(findchan(chan)->vop_count>=cs_vops_max) {
			notice(cs_name,src,CS_XOP_ERR_LIMIT,"Vop",cs_vops_max,chan);
			return;

		}
		cs_xop_add(src, chan, VOP_LIST, nick);
		return;
	} else if (stricmp(av[2], "DEL") == 0) {
		if(ac<4) {
			notice(cs_name,src,CS_XOP_RPL_USAGE,"VOP <Channel> DEL <Nickname>");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"VOP DEL");
			return;
		}
		chan = av[1];
		nick = av[3];
		cs_xop_del(src, chan, VOP_LIST, nick);
		return;
	} else if (stricmp(av[2], "LIST") == 0) {
		if(ac<3) {
			notice(cs_name,src,CS_XOP_RPL_USAGE,"VOP <Channel> LIST");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"VOP LIST");
			return;
		}
		chan = av[1];
		cs_xop_list(src, chan, VOP_LIST);
		return;
	} else if (stricmp(av[2], "WIPE") == 0) {
		if(ac<3) {
			notice(cs_name,src,CS_XOP_RPL_USAGE,"VOP <Channel> LIST");
			notice(cs_name,src,CS_RPL_HLP,cs_name,"VOP LIST");
			return;
		}
		chan = av[1];
		cs_xop_wipe(src, chan, VOP_LIST);
		return;
	} else {
		notice(cs_name,src,CS_ERR_NOSUCHCMD,av[2]);
		notice(cs_name,src,CS_XOP_ERR_USAGE,"VOP");
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
	int alist[] = { 0, cs_uop_add, cs_vop_add, cs_hop_add, cs_aop_add, cs_sop_add, cs_cop_add, cs_qop_add };
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
		notice(cs_name, src, CS_XOP_ERR_HIGHERACCESS, get_opacc(alist[list]));
		return;
	}
	int existing_level = cs_isonlist(nick,chan,list,1);
	NickInfo *n = findnick(nick);
	if(existing_level==0) {
		notice(cs_name,src,CS_XOP_ERR_ALREADYONLIST,nick,acclist[list],chan);
		return;
	} else if(cs_isfounder(n->id,chan)) {
		notice(cs_name,src,CS_XOP_ERR_FOUNDERCANNOTADD,nick,chan,acclist[list]);
		return;
	} else if(cs_issuccessor(n->id,chan)) {
		notice(cs_name,src,CS_XOP_ERR_FOUNDERCANNOTADD,nick,chan,acclist[list]);
		return;
	} else if(existing_level>0) {
		if((finduser(src)->oper < OPER_SERVICES_ADMIN) && (n->auth_chan) && (list>existing_level)) {
			add_auth_entry(nick,chan,list,src,listacc);
			return;
		}
		move_in_list(nick,chan,list,existing_level,src,listacc);
		notice(cs_name,src,CS_XOP_RPL_MOVED,nick,acclist[existing_level], acclist[list],chan);
		return;
	} else {
		if((finduser(src)->oper < OPER_SERVICES_ADMIN) && (n->auth_chan) && (list>existing_level)) {
			add_auth_entry(nick,chan,list,src,listacc);
			return;
		}
		notice(cs_name,src,CS_XOP_RPL_ADDED,nick,acclist[list],chan);
		add_to_list(nick,chan,list,src,listacc);
	}
}

/********************************************************************/
/**
 * input of a chanserv SOP/AOP/UOP/HOP/VOP command - remove a nick
 * from specified list of the specified channel
 */
void cs_xop_del(char *src, char *chan, int list, char *nick) {
	int add[] =
			{ 0, cs_uop_del, cs_vop_del, cs_hop_del, cs_aop_del, cs_sop_del, cs_cop_del, cs_qop_del };
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

	if (cs_xop_get_level(u, c) < add[list]) {
		notice(cs_name, src, CS_XOP_ERR_HIGHERACCESS, get_opacc(add[list]));
		return;
	}

	int existing_level = cs_isonlist(nick, chan, list,0);

	if (existing_level < 0) {
		notice(cs_name, src, CS_XOP_ERR_NOTONLIST, nick, get_opacc(list), chan);
		return;
	}
	op *o = find_list_entry(nick,chan,list);
	remove_from_list(o);
	dec_list(chan,list);
	notice(cs_name,src,CS_XOP_RPL_DELETED,nick,get_opacc(list),chan);
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

	struct cschans *uc = u->cschans;
	while(uc) {
		if((stricmp(uc->channel,c->name)==0) && (uc->level==CHAN_IDENTIFIED)) {
			return ACCESS_FND_FULL;
		}
		uc = uc->next;
	}
	while(un) {
		if(un->level==2) {
			return get_access_for_nick(c,un->n);
		}
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
	int alist[] = { 0, cs_uop_list, cs_vop_list, cs_hop_list, cs_aop_list, cs_sop_list, cs_cop_list, cs_qop_list };
	user *u = finduser(src);
	if (!isregcs(chan)) {
		notice(cs_name, src, CS_ERR_NOTREG, chan);
		return;
	}
	ChanInfo *c = findchan(chan);

	if (cs_xop_get_level(u, c) < alist[list]) {
		notice(cs_name, src, CS_XOP_ERR_HIGHERACCESS, get_opacc(alist[list]));
		return;
	}
	op *o = global_op_list;
	int i = 0;
	char str[128];
	notice(cs_name, src, CS_XOP_RPL_LIST_BEGIN, get_opacc(list), chan);
	while (o) {
		if (stricmp(chan, o->chan->name) == 0) {
			if (o->level == list) {
				strftime(str, 100, "%d/%m/%Y %T %Z", localtime(&o->addedon));
				notice(cs_name, src, CS_XOP_RPL_LIST, i + 1, o->nick->nick,
						chan_access_level[o->addedbyacc], o->addedby, str);
				i++;
			}
		}
		o = o->next;
	}
	if ((i > 1) || (i == 0)) {
		notice(cs_name, src, CS_XOP_RPL_LIST_COMPLETE1, i);
	} else {
		notice(cs_name, src, CS_XOP_RPL_LIST_COMPLETE2);
	}
}
/********************************************************************/
/**
 * input of a chanserv SOP/AOP/UOP/HOP/VOP command - remove all the
 * nicks from the specified list of the specified channel
 */
void cs_xop_wipe(char *src, char *chan, int list) {
	int wipe[] = { 0, cs_uop_wipe, cs_vop_wipe, cs_hop_wipe, cs_aop_wipe, cs_sop_wipe, cs_cop_wipe, cs_qop_wipe };
	user *u = finduser(src);
	if (!isregcs(chan)) {
		notice(cs_name, src, CS_ERR_NOTREG, chan);
		return;
	}
	ChanInfo *c = findchan(chan);
	if (cs_xop_get_level(u, c) < wipe[list]) {
		notice(cs_name, src, CS_XOP_ERR_HIGHERACCESS, get_opacc(wipe[list]));
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
	wipe_list(chan,list);

	if (i == 1) {
		notice(cs_name, src, CS_XOP_RPL_WIPED1, get_opacc(list), chan);
	} else {
		notice(cs_name, src, CS_XOP_RPL_WIPED2, get_opacc(list), chan, i);
	}
	return;
}

/********************************************************************/
/**
 * find an auth entry
 */
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

/********************************************************************/
/**
 * find a op list entry
 */
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
/********************************************************************/
/**
 * return the type of access a nick has to a channel
 */
int get_access_for_nick(ChanInfo *c, NickInfo *n) {
	op *o = global_op_list;
	while(o) {
		if((stricmp(o->nick->nick,n->nick)==0) && (stricmp(c->name,o->chan->name)==0)) {
			return o->level;
		}
		o = o->next;
	}
	return 0;
}

/********************************************************************/
/**
 * change the access type of a nick
 */
void move_in_list(char *nick, char *chan, int level, int existing_level, char *addnick, int addlevel) {
	op *o = find_list_entry(nick,chan,existing_level);
	o->level = level;
	o->addedby = sstrdup(addnick);
	o->addedbyacc = addlevel;
	o->addedon = time(NULL);
	dec_list(chan,existing_level);
	inc_list(chan,level);

}

void inc_list(char *chan, int level) {
	ChanInfo *c = findchan(chan);
	if(!c) {
		addlog(2,"Channel not found");
	} else {
		switch(level) {
		case UOP_LIST:
			c->uop_count++;
			return;
		case VOP_LIST:
			c->vop_count++;
			return;
		case HOP_LIST:
			c->hop_count++;
			return;
		case AOP_LIST:
			c->aop_count++;
			return;
		case SOP_LIST:
			c->sop_count++;
			return;
		case COP_LIST:
			c->cop_count++;
			return;
		case QOP_LIST:
			c->qop_count++;
			return;
		default:
			return;
		}
	}
}

void wipe_list(char *chan, int level) {
	ChanInfo *c = findchan(chan);
	if(!c) {
		addlog(2,"Channel not found");
	} else {
		switch(level) {
		case UOP_LIST:
			c->uop_count = 0;
			return;
		case VOP_LIST:
			c->vop_count = 0;
			return;
		case HOP_LIST:
			c->hop_count = 0;
			return;
		case AOP_LIST:
			c->aop_count = 0;
			return;
		case SOP_LIST:
			c->sop_count = 0;
			return;
		case COP_LIST:
			c->cop_count = 0;
			return;
		case QOP_LIST:
			c->qop_count = 0;
			return;
		default:
			return;
		}
	}
}

void dec_list(char *chan, int level) {
	ChanInfo *c = findchan(chan);
	if(!c) {
		addlog(2,"Channel not found");
	} else {
		switch(level) {
		case UOP_LIST:
			c->uop_count--;
			return;
		case VOP_LIST:
			c->vop_count--;
			return;
		case HOP_LIST:
			c->hop_count--;
			return;
		case AOP_LIST:
			c->aop_count--;
			return;
		case SOP_LIST:
			c->sop_count--;
			return;
		case COP_LIST:
			c->cop_count--;
			return;
		case QOP_LIST:
			c->qop_count--;
			return;
		default:
			return;
		}
	}
}

/********************************************************************/
/**
 * remove a nick from the global op list
 */
void remove_from_list(op *o) {
	if (o->prev)
		o->prev->next = o->next;
	else
		global_op_list = o->next;
	if (o->next)
		o->next->prev = o->prev;
	free(o);
}
