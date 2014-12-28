/*
 *      os_akill.c - severin
 *
 *      Copyright 2014 Severin Mueller <severin.mueller@reefmaster.org>
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
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

#include "main.h"

static char *oline[] = {
		"",
		"Help Operator",
		"IRC Operator",
		"Co Administrator",
		"Server Administrator",
		"Services Administrator",
		"Network Administrator"
};

void os_chghost(char *src, int ac, char **av) {
	if(ac<4) {
		notice(os_name,src,OS_RPL_AKILL_ADD_USAGE);
		notice(os_name,src,OS_RPL_HELP,"AKILL ADD");
		return;
	}
	user *u = finduser(src);
	if(u->oper<os_access_flag) {
		notice(os_name,src,OS_ERR_ACCESSDENIED,oline[os_access_flag]);
		return;
	} else {
		operuser *o = findoper(src);
		if(o) {
			if(!o->can_akill) {
				notice(os_name,src,OS_ERR_ACCESSDENIED2);
				return;
			}
		}
	}
	if(findakill(av[2])) {
		notice(os_name,src,OS_ERR_AKILL_EXISTS,av[2]);
		return;
	}

	notice(os_name,src,OS_RPL_AKILL_ADD_SUCCESS,av[2]);
	return;
}
