/*
 * cs_ cadmin.c
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

void cs_admin(char *src, int ac, char **av) {
	char *chan = av[1];
	if (stricmp(av[2], "ADD") == 0) {
		char *nick = av[3];
		cs_xop_add(src, chan, ADMIN_LIST, nick);
		return;
	} else if (stricmp(av[2], "DEL") == 0) {
		char *nick = av[3];
		cs_xop_del(src, chan, ADMIN_LIST, nick);
		return;
	} else if (stricmp(av[2], "LIST") == 0) {
		cs_xop_list(src, chan, ADMIN_LIST);
		return;
	} else if (stricmp(av[2], "WIPE") == 0) {
		cs_xop_wipe(src, chan, ADMIN_LIST);
		return;
	}
	return;
}
