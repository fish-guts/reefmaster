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

static void new_oper(char *nick);
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
	if(ac<3) {
		notice(os_name,src,OS_RPL_OPER_ADD_USAGE);
		notice(os_name,src,OS_RPL_HELP,"OPER ADD");
		return;
	}
	user *u = finduser(src);
	if(u->oper<os_access_flag) {
		notice(os_name,src,OS_ERR_ACCESSDENIED,oline[os_access_flag]);
		return;
	}
	if(!isreg(av[2])) {
		notice(os_name,src,NS_ERR_NOTREG,av[2]);
		return;
	}
	new_oper(av[2]);
	notice(os_name,src,OS_RPL_OPER_ADD_SUCCESS,av[2]);
	return;
}

static void new_oper(char *nick) {
	operuser *o = scalloc(sizeof(operuser), 1);
	o->nick = sstrdup(nick);
	o->can_akill = os_can_akill;
	o->can_chatops = os_can_chatops;
	o->can_chghost = os_can_chghost;
	o->can_global = os_can_global;
	o->can_kick = os_can_kick;
	o->can_kill = os_can_kill;
	o->can_local = os_can_local;
	o->can_sgline = os_can_sgline;
	o->can_skline = os_can_skline;
	o->can_sqline = os_can_sqline;
	o->can_svsnick = os_can_svsnick;
	o->can_szline = os_can_szline;
	o->vhost = sstrdup(os_vhost);
	o->next = opers;
	if (opers)
		opers->prev = o;
	opers = o;
}
static void os_oper_del(char *src, int ac, char **av) {
}
static void os_oper_list(char *src, int ac, char **av) {
}

