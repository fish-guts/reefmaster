/*
 * ns_identify.c
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
 * ns_identify Handle the Nickserv IDENTIFY command
 * Identify for a registered nickname.
 */
void ns_identify(char *src, int ac, char **av) {
	user *u;
	char *nick, *pass;
	time_t cur;
	u = finduser(src);
	if (!u)
		return;
	if (ac <= 1) {
		notice(ns_name, src, NS_IDENTIFY_RPL_USAGE, ns_name);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"IDENTIFY");
		return;
	}
	if (ac == 2) {
		nick = src;
		pass = av[1];
	} else if (ac >= 3) {
		nick = av[1];
		pass = av[2];
	}
	if (!isreg(nick)) {
		notice(ns_name, src, NS_ERR_NOTREG, nick);
		return;
	}
	if (isidentified(u, nick) > 0) {
		notice(ns_name, src, NS_IDENTIFY_RPL_ALREADYIDF, nick);
		return;
	} else {
		if (ns_checkpass(nick, pass) == 0) {
			add_identified(u, nick);
			notice(ns_name, src, NS_IDENTIFY_RPL_PASSACCEPTED);
			NickInfo *n = findnick(nick);
			cur = time(NULL);
			char msk[128];
			sprintf(msk, "%s@%s", u->username, u->hostname);
			if (strcmp(src, nick) == 0)
				svs2mode(s_name, src, "+r 0", NULL);
			sprintf(msk, "%s@%s", u->username, u->hostname);
			n->last_realname = sstrdup(u->realname);
			n->last_seen = cur;
			n->last_usermask = sstrdup(msk);
			remove_timeout(u, TO_COLLIDE);
			remove_timeout(u, TO_COLLIDE_TL);
			if(n->mlock)
				mode(src,src,n->mlock,NULL);
			userchan *uc = u->chans;
			while(uc) {
				channel *c = findchannel(uc->chan->name);
				check_status(c,u);
				uc = uc->next;
			}
			return;
		} else {
			if (++u->pw_cnt == s_PassLimit)
				ns_passlimit(u);
			else {
				notice(ns_name, src, NS_IDENTIFY_RPL_WRONGPASS, nick);
				return;
			}
		}
	}
}
