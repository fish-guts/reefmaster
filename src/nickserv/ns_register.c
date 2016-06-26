/*
 * ns_register.c
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

static char *oline[] = {
		"",
		"",
		"Help Operator",
		"IRC Operator",
		"Co Administrator",
		"Server Administrator",
		"Services Administrator",
		"Network Administrator"
};

/********************************************************************/
/**
 * ns_register Handle the Nickserv REGISTER command
 * Register a nickname with Nickserv. Special privileges
 * may be required, this is configurable.
 */
void ns_register(char *src, int ac, char **av) {
	user *u;
	u = finduser(src);
	time_t del = 0;
	time_t cur = time(NULL);
	time_t now = time(NULL);
	if(ac<3) {
		notice(ns_name, src, NS_REGISTER_RPL_USAGE);
		notice(ns_name, src, NS_RPL_HLP_SHORT, ns_name,"REGISTER");
		return;
	}
	if (u->lastnickreg)
		del = (now - u->lastnickreg);
	char *pass = sstrdup(av[1]);
	char *email = sstrdup(av[2]);
	/* Check for proper access */
	if ((u->oper + 1) < ns_usage_access) {
		notice(ns_name, src, NS_REGISTER_ERR_PRIVS, oline[ns_usage_access]);
		return;
	}
	/* checks whether the nickname is already registered */
	if (isreg(src)) {
		notice(ns_name, src, NS_REGISTER_ERR_ALREADYREG, src);
		return;
	}
	/* check, whether the user has registered too many nickname within (ns_delay) seconds */
	if ((del) && (del < ns_delay)) {
		notice(ns_name, src, NS_REGISTER_ERR_DELAY, del);
		return;
	}
	/* check for the correct parameters */
	if ((!email || !strcmp(email, "")) || (!pass || !strcmp(pass, ""))) {
		notice(ns_name, src, NS_REGISTER_RPL_USAGE);
		notice(ns_name, src, NS_RPL_HLP_SHORT, ns_name,"REGISTER");
		return;
	}
	/* the email address should contain a '@' */
	if (!strchr(email, '@')) {
		notice(ns_name, src, NS_REGISTER_ERR_INVALDEMAIL);
		notice(ns_name, src, NS_RPL_HLP_SHORT, ns_name,"REGISTER");
		return;
	}
	/* the password should be at least 5 characters long */
	if (strlen(pass) < 5) {
		notice(ns_name, src, NS_REGISTER_ERR_PASSTOOSHORT);
		notice(ns_name, src, NS_RPL_HLP_SHORT, ns_name,"REGISTER");
		return;
	}

	char *dest = (char*) malloc(sizeof(char*) * NICKMAX);
	strcpy(dest, src);

	/* the password shouldn't be the same as the nickname */
	if (stricmp(pass, dest) == 0) {
		notice(ns_name, src, NS_REGISTER_ERR_PASSSAMEASNICK);
		notice(ns_name, src, NS_RPL_HLP_SHORT, ns_name,"REGISTER");
		free(dest);
		return;
	} else {
		char *usermask = (char*) malloc(sizeof(char*) * 256);
		sprintf(usermask, "%s@%s", u->username, mask(src, u->hostname));
		register_nick(src, pass, email);
		notice(ns_name, dest, NS_REGISTER_RPL_SUCCESS1, src);
		notice(ns_name, dest, NS_REGISTER_RPL_SUCCESS2, pass);
		// mark the timestamp of registration
		u->lastnickreg = time(&cur);
		if (ns_autoaccess == 1)
			notice(ns_name, dest, NS_REGISTER_RPL_SUCCESS3, usermask);
		/* set identified */
		add_identified(u, dest);
		svs2mode(s_name, dest, "+r 0", NULL); // give the nick the usermode +r
		free(dest);
		return;
	}
}
