/*
 * cs_unban.c
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

/**
 * cs_unban Handle the Chanserv UNBAN command
 * User can lift a ban from Chanserv that matches its mask. UOP Access is required.
 */
void cs_unban(char *src, int ac, char **av) {
	if(ac<2) {
		notice(cs_name,src,"CS_RPL_UBN_USAGE",cs_name);

	}
	user *u = finduser(src);
	char *chan = sstrdup(av[1]);
	if (!isregcs(chan)) {
		notice(cs_name, src, CS_ERR_NOTREG, chan);
		return;
	}
}
