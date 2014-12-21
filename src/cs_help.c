/*
 * cs_help.c
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
 * cs_help handle the Chanserv HELP commands
 * Displays the usage of the specified Chanserv command
 */
void cs_help(char *src, int ac, char **av) {
	char help[64];
	if(ac<2) {
		sprintf(help,"%s/%s.help",CS_HELP_PATH,"chanserv");
		help_message(ns_name,src,help);
		return;
	} else if(ac==2) {
		sprintf(help,"%s/%s.help",CS_HELP_PATH,strlower(av[1]));
	}  else if(ac==3) {
		sprintf(help,"%s/%s_%s.help",CS_HELP_PATH,strlower(av[1]),strlower(av[2]));
	}
	if(file_exists(help)) {
		help_message(cs_name,src,help);
	} else {
		notice(cs_name,src,"No Help on that Subject is available");
	}
}
