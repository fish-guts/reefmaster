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

static void chan_del_bot(bot *b,botchan *bc);

extern int bs_connect(int sock)
{
	char *nick = (char*)malloc(sizeof(char)*256);
	sprintf(nick,SNICK,bs_name,s_user,s__host,s_name,bs_realname);
	int rc = send(sock,nick,(int)strlen(nick),0);
	return rc;
}

static bs_cmd bs_cmds[] = {
	{ "ADD", bs_add },
	{ "DEL", bs_del },
	{ "DEHALFOP", bs_dehalfop },
	{ "DEOP", bs_deop },
	{ "DEVOICE", bs_devoice },
	{ "GETPASS", bs_getpass },
	{ "HELP", bs_help },
	{ "IDENTIFY", bs_identify },
	{ "INFO", bs_info },
	{ "KICK", bs_kick },
	{ "OP", bs_op },
	{ "LIST", bs_list },
	{ "MSG", bs_msg },
	{ "SET", bs_set },
	{ "SETPASS", bs_setpass },


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
	} else {
		addlog(2, LOG_DBG_NS_UNKNOWN, bs_name, src, u->username, u->hostname,av);
	}
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
void load_bot(int id,char *botname, char *password, char *username, char *realname) {
	bot *b = scalloc(sizeof(bot),1);
	b->id = id;
	b->name = sstrdup(botname);
	b->password = sstrdup(password);
	b->realname = sstrdup(realname);
	b->username = sstrdup(username);
	b->next = botlist;
	if (botlist)
		botlist->prev = b;
	botlist = b;
}
void connect_bot(char *botname) {
	bot *b = findbot(botname);
	char *nick = (char*)malloc(sizeof(char)*1024);
	sprintf(nick,"& %s 1 0 %s %s %s 0 +qdB * :%s\r\n",b->name,b->username,s_name,s_name,b->realname);
	send(mainsock,nick,(int)strlen(nick),0);
}
void connect_bots(void) {
	bot *b = botlist;
	while(b) {
		connect_bot(b->name);
		b = b->next;
	}
}
void delete_bot(char *botname) {
	bot *b = findbot(botname);
	if (b->prev)
		b->prev->next = b->next;
	else
		botlist = b->next;
	if (b->next)
		b->next->prev = b->prev;
	free(b);
}
void disconnect_bot(char *botname) {
	quit(botname);
}
void add_bot_to_chan(char *botname, char *chan) {
	bot *b = findbot(botname);
	botchan *bc = scalloc(sizeof(botchan),1);
	bc->next = b->chanlist;
	if(b->chanlist)
		b->chanlist->prev = bc;
	b->chanlist = bc;
	bc->chan = sstrdup(chan);
}
void remove_bot_from_chan(char *botname, char *chan) {
	bot *b = findbot(botname);
	botchan *bc = b->chanlist;
	while(bc) {
		if(stricmp(bc->chan,chan)==0) {
			chan_del_bot(b,bc);
		}
		bc = bc->next;
	}
}
static void chan_del_bot(bot *b,botchan *bc) {
    free(bc->chan);
    if(bc->prev)
		bc->prev->next = bc->next;
    else
		b->chanlist = bc->next;
	if (bc->next)
		bc->next->prev = bc->prev;
	free(bc);
}
/********************************************************************/
/**
 * find a registered channel in the botserv table
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
bot *findbot_onchan(char *botname,char *chan) {
	bot *b = findbot(botname);
	botchan *bc = b->chanlist;
	while(bc) {
		if(stricmp(bc->chan,chan)==0) {
			return b;
		}
		bc = bc->next;
	}
	return NULL;
}
/********************************************************************/
/**
 * write the bot table to the database
 */
bot *find_bot_by_id(unsigned int id) {
	bot *b = botlist;
	while(b) {
		if(b->id == id) {
			return b;
		}
		b = b->next;
	}
	return NULL;
}
