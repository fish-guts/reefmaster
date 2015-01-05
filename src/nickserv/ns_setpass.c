/*
 * ns_setpass.c
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
 * ns_setpass Handle the Nickserv SETPASS command
 * Sets a new password for the specified nick. Requires special
 * privileges set in the config
 */
void ns_setpass(char *src, int ac, char **av) {
	user *u = finduser(src);
	/* check if the function is enabled */
	if (ns_spass <= 0) {
		notice(as_name, src, AS_FUNCTIONDISABLED);
		return;
	}
	/* check whether the user has the required privileges */
	if (u->oper < ns_spass) {
		notice(ns_name, src, NS_ERR_NEEDMOREPRIVS);
		return;
	}
	/* for the correct argument count */
	if (ac <= 2) {
		notice(ns_name, src, NS_ERR_SPASS_USAGE);
		notice(ns_name, src, NS_RPL_HLP_SHORT, ns_name,"SETPASS");
		return;
	}
	char *nick = av[1];
	char *pass = av[2];
	if (!isreg(nick)) {
		notice(ns_name, src, NS_ERR_NOTREG, nick);
		return;
	}
	NickInfo *n = findnick(nick);
	/* the new password should be at least 5 characters long */
	if (strlen(pass) < 5) {
		notice(ns_name, src, NS_ERR_REG_PASSTOOSHORT);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"SETPASS");
		return;
	}
	/* the password must not be the same as the nickname */
	else if (stricmp(nick, pass) == 0) {
		notice(ns_name, src, NS_ERR_REG_PASSSAMEASNICK);
		return;
	} else {
		strscpy(n->pass, pass, PASSMAX);
		notice(ns_name, src, NS_RPL_SPASS_SUCCESS, nick, pass);
		notice(ns_name,src,NS_RPL_GPASS_LOGGED);
		addlog(1,NS_LOG_SETPASS_USED,ns_name,src,nick);
		chatops(ns_name,NS_CTP_SETPASS_USED,src,nick);
		return;
	}
}
