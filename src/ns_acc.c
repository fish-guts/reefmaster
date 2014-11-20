/*
 * ns_acc.c
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
 * cs_acc Handle the Nickserv ACC Command
 * Displayes why a user has access to a nickname
 * Possible return values are:
 * 		0 - no access - User hasn't identified and doesn't have a matching entry in its access list
 * 		1 - Matches an entry in the access list - User hasn't identified for this nickname
 * 			but his usermask (user@host) matches an entry in the nickname's access list
 * 		2 - User has identified for this nickname using its password.
 */
void ns_acc(char *src, int ac, char **av) {
	if (ac < 2) {
		notice(ns_name, src, NS_ERR_CACC_USAGE, ns_name);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"ACC");
		return;
	}
	user *u = finduser(av[1]);
	char *mask = (char*) malloc(sizeof(char*) * 128);
	if (!u) {
		notice(ns_name, src, NS_ERR_NOSUCHUSER, av[1]);
		return;
	}
	sprintf(mask, "%s@%s", u->username, u->hostname);
	if (!isreg(av[1])) {
		notice(ns_name, src, NS_ERR_NOTREG, av[1]);
		return;
	}
	if (isidentified(u, u->nick)) {
		notice(ns_name, src, NS_RPL_ACC_LEVEL2, av[1]);
		return;
	} else if (ismatch(u, mask) == 1) {
		notice(ns_name, src, NS_RPL_ACC_LEVEL1, av[1]);
		return;
	} else {
		notice(ns_name, src, NS_RPL_ACC_LEVEL0, av[1]);
		return;
	}
}
