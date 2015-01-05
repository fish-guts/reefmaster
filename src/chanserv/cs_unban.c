/*
 * cs_unban.c
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
 * check if there a matching bans on the channel
 */
chanban *match_ban(char *mask,channel *c) {
	chanban *b = c->banlist;
	while(b) {
		if(ifmatch_0(b->mask,mask)) {
			return b;
		}
		b = b->next;
	}
	return NULL;
}

/**
 * cs_unban Handle the Chanserv UNBAN command
 * User can lift a ban from Chanserv that matches its mask. UOP Access is required.
 */
void cs_unban(char *src, int ac, char **av) {
	if(ac<2) {
		notice(cs_name,src,CS_RPL_UBN_USAGE);
		notice(cs_name, src, CS_RPL_HLP, cs_name, "UNBAN");
		return;
	}
	char finalmask[256];
	user *u = finduser(src);
	char *chan = sstrdup(av[1]);
	if (!isregcs(chan)) {
		notice(cs_name, src, CS_ERR_NOTREG, chan);
		return;
	}
	ChanInfo *c = findchan(chan);
	if (cs_xop_get_level(finduser(src),c) < ACCESS_UOP) {
		notice(cs_name, src, CS_ERR_XOP_HIGHERACCESS, "Uop");
		return;
	}
	sprintf(finalmask,"%s!%s@%s",u->nick,u->username,u->hostname);
	channel *cl = findchannel(chan);
	chanban *b = cl->banlist;
	int i = 0;
	while(b) {
		i++;
		if(ifmatch_0(b->mask,finalmask)) {
			mode(cs_name,b->mask,"-b",c->name);
			channel_remove_ban(cs_name,cl, b->mask);
		}
		b = b->next;
	}
	if(i) {
		notice(cs_name,src,CS_RPL_UBN_LIFTED,i-1,c->name);
		return;
	} else {
		notice(cs_name,src,CS_RPL_UBN_NOT_FOUND,c->name);
		return;
	}
}
