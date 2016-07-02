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

static myacc *find_mask(NickInfo *n, char *mask);

/**
 * ns_access Handle the Nickserv ACCESS Command
 * Possible subcommands are:
 * ADD - Add an entry to the access list of a nickname
 * DEL - Remove an entry from the access list of a nickname
 * LIST - List all access entries of a nickname
 * WIPE - Delete all access entries of a nickname
 */
void ns_access_cmd(char *src, int ac, char **av) {
	if (ac < 2) {
		notice(ns_name, src, NS_ACC_USAGE, ns_name);
		notice(ns_name, src, NS_RPL_HLP_SHORT, ns_name, "ACCESS");
		return;
	}
	char *cmd = av[1];
	char *mask = av[2];
	char *nick = (char*) malloc(sizeof(char) * 128);
	if (stricmp(cmd, "ADD") == 0) {
		if (ac >= 4) {
			nick = av[3];
		} else {
			nick = src;
		}
		ns_access_add(src, nick, mask);
	} else if (stricmp(cmd, "DEL") == 0) {
		if (ac >= 4) {
			nick = av[3];
		} else {
			nick = src;
		}
		ns_access_del(src, nick, mask);
	} else if (stricmp(cmd, "LIST") == 0) {
		if (ac >= 3) {
			nick = av[2];
		} else {
			nick = src;
		}
		ns_access_list(src, nick);
	} else if (stricmp(cmd, "WIPE") == 0) {
		if (ac >= 3) {
			nick = av[2];
		} else {
			nick = src;
		}
		ns_access_wipe(src, nick);
	} else {
		notice(ns_name, src, NS_ERR_NOSUCHCMD, cmd);
		notice(ns_name, src, NS_RPL_HLP, ns_name, "ACCESS", "WIPE");
	}
}
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
		notice(ns_name, src, NS_ACCESS_ERR_MASKFORMAT);
		notice(ns_name, src, NS_RPL_HLP, ns_name, "ACCESS", "ADD");
		return;
	}
	if ((strcmp(mask, "*@*.*") == 0 || strcmp(mask, "*@*") == 0)) {
		notice(ns_name, src, NS_ACCESS_ERR_MASKFORMAT2, mask);
		notice(ns_name, src, NS_RPL_HLP, ns_name, "ACCESS", "ADD");
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
			if (find_mask(n, mask) != NULL) {
				if (stricmp(src, nick) != 0)
					notice(ns_name, src, NS_ACCESS_ERR_MASKEXISTS2, mask, nick);
				else
					notice(ns_name, src, NS_ACCESS_ERR_MASKEXISTS, mask);
				return;
			}

			ns_access_add_mask(n, mask);

			if (stricmp(src, nick) != 0) {
				notice(ns_name, src, NS_ACCESS_RPL_ADDSUCCESS2, mask, nick);
			} else {
				notice(ns_name, src, NS_ACCESS_RPL_ADDSUCCESS, mask);
			}
		}
	}
	return;
}

/********************************************************************/
/**
 * add an access mask to a nickname
 */
void ns_access_add_mask(NickInfo *n, char *mask) {
	myacc *a = scalloc(sizeof(myacc), 1);
	a->next = n->accesslist;
	if (n->accesslist) {
		n->accesslist->prev = a;
	}
	n->accesslist = a;
	a->mask = sstrdup(mask);
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
	myacc *a = find_mask(n, mask);
	if (a == NULL) {
		if (stricmp(src, nick) != 0) {
			notice(ns_name, src, NS_ACCESS_ERR_MASKNOTFOUND2, mask, nick);
		} else {
			notice(ns_name, src, NS_ACCESS_ERR_MASKNOTFOUND, mask);
		}
		return;
	}

	if (a->prev) {
		a->prev->next = a->next;
	} else {
		n->accesslist = a->next;
	}

	if (a->next) {
		a->next->prev = a->prev;
	}

	free(a);
	if (stricmp(src, nick) != 0) {
		notice(ns_name, src, NS_ACCESS_RPL_DELSUCCESS2, mask, nick);
	} else {
		notice(ns_name, src, NS_ACCESS_RPL_DELSUCCESS, mask);
	}
	return;
}
/********************************************************************/
/**
 * find an existing access mask in a nickname
 */
static myacc *find_mask(NickInfo *n, char *mask) {
	myacc *a = n->accesslist;
	while(a != NULL) {
		if (stricmp(mask, a->mask) == 0) {
			return a;
		}
		a = a->next;
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
		myacc *a = n->accesslist;

		if (!a) {
			if (stricmp(src, nick) != 0) {
				notice(ns_name, src, NS_ACCESS_RPL_NOENTRIES2, nick);
			} else {
				notice(ns_name, src, NS_ACCESS_RPL_NOENTRIES);
			}
			return;
		} else {
			notice(ns_name, src, NS_ACCESS_RPL_LIST, nick);
			int i = 0;
			while (a != NULL) {
				notice(ns_name, src, NS_ACCESS_RPL_LISTENTRIES, ++i, a->mask);
				a = a->next;
			}
			if (i == 2) {
				notice(ns_name, src, NS_ACCESS_RPL_LISTFOUND1, i);
			} else {
				notice(ns_name, src, NS_ACCESS_RPL_LISTFOUND2, i);
			}
		}
	}
}

/********************************************************************/
/**
 * remove all entries from the nickname's access list.
 */
void ns_access_wipe(char *src, char *nick) {
	user *u1 = finduser(src);
	if (!isreg(nick)) {
		notice(ns_name, src, NS_ERR_NOTREG, nick);
		return;
	} else {
		NickInfo *n = findnick(nick);
		if (isidentified(u1, nick) < 1) {
			notice(ns_name, src, NS_ERR_ACCESSDENIED, nick);
			notice(ns_name, src, NS_RPL_NEEDIDENTIFY, nick);
			return;
		}
		free(n->accesslist);
		n->accesslist = NULL;
		if (stricmp(src, nick) != 0)
			notice(ns_name, src, NS_ACCESS_RPL_WIPESUCCESS2, nick);
		else
			notice(ns_name, src, NS_ACCESS_RPL_WIPESUCCESS);
	}
	return;
}
