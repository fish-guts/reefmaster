/*
 * cs_invite.c
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
 * handle the INVITE command
 */
void cs_invite(char *src,int ac, char **av) {
	ChanInfo *c;
	char *chan;
	char *nick;
	user *u = finduser(src);
	if(ac<2) {
		notice(cs_name,src,CS_ERR_INV_USAGE);
		notice(cs_name,src,CS_RPL_HLP,"INVITE",cs_name);
		return;
	}
	chan = sstrdup(av[1]);
	if(ac==2)
		nick = sstrdup(src);
	else
		nick = sstrdup(av[2]);
	if(!isregcs(chan)) {
		notice(cs_name,src,CS_ERR_NOTREG,chan);
		return;
	}
	c = findchan(chan);
	int lvl = cs_xop_get_level(u,c);
	if(lvl<cs_cmd_invite) {
		notice(cs_name,src,CS_ERR_XOP_HIGHERACCESS,(cs_cmd_invite));
		return;
	}
	if(!findchannel(chan)) {
		notice(cs_name,src,CS_ERR_NOSUCHCHAN,chan);
		return;
	}
	if(ison(findchannel(chan),u)) {
		if(stricmp(src,nick)==0)
			notice(cs_name,src,CS_ERR_INV_ALREADYONCHAN2,chan);
		else
			notice(cs_name,src,CS_ERR_INV_ALREADYONCHAN,nick,chan);
		return;
	}
	invite(cs_name,nick,chan);
	return;
}
