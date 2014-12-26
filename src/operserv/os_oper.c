/*
 *      os_oper.c - severin
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

static void os_oper_add(char *src, int ac, char **av);
static void os_oper_del(char *src, int ac, char **av);
static void os_oper_list(char *src, int ac, char **av);

void os_oper(char *src, int ac, char **av) {
	if(stricmp(av[2],"ADD")==0) {
		os_oper_add(src,ac,av);
	} else if(stricmp(av[2],"DEL")==0) {
		os_oper_del(src,ac,av);
	} else if(stricmp(av[2],"LIST")==0) {
		os_oper_list(src,ac,av);
	} else {
		notice(bs_name,src,BS_ERR_NOSUCHCMD,av[2]);
		return;
	}
}

static void os_oper_add(char *src, int ac, char **av) {

}
static void os_oper_del(char *src, int ac, char **av) {
}
static void os_oper_list(char *src, int ac, char **av) {
}

