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
	int rc = 0;
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
			notice(ns_name, src, NS_ERR_NOTREG, av[2]);
			notice(ns_name, src, NS_ERR_NFY_MUSTBEREG2);
			return;
		}
		if ((rc = ns_notifylist(src, nick)) > 0) {
			notice(ns_name, src, NS_RPL_NFY_ALREADYINLIST, av[2]);
			return;
		}
		/* the sending nick */
		NickInfo *n1 = findnick(src);
		/* the target nick */
		NickInfo *n2 = findnick(nick);
		/* if the target nick has AUTH for notify requests enabled, add a
		 * respective entry to the auth list.
		 */
		if (n2->auth_notify == 1) {
			if (findauth_notify(src, nick)) {
				notice(as_name, src, NS_RPL_ATH_ALREADYINLIST, nick);
				return;
			}
			notice(ns_name, src, NS_RPL_NFY_REQUESTSENT1, nick);
			notice(ns_name, src, NS_RPL_NFY_REQUESTSENT2, nick);
			notice(ns_name, src, NS_RPL_NFY_REQUESTSENT3, nick);
			auth *a = scalloc(sizeof(auth), 1);
			user *u1;
			a->sender = sstrdup(src);
			a->target = sstrdup(nick);
			a->type = 0;
			a->list = sstrdup(src);
			a->next = n2->authlist;
			a->date = time(NULL);
			if (n2->authlist)
				n2->authlist->prev = a;
			n2->authlist = a;
			n2->authcount++;
			if ((u1 = finduser(nick)) != NULL) {
				notice(ns_name, nick, NS_RPL_ATH_TEXT1, src);
			}
			return;
		}
		/* if no authorization is required, just process with adding the entry */
		else {
			n1->notifycount++;
			n1->notifylist = srealloc(n1->notifylist,
					sizeof(char *) * n1->notifycount);
			n1->notifylist[n1->notifycount - 1] = nick;
			notice(ns_name, src, NS_RPL_NFY_NICKADDED, nick);
		}
	}
}
void ns_notify_del(char *src,int ac, char **av) {
	int rc = 0;
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
		if ((rc = ns_notifylist(src, nick)) <= 0) {
			notice(ns_name, src, NS_ERR_NFY_NICKNOTFOUND, av[2]);
			return;
		}
		char **notify;
		int i = 0;
		for (notify = n->notifylist, i = 0; i < n->notifycount;
				notify++, i++) {
			if (stricmp(*notify, nick) == 0)
				break;
		}
		n->notifycount--;
		if (i < n->notifycount) /* if it wasn't the last entry... */
			memmove(notify, notify + 1,
					(n->notifycount - i) * sizeof(char *));
		if (n->notifycount) /* if there are any entries left... */
			n->notifylist = srealloc(n->notifylist,
					n->notifycount * sizeof(char *));
		else {
			free(n->notifylist);
			n->notifylist = NULL;
		}
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
	} else {
		NickInfo *n;
		n = findnick(src);
		user *u1 = finduser(src);
		if (isidentified(u1, src) < 0) {
			notice(ns_name, src, NS_ERR_ACCESSDENIED, src);
			notice(ns_name, src, NS_RPL_NEEDIDENTIFY, src);
			return;
		}
		if (n->notifycount <= 0) {
			if (ac > 2)
				notice(ns_name, src, NS_RPL_NFY_NOENTRIES2, nick);
			else
				notice(ns_name, src, NS_RPL_NFY_NOENTRIES);
			return;
		} else {
			notice(ns_name, src, NS_RPL_NFY_LIST, nick);
			int i;
			for (i = 1; i <= n->notifycount; i++) {
				notice(ns_name, src, NS_RPL_NFY_LISTENTRIES, i,
						n->notifylist[i - 1]);
			}
			if (i == 2)
				notice(ns_name, src, NS_RPL_ACC_LISTFOUND1, i - 1);
			else
				notice(ns_name, src, NS_RPL_ACC_LISTFOUND2, i - 1);
			return;
		}
	}
}
void ns_notify_wipe(char *src,int ac,char **av) {

}
/********************************************************************/
/**
 * look for an entry in the target's notify list
 */
int ns_notifylist(char *src, char *dest) {
	NickInfo *n = findnick(src);
	int i;
	for (i = 0; i < n->notifycount; i++) {
		if (stricmp(dest, n->notifylist[i]) == 0) {
			return 1;
		}
	}
	return -1;
}
