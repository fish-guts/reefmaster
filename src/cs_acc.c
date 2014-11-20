/*
 * cs_acc.c
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


void cs_acc(char *src, int ac, char **av) {
	if (ac < 3) {
		notice(cs_name, src, CS_ERR_ACC_USAGE, cs_name);
		notice(cs_name, src, CS_RPL_ACC_HLP, cs_name);
		return;
	}
	char *chan = sstrdup(av[1]);
	char *nick = sstrdup(av[2]);
	if (!isregcs(chan)) {
		notice(cs_name, src, CS_ERR_NOTREG);
		return;
	}
	if (!isreg(nick)) {
		notice(cs_name, src, NS_ERR_NOTREG);
		return;
	}
	user *u = finduser(nick);
	if (!u) {
		notice(cs_name, src, NS_ERR_NOSUCHUSER, nick);
		return;
	}
	ChanInfo *c = findchan(chan);
	int level = cs_xop_get_level(u, c);
	char *why;
	if(level==12) {
		why = sstrdup(c->name);
	} else {
		why = cs_get_why(u, c);
	}
	switch (level) {
	case 13:
		notice(cs_name, src, CS_RPL_ACC_IRCOP, u->nick, get_oline(u->oper),
				c->name);
		return;
	case 12:
		notice(cs_name,src,CS_RPL_ACC_IDENTIFIED,u->nick,why);
		return;
	case 11:
		notice(cs_name, src, CS_RPL_ACC_SUCCFND, u->nick, why, "Founder",c->name);
		return;
	case 10:
		notice(cs_name, src, CS_RPL_ACC_SUCCFND_ACC, u->nick, why, "Founder",c->name);
		return;
	case 9:
		notice(cs_name, src, CS_RPL_ACC_SUCCFND, u->nick, why, "Successor",c->name);
		return;

	case 8:
		notice(cs_name, src, CS_RPL_ACC_SUCCFND_ACC, u->nick, why, "Successor",c->name);
		return;
	case 7:
	case 6:
	case 5:
	case 4:
	case 3:
	case 2:
	case 1:
		notice(cs_name, src, CS_RPL_ACC_XOP, u->nick, why, get_opacc(level),
				c->name);
		return;
	case 0:
		notice(cs_name, src, CS_RPL_ACC_NOACCESS, u->nick, c->name);
		return;
	}
}
