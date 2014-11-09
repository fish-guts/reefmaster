/*
 * ns_listchans.c
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

void ns_listchans(char *src, int ac, char **av) {
	static char *opacc[] = { NULL, "Uop", "Vop", "Hop", "Aop", "Sop","Admin","Owner",
			"Successor", "Founder" };
	user *u = finduser(src);
	char *nick = (char*) malloc(sizeof(char*) * 64);
	if (ac == 2)
		nick = sstrdup(av[1]);
	else
		nick = sstrdup(src);

	if (!isreg(nick)) {
		notice(ns_name, src, NS_ERR_NOTREG, nick);
		return;
	}
	if (hasaccess(u, nick) < 0) {
		notice(ns_name, src, NS_ERR_ACCESSDENIED, nick);
		notice(ns_name, src, NS_RPL_NEEDIDENTIFY, nick);
		return;
	}
	static char *addedby_lvl[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8","9","10","11","12",
			"\2ServiceRootAdmin\2" };
	op *o = global_op_list;
	int i = 0;
	char str[128];
	notice(ns_name, src, NS_RPL_LISTCHANS_BEGIN, nick);
	ChanInfo *c = chans;
	while(c) {
		if(stricmp(c->founder,nick)==0) {
			notice(ns_name, src, NS_RPL_LISTCHANS_ENTRY2,i+1,"Founder",c->name);
			i++;
		}
		else if(c->successor) {
			if(stricmp(c->successor,nick)==0) {
				notice(ns_name, src, NS_RPL_LISTCHANS_ENTRY2,"Successor",o->chan);
				i++;
			}
		}
		c = c->next;
	}
	while (o) {
		if (stricmp(nick, o->nick) == 0) {
			if ((o->level > 8) && (o->level<AKICK_LIST)) {
				notice(ns_name, src, NS_RPL_LISTCHANS_ENTRY2, opacc[o->level],
						o->chan);
			} else {
				strftime(str, 100, "%d/%m/%Y %T %Z", localtime(&o->addedon));
				notice(ns_name, src, NS_RPL_LISTCHANS_ENTRY, i + 1,
						opacc[o->level], o->chan, addedby_lvl[o->addedbyacc],
						o->addedby, str);
			}
			i++;
		}
		o = o->next;
	}
	if ((i > 1) || (i == 0)) {
		notice(ns_name, src, NS_RPL_LISTCHANS_END2, i);
	} else {
		notice(ns_name, src, NS_RPL_LISTCHANS_END1);
	}
}
