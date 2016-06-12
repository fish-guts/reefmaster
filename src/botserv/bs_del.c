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


/********************************************************************/
/**
 * handle the Botserv DEL command
 */
void bs_del(char *src,int ac,char **av) {
	user *u = finduser(src);
	char *botname;
	if (u->oper<bs_access_del) {
		notice(bs_name,src,NS_ERR_NEEDMOREPRIVS);
		return;
	}
	if (ac<2) {
		notice(bs_name,src,BS_DEL_ERR_USAGE);
		notice(bs_name,src,BS_RPL_HLP,bs_name,"DEL");
		return;
	}
	botname = sstrdup(av[1]);
	if (!check_valid_nickname(botname)) {
		notice(bs_name,src,BS_ERR_INVALIDNICKNAME,botname);
		return;
	}
	if (!isregbot(botname)) {
		notice(bs_name,src,BS_ERR_NOTFOUND,botname);
		return;
	}
	disconnect_bot(botname);
	delete_bot(botname);
	notice(cs_name,src,BS_DEL_RPL_SUCCESS,botname);
}
