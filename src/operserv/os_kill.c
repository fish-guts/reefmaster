/*
 *      os_akill.c - severin
 *
 *      Copyright 2014 Severin Mueller <severin.mueller@reefmaster.org>
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
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

#include "main.h"

static char *oline[] = {
		"",
		"Help Operator",
		"IRC Operator",
		"Co Administrator",
		"Server Administrator",
		"Services Administrator",
		"Network Administrator"
};

void os_kill(char *src, int ac, char **av) {
	if(ac<3) {
		notice(os_name,src,OS_RPL_KILL_USAGE);
		notice(os_name,src,OS_RPL_HELP,"KILL");
		return;
	}
	user *u = finduser(src);
	operuser *o = findoper(src);
	if(o) {
		if(!isidentified(u,src)) {
			notice(os_name,src,OS_ERR_ACCESSDENIED2);
			notice(os_name,src,NS_RPL_NEEDIDENTIFY,src);
			return;
		}
		if(!o->can_kill) {
			notice(os_name,src,OS_ERR_ACCESSDENIED2);
			return;
		}
	} else {
		if(u->oper<os_access_flag) {
			notice(os_name,src,OS_ERR_ACCESSDENIED,os_name,oline[os_access_flag]);
			return;
		}
	}
	char *nick = sstrdup(av[1]);
	if(!finduser(nick)) {
		notice(os_name,src,OS_ERR_USERNOTFOUND,nick);
		return;
	}
	char reason[1024] = "";
		int i = 2;
		for(i=2;i<ac;i++) {
		strcat(reason,av[i]);
		if(i<ac) {
			strcat(reason," ");
		}
	}
	s_kill(os_name,av[1],reason);
	notice(os_name,src,OS_RPL_KILL_SUCCESS,av[1]);
	return;
}
