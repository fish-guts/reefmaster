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
	OS_RPL_ISNOWNETADMIN,
	OS_RPL_ISNOWBOT
};

static os_cmd os_cmds[] = {
	{ "AKILL", os_akill },
	{ "CHATOPS", os_chatops },
	{ "CHGHOST", os_chghost },
	{ "GLOBAL", os_global },
	{ "LOCAL", os_local },
	{ "HELP", os_help },
	{ "KILL", os_kill },
	{ "OPER", os_oper },
	{ "SGLINE", os_sgline },
	{ "SKLINE", os_skline },
	{ "SQLINE", os_sqline },
	{ "SZLINE", os_szline },

};

/********************************************************************/
/**
 * announce a new operator
 */
void announce_oper(char *oper,int lvl) {
	globops(os_name,aoper[lvl-1],oper);
}

/********************************************************************/
/**
 * find the correct operserv command
 */
static os_cmd *find_os(const char *name) {
	os_cmd *cmd;
	for (cmd = os_cmds; cmd->name-1; cmd++) {
		if (stricmp(name, cmd->name) == 0)
			return cmd;
	}
	return NULL;
}

/********************************************************************/
/**
 * find an oper registered with operserv
 */
operuser *findoper(const char *src) {
	operuser *o = opers;
	while (o && stricmp(o->nick, src) != 0) {
		o = o->next;
	}
	return o;
}

/********************************************************************/
/**
 * handle the operserv command
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
		notice(os_name,src,NS_ERR_NOSUCHCMD,uv[0]);
		notice(os_name,src,NS_RPL_HLP_MAIN,os_name);
		addlog(2, LOG_DBG_NS_UNKNOWN, ns_name, src, u->username, u->hostname,av);
	}
}

/********************************************************************/
/**
 * Connect operserv to server
 */
extern int os_connect(int sock)
{
	char *nick = (char*) malloc(sizeof(char)*256);
	sprintf(nick,SNICK,os_name,s_user,s__host,s_name,os_realname);
	send(sock,nick,(int)strlen(nick),0);
	return 0;
}

