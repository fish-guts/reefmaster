/*
 * ns_notify.c
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

/**
 * add a nickname to another nickname's notify list
 * @param src the sending nickname. Never null
 * @param nick the nick to be added. Never null
 */
void add_notify(char *src,char *nick) {
	NickInfo *n1 = findnick(src);
	NickInfo *n2 = findnick(nick);
	notify *no = scalloc(sizeof(notify), 1);
	no->next = n1->notifylist;
	if (n1->notifylist)
		n1->notifylist->prev = no;
	n1->notifylist = no;
	no->nick = n2;
	notice(ns_name, src, NS_RPL_NFY_NICKADDED, nick);
	return;
}

/**
 * add an entry to a nickname's auth list for for notify list
 */
void add_notify_auth_entry(char *src,char *nick) {
	NickInfo *n2 = findnick(nick);
	notice(ns_name, src, NS_RPL_NFY_REQUESTSENT1, nick);
	notice(ns_name, src, NS_RPL_NFY_REQUESTSENT2, nick);
	notice(ns_name, src, NS_RPL_NFY_REQUESTSENT3, nick);
	auth *a = scalloc(sizeof(auth), 1);
	user *u1;
	a->sender = sstrdup(src);
	a->target = sstrdup(nick);
	a->type = AUTH_NOTIFY;
	a->next = n2->authlist;
	a->date = time(NULL);
	if (n2->authlist)
		n2->authlist->prev = a;
	n2->authlist = a;
	if ((u1 = finduser(nick)) != NULL) {
		notice(ns_name, nick, NS_RPL_ATH_TEXT_NOTIFY, src);
	}
	return;
}
/********************************************************************/
/**
 * look for an entry in the target's notify list
 */
notify *find_notify(char *src, char *dest) {
	NickInfo *n = findnick(src);
	notify *no = n->notifylist;
	while(no) {
		if(stricmp(no->nick->nick,dest)==0) {
			return no;
		}
		no = no->next;
	}
	return NULL;
}
/**
 * ns_notify Handle the Nickserv NS_NOTIFY command.
 * Possible subcommands are:
 * ADD - Add a Nickname to the notify list
 * DEL - Delete a Nickname from the notify list
 * LIST - List all entries of the notify list
 * WIPE - Remove all entries from the notify list
 */
