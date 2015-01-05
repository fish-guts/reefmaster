/*
 * cs_drop.c
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
 * handle the DROP command
 */

void cs_drop(char *src, int ac, char **av) {
	user *u = finduser(src);
	ChanInfo *c;
	if (ac < 2) {
		notice(cs_name, src, NS_ERR_DRP_USAGE);
		notice(cs_name, src, CS_RPL_HLP,ns_name,"DROP");
		return;
	}
	char *chan = av[1];
	if (!isregcs(chan)) {
		notice(cs_name, src, CS_ERR_NOTREG, chan);
		return;
	}
	c = findchan(chan);
	if (cs_xop_get_level(u,c)<FOUNDER) {
		notice(ns_name, src, CS_ERR_ACCESSDENIED, chan);
		notice(ns_name, src, CS_RPL_NEEDIDENTIFY, chan);
		return;
	}
	notice(ns_name, src, CS_RPL_DRP_SUCCESS, chan);
	delete_chan(c);
	mode(s_name, chan, "-r", NULL);
	return;
}

