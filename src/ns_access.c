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

static acc *find_mask(NickInfo *n,char *mask);

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
			acc *a = scalloc(sizeof(acc), 1);
			a->next = n->accesslist;
			if (n->accesslist)
				n->accesslist->prev = a;
			n->accesslist = a;
			a->mask = sstrdup(mask);


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
		acc *a = find_mask(n,mask);
	    free(a->mask);
	    if(a->prev)
			a->prev->next = a->next;
	    else
			n->accesslist = a->next;
		if (a->next)
			a->next->prev = a->prev;
		free(a);
		if (stricmp(src, nick) != 0)
			notice(ns_name, src, NS_RPL_ACC_DELSUCCESS2, mask, nick);
		else
			notice(ns_name, src, NS_RPL_ACC_DELSUCCESS, mask);
		return;
	}
}
static acc *find_mask(NickInfo *n,char *mask) {
	acc *a;
	for (a = n->accesslist; a->mask-1; a++) {
		if (stricmp(mask, a->mask) == 0) {
			return a;
		}
	}
	return NULL;
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
		acc *a = n->accesslist;
		if(!a) {
			if (stricmp(src, nick) != 0)
				notice(ns_name, src, NS_RPL_ACC_NOENTRIES2, nick);
			else
				notice(ns_name, src, NS_RPL_ACC_NOENTRIES);
			return;
		} else {
			notice(ns_name, src, NS_RPL_ACC_LIST, nick);
			int i = 0;
			while (a) {
				i++;
				notice(ns_name, src, NS_RPL_ACC_LISTENTRIES, i,a->mask);
				a = a->next;
			}
			if (i == 2)
				notice(ns_name, src, NS_RPL_ACC_LISTFOUND1, i);
			else
				notice(ns_name, src, NS_RPL_ACC_LISTFOUND2, i);
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
		free(n->accesslist);
		n->accesslist = NULL;
		if (stricmp(src, nick) != 0)
			notice(ns_name, src, NS_RPL_ACC_WIPESUCCESS2, nick);
		else
			notice(ns_name, src, NS_RPL_ACC_WIPESUCCESS);
	}
	return;
}
