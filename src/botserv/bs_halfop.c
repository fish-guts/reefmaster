/*
 *      bs_halfop.c - severin
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

void bs_halfop(char *src,int ac,char **av) {
	user *u = finduser(src);
	char *botname;
	char *chan;
	char *nick;

	if(ac<3) {
		notice(bs_name,src,BS_ERR_DEHALFOP_USAGE);
		notice(bs_name,src,BS_RPL_HLP,bs_name,"HALFOP");
		return;
	}
	botname = sstrdup(av[1]);
	chan = sstrdup(av[2]);
	nick = sstrdup(av[3]);

	bot *b = findbot(botname);

	if(!b) {
		notice(bs_name,src,BS_ERR_NOTFOUND,botname);
		return;
	}

	if(!is_bot_on_chan(botname,chan)) {
		notice(bs_name,src,BS_ERR_OP_NOT_ON_CHAN,botname,chan);
		return;
	}
	if(!bot_identified(u,b)) {
		notice(bs_name,src,BS_ERR_ACCESSDENIED,b->name,bs_name);
		return;
	}
	hop(b->name,nick,chan);

	return;

}
