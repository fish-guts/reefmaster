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

static void new_akill(char *src,char *mask, char *reason, int duration);
static void os_akill_add(char *src, int ac, char **av);
static void os_akill_del(char *src, int ac, char **av);
static void os_akill_list(char *src, int ac, char **av);

akill *akills = NULL;

static char *oline[] = {
		"",
		"",
		"Help Operator",
		"IRC Operator",
		"Co Administrator",
		"Server Administrator",
		"Services Administrator",
		"Network Administrator"
};

void os_akill(char *src, int ac, char **av) {
	if(stricmp(av[2],"ADD")==0) {
		os_akill_add(src,ac,av);
	} else if(stricmp(av[2],"DEL")==0) {
		os_akill_del(src,ac,av);
	} else if(stricmp(av[2],"LIST")==0) {
		os_akill_list(src,ac,av);
	} else {
		notice(bs_name,src,BS_ERR_NOSUCHCMD,av[2]);
		return;
	}
}

static void os_akill_add(char *src, int ac, char **av) {
	if(ac<5) {
		notice(os_name,src,OS_RPL_AKILL_ADD_USAGE);
		notice(os_name,src,OS_RPL_HELP,"AKILL ADD");
		return;
	}
	user *u = finduser(src);
	if(u->oper<os_access_flag) {
		notice(os_name,src,OS_ERR_ACCESSDENIED,oline[os_access_flag]);
		return;
	}
	operuser *o = findoper(src);
	if(!o->can_akill) {
		notice(os_name,src,OS_ERR_ACCESSDENIED2);
		return;
	}
	if(findakill(av[2])) {
		notice(os_name,src,OS_ERR_AKILL_EXISTS,av[2]);
		return;
	}
	char reason[1024];
	int i = 3;
	for(i=3;i<ac;i++) {
		strcat(reason,av[i]);
		if(i<ac) {
			strcat(reason," ");
		}
	}
	new_akill(src,av[2],reason,atoi(av[4]));
	notice(os_name,src,OS_RPL_AKILL_ADD_SUCCESS,av[2]);
	return;
}

static void new_akill(char *src,char *mask, char *reason, int duration) {
	akill *a = scalloc(sizeof(akill), 1);
	a->added_by = sstrdup(src);
	a->mask = sstrdup(mask);
	a->reason = sstrdup(reason);
	a->expires = (time(NULL) + (duration*60));
	a->next = akills;
	if (akills)
		akills->prev = a;
	akills = a;
}
static void os_akill_del(char *src, int ac, char **av) {
	if(ac<3) {
		notice(os_name,src,OS_RPL_AKILL_DEL_USAGE);
		notice(os_name,src,OS_RPL_HELP,"OPER DEL");
		return;
	}
	user *u = finduser(src);
	if(u->oper<os_access_flag) {
		notice(os_name,src,OS_ERR_ACCESSDENIED,oline[os_access_flag]);
		return;
	}
	if(!findoper(av[2])) {
		notice(os_name,src,OS_RPL_AKILL_NOTFOUND,av[2]);
		return;
	}
	delete_akill(av[2]);
	notice(os_name,src,OS_RPL_AKILL_DEL_SUCCESS,av[2]);
	return;
}
void delete_akill(char *mask) {
	akill *a = findakill(mask);
	if (a->prev)
		a->prev->next = a->next;
	else
		akills = a->next;
	if (a->next)
		a->next->prev = a->prev;
	free(a);
}
static void os_akill_list(char *src, int ac, char **av) {
	if(ac<2) {
		notice(os_name,src,OS_RPL_OPER_LIST_USAGE);
		notice(os_name,src,OS_RPL_HELP,"OPER LIST");
		return;
	}
	user *u = finduser(src);
	if(u->oper<os_access_flag) {
		notice(os_name,src,OS_ERR_ACCESSDENIED,oline[os_access_flag]);
		return;
	}
	int i = 0;
	notice(os_name,src,OS_RPL_OPER_LIST_BEGIN,os_name);
	akill *a = akills;
	while(a) {
		++i;
		notice(os_name,src,OS_RPL_AKILL_LIST_ENTRY,i,a->mask,a->added_by,a->reason,a->expires);
		a = a->next;
	}
	if(i==1) {
		notice(os_name,src,OS_RPL_LIST_END1);
	} else {
		notice(os_name,src,OS_RPL_LIST_END2);
	}
}
akill *findakill(const char *mask) {
	akill *a = akills;
	while (a && stricmp(a->mask, mask) != 0) {
		a = a->next;
	}
	return a;
}
