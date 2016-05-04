/*
 * cs_getpass.c
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
 * handle the GETPASS command
 */
void cs_getpass(char *src, int ac, char **av) {
	user *u = finduser(src);
	if (cs_gpass <= 0) {
		notice(as_name, src, AS_FUNCTIONDISABLED);
		return;
	}
	if (u->oper < cs_gpass) {
		notice(cs_name, src, NS_ERR_NEEDMOREPRIVS);
		return;
	}
	if (ac <= 1) {
		notice(cs_name, src, CS_GETPASS_RPL_USAGE);
		notice(cs_name, src, CS_RPL_HLP, cs_name,"GETPASS");
		return;
	}
	if (!isregcs(av[1])) {
		notice(cs_name, src, CS_ERR_NOTREG, av[1]);
		return;
	} else {
		ChanInfo *c = findchan(av[1]);
		notice(cs_name, src, CS_GETPASS_RPL_SUCCESS,c->name,c->pass);
		notice(cs_name, src, NS_GETPASS_MSG_LOGGED);
		globops(cs_name,CS_GLOBOPS_GETPASS_USED,src,c->name);
		addlog(1,CS_LOG_GETPASS_USED,cs_name,src);
	}
}
