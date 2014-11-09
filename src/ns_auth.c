/*
 * ns_auth.c
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

void ns_auth(char *src, int ac, char **av) {
	char *cmd = av[1];
	if (ac < 2) {
		notice(ns_name, src, NS_ERR_ATH_USAGE, ns_name);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"AUTH");
		return;
	}
	if (stricmp(cmd, "ACCEPT") == 0) {
		ns_auth_accept(src, ac, av);
	} else if (stricmp(cmd, "DECLINE") == 0) {
		ns_auth_decline(src, ac, av);
	} else if (stricmp(cmd, "READ") == 0) {
		ns_auth_read(src, ac, av);
	} else if (stricmp(cmd, "LIST") == 0) {
		ns_auth_list(src, ac, av);
	} else {
		notice(ns_name, src, NS_ERR_NOSUCHCMD, cmd);
		notice(ns_name, src, NS_RPL_HLP, ns_name, "AUTH");
		return;
	}
}
void ns_auth_accept(char *src, int ac, char **av) {
	static char *xop[] = { "", UOP_STR, VOP_STR, HOP_STR, AOP_STR, SOP_STR };
	user *u = finduser(src);
	if (ac < 3) {
		notice(ns_name, src, NS_ERR_ATH_ACCEPTUSAGE, ns_name);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"AUTH ACCEPT");
		notice(as_name,src,xop[4]);
		return;
	}
	/* if the nickname is not registered, trigger an error */
	if (!isreg(src)) {
		notice(ns_name, src, NS_ERR_NOTREG);
		return;
	}
	NickInfo *n = findnick(src);
	/* if the user has not identified for then nickname, trigger an error */
	if (!isidentified(u, src)) {
		notice(ns_name, src, NS_ERR_ACCESSDENIED, src);
		notice(ns_name, src, NS_RPL_NEEDIDENTIFY);
		return;
	}
	/* if the supplied value is not a number, issue an error message */
	if (!isnum(av[2])) {
		notice(ns_name, src, NS_ERR_ATH_ISNONUM);
		notice(ns_name, src, NS_ERR_ATH_ACCEPTUSAGE, ns_name);
		notice(ns_name, src, NS_RPL_HLP, ns_name, "AUTH", "ACCEPT");
		return;
	}
	/* if the value if greater than the number of actual requests, trigger an error */
	if ((atoi(av[2]) > n->authcount) || (atoi(av[2]) == 0)) {
		notice(ns_name, src, NS_ERR_ATH_NUMTOOBIG, atoi(av[2]));
		return;
	} else {
		int i = 0;
		auth *a = n->authlist;
		while ((i + 1) < atoi(av[2])) {
			a = a->next;
			i++;
		}
		if (a->type == AUTH_NOTIFY) {
			/*NickInfo *n2 = findnick(a->sender);
			n2->notifycount++;
			n2->notifylist = srealloc(n2->notifylist,
					sizeof(char *) * n2->notifycount);
			n2->notifylist[n2->notifycount - 1] = sstrdup(src);
			notice(ns_name, src, NS_RPL_ATH_ACCEPTED, a->sender);
			user *u1 = finduser(a->sender);
			if (u1) {
				notice(ns_name, u1->nick, NS_RPL_ATH_HASACCEPTED_NFY, src);
			}
			notice(ns_name, src, NS_RPL_ATH_ACCEPTED, a->sender);*/
			return;
		} else if (a->type > AUTH_NOTIFY) {
			ChanInfo *c = findchan(a->target);
			if (a->type == AUTH_FOUND) {
				strscpy(c->founder, src, NICKMAX);
			} else if (a->type == AUTH_SUCC) {
				strscpy(c->successor, src, NICKMAX);
			} else {
/*
				op *o = scalloc(sizeof(op), 1);
				o->addedby = sstrdup(a->sender);
				o->addedbyacc = a->acctype;
				o->level = a->type;
				o->addedon = a->date;
				o->nick = sstrdup(src);
				o->chan = sstrdup(c->name);
				o->next = global_op_list;
				update_xop_list(o);
				inc_list(c, a->type);
				user *u1 = finduser(a->sender);
				if (u1) {
					notice(ns_name, a->sender, NS_RPL_ATH_HASACCEPTED_CHN, src,
							xop[a->type], a->target);
				}
				notice(ns_name, src, NS_RPL_ATH_ACCEPTED, a->sender);
			*/}
		}
		n->authcount--;
		free(a->sender);
		free(a->target);
		if (a->prev)
			a->prev->next = a->next;
		else
			n->authlist = a->next;
		if (a->next)
			a->next->prev = a->prev;
		free(a);
	}
}
void ns_auth_decline(char *src, int ac, char **av) {
	int count = 0;
	user *u = finduser(src);
	if (ac < 3) {
		notice(ns_name, src, NS_ERR_ATH_DECLINEUSAGE, ns_name);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"AUTH DECLINE");
		return;
	}
	/* if the nickname is not registered, trigger an error */
	if (!isreg(src)) {
		notice(ns_name, src, NS_ERR_NOTREG);
		return;
	}
	NickInfo *n = findnick(src);
	/* if the user has not identified for then nickname, trigger an error */
	if (!isidentified(u, src)) {
		notice(ns_name, src, NS_ERR_ACCESSDENIED, src);
		notice(ns_name, src, NS_RPL_NEEDIDENTIFY);
		return;
	}
	/* if the supplied value is not a number, trigger an error */
	if (!isnum(av[2])) {
		notice(ns_name, src, NS_ERR_ATH_ISNONUM);
		notice(ns_name, src, NS_ERR_ATH_DECLINEUSAGE, ns_name);
		notice(ns_name, src, NS_RPL_HLP, ns_name, "AUTH", "DECLINE");
		return;
	}
	/* if the value if greater than the number of actual requests, trigger an error */
	if (atoi(av[2]) > count) {
		notice(ns_name, src, NS_ERR_ATH_NUMTOOBIG, atoi(av[2]));
		return;
	} else {
		int i = 0;
		auth *a = n->authlist;
		while ((i + 1) < atoi(av[2])) {
			a = a->next;
			i++;
		}
		notice(ns_name, src, NS_RPL_ATH_DECLINED, a->sender);
		n->authcount--;
		free(a->sender);
		free(a->target);
		if (a->prev)
			a->prev->next = a->next;
		else
			n->authlist = a->next;
		if (a->next)
			a->next->prev = a->prev;
		free(a);
	}
	return;
}
void ns_auth_list(char *src, int ac, char **av) {
	user *u = finduser(src);
	if (isidentified(u, src) < 0) {
		notice(ns_name, src, NS_ERR_ACCESSDENIED, src);
		notice(ns_name, src, NS_RPL_NEEDIDENTIFY, src);
		return;
	}
	NickInfo *n = findnick(src);
	if (n->authcount <= 0) {
		notice(ns_name, src, NS_RPL_ATH_NOENTRIES);
		return;
	} else {
		int i;
		auth *a = n->authlist;
		notice(ns_name, src, NS_RPL_ATH_PENDING);
		for (i = 0; i < n->authcount; i++) {
			notice(ns_name, src, NS_RPL_ATH_REQUESTLIST, (i + 1), a->sender);
			a = a->next;
		}
		if (i == 0) {
			notice(ns_name, src, NS_ERR_ATH_LISTCOMPLETE1);
		} else {
			notice(ns_name, src, NS_ERR_ATH_LISTCOMPLETE2, i);
		}
		return;
	}
	return;
}
void ns_auth_read(char *src, int ac, char **av) {
	static char *xop[] = { "", UOP_STR, VOP_STR, HOP_STR, AOP_STR, SOP_STR };
	/* AUTH types are:
	 * 0 = notify request
	 * 1 = UOP list
	 * 2 = VOP list
	 * 3 = HOP list
	 * 4 = AOP list
	 * 5 = SOP list
	 * 6 = successor for a channel
	 * 7 = founder for a channel
	 */
	/* this is the pending text */
	static char *text[] = { NS_RPL_ATH_TEXT1, NS_RPL_ATH_TEXT2,
			NS_RPL_ATH_TEXT3, NS_RPL_ATH_TEXT4, NS_RPL_ATH_TEXT5,
			NS_RPL_ATH_TEXT6, NS_RPL_ATH_TEXT7, NS_RPL_ATH_TEXT8 };
	if (ac < 3) {
		notice(ns_name, src, NS_ERR_ATH_READUSAGE, ns_name);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"AUTH READ");
		return;
	}
	NickInfo *n = findnick(src);
	user *u = finduser(src);
	/* if the nickname is not registered, trigger an error */
	if (!isreg(src)) {
		notice(ns_name, src, NS_ERR_NOTREG);
		return;
	}
	/* if the user has not identified for then nickname, trigger an error */
	if (!isidentified(u, src)) {
		notice(ns_name, src, NS_ERR_ACCESSDENIED, src);
		notice(ns_name, src, NS_RPL_NEEDIDENTIFY);
		return;
	}
	/* if the supplied value is not a number, trigger an error */
	if (!isnum(av[2])) {
		notice(ns_name, src, NS_ERR_ATH_ISNONUM);
		notice(ns_name, src, NS_ERR_ATH_READUSAGE, ns_name);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"AUTH READ");
		return;
	}
	/* if the value if greater than the number of actual requests, trigger an error */
	if ((atoi(av[2]) > n->authcount) || (atoi(av[2]) == 0)) {
		notice(ns_name, src, NS_ERR_ATH_NUMTOOBIG, atoi(av[2]));
		return;
	} else {
		int u;
		auth *a = n->authlist;
		for (u = 1; u <= atoi(av[2]); u++) {
			if (u == atoi(av[2])) {
				if (a->type == AUTH_NOTIFY) {
					notice(ns_name, src, NS_RPL_ATH_READNOTIFY, (atoi(av[2])),
							a->sender, text[a->type]);
					notice(ns_name, src, NS_RPL_ATH_TEXT1, a->sender);
				} else {
					notice(ns_name, src, NS_RPL_ATH_XOP_READ, av[2], a->sender,
							xop[a->type], a->target);
					return;
				}
			} else {
				a = a->next;
			}
		}
	}
	return;
}
