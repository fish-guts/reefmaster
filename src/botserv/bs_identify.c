/*
 *      bs_identify.c - severin
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
 * handle the Botserv IDENTIFY command
 */
void bs_identify(char *src,int ac,char **av) {
	user *u = finduser(src);
	char *botname;
	char *password;

	if(ac<2) {
		notice(bs_name,src,BS_IDENTIFY_ERR_USAGE);
		notice(bs_name,src,BS_RPL_HLP,bs_name,"IDENTIFY");
		return;
	}

	botname = sstrdup(av[1]);
	password = sstrdup(av[2]);

	bot *b = findbot(botname);

	if (!b) {
		notice(bs_name,src,BS_ERR_NOTFOUND,botname);
		return;
	}

	if (stricmp(b->password,password)!=0) {
		notice(bs_name,src,BS_IDENTIFY_ERR_WRONGPASS,b->name);
		return;
	} else {
		notice(bs_name,src,BS_IDENTIFY_ERR_PASSACC,b->name);
		user_add_bot(u,b);
	}

	return;

}

int bot_identified(user *u, bot *b) {
	botaccess *ba = u->bots;
	while (ba) {
		if (ba->b->id==b->id) {
			return 1;
		}
		ba = ba->next;
	}
	return 0;
}
