/*
 *      os_skline.c - severin
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

static void os_skline_add(char *src, int ac, char **av);
static void os_skline_del(char *src, int ac, char **av);


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
 * handle the Operserv SKLINE command
 */
void os_skline(char *src, int ac, char **av) {
	if(stricmp(av[1],"ADD")==0) {
		os_skline_add(src,ac,av);
	} else if(stricmp(av[1],"DEL")==0) {
		os_skline_del(src,ac,av);
	}  else {
		notice(os_name,src,OS_ERR_NOSUCHCMD,av[1]);
		notice(os_name,src,OS_RPL_HELP,"SKLINE");
		return;
	}
}

/********************************************************************/
/**
 * handle the Operserv SKLINE ADD command
 */
static void os_skline_add(char *src, int ac, char **av) {
	long duration = 0;
	if(ac<4) {
		notice(os_name,src,OS_RPL_SKLINE_ADD_USAGE);
		notice(os_name,src,OS_RPL_HELP,"SKLINE ADD");
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
		if(!o->can_skline) {
			notice(os_name,src,OS_ERR_ACCESSDENIED2);
			return;
		}
	} else {
		if(u->oper<os_access_flag) {
			notice(os_name,src,OS_ERR_ACCESSDENIED,os_name,oline[os_access_flag]);
			return;
		}
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
	char *mask = sstrdup(av[2]);
	char **res = NULL;
	char *username;
	char *hostname;
	if(!strchr(mask,'@')) {
		user *u =  finduser(mask);
		if(u) {
			username = sstrdup(u->username);
			hostname = sstrdup(u->hostname);
		} else {
			username = sstrdup("*");
			hostname = sstrdup(mask);
		}
	} else {
		int n_spaces = 0;
		char delimiter[] = "@";
		char *ptr = strtok (mask, delimiter);
		while (ptr) {
		  res = realloc (res, sizeof (char*) * ++n_spaces);
		  res[n_spaces-1] = ptr;
		  ptr = strtok (NULL, delimiter);
		}
		/* realloc one extra element for the last NULL */

		res = realloc (res, sizeof (char*) * (n_spaces+1));
		res[n_spaces] = 0;
		username = sstrdup(res[0]);
		hostname = sstrdup(res[1]);
	}
	char pubmask[128];
	sprintf(pubmask,"%s@%s",username,hostname);
	if(duration > 0) {
		char str[100];
		time_t expiry = (time(NULL) + duration*60);
		strftime(str, 100, "%d/%m/%Y %T %Z", localtime(&expiry));
		globops(os_name,OS_RPL_SKLINE_ADDED,src,pubmask,reason,str);
		kline(os_name,username,hostname,reason,duration);
	} else {
		globops(os_name,OS_RPL_SKLINE_ADDED2,src,pubmask,reason);
		kline(os_name,username,hostname,reason,0);
	}
	notice(os_name,src,OS_RPL_SKLINE_ADD_SUCCESS,av[2]);
	return;
}


/********************************************************************/
/**
 * handle the Operserv SKLINE DEL command
 */
static void os_skline_del(char *src, int ac, char **av) {
	if(ac<3) {
		notice(os_name,src,OS_RPL_SKLINE_DEL_USAGE);
		notice(os_name,src,OS_RPL_HELP,"SKLINE DEL");
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
		if(!o->can_skline) {
			notice(os_name,src,OS_ERR_ACCESSDENIED2);
			return;
		}
	} else {
		if(u->oper<os_access_flag) {
			notice(os_name,src,OS_ERR_ACCESSDENIED,os_name,oline[os_access_flag]);
			return;
		}
	}
	char *mask = sstrdup(av[2]);
	char **res = NULL;
	char *username;
	char *hostname;
	if(!strchr(mask,'@')) {
		user *u =  finduser(mask);
		if(u) {
			username = sstrdup(u->username);
			hostname = sstrdup(u->hostname);
		} else {
			username = sstrdup("*");
			hostname = sstrdup(mask);
		}
	} else {
		int n_spaces = 0;
		char delimiter[] = "@";
		char *ptr = strtok (mask, delimiter);
		while (ptr) {
		  res = realloc (res, sizeof (char*) * ++n_spaces);
		  res[n_spaces-1] = ptr;
		  ptr = strtok (NULL, delimiter);
		}
		/* realloc one extra element for the last NULL */
		res = realloc (res, sizeof (char*) * (n_spaces+1));
		res[n_spaces] = 0;
		username = sstrdup(res[0]);
		hostname = sstrdup(res[1]);
	}
	char pubmask[128];
	sprintf(pubmask,"%s@%s",username,hostname);
	rkline(s_name,username,hostname);
	notice(os_name,src,OS_RPL_SKLINE_DEL_SUCCESS,pubmask);
	return;
}

