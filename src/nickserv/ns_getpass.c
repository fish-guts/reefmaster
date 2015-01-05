/*
 * ns_getpass.c
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
 * ns_getpass Handle the Nickserv GETPASS commands
 * Retrieve the specified nickname's password. The
 * required privileges are configurable in the config.
 */
void ns_getpass(char *src, int ac, char **av) {
	user *u = finduser(src);
	if (ns_gpass <= 0) {
		notice(as_name, src, AS_FUNCTIONDISABLED);
		return;
	}
	if (u->oper < ns_gpass) {
		notice(ns_name, src, NS_ERR_NEEDMOREPRIVS);
		return;
	}
	if (ac <= 1) {
		notice(ns_name, src, NS_ERR_GPASS_USAGE);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"GETPASS");
		return;
	}
	if (!isreg(av[1])) {
		notice(ns_name, src, NS_ERR_NOTREG, av[1]);
		return;
	} else {
		NickInfo *n = findnick(av[1]);
		notice(ns_name, src, NS_RPL_GPASS_SUCCESS,n->nick,n->pass);
		notice(ns_name, src, NS_RPL_GPASS_LOGGED);
		chatops(ns_name,NS_CTP_GETPASS_USED,src,n->nick);
		addlog(1,NS_LOG_GETPASS_USED,cs_name,src);
	}
}
