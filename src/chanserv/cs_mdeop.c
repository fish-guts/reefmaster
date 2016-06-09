/*
 * mdeop.c
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
 * handle the MDEOP command
 */
void cs_mdeop(char *src, int ac, char **av) {
	int addacc;
	if (ac < 1) {
		notice(cs_name, src, CS_MDEOP_ERR_USAGE);
		notice(cs_name, src, CS_RPL_HLP, cs_name, "MDEOP");
		return;
	}
	char *chan = sstrdup(av[1]);
	user *u = finduser(src);
	if (!isregcs(chan)) {
		notice(cs_name, src, CS_ERR_NOTREG, chan);
		return;
	}
	ChanInfo *c = findchan(chan);
	if ((addacc = cs_xop_get_level(u, c)) < cs_mkick_access) {
		notice(cs_name, src, CS_XOP_ERR_HIGHERACCESS, get_opacc(cs_mkick_access));
		return;
	}
	channel *channel = findchannel(chan);

	do_mdeop(channel);

	return;
}

void do_mdeop(channel *c) {
	do_join(cs_name,c->name);
	do_op(cs_name,cs_name,c->name);
	if(c) {
		chanuser *cu = c->users;
		while(cu) {
			if(isop(c,cu->u)) {
				deop(cs_name,cu->u->nick,c->name);
			}
			cu = cu->next;
		}
	}
	do_part(cs_name,c->name,"Leaving");
	return;
}
