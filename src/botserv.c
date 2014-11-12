/*
 *      botserv.c - severin
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

bot *botlist = NULL;

static bs_cmd *find_bs(const char *name);

extern int bs_connect(int sock)
{
	char *nick = (char*)malloc(sizeof(char)*256);
	sprintf(nick,"& %s 1 0 %s %s %s 0 +qdS * :%s\r\n",bs_name,s_user,s__host,s_name,bs_realname);
	int rc = send(sock,nick,(int)strlen(nick),0);
	return rc;
}

static bs_cmd bs_cmds[] = {
	{ "ADD", bs_add },
	{ "DEL", NULL },
	{ "LIST", NULL },
	{ "CHAN" , NULL },
	{ "SET" , NULL }
};

/********************************************************************/
/**
 * the main botserv routine
 */
void botserv(char *src, char *av) {
	int i = 0;
	char **uv = (char**) malloc(sizeof(char**) * 4096);
	char *pch = strtok(av, " ");
	bs_cmd *bs;
	user *u = finduser(src);
	while (pch != NULL) {
		uv[i] = sstrdup(pch);
		i++;
		pch = strtok(NULL, " ");
	}
	if ((bs = find_bs(uv[0]))) {
		if (bs->func)
			bs->func(src, i, uv);
	} else
		addlog(2, LOG_DBG_NS_UNKNOWN, bs_name, src, u->username, u->hostname,av);
}

void bs_add(char *src,int ac,char **av) {
	user *u = finduser(src);
	char *botname;
	char *password;
	if(u->oper<bs_acc_manage) {
		notice(bs_name,src,NS_ERR_NEEDMOREPRIVS);
		return;
	}
	if(ac<3) {
		notice(bs_name,src,BS_ERR_ADD_USAGE);
		notice(bs_name,src,BS_RPL_HLP,bs_name,"ADD");
		return;
	}
	botname = sstrdup(av[1]);
	password = sstrdup(av[2]);
	if (match(botname,"([A-Z0-9a-z\\-\\_\\|]+)")!= 1) {
		notice(bs_name,src,BS_ERR_ADD_INVALIDCHARS);
		return;
	}
	if((stricmp(botname,"NONE")==0)
			|| (stricmp(botname,cs_name)==0)
			|| (stricmp(botname,ns_name)==0)
			|| (stricmp(botname,ms_name)==0)
			|| (stricmp(botname,cs_name)==0)
			|| (stricmp(botname,bs_name)==0)
			|| (stricmp(botname,as_name)==0)
			|| (stricmp(botname,os_name)==0)
			|| (isreg(botname))
			|| (isregcs(botname))) {
		notice(bs_name,src,BS_ERR_INVALIDNICKNAME,botname);
		return;
	}
	if (strlen(password) < 5) {
		notice(bs_name, src, BS_ERR_PASSTOOSHORT);
		notice(bs_name,src,BS_RPL_HLP,bs_name,"ADD");
		return;
	}
	/* the password shouldn't be the same as the nickname */
	if (stricmp(password, botname) == 0) {
		notice(bs_name, src, BS_ERR_PASSSAMEASNICK);
		notice(bs_name, src, CS_RPL_REG_HLP, cs_name,"ADD");
		return;
	}
	if(isregbot(botname)) {
		notice(bs_name,src,BS_ERR_ADD_EXISTS,botname);
		return;
	}
	notice(cs_name,src,BS_RPL_ADD_SUCCESS1,botname);
	notice(cs_name,src,BS_RPL_ADD_SUCCESS2,password);
	notice(cs_name,src,BS_RPL_ADD_SUCCESS3);
	if(register_bot(botname,password))
		connect_bot(botname);

	return;

}
/********************************************************************/
/**
 * find the correct botserv command
 */
static bs_cmd *find_bs(const char *name) {
	bs_cmd *cmd;
	for (cmd = bs_cmds; cmd->name; cmd++) {
		if (stricmp(name, cmd->name) == 0)
			return cmd;
	}
	return NULL;
}
bot *register_bot(char *botname,char *password) {
	bot *b;
	b = scalloc(sizeof(bot)+1, 1);
	b->name = sstrdup(botname);
	b->password = sstrdup(password);
	b->realname = sstrdup(botname);
	b->username = sstrdup(botname);
	b->next = botlist;
	if (botlist)
		botlist->prev = b;
	botlist = b;


	return b;
}
void connect_bot(char *botname) {
	bot *b = findbot(botname);
	char *nick = (char*)malloc(sizeof(char)*256);
	sprintf(nick,"& %s 1 0 %s %s %s 0 +qdB * :%s\r\n",b->name,b->username,s_name,s_name,b->realname);
	send(mainsock,nick,(int)strlen(nick),0);
}

void bot_add_chan(bot *b,char *chan) {

}
void bot_del_chan(bot *b,char *chan) {

}
/********************************************************************/
/**
 * find a registered channel in the chanserv table
 */
bot *findbot(const char *botname) {
	bot *b = botlist;
	if (botlist == NULL) {
		return NULL;
	}
	while (b) {
		if(stricmp(b->name, botname) == 0) {
			return b;
		}
		b = b->next;
	}
	return NULL;
}
bot *findbot_onchan(char *chan) {
 return NULL;
}
