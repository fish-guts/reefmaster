/*
 * ns_info.c
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
 * Handle the Nickserv INFO command
 * Display information about a registered nickname.
 * The exact host will be masked to users without IRC Operator privileges.
 */
void ns_info(char *src, int ac, char **av) {
	char *nick = av[1];
	user *usrc = finduser(src);
	if(ac<2) {
		notice(ns_name, src,NS_INFO_RPL_USAGE);
		return;
	}
	if (!isreg(nick)) {
		notice(ns_name, src, NS_ERR_NOTREG, nick);
		return;
	}
	NickInfo *n;
	int i = 0;
	char **uv = (char**) malloc(sizeof(char**) * 128);
	char *buf = (char*) malloc(sizeof(char*) * 512);
	char str_now[256], str_last[80], str_reg[80];
	user *u = finduser(nick);
	n = findnick(nick);
	char *msk = sstrdup(n->last_usermask);
	char *pch = strtok((char*) msk, "@");
	while (pch != NULL) {
		uv[i] = sstrdup(pch);
		i++;
		pch = strtok(NULL, "@");
	}
	if(usrc->oper) {
		sprintf(buf, "%s@%s", uv[0], uv[1]);
	} else {
		sprintf(buf, "%s@%s", uv[0], mask(src, uv[1]));
	}
	time_t cur = time(NULL);
	strftime(str_now, 100, "%d/%m/%Y %T %Z", localtime(&cur));
	strftime(str_last, 100, "%d/%m/%Y %T %Z", localtime(&n->last_seen));
	strftime(str_reg, 100, "%d/%m/%Y %T %Z", localtime(&n->time_reg));
	if (u) {
		if (isidentified(u, src) > 0)
			notice(ns_name, src, NS_INFO_RPL_HEAD1, nick, n->last_realname);
		else
			notice(ns_name, src, NS_INFO_RPL_HEAD2, nick, n->last_realname);
	} else
		notice(ns_name, src, NS_INFO_RPL_HEAD2, nick, n->last_realname);
	if (!n->hidemail)
		notice(ns_name, src, NS_INFO_RPL_EMAIL, n->email);
	notice(ns_name, src, NS_INFO_RPL_LASTADDR, buf);
	notice(ns_name, src, NS_INFO_RPL_TIMEREG, str_reg);
	notice(ns_name, src, NS_INFO_RPL_LASTSEEN, str_last);
	notice(ns_name, src, NS_INFO_RPL_TIMENOW, str_now);
	if (n->noop)
		notice(ns_name, src, NS_INFO_RPL_NOOP, cs_name);
	if (n->auth_chan)
		notice(ns_name, src, NS_INFO_RPL_AUTHCHAN);
	if (n->auth_notify)
		notice(ns_name, src, NS_INFO_RPL_AUTHNOTIFY);
	if (n->protect == 2)
		notice(ns_name, src, NS_INFO_RPL_PROTECT1);
	else if (n->protect == 3)
		notice(ns_name, src, NS_INFO_RPL_PROTECT2);
	if (n->mforward == 1)
		notice(ns_name, src, NS_INFO_RPL_MFORWARD, n->mforward_to);
	if (n->nomemo)
		notice(ns_name, src, NS_INFO_RPL_NOMEMO);
}
