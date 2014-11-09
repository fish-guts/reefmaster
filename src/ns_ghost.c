/*
 * ns_ghost.c
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

void ns_ghost(char *src, int ac, char **av) {
	user *u, *u1;
	time_t cur;
	char *killmsg = (char*) malloc(sizeof(char) * 128);
	sprintf(killmsg, "Ghost command used by %s", src);
	u = finduser(src);
	u1 = finduser(av[1]);
	NickInfo *n = findnick(av[1]);
	if (!u1) {
		notice(ns_name, src, NS_ERR_NOSUCHUSER, av[1]);
		return;
	}
	if (ac < 2) {
		notice(ns_name, src, NS_ERR_GHT_USAGE);
		return;
	}
	if (!isreg(n->nick)) {
		notice(ns_name, src, NS_ERR_NOTREG, av[1]);
		return;
	}
	if (ac == 2) {
		if (hasaccess(u, n->nick) < 0) {
			notice(ns_name, src, NS_ERR_ACCESSDENIED, av[1]);
			notice(ns_name, src, NS_RPL_NEEDIDENTIFY, av[1]);
			return;
		}
	}
	if (ac >= 3) {
		if (ns_checkpass(av[1], av[2]) != 0) {
			if (++u->pw_cnt < s_PassLimit) {
				notice(ns_name, src, NS_ERR_IDF_WRONGPASS, av[1]);
				return;
			} else if (u->pw_cnt++ >= s_PassLimit) {
				ns_passlimit(u);
				return;
			}
		}
	}
	if (n->enforced == 1) {
		notice(ns_name, src, NS_ERR_GHT_NICKISHELD, av[1]);
		notice(ns_name, src, NS_RPL_GHT_NEEDRELEASE, ns_name);
		return;
	}
	add_identified(u, n->nick);
	cur = time(NULL);
	char msk[128];
	sprintf(msk, "%s@%s", u->username, u->hostname);
	if (strcmp(src, av[1]) == 0) {
		svs2mode(s_name, src, "+r 0", NULL);
	}
	sprintf(msk, "%s@%s", u->username, mask(src, u->hostname));
	n->last_realname = sstrdup(u->realname);
	n->last_seen = cur;
	n->last_usermask = sstrdup(msk);
	remove_timeout(u, TO_COLLIDE);
	remove_timeout(u, TO_COLLIDE_TL);
	remove_timeout(u1, TO_COLLIDE);
	remove_timeout(u1, TO_COLLIDE_TL);
	s_kill(ns_name, n->nick, killmsg);
	notice(ns_name, src, NS_RPL_GHT_GHOSTDISCONN);
	return;
}
