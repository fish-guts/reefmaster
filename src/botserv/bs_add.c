/*
 *      bs_add.c - severin
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
 * handle the Botserv ADD command
 */
void bs_add(char *src,int ac,char **av) {
	user *u = finduser(src);
	char *botname;
	char *password;
	if(u->oper<bs_access_add) {
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
	if (!check_valid_nickname(botname)) {
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
