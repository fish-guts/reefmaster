/*
 * ns_drop.c
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
 *  ns DROP Handle the Nickserv DROP command
 *  Deletes the specified Nickname
 */
void ns_drop(char *src, int ac, char **av) {
	user *u = finduser(src);
	if (ac < 2) {
		notice(ns_name, src, NS_DROP_ERR_USAGE);
		notice(ns_name, src, NS_RPL_HLP_SHORT,ns_name,"DROP");
		return;
	}
	char *nick = av[1];
	if (!isreg(nick)) {
		notice(ns_name, src, NS_ERR_NOTREG, av[1]);
		return;
	}
	NickInfo *n = findnick(nick);
	if (!isidentified(u, nick)) {
		notice(ns_name, src, NS_ERR_ACCESSDENIED, nick);
		notice(ns_name, src, NS_RPL_NEEDIDENTIFY, nick);
		return;
	}
	notice(ns_name, src, NS_DROP_RPL_SUCCESS, nick);
	cs_check_successor(nick);
	cs_drop_nick(nick);
	delete_nick(n);
	svs2mode(s_name, nick, "-rR 0", NULL);
	return;
}
