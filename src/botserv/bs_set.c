/*
 *      bs_set.c - severin
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

// ---- static

static void bs_set_name(char *src,int ac,char **av);
static void bs_set_password(char *src,int ac,char **av);
static void bs_set_realname(char *src,int ac,char **av);
static void bs_set_username(char *src,int ac,char **av);

void bs_set(char *src,int ac,char **av) {
	user *u = finduser(src);
	if(u->oper<bs_access_set) {
		notice(bs_name,src,BS_ERR_NEEDMOREPRIVS,bs_name);
		return;
	}
	if(ac<2) {
		notice(bs_name,src,BS_ERR_SET_USAGE);
		notice(bs_name,src,BS_RPL_HLP,bs_name,"SET");
		return;
	}
	bot *b = findbot(av[1]);
	if(!b) {
		notice(bs_name,src,BS_ERR_KICK_BOT,av[1]);
		return;
	}
	if(!bot_identified(u,b)) {
		notice(bs_name,src,BS_ERR_ACCESSDENIED,b->name,bs_name);
		return;
	}
	if(!is_bot_on_chan(av[1],av[2])) {
		notice(bs_name,src,BS_ERR_OP_NOT_ON_CHAN,av[1],av[2]);
		return;
	}
	if(stricmp(av[2],"NAME")==0) {
		bs_set_name(src,ac,av);
	} else if(stricmp(av[2],"USERNAME")==0) {
		bs_set_username(src,ac,av);
	} else if(stricmp(av[2],"PASSWORD")==0) {
		bs_set_password(src,ac,av);
	} else if(stricmp(av[2],"REALNAME")==0) {
		bs_set_realname(src,ac,av);
	} else {
		notice(bs_name,src,BS_ERR_NOSUCHCMD,av[2]);
		return;
	}
}
static void bs_set_name(char *src,int ac,char **av) {
	if(ac<4) {
		notice(bs_name,src,BS_ERR_SET_OPT_USAGE,"NAME");
		notice(bs_name,src,BS_RPL_HLP,bs_name,"SET NAME");
		return;
	}
	if (!check_valid_nickname(av[3])) {
		notice(bs_name,src,BS_ERR_INVALIDNICKNAME,av[3]);
		return;
	}
	bot *b = findbot(av[1]);
	b->name = sstrdup(av[3]);
	s_kill(bs_name,av[1],BS_KILL_NAMECHANGE);
	notice(bs_name,src,BS_SET_NAME_SUCCESS,av[1],av[3]);
}
static void bs_set_password(char *src,int ac,char **av) {
	if(ac<4) {
		notice(bs_name,src,BS_ERR_SET_OPT_USAGE,"PASSWORD");
		notice(bs_name,src,BS_RPL_HLP,bs_name,"SET PASSWORD");
		return;
	}
	if (strlen(av[3]) < 5) {
		notice(bs_name, src, BS_ERR_PASSTOOSHORT);
		notice(bs_name,src,BS_RPL_HLP,bs_name,"ADD");
		return;
	}
	/* the password shouldn't be the same as the nickname */
	if (stricmp(av[3], av[1]) == 0) {
		notice(bs_name, src, BS_ERR_PASSSAMEASNICK);
		notice(bs_name, src, CS_RPL_REG_HLP, cs_name,"ADD");
		return;
	}
	bot *b = findbot(av[1]);
	s_kill(bs_name,av[1],BS_KILL_NAMECHANGE);
	b->password = sstrdup(av[3]);
	notice(bs_name,src,BS_SET_PASS_SUCCESS,av[1],av[3]);
}
static void bs_set_realname(char *src,int ac,char **av) {
	if(ac<4) {
		notice(bs_name,src,BS_ERR_SET_OPT_USAGE,"REALNAME");
		notice(bs_name,src,BS_RPL_HLP,bs_name,"SET REALNAME");
		return;
	}
	char realname[256];
	int i = 3;
	for(i=3;i<ac;i++) {
		strcat(realname,av[i]);
		if(i<ac) {
			strcat(realname," ");
		}
	}
	s_kill(bs_name,av[1],BS_KILL_NAMECHANGE);
	bot *b = findbot(av[1]);
	b->realname = sstrdup(realname);
	notice(bs_name,src,BS_SET_REALNAME_SUCCESS,av[1],realname);
}
static void bs_set_username(char *src,int ac,char **av) {
	if(ac<4) {
		notice(bs_name,src,BS_ERR_SET_OPT_USAGE,"USERNAME");
		notice(bs_name,src,BS_RPL_HLP,bs_name,"SET USERNAME");
		return;
	}
	s_kill(bs_name,av[1],BS_KILL_NAMECHANGE);
	bot *b = findbot(av[1]);
	b->username = sstrdup(av[3]);
	notice(bs_name,src,BS_SET_USERNAME_SUCCESS,av[1],av[3]);
}
