/*
 *      as_savedata.c - severin
 *      
 *      Copyright (c) 2015 Severin Mueller <severin.mueller@reefmaster.org>
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

static char *acc[] = {
		"",
		"Help Operator",
		"IRC Operator",
		"Co Administrator",
		"Server Administrator",
		"Services Administrator",
		"Network Administrator"
};


/**
 * forces the data to be saved on disk
 */
void as_savedata(char *src,int ac,char **av) {
	user *u = finduser(src);
	if (u->oper<as_access_flag) {
		notice(as_name,src,AS_ERR_ACCESS_DENIED,as_name,acc[as_access_flag]);
		return;
	}
	save_database();
	notice(as_name,src,"Data successfully saved");
}
