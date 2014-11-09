/*
 * cs_identify.c
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

void cs_identify(char *src,int ac,char **av) {
	if(ac<3) {
		notice(cs_name,src,CS_ERR_IDF_USAGE);
		notice(cs_name,src,CS_RPL_HLP,cs_name,"HELP IDENTIFY");
		return;
	}
	char *chan = sstrdup(av[1]);
	char *pass = sstrdup(av[2]);
	user *u = finduser(src);
	if (!isregcs(chan)) {
		notice(cs_name, src, CS_ERR_NOTREG, chan);
		return;
	}
	if (isidentified(u, chan) > 0) {
		notice(ns_name, src, CS_RPL_IDF_ALREADYIDF, chan);
		return;
	}
	ChanInfo *c = findchan(chan);
	if(stricmp(pass,c->pass)!=0) {
		notice(cs_name,src,CS_ERR_IDF_WRONGPASS,chan);
		return;
	} else {
		notice(cs_name,src,CS_RPL_IDF_PASSACCEPTED,chan);
		add_identifiedcs(u,chan);
	}
	return;
}
