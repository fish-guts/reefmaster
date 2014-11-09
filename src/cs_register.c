/*
 * cs_register.c
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

void cs_register(char *src, int ac, char **av) {
	char *chan = av[1];
	char *pass = av[2];

	char *desc = (char*) malloc(sizeof(char*) * DESCMAX);
	int i;
	for (i = 3; i < ac; i++) {
		strcat(desc, av[i]);
		if (i != (ac - 1)) {
			strcat(desc, " ");
		}
	}
	user *u = finduser(src);
	channel *c = findchannel(chan);
	int del;
	int reglevel = cs_regaccess;
	char *dest = src;
	time_t now;
	now = time(NULL);
	del = (now - u->lastchanreg);
	/* Check for proper access */
	if ((u->oper + 1) < reglevel) {
		notice(ns_name, dest, CS_ERR_REG_PRIVS, get_oline(reglevel));
		return;
	}
	/* checks whether the nickname is registered */
	if (!isreg(src)) {
		notice(cs_name, dest, NS_ERR_NOTREG, src);
		notice(cs_name, dest, CS_ERR_NEEDREG);
		return;
	}
	/* the channel name must contain a '#' */
	if (!strchr(chan, '#')) {
		notice(cs_name, dest, CS_ERR_NOSUCHCHANNEL, chan);
		return;
	}
	if (isregcs(chan)) {
		notice(cs_name, dest, CS_ERR_ALREADYREG, chan);
		return;
	}
	if (del <= cs_delay) {
		notice(cs_name, dest, CS_ERR_REG_DELAY, del);
		return;
	}
	if ((!desc || !strcmp(desc, "")) || (!pass || !strcmp(pass, ""))) {
		notice(cs_name, dest, CS_RPL_REG_USAGE);
		notice(cs_name, dest, CS_RPL_REG_HLP, cs_name);
		return;
	}
	/* the password should be at least 5 characters long */
	if (strlen(pass) < 5) {
		notice(cs_name, dest, NS_ERR_REG_PASSTOOSHORT);
		notice(cs_name, dest, CS_RPL_REG_HLP, cs_name);
		return;
	}
	/* the password shouldn't be the same as the nickname */
	if (stricmp(pass, chan) == 0) {
		notice(cs_name, dest, CS_ERR_REG_PASSSAMEASCHAN);
		notice(cs_name, dest, CS_RPL_REG_HLP, cs_name);
		return;
	}
	if (stricmp(pass, src) == 0) {
		notice(cs_name, dest, CS_ERR_REG_PASSSAMEASFND);
		notice(cs_name, dest, CS_RPL_REG_HLP, cs_name);
		return;
	}
	/* the user must be on channel to register it, unless he's oper */
	if ((!ison(c, u)) && (!u->oper)) {
		notice(ns_name, src, CS_ERR_REG_NEEDTOBEONCHAN, chan);
		return;
	}
	/* the user must be on operator (+o) channel to register it, unless he's oper */
	if ((!isop(c, u)) && (!u->oper)) {
		notice(ns_name, src, CS_ERR_REG_NEEDTOBEOP, chan);
		return;
	}
	char i_mode[128];
	sprintf(i_mode, "%s", cs_mlock);
	mode(s_name, chan, "+rtn", NULL);
	mode(cs_name, chan, i_mode, NULL);
	notice(cs_name, src, CS_RPL_REG_SUCCESS1, chan);
	notice(cs_name, src, CS_RPL_REG_SUCCESS2, pass);
	register_chan(src, chan, pass, desc);
}

