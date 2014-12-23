/*
 * cs_list.c
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

void cs_list(char *src,int ac,char **av) {
	user *u = finduser(src);
	ChanInfo *c = chans;
	int count = 0;
	char *pattern;
	if((u->oper<=0) && (cs_operonly)) {
		notice(cs_name,src,NS_ERR_NEEDMOREPRIVS);
		return;
	}
	if(ac<2) {
		notice(cs_name,src,CS_ERR_LIST_USAGE);
		notice(cs_name,src,CS_RPL_HLP,"LIST");
		return;
	}
	if(!strchr(av[1],'#')) {
		pattern = (char*)malloc(sizeof(char*)*256);
		sprintf(pattern,"#%s",av[1]);
	} else {
		pattern = sstrdup(av[1]);
	}
	notice(cs_name,src,CS_RPL_LIST_BEGIN,pattern);
	while (c) {
		if(ifmatch_0(pattern,c->name)) {
			count++;
			notice(cs_name,src,CS_RPL_LIST_ENTRY,count,c->name,c->founder);
		}
		c = c->next;
	}
	if(count==1) {
		notice(cs_name,src,CS_RPL_LIST_END2);
		return;
	} else {
		notice(cs_name,src,CS_RPL_LIST_END1,count);
		return;
	}
}
