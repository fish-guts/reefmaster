/*
 *      adminserv.c - severin
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

static as_cmd *find_as(const char *name);

as_cmd as_cmds[] = {
		{ "SAVEDATA",	as_savedata }
};


extern int as_connect(int sock)
{
	int rc;
	char *nick = (char*)malloc(sizeof(char)*256);
	sprintf(nick,"& %s 1 0 %s %s %s 0 +qdS * :%s\r\n",as_name,s_user,s__host,s_name,as_realname);
	rc = send(sock,nick,(int)strlen(nick),0);
	free(nick);
	return rc;
}

void adminserv(char *src, char *av) {
	int i = 0;
	char **uv = (char**) malloc(sizeof(char) * 1024);
	char *pch = strtok(av, " ");
	as_cmd *as;
	user *u = finduser(src);
	while (pch != NULL) {
		uv[i] = sstrdup(pch);
		i++;
		pch = strtok(NULL, " ");
	}
	if ((as = find_as(uv[0]))) {
		if (as->func) {
			as->func(src, i, uv);
		}
		if (strcmp(uv[0], "PING") != 0) {
			addlog(1, LOG_DBG_NS, as_name, src, u->username, u->hostname, av);
		}
	} else {
		addlog(2, LOG_DBG_NS_UNKNOWN, as_name, src, u->username, u->hostname,
				av);
	}
}

void as_savedata(char *src,int ac,char **av) {
	save_botserv_db();
	save_nickserv_db();
	save_chanserv_db();
	notice(as_name,src,"Data saved");
}

static as_cmd *find_as(const char *name) {
	as_cmd *cmd;
	for (cmd = as_cmds; cmd->name; cmd++) {
		if (stricmp(name, cmd->name) == 0)
			return cmd;
	}
	return NULL;
}

