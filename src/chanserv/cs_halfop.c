/*
 * cs_dehalfop.c
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
 * handle the DEHALFOP command
 */
void cs_dehalfop(char *src, int ac, char **av) {
	char *nick,*chan;
	int level_src,level_target;
	user *u,*u1;
	ChanInfo *c;
	if(ac<3) {
		notice(cs_name,src,CS_ERR_ACCCMD_USAGE,"DEHALFOP");
		notice(cs_name,src,CS_RPL_HLP,"DEHALFOP");
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
	if(level_src<HOP_LIST) {
		notice(cs_name,src,CS_ERR_XOP_HIGHERACCESS,"Hop");
		return;
	}
	if(level_target<HOP_LIST) {
		if(stricmp(src,nick)==0) {
			notice(cs_name,src,CS_ERR_XOP_HIGHERACCESS,"Hop");
			return;
		} else {
			notice(cs_name,src,CS_ERR_XOP_HIGHERACCESS2,nick);
			return;
		}
	}
	dehop(cs_name,nick,chan);
	return;
}

/********************************************************************/
/**
 * handle the HALFOP command
 */
void cs_halfop(char *src, int ac, char **av) {
	char *nick,*chan;
	int level_src,level_target;
	user *u,*u1;
	ChanInfo *c;
	if(ac<3) {
		notice(cs_name,src,CS_ERR_ACCCMD_USAGE,"HALFOP");
		notice(cs_name,src,CS_RPL_HLP,"HALFOP");
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
	if(level_src<HOP_LIST) {
		notice(cs_name,src,CS_ERR_XOP_HIGHERACCESS,"Hop");
		return;
	}
	if(level_target<HOP_LIST) {
		if(stricmp(src,nick)==0) {
			notice(cs_name,src,CS_ERR_XOP_HIGHERACCESS,"Hop");
			return;
		} else {
			notice(cs_name,src,CS_ERR_XOP_HIGHERACCESS2,nick);
			return;
		}
	}
	hop(cs_name,nick,chan);
	return;
}
