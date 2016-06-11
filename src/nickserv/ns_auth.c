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

/********************************************************************/
/**
 * accept an auth request.param can never be null
 */
void accept_auth(char *src, auth *a,int i) {
	if(a->type==AUTH_NOTIFY) {
		accept_auth_notify(src,a);
	} else {
		accept_auth_chan(src,a);
	}
	remove_auth(src,a);
	notice(ns_name,src,NS_AUTH_RPL_ACCEPTED,i);
}

/********************************************************************/
/**
 * accept an add request for a channel access list. params can never be null
 */
void accept_auth_chan(char *src,auth *a) {
	add_to_list(src,a->target, a->type, a->sender, a->acclevel);
	return;
}

/********************************************************************/
/**
 * accept a notify list request. params can never be null
 */
void accept_auth_notify(char *src,auth *a) {
	add_notify(a->sender,src);
	return;
}
/********************************************************************/
/** check whether a nick has open requests
 *
 */
int has_open_auth(NickInfo *n) {
	if(n->authlist)
		return 1;
	return 0;
}

/********************************************************************/
/**
 * ns_auth Handle the Nickserv NS AUTH command.
 * Possible subcommands are:
 * ACCEPT - Accept the specified pending auth request
 * DECLINE - Reject the specified pending auth request.
 * LIST - Lists all pending auth request
 * READ - Read the specified pending auth request.
 */
