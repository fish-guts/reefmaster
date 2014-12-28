/*
 *      operserv.c - severin
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

operuser *opers = NULL;

static os_cmd *find_os(const char *name);

static char *aoper[] = {
	OS_RPL_ISNOWHELPOP,				
	OS_RPL_ISNOWIRCOP,
	OS_RPL_ISNOWCOADMIN,
	OS_RPL_ISNOWADMIN,
	OS_RPL_ISNOWSA,
	OS_RPL_ISNOWNETADMIN
};

static os_cmd os_cmds[] = {
	{ "AKILL", os_akill },
	{ "CHGHOST", os_chghost },
	{ "GLOBAL", os_global },
	{ "LOCAL", NULL },
	{ "HELP", NULL },
	{ "KICK", NULL },
	{ "KILL", NULL },
	{ "OPER", os_oper },
	{ "SGLINE", NULL },
	{ "SKLINE", NULL },
	{ "SQLINE", NULL },
	{ "SVSNICK", NULL },
	{ "SZLINE", NULL },

};

/**
 * the main operserv routine
 */
void operserv(char *src, char *av) {
	int i = 0;
	char **uv = (char**) malloc(sizeof(char**) * 4096);
	char *pch = strtok(av, " ");
	os_cmd *os;
	user *u = finduser(src);
	while (pch != NULL) {
		uv[i] = sstrdup(pch);
		i++;
		pch = strtok(NULL, " ");
	}
	if ((os = find_os(uv[0]))) {
		if (os->func)
			os->func(src, i, uv);
	} else {
		addlog(2, LOG_DBG_NS_UNKNOWN, ns_name, src, u->username, u->hostname,av);
	}
}
/********************************************************************/
/**
 * find the correct operserv command
 */
static os_cmd *find_os(const char *name) {
	os_cmd *cmd;
	for (cmd = os_cmds; cmd->name; cmd++) {
		if (stricmp(name, cmd->name) == 0)
			return cmd;
	}
	return NULL;
}

extern int os_connect(int sock)
{
	char *nick = (char*) malloc(sizeof(char)*256);
	sprintf(nick,SNICK,os_name,s_user,s__host,s_name,os_realname);
	send(sock,nick,(int)strlen(nick),0);
	return 0;
}

void announce_oper(char *oper,int lvl)
{
	globops(os_name,aoper[lvl-1],oper);
}
operuser *findoper(const char *src) {
	operuser *o = opers;
	while (o && stricmp(o->nick, src) != 0) {
		o = o->next;
	}
	return o;
}
