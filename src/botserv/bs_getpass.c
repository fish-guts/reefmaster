/*
 * bs_getpass.c
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
 * Handle the Botserv GETPASS commands
 */
void bs_getpass(char *src, int ac, char **av) {
	user *u = finduser(src);
	if (bs_access_getpass <= 0) {
		notice(bs_name, src, AS_FUNCTIONDISABLED);
		return;
	}
	if (u->oper < bs_access_getpass) {
		notice(bs_name, src, NS_ERR_NEEDMOREPRIVS);
		return;
	}
	if (ac <= 1) {
		notice(bs_name, src, BS_ERR_GETPASS_USAGE);
		notice(bs_name, src, BS_RPL_HLP, ns_name,"GETPASS");
		return;
	}
	if (!findbot(av[1])) {
		notice(bs_name, src, BS_ERR_NOTFOUND, av[1]);
		return;
	} else {
		bot *b = findbot(av[1]);
		notice(bs_name, src, BS_RPL_GETPASS_SUCCESS,b->name,b->password);
		notice(ns_name, src, NS_RPL_GPASS_LOGGED);
		chatops(ns_name,NS_CTP_GETPASS_USED,src,b->name);
		addlog(1,NS_LOG_GETPASS_USED,bs_name,src);
	}
}
