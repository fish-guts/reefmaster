/*
 * ns_list.c
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
 * ns_list Handle the Nickserv LIST command
 * List the registered nicknames using the specified search criteria. Requires special privileges
 * configured in the config.
 */
void ns_list(char *src,int ac,char **av) {
	user *u = finduser(src);
	NickInfo *n = nicklist;
	int count = 0;
	char *pattern;
	if((u->oper<=0) && (ns_operonly)) {
		notice(ns_name,src,NS_ERR_NEEDMOREPRIVS);
		return;
	}
	if(ac<2) {
		notice(ns_name,src,NS_ERR_LIST_USAGE);
		notice(ns_name,src,NS_RPL_HLP_SHORT,"LIST");
		return;
	}
	pattern = sstrdup(av[1]);
	notice(ns_name,src,NS_RPL_LIST_BEGIN,pattern);
	while (n) {
		if(ifmatch_0(pattern,n->nick)) {
			count++;
			notice(ns_name,src,NS_RPL_LIST_ENTRY,count,n->nick,n->last_usermask);
		}
		n = n->next;
	}
	if(count==1) {
		notice(ns_name,src,NS_RPL_LIST_END2);
		return;
	} else {
		notice(ns_name,src,NS_RPL_LIST_END1,count);
		return;
	}
}
