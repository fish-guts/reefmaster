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
	static char *opacc[] = {
			NULL,
			"Uop",
			"Vop",
			"Hop",
			"Aop",
			"Sop",
			"Successor",
			"Founder"
	};
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
	static char *addedby_lvl[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8","\2ServiceRootAdmin\2" };
	NickInfo *n = findnick(nick);
	int i = 0;
	char str[128];
	notice(ns_name, src, NS_RPL_LISTCHANS_BEGIN, nick);
	op *o = global_op_list;
	while (o) {
		if (n->id == o->nick->id) {
			i++;
			if (o->level > 5) {
				notice(ns_name, src, NS_RPL_LISTCHANS_ENTRY2,i, opacc[o->level],o->chan->name);
			} else {
				strftime(str, 100, "%d/%m/%Y %T %Z", localtime(&o->addedon));
				notice(ns_name, src, NS_RPL_LISTCHANS_ENTRY, i,
					opacc[o->level], o->chan->name, addedby_lvl[o->addedbyacc],
					o->addedby, str);
			}
		}
		o = o->next;
	}
	if (i==1) {
		notice(ns_name, src, NS_RPL_LISTCHANS_END1);
	} else {
		notice(ns_name, src, NS_RPL_LISTCHANS_END2, i);
	}
}
