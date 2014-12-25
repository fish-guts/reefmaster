/*
 *      bs_kick.c - severin
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

void bs_info(char *src,int ac,char **av) {
	char *botname;

	if(ac<1) {
		notice(bs_name,src,BS_ERR_INFO_USAGE);
		notice(bs_name,src,BS_RPL_HLP,bs_name,"INFO");
		return;
	}
	botname = sstrdup(av[1]);
	bot *b = findbot(botname);

	if(!b) {
		notice(bs_name,src,BS_ERR_NOTFOUND,botname);
		return;
	}

	char channellist[8196] = "";
	channel *c = chanlist;
	while(c) {
		if(stricmp(c->bot,b->name)==0) {
			strcat(channellist,c->name);
			strcat(channellist,", ");
		}
		c = c->next;
	}
	if(strlen(channellist)>2) {
		channellist[strlen(channellist)-2] = 0;
	}
	notice(bs_name,src,BS_RPL_INF_HEAD,b->name,b->realname);
	notice(bs_name,src,BS_RPL_INF_CHANS,b->name,channellist);
	notice(bs_name,src,BS_RPL_INF_END);
	return;
}
