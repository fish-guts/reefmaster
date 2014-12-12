/*
 * cs_mkick.c
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

void cs_mkick(char *src, int ac, char **av) {
	notice(as_name,src,"debug");
	int addacc;
	if (ac < 2) {
		notice(cs_name, src, CS_ERR_MKICK_USAGE);
		notice(cs_name, src, CS_RPL_HLP, cs_name, "MKICK");
		return;
	}
	char *chan = sstrdup(av[1]);
	char *reason = sstrdup(av[2]);
	user *u = finduser(src);
	if (!isregcs(chan)) {
		notice(cs_name, src, CS_ERR_NOTREG, chan);
		return;
	}
	ChanInfo *c = findchan(chan);
	if ((addacc = cs_xop_get_level(u, c)) < cs_mkick_access) {
		notice(cs_name, src, CS_ERR_XOP_HIGHERACCESS, get_opacc(cs_mkick_access));
		return;
	}
	channel *channel = findchannel(chan);
	int relevant_count;
	if(channel->bot) {
		relevant_count = 1;
	} else {
		relevant_count = 0;
	}
		if(channel->ucnt<relevant_count) {
		notice(cs_name,src,CS_RPL_MKICK_NOUSERS,chan);
		return;
	}
	char final_reason[256];
	sprintf(final_reason,"MKICK Command used by %s (%s)",src,reason);
	do_mkick(src,channel,final_reason);

	return;
}

void do_mkick(char *src,channel *c, char *reason) {
	do_join(cs_name,c->name);
	if(c) {
		chanuser *cu = c->users;
		while(cu) {
			kick(cs_name,cu->u->nick,c->name,reason);
			cu = cu->next;
		}
	}
	do_part(cs_name,c->name,"Leaving");
}