void ns_auth(char *src, int ac, char **av) {
	char *cmd = av[1];
	if (ac < 2) {
		notice(ns_name, src, NS_AUTH_ERR_USAGE, ns_name);
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

/********************************************************************/
/*
 * Handles the NS AUTH ACCEPT command. Purpose is to accept a request
 * that authorization is required for.
 */
void ns_auth_accept(char *src, int ac, char **av) {
	user *u = finduser(src);
	if (ac < 3) {
		static char *xop[] = { "", UOP_STR, VOP_STR, HOP_STR, AOP_STR, SOP_STR };
		notice(ns_name, src, NS_AUTH_ERR_ACCEPTUSAGE, ns_name);
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
	/* if the user has not identified for then nickname */
	if (!isidentified(u, src)) {
		notice(ns_name, src, NS_ERR_ACCESSDENIED, src);
		notice(ns_name, src, NS_RPL_NEEDIDENTIFY);
		return;
	}
	/* if the supplied value is not a number */
	if (!isnum(av[2])) {
		notice(ns_name, src, NS_AUTH_ERR_ISNONUM);
		notice(ns_name, src, NS_AUTH_ERR_ACCEPTUSAGE, ns_name);
		notice(ns_name, src, NS_RPL_HLP, ns_name, "AUTH", "ACCEPT");
		return;
	}
	if (atoi(av[2]) == 0) {
		notice(ns_name, src, NS_AUTH_ERR_NUMTOOBIG, atoi(av[2]));
		return;
	} else {
		int i = 0;
		auth *a = n->authlist;
		while(a) {
			i++;
			if(atoi(av[2])==i) {
				accept_auth(src,a,i);
				return;
			}
			a = a->next;
		}
		notice(ns_name, src, NS_AUTH_ERR_NUMTOOBIG, atoi(av[2]));
		return;
	}
}
/********************************************************************/
/**
 * decline an auth request
 */
void ns_auth_decline(char *src, int ac, char **av) {
	user *u = finduser(src);
	if (ac < 3) {
		notice(ns_name, src, NS_AUTH_ERR_DECLINEUSAGE, ns_name);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"AUTH DECLINE");
		return;
	}
	/* if the nickname is not registered */
	if (!isreg(src)) {
		notice(ns_name, src, NS_ERR_NOTREG);
		return;
	}
	NickInfo *n = findnick(src);
	/* if the user has not identified for then nickname */
	if (!isidentified(u, src)) {
		notice(ns_name, src, NS_ERR_ACCESSDENIED, src);
		notice(ns_name, src, NS_RPL_NEEDIDENTIFY);
		return;
	}
	/* if the supplied value is not a number */
	if (!isnum(av[2])) {
		notice(ns_name, src, NS_AUTH_ERR_ISNONUM);
		notice(ns_name, src, NS_AUTH_ERR_DECLINEUSAGE, ns_name);
		notice(ns_name, src, NS_RPL_HLP, ns_name, "AUTH", "DECLINE");
		return;
	}
	/* if 0 is passed */
	if (atoi(av[2]) ==0) {
		notice(ns_name, src, NS_AUTH_ERR_NUMTOOBIG, atoi(av[2]));
		return;
	}	int i = 0;
	auth *a = n->authlist;
	while(a) {
		i++;
		if (i == atoi(av[2])) {
			notice(cs_name,src,NS_AUTH_RPL_DECLINED,i);
			remove_auth(src,a);
			return;
		}
		a = a->next;
	}
	notice(ns_name, src, NS_AUTH_ERR_NUMTOOBIG, atoi(av[2]));
	return;
}

/********************************************************************/
/**
 * list all open auth requests.
 */
void ns_auth_list(char *src, int ac, char **av) {
	user *u = finduser(src);
	if (!isreg(src)) {
		notice(ns_name, src, NS_ERR_NOTREG, src);
		return;
	}
	if (isidentified(u, src) < 0) {
		notice(ns_name, src, NS_ERR_ACCESSDENIED, src);
		notice(ns_name, src, NS_RPL_NEEDIDENTIFY, src);
		return;
	}
	NickInfo *n = findnick(src);

	int i = 0;
	auth *a = n->authlist;
	notice(ns_name, src, NS_AUTH_RPL_PENDING);
	while(a) {
		i++;
		notice(ns_name, src, NS_AUTH_RPL_REQUESTLIST,i, a->sender);
		a = a->next;
	}
	if (i == 0) {
		notice(ns_name,src,NS_AUTH_RPL_NOENTRIES);
	} else if (i == 1) {
		notice(ns_name, src, NS_AUTH_ERR_LISTCOMPLETE1);
	} else {
		notice(ns_name, src, NS_AUTH_ERR_LISTCOMPLETE2, i);
	}
	return;
}

/********************************************************************/
/**
 * read an auth request
 */
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
	if (ac < 3) {
		notice(ns_name, src, NS_AUTH_ERR_READUSAGE, ns_name);
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
		notice(ns_name, src, NS_AUTH_ERR_ISNONUM);
		notice(ns_name, src, NS_AUTH_ERR_READUSAGE, ns_name);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"AUTH READ");
		return;
	}
	/* if the value if greater than the number of actual requests, trigger an error */
	if (atoi(av[2]) == 0) {
		notice(ns_name, src, NS_AUTH_ERR_NUMTOOBIG, atoi(av[2]));
		return;
	}
	int i = 0;
	auth *a = n->authlist;
	while(a) {
		++i;
		if (i == atoi(av[2])) {
			if (a->type == AUTH_NOTIFY) {
				notice(ns_name, src, NS_AUTH_RPL_READNOTIFY, (atoi(av[2])),
						a->sender);
				notice(ns_name, src, NS_AUTH_RPL_TEXT_NOTIFY, a->sender);
			} else {
				notice(ns_name, src, NS_AUTH_RPL_XOP_READ, av[2], a->sender,
						xop[a->type], a->target);
				return;
			}
		}
		a = a->next;
	}
	notice(ns_name, src, NS_AUTH_ERR_NUMTOOBIG, atoi(av[2]));
	return;
}

/********************************************************************/
/**
 * remove an auth request
 */
void remove_auth(char *src, auth *a) {
	NickInfo *n = findnick(src);
	if (a->prev)
		a->prev->next = a->next;
	else
		n->authlist = a->next;
	if (a->next)
		a->next->prev = a->prev;
	free(a);
}
