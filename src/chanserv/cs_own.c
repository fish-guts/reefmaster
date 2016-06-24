/*
 * cs_own.c
 *
 *      Copyright (c) 2016 Severin Mueller <severin.mueller@reefmaster.org>
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
 * handle the ADMIN command
 */
void cs_own(char *src, int ac, char **av) {
	char *nick,*chan;
	int level_src,level_target;
	user *u,*u1;
	ChanInfo *c;
	if(ac<3) {
		notice(cs_name,src,CS_OP_ERR_USAGE,"OWN");
		notice(cs_name,src,CS_RPL_HLP,cs_name,"OWN");
		return;
	}
	nick = sstrdup(av[2]);
	chan = sstrdup(av[1]);
	if(!isregcs(chan)) {
		notice(cs_name,src,CS_ERR_NOTREG,chan);
		return;
	}
	if(!isreg(nick)) {
		notice(cs_name,src,NS_ERR_NOTREG,nick);
		return;
	}
	u = finduser(src);
	u1 = finduser(nick);
	c = findchan(chan);
	level_src = cs_xop_get_level(u,c);
	level_target = cs_xop_get_level(u1,c);
	if(level_src<QOP_LIST) {
		notice(cs_name,src,CS_XOP_ERR_HIGHERACCESS,"Qop");
		return;
	}
	if(level_target<QOP_LIST) {
		if(stricmp(src,nick)==0) {
			notice(cs_name,src,CS_XOP_ERR_HIGHERACCESS,"Qop");
			return;
		} else {
			notice(cs_name,src,CS_XOP_ERR_HIGHERACCESS2,nick);
			return;
		}
	}
	do_owner(cs_name,nick,chan);
	return;
}

/********************************************************************/
/**
 * handle the DEADMIN command
 */
void cs_deown(char *src, int ac, char **av) {
	char *nick,*chan;
	int level_src,level_target;
	user *u,*u1;
	ChanInfo *c;
	if(ac<3) {
		notice(cs_name,src,CS_OP_ERR_USAGE,"DEOWN");
		notice(cs_name,src,CS_RPL_HLP,"DEOWN");
		return;
	}
	nick = sstrdup(av[2]);
	chan = sstrdup(av[1]);
	if(!isregcs(chan)) {
		notice(cs_name,src,CS_ERR_NOTREG,chan);
		return;
	}
	if(!isreg(nick)) {
		notice(cs_name,src,NS_ERR_NOTREG,nick);
		return;
	}
	u = finduser(src);
	u1 = finduser(nick);
	c = findchan(chan);
	level_src = cs_xop_get_level(u,c);
	level_target = cs_xop_get_level(u1,c);
	if(level_src<QOP_LIST) {
		notice(cs_name,src,CS_XOP_ERR_HIGHERACCESS,"Qop");
		return;
	}
	if(level_target<QOP_LIST) {
		if(stricmp(src,nick)==0) {
			notice(cs_name,src,CS_XOP_ERR_HIGHERACCESS,"Qop");
			return;
		} else {
			notice(cs_name,src,CS_XOP_ERR_HIGHERACCESS2,nick);
			return;
		}
	}
	deowner(cs_name,nick,chan);
	return;
}
