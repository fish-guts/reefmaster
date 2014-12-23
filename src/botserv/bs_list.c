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

void bs_list(char *src,int ac,char **av) {
	user *u = finduser(src);
	if(u->oper<bs_access_list) {
		notice(bs_name,src,BS_ERR_NEEDMOREPRIVS,bs_name);
		return;
	}
	if(ac<1) {
		notice(bs_name,src,BS_ERR_LIST_USAGE);
		notice(bs_name,src,BS_RPL_HLP,bs_name,"LIST");
		return;
	}
	int i = 0;
	notice(bs_name,src,BS_RPL_LIST_BEGIN);
	bot *b = botlist;
	while(b) {
		++i;
		notice(bs_name,src,BS_RPL_LIST_ENTRY,i,b->name,b->username,s_name,b->realname);
		b = b->next;
	}
	if(i==1) {
		notice(bs_name,src,BS_RPL_LIST_COMPLETE1);
	} else {
		notice(bs_name,src,BS_RPL_LIST_COMPLETE2,i);
	}
}
