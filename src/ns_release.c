/*
 * ns_release.c
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

void ns_release(char *src, int ac, char **av) {
	user *u = finduser(src);
	/* check for the correct argument count */
	if (ac <= 1) {
		notice(ns_name, src, NS_ERR_REL_USAGE);
		notice(ns_name, src, NS_RPL_HLP_SHORT, ns_name,"RELEASE");
		return;
	}
	/* if the nick is not registered */
	if (!isreg(av[1])) {
		notice(ns_name, src, NS_ERR_NOTREG, av[1]);
		return;
	} else {
		if (ac == 2) {
			if (hasaccess(u, av[1]) < 0) {
				notice(ns_name, src, NS_ERR_ACCESSDENIED, av[1]);
				notice(ns_name, src, NS_RPL_NEEDIDENTIFY, av[1]);
				return;
			}
		} else if (ac > 2) {
			if (ns_checkpass(av[1], av[2]) < 0) {
				if (++u->pw_cnt < s_PassLimit) {
					notice(ns_name, src, NS_ERR_IDF_WRONGPASS, src);
					return;
				} else if (u->pw_cnt++ >= s_PassLimit) {
					ns_passlimit(u);
					return;
				}
			}
		}
		NickInfo *n = findnick(av[1]);
		if (n->enforced == 0) {
			notice(ns_name, src, NS_ERR_REL_NICKNOTHELD, av[1]);
			return;
		}
		add_identified(u, n->nick);
		char mask[128];
		sprintf(mask, "%s@%s", u->username, u->hostname);
		n->last_seen = time(NULL);
		n->last_usermask = sstrdup(mask);
		n->last_realname = sstrdup(u->realname);
		n->enforced = 0;
		if (strcmp(src, av[1]) == 0)
			svs2mode(s_name, src, "+r 0", NULL);
		remove_timeout(u, TO_COLLIDE);
		remove_timeout(u, TO_COLLIDE_TL);
		quit(av[1]);
		notice(ns_name, src, NS_RPL_REL_NICKRELEASED, av[1]);
	}
	return;
}
