/*
 * cs_setpass.c
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
 * handle the SETPASS command
 */
void cs_setpass(char *src, int ac, char **av) {
	user *u = finduser(src);
	/* check if the function is enabled */
	if (cs_spass <= 0) {
		notice(as_name, src, AS_FUNCTIONDISABLED);
		return;
	}
	/* check whether the user has the required privileges */
	if (u->oper < cs_spass) {
		notice(cs_name, src, NS_ERR_NEEDMOREPRIVS);
		return;
	}
	/* for the correct argument cound */
	if (ac <= 2) {
		notice(cs_name, src, CS_ERR_SPASS_USAGE);
		notice(cs_name, src, CS_RPL_HLP, ns_name,"SETPASS");
		return;
	}
	char *chan = av[1];
	char *pass = av[2];
	if (!isregcs(chan)) {
		notice(ns_name, src, NS_ERR_NOTREG, chan);
		return;
	}
	ChanInfo *c = findchan(chan);
	/* the new password should be at least 5 characters long */
	if (strlen(pass) < 5) {
		notice(cs_name, src, NS_REGISTER_ERR_PASSTOOSHORT);
		notice(cs_name, src, CS_RPL_HLP, ns_name,"SETPASS");
		return;
	}
	/* the password must not be the same as the nickname */
	else if (stricmp(chan, pass) == 0) {
		notice(cs_name, src, CS_REGISTER_ERR_PASSSAMEASCHAN);
		return;
	} else {
		strscpy(c->pass, pass, PASSMAX);
		notice(cs_name, src, CS_RPL_SPASS_SUCCESS, chan, pass);
		notice(cs_name,src,NS_GETPASS_MSG_LOGGED);
		addlog(1,NS_LOG_SETPASS_USED,cs_name,src);
		chatops(cs_name,NS_GLOBAL_SETPASS_USED,src,c->name);
		return;
	}
}
