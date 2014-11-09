/*
 * ns_access.c
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

void ns_access(char *src, int ac, char **av) {
	char *cmd = av[1];
	char *msk = av[2];
	char *nick = (char*) malloc(sizeof(char) * 128);
	if (ac < 2) {
		notice(ns_name, src, NS_ERR_ACC_USAGE, ns_name);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"ACCESS");
		return;
	}
	if (stricmp(cmd, "ADD") == 0) {
		if (ac >= 4)
			nick = av[3];
		else
			nick = src;
		ns_access_add(src, nick, msk);
		return;
	}
	if (stricmp(cmd, "DEL") == 0) {
		if (ac >= 4)
			nick = av[3];
		else
			nick = src;

		ns_access_del(src, nick, msk);
		return;
	} else if (stricmp(cmd, "LIST") == 0) {
		if (ac >= 3)
			nick = av[2];
		else
			nick = src;
		ns_access_list(src, nick);
	} else if (stricmp(cmd, "WIPE") == 0) {
		if (ac >= 3)
			nick = av[2];
		else
			nick = src;
		ns_access_wipe(src, nick);
	} else {
		notice(ns_name, src, NS_ERR_NOSUCHCMD, cmd);
		notice(ns_name, src, NS_RPL_HLP, ns_name, "ACCESS", "WIPE");
		return;
	}
}
/********************************************************************/
/**
 * add an entry to the nickname's access list
 */
void ns_access_add(char *src, char *nick, char *mask) {
	NickInfo *n = findnick(nick);
	user *u1 = finduser(src);
	if (isidentified(u1, nick) < 1) {
		notice(ns_name, src, NS_ERR_ACCESSDENIED, nick);
		notice(ns_name, src, NS_RPL_NEEDIDENTIFY, nick);
		return;
	}
	if (!strchr(mask, '@')) {
		notice(ns_name, src, NS_ERR_ACC_MASKFORMAT);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"ACCESS ADD");
		return;
	}
	if ((strcmp(mask, "*@*.*") == 0 || strcmp(mask, "*@*") == 0)) {
		notice(ns_name, src, NS_ERR_ACC_MASKFORMAT2, mask);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"ACCESS ADD");
		return;
	} else {
		if (!isreg(nick)) {
			notice(ns_name, src, NS_ERR_NOTREG, nick);
			return;
		} else {
			if (isidentified(u1, nick) < 1) {
				notice(ns_name, src, NS_ERR_ACCESSDENIED, nick);
				notice(ns_name, src, NS_RPL_NEEDIDENTIFY, nick);
				return;
			}
			if (ns_checkmask(nick, mask) >= 0) {
				if (stricmp(src, nick) != 0)
					notice(ns_name, src, NS_ERR_ACC_MASKEXISTS2, mask, nick);
				else
					notice(ns_name, src, NS_ERR_ACC_MASKEXISTS, mask);
				return;
			}
			n->accesscount++;
			n->accesslist = srealloc(n->accesslist,
					sizeof(char *) * n->accesscount);
			n->accesslist[n->accesscount - 1] = sstrdup(mask);
			if (stricmp(src, nick) != 0)
				notice(ns_name, src, NS_RPL_ACC_ADDSUCCESS2, mask, nick);
			else
				notice(ns_name, src, NS_RPL_ACC_ADDSUCCESS, mask);
		}
	}
	return;
}
/********************************************************************/
/**
 * remove an entry from the nickname's access list
 */
void ns_access_del(char *src, char *nick, char *mask) {
	NickInfo *n;
	user *u1;
	char **access;
	if (!isreg(nick)) {
		notice(ns_name, src, NS_ERR_NOTREG, nick);
		return;
	} else {
		n = findnick(nick);
	}
	u1 = finduser(src);
	if (isidentified(u1, nick) < 1) {
		notice(ns_name, src, NS_ERR_ACCESSDENIED, nick);
		notice(ns_name, src, NS_RPL_NEEDIDENTIFY, nick);
		return;
	}
	if (ns_checkmask(nick, mask) < 0) {
		if (stricmp(src, nick) != 0)
			notice(ns_name, src, NS_ERR_ACC_MASKNOTFOUND2, mask, nick);
		else
			notice(ns_name, src, NS_ERR_ACC_MASKNOTFOUND, mask);
		return;
	} else {
		int i = 0;
		for (access = n->accesslist, i = 0; i < n->accesscount; access++, i++) {
			if (stricmp(*access, mask) == 0)
				break;
		}
		n->accesscount--;
		if (i < n->accesscount) /* if it wasn't the last entry... */
			memmove(access, access + 1, (n->accesscount - i) * sizeof(char *));
		if (n->accesscount) /* if there are any entries left... */
			n->accesslist = srealloc(n->accesslist,
					n->accesscount * sizeof(char *));
		else {
			free(n->accesslist);
			n->accesslist = NULL;
		}
		if (stricmp(src, nick) != 0)
			notice(ns_name, src, NS_RPL_ACC_DELSUCCESS2, mask, nick);
		else
			notice(ns_name, src, NS_RPL_ACC_DELSUCCESS, mask);
		return;
	}
}
/********************************************************************/
/**
 * List all the nickname's access entries
 */
void ns_access_list(char *src, char *nick) {
	NickInfo *n;
	user *u1 = finduser(src);
	if (hasaccess(u1, nick) < 1) {
		notice(ns_name, src, NS_ERR_ACCESSDENIED, nick);
		notice(ns_name, src, NS_RPL_NEEDIDENTIFY, nick);
		return;
	}
	if (!isreg(nick)) {
		notice(ns_name, src, NS_ERR_NOTREG, nick);
		return;
	} else {
		n = findnick(nick);
		if (hasaccess(u1, nick) < 0) {
			notice(ns_name, src, NS_ERR_ACCESSDENIED, nick);
			notice(ns_name, src, NS_RPL_NEEDIDENTIFY, nick);
			return;
		}
		if (n->accesscount <= 0) {
			if (stricmp(src, nick) != 0)
				notice(ns_name, src, NS_RPL_ACC_NOENTRIES2, nick);
			else
				notice(ns_name, src, NS_RPL_ACC_NOENTRIES);
			return;
		} else {
			notice(ns_name, src, NS_RPL_ACC_LIST, nick);
			int i;
			for (i = 1; i <= n->accesscount; i++) {
				notice(ns_name, src, NS_RPL_ACC_LISTENTRIES, i,
						n->accesslist[i - 1]);
			}
			if (i == 2)
				notice(ns_name, src, NS_RPL_ACC_LISTFOUND1, i - 1);
			else
				notice(ns_name, src, NS_RPL_ACC_LISTFOUND2, i - 1);
			return;
		}
	}
}
/********************************************************************/
/**
 * remove all entries from the nickname's access list.
 */
void ns_access_wipe(char *src, char *nick) {
	NickInfo *n;
	user *u1 = finduser(src);
	if (!isreg(nick)) {
		notice(ns_name, src, NS_ERR_NOTREG, nick);
		return;
	} else {
		n = findnick(nick);
		if (isidentified(u1, nick) < 1) {
			notice(ns_name, src, NS_ERR_ACCESSDENIED, nick);
			notice(ns_name, src, NS_RPL_NEEDIDENTIFY, nick);
			return;
		}
		n->accesscount = 0;
		free(n->accesslist);
		n->accesslist = NULL;
		if (stricmp(src, nick) != 0)
			notice(ns_name, src, NS_RPL_ACC_WIPESUCCESS2, nick);
		else
			notice(ns_name, src, NS_RPL_ACC_WIPESUCCESS);
	}
	return;
}
