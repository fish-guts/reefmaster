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
		notice(as_name,src,"debug");
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
void cs_hop(char *src, int ac, char **av) {
	char *chan = av[1];
	if (stricmp(av[2], "ADD") == 0) {
		char *nick = av[3];
		cs_xop_add(src, chan, HOP_LIST, nick);
		return;
	} else if (stricmp(av[2], "DEL") == 0) {
		char *nick = av[3];
		cs_xop_del(src, chan, HOP_LIST, nick);
		return;
	} else if (stricmp(av[2], "LIST") == 0) {
		cs_xop_list(src, chan, HOP_LIST);
		return;
	} else if (stricmp(av[2], "WIPE") == 0) {
		cs_xop_wipe(src, chan, HOP_LIST);
		return;
	}
	return;
}
void cs_sop(char *src, int ac, char **av) {
	char *chan = av[1];
	if (stricmp(av[2], "ADD") == 0) {
		char *nick = av[3];
		cs_xop_add(src, chan, SOP_LIST, nick);
		return;
	} else if (stricmp(av[2], "DEL") == 0) {
		char *nick = av[3];
		cs_xop_del(src, chan, SOP_LIST, nick);
		return;
	} else if (stricmp(av[2], "LIST") == 0) {
		cs_xop_list(src, chan, SOP_LIST);
		return;
	} else if (stricmp(av[2], "WIPE") == 0) {
		cs_xop_wipe(src, chan, SOP_LIST);
		return;
	}
	return;
}
/********************************************************************/
/**
 * cs UOP - handle the chanserv UOP command
 */
void cs_uop(char *src, int ac, char **av) {
	char *chan = av[1];
	if (stricmp(av[2], "ADD") == 0) {
		char *nick = av[3];
		cs_xop_add(src, chan, UOP_LIST, nick);
		return;
	} else if (stricmp(av[2], "DEL") == 0) {
		char *nick = av[3];
		cs_xop_del(src, chan, UOP_LIST, nick);
		return;
	} else if (stricmp(av[2], "LIST") == 0) {
		cs_xop_list(src, chan, UOP_LIST);
		return;
	} else if (stricmp(av[2], "WIPE") == 0) {
		cs_xop_wipe(src, chan, UOP_LIST);
		return;
	}
	return;
}

/********************************************************************/
/**
 * cs VOP - handle the chanserv VOP command
 */
void cs_vop(char *src, int ac, char **av) {
	char *chan = av[1];
	if (stricmp(av[2], "ADD") == 0) {
		char *nick = av[3];
		cs_xop_add(src, chan, VOP_LIST, nick);
		return;
	} else if (stricmp(av[2], "DEL") == 0) {
		char *nick = av[3];
		cs_xop_del(src, chan, VOP_LIST, nick);
		return;
	} else if (stricmp(av[2], "LIST") == 0) {
		cs_xop_list(src, chan, VOP_LIST);
		return;
	} else if (stricmp(av[2], "WIPE") == 0) {
		cs_xop_wipe(src, chan, ADMIN_LIST);
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
	if(!isregcs(chan)) {
		notice(cs_name,src,CS_ERR_NOTREG,chan);
		return;
	}
	if(!isreg(nick)) {
		notice(cs_name,src,NS_ERR_NOTREG,nick);
		return;
	}
	notice(as_name,src,"Level: %i",cs_xop_get_level(finduser(src),findchan(chan)));

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
	if (cs_isonlist(nick, chan, list) < 0) {
		notice(cs_name, src, CS_ERR_XOP_NOTONLIST, nick, get_opacc(list), chan);
		return;
	}
	op *o = global_op_list;
	while (o) {
		if (stricmp(chan, o->chan->name) == 0) {
			if (stricmp(nick, o->nick->nick) == 0) {
				if (o->prev)
					o->prev->next = o->next;
				else
					global_op_list = o->next;
				if (o->next)
					o->next->prev = o->prev;
				free(o);
				notice(cs_name, src, CS_RPL_XOP_DELETED, nick, get_opacc(list),
						chan);
				return;
			}
		}
		o = o->next;
	}
}
/********************************************************************/
/**
 * check the level a nick has to the specified channel
 */
int cs_xop_get_level(user *u, ChanInfo *c) {
	if(u->oper>cs_admin_access) {
		return ACCESS_SRA;
	}
	struct usernicks *un = u->usernicks;
	int level = 0;
	while(un) {
		NickInfo *n = findnick(un->nick);
		if(un->level==1)
			level = get_access_for_nick(c,n) -1;
		else
			level = get_access_for_nick(c,n);
		un = un->next;
	}
	return level;
}
int get_access_for_nick(ChanInfo *c, NickInfo *n) {
	op *o = global_op_list;
	while(o) {
		if(o->nick->id==n->id) {
			return o->level;
		}
		o = o->next;
	}
	return 0;
}
/********************************************************************/
/**
 * input of a chanserv SOP/AOP/UOP/HOP/VOP command - list all the nicks
 * that have the specified access to the specified channel
 *
 */
void cs_xop_list(char *src, char *chan, int list) {
	int listacc;
	*addedby_lvl[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "\2ServiceRootAdmin\2" };
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
				if (o->prev)
					o->prev->next = o->next;
				else
					global_op_list = o->next;
				if (o->next)
					o->next->prev = o->prev;
				free(o);
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