void ns_notify(char *src, int ac, char **av) {
	if(ac<2) {
		notice(ns_name,src,NS_ERR_NFY_USAGE);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"NOTIFY");
		return;
	}
	if (stricmp(av[1], "ADD") == 0) {
		ns_notify_add(src,ac,av);
	} else if (stricmp(av[1], "DEL") == 0) {
		ns_notify_del(src,ac,av);
	} else if (stricmp(av[1], "LIST") == 0) {
		ns_notify_list(src,ac,av);
	} else if (stricmp(av[1], "WIPE") == 0) {
		ns_notify_wipe(src,ac,av);
	} else {
		notice(ns_name, src, NS_ERR_NOSUCHCMD, av[1]);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"NOTIFY");
		return;
	}
	return;
}
void ns_notify_add(char *src,int ac,char **av) {
	if (!isreg(src)) {
		notice(ns_name, src, NS_ERR_NOTREG, src);
		notice(ns_name, src, NS_ERR_NFY_MUSTBEREG);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"NOTIFY ADD");
		return;
	}
	if (stricmp(src, av[2]) == 0) {
		notice(ns_name, src, NS_ERR_NFY_SAMEASSRC);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"NOTIFY ADD");
		return;
	} else {
		char *nick = sstrdup(av[2]);
		user *u = finduser(src);
		if (isidentified(u, src) < 0) {
			notice(ns_name, src, NS_ERR_ACCESSDENIED, src);
			notice(ns_name, src, NS_RPL_NEEDIDENTIFY, src);
			return;
		}
		if (!isreg(nick)) {
			notice(ns_name, src, NS_ERR_NOTREG, nick);
			notice(ns_name, src, NS_ERR_NFY_MUSTBEREG2);
			return;
		}
		if (find_notify(src, nick)) {
			notice(ns_name, src, NS_RPL_NFY_ALREADYINLIST, av[2]);
			return;
		}
		/* the target nick */
		NickInfo *n2 = findnick(nick);
		/* if the target nick has AUTH for notify requests enabled, add a
		 * respective entry to the auth list.
		 */
		if (n2->auth_notify) {
			if (findauth_notify(src, nick)) {
				notice(as_name, src, NS_RPL_ATH_ALREADYINLIST, nick);
				return;
			}
			add_notify_auth_entry(src,nick);
			return;
		}
		/* if no authorization is required, just process with adding the entry */
		else {
			add_notify(src,nick);
			return;
		}
	}
}
void ns_notify_del(char *src,int ac, char **av) {
	if (ac < 3) {
		notice(ns_name, src, NS_ERR_NFY_USAGE);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"NOTIFY DEL");
		return;
	}
	if ((src) < 0) {
		notice(ns_name, src, NS_ERR_NOTREG, src);
		notice(ns_name, src, NS_ERR_NFY_MUSTBEREG);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"NOTIFY DEL");
		return;
	} else {
		user *u = finduser(src);
		if (isidentified(u, src) < 0) {
			notice(ns_name, src, NS_ERR_ACCESSDENIED, src);
			notice(ns_name, src, NS_RPL_NEEDIDENTIFY, src);
			return;
		}
		char *nick = sstrdup(av[2]);
		NickInfo *n = findnick(src);
		if (!isreg(nick)) {
			notice(ns_name, src, NS_ERR_NOTREG, nick);
			notice(ns_name, src, NS_ERR_NFY_MUSTBEREG2);
			notice(ns_name, src, NS_RPL_HLP, ns_name,"NOTIFY DEL");
			return;
		}
		notify *no = find_notify(src,nick);
		if (!no) {
			notice(ns_name, src, NS_ERR_NFY_NICKNOTFOUND, av[2]);
			return;
		}
		if (no->prev)
			no->prev->next = no->next;
		else
			n->notifylist = no->next;
		if (no->next)
			no->next->prev = no->prev;
		free(no);
		notice(ns_name, src, NS_RPL_NFY_NICKDELETED, nick);
		return;
	}
	return;
}
void ns_notify_list(char *src,int ac,char **av) {
	char *nick;
	if (ac >= 3)
		nick = sstrdup(av[2]);
	else
		nick = src;
	if (!isreg(nick)) {
		notice(ns_name, src, NS_ERR_NOTREG, nick);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"NOTIFY LIST");
		return;
	}
	NickInfo *n;
	n = findnick(src);
	user *u1 = finduser(src);
	if (isidentified(u1, src) < 0) {
		notice(ns_name, src, NS_ERR_ACCESSDENIED, src);
		notice(ns_name, src, NS_RPL_NEEDIDENTIFY, src);
		return;
	}
	notice(ns_name,src,NS_RPL_NFY_LIST,nick);
	notify *no = n->notifylist;
	int i = 0;
	while(no) {
		i++;
		notice(ns_name,src,NS_RPL_NFY_LISTENTRIES,i,no->nick->nick);
		no = no->next;
	}
	if(i==1) {
		notice(ns_name,src,NS_RPL_NFY_LIST_COMPLETE_1);
		return;
	} else {
		notice(ns_name,src,NS_RPL_NFY_LIST_COMPLETE,i);
		return;
	}
}
void ns_notify_wipe(char *src,int ac,char **av) {
	char *nick;
	if (ac >= 3)
		nick = sstrdup(av[2]);
	else
		nick = src;
	if (!isreg(nick)) {
		notice(ns_name, src, NS_ERR_NOTREG, nick);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"NOTIFY LIST");
		return;
	}
	NickInfo *n;
	n = findnick(src);
	user *u1 = finduser(src);
	if (isidentified(u1, src) < 0) {
		notice(ns_name, src, NS_ERR_ACCESSDENIED, src);
		notice(ns_name, src, NS_RPL_NEEDIDENTIFY, src);
		return;
	}
	free(n->notifylist);
	n->notifylist = NULL;
	notice(ns_name,src,NS_RPL_NFY_WIPESUCCESS);
	return;
}
