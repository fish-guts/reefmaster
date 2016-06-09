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

static void new_akill(char *src,char *mask, char *reason, time_t duration);
static void os_akill_add(char *src, int ac, char **av);
static void os_akill_del(char *src, int ac, char **av);
static void os_akill_list(char *src, int ac, char **av);

akill *akills = NULL;

static char *oline[] = {
		"",
		"Help Operator",
		"IRC Operator",
		"Co Administrator",
		"Server Administrator",
		"Services Administrator",
		"Network Administrator"
};

/********************************************************************/
/**
 * remove an akill mask from the akill list
 */
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

/********************************************************************/
/**
 * find an akill entry in the akill list
 */
akill *findakill(const char *mask) {
	akill *a = akills;
	while (a && stricmp(a->mask, mask) != 0) {
		a = a->next;
	}
	return a;
}

/********************************************************************/
/**
 * add new akill mask to akill list
 */
static void new_akill(char *src,char *mask, char *reason, time_t duration) {
	akill *a = scalloc(sizeof(akill), 1);
	a->added_by = sstrdup(src);
	a->mask = sstrdup(mask);
	a->reason = sstrdup(reason);
	if(duration) {
		a->expires = (time(NULL) + (duration*60));
	} else {
		a->expires = 0;
	}
	a->next = akills;
	if (akills)
		akills->prev = a;
	akills = a;
}

/********************************************************************/
/**
 * handle the Operserv AKILL command
 */
void os_akill(char *src, int ac, char **av) {
	if(stricmp(av[1],"ADD")==0) {
		os_akill_add(src,ac,av);
	} else if(stricmp(av[1],"DEL")==0) {
		os_akill_del(src,ac,av);
	} else if(stricmp(av[1],"LIST")==0) {
		os_akill_list(src,ac,av);
	} else {
		notice(os_name,src,OS_AKILL_ERR_NOSUCHCMD,av[1]);
		return;
	}
}

/********************************************************************/
/**
 * handle the Operserv AKILL ADD command
 */
static void os_akill_add(char *src, int ac, char **av) {
	int duration = 0;
	if(ac<4) {
		notice(os_name,src,OS_AKILL_RPL_ADD_USAGE);
		notice(os_name,src,OS_RPL_HELP,"AKILL ADD");
		return;
	}
	duration = get_duration(av[3]);
	user *u = finduser(src);
	operuser *o = findoper(src);
	if(o) {
		if(!isidentified(u,src)) {
			notice(os_name,src,OS_ERR_ACCESSDENIED2);
			notice(os_name,src,NS_RPL_NEEDIDENTIFY,src);
			return;
		}
		if(!o->can_akill) {
			notice(os_name,src,OS_ERR_ACCESSDENIED2);
			return;
		}
	} else {
		if(u->oper<os_access_flag) {
			notice(os_name,src,OS_ERR_ACCESSDENIED,os_name,oline[os_access_flag]);
			return;
		}
	}

	if(findakill(av[2])) {
		notice(os_name,src,OS_AKILL_ERR_EXISTS,av[2]);
		return;
	}
	char reason[1024] = "";
	int i = 4;
	if(duration) {
		for(i=4;i<ac;i++) {
			strcat(reason,av[i]);
			if(i<ac-1) {
				strcat(reason," ");
			}
		}
	} else {
		for(i=3;i<ac;i++) {
			strcat(reason,av[i]);
			if(i<ac) {
				strcat(reason," ");
			}
		}
	}
	if(duration > 0) {
		char str[100];
		time_t expiry = (time(NULL) + duration*60);
		strftime(str, 100, "%d/%m/%Y %T %Z", localtime(&expiry));
		globops(os_name,OS_AKILL_RPL_ADDED,src,av[2],reason,str);
		new_akill(src,av[2],reason,duration);
	} else {
		globops(os_name,OS_AKILL_RPL_ADDED2,src,av[2],reason);
		new_akill(src,av[2],reason,0);
	}
	notice(os_name,src,OS_AKILL_RPL_ADD_SUCCESS,av[2]);
	return;
}

/********************************************************************/
/**
 * handle the Operserv AKILL DEL command
 */
static void os_akill_del(char *src, int ac, char **av) {
	if(ac<3) {
		notice(os_name,src,OS_AKILL_RPL_DEL_USAGE);
		notice(os_name,src,OS_RPL_HELP,"AKILL DEL");
		return;
	}
	user *u = finduser(src);
	operuser *o = findoper(src);
	if(o) {
		if(!isidentified(u,src)) {
			notice(os_name,src,OS_ERR_ACCESSDENIED2);
			notice(os_name,src,NS_RPL_NEEDIDENTIFY,src);
			return;
		}
		if(!o->can_sgline) {
			notice(os_name,src,OS_ERR_ACCESSDENIED2);
			return;
		}
	} else {
		if(u->oper<os_access_flag) {
			notice(os_name,src,OS_ERR_ACCESSDENIED,os_name,oline[os_access_flag]);
			return;
		}
	}
	if(!findakill(av[2])) {
		notice(os_name,src,OS_AKILL_RPL_NOTFOUND,av[2]);
		return;
	}
	delete_akill(av[2]);
	notice(os_name,src,OS_AKILL_RPL_DEL_SUCCESS,av[2]);
	return;
}


/********************************************************************/
/**
 * handle the Operserv AKILL LIST command
 */
static void os_akill_list(char *src, int ac, char **av) {
	if(ac<2) {
		notice(os_name,src,OS_AKILL_LIST_ERR_USAGE);
		notice(os_name,src,OS_RPL_HELP,"AKILL LIST");
		return;
	}
	user *u = finduser(src);
	operuser *o = findoper(src);
	if(o) {
		if(!isidentified(u,src)) {
			notice(os_name,src,OS_ERR_ACCESSDENIED2);
			notice(os_name,src,NS_RPL_NEEDIDENTIFY,src);
			return;
		}
		if(!o->can_sgline) {
			notice(os_name,src,OS_ERR_ACCESSDENIED2);
			return;
		}
	} else {
		if(u->oper<os_access_flag) {
			notice(os_name,src,OS_ERR_ACCESSDENIED,os_name,oline[os_access_flag]);
			return;
		}
	}
	int i = 0;
	notice(os_name,src,OS_AKILL_RPL_LIST_BEGIN,os_name);
	akill *a = akills;
	while (a) {
		++i;
		notice(os_name,src,OS_AKILL_LIST_RPL_ENTRY,i,a->mask,a->added_by,a->reason,a->expires);
		a = a->next;
	}
	if (i==1) {
		notice(os_name,src,OS_LIST_RPL_END1);
	} else {
		notice(os_name,src,OS_LIST_RPL_END2);
	}
}

