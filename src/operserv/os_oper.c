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
static void os_oper_set(char *src, int ac, char **av);
static void os_oper_set_akill(char *src,operuser *o,char *option);
static void os_oper_set_chatops(char *src,operuser *o,char *option);
static void os_oper_set_chghost(char *src,operuser *o,char *option);
static void os_oper_set_global(char *src,operuser *o,char *option);
static void os_oper_set_kill(char *src,operuser *o,char *option);
static void os_oper_set_local(char *src,operuser *o,char *option);
static void os_oper_set_sgline(char *src,operuser *o,char *option);
static void os_oper_set_skline(char *src,operuser *o,char *option);
static void os_oper_set_sqline(char *src,operuser *o,char *option);
static void os_oper_set_szline(char *src,operuser *o,char *option);
static void os_oper_set_vhost(char *src,operuser *o,char *option);


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

/********************************************************************/
/**
 * handle the Operserv OPER command
 */
void os_oper(char *src, int ac, char **av) {
	if(stricmp(av[1],"ADD")==0) {
		os_oper_add(src,ac,av);
	} else if(stricmp(av[1],"DEL")==0) {
		os_oper_del(src,ac,av);
	} else if(stricmp(av[1],"LIST")==0) {
		os_oper_list(src,ac,av);
	} else if(stricmp(av[1],"SET")==0) {
		os_oper_set(src,ac,av);
	} else {
		notice(bs_name,src,BS_ERR_NOSUCHCMD,av[2]);
		return;
	}
}

/********************************************************************/
/**
 * handle the Operserv OPER ADD command
 */
static void os_oper_add(char *src, int ac, char **av) {
	if(ac<3) {
		notice(os_name,src,OS_OPER_ADD_ERR_USAGE);
		notice(os_name,src,OS_RPL_HELP,"OPER ADD");
		return;
	}
	user *u = finduser(src);
	if(u->oper<os_access_flag) {
		notice(os_name,src,OS_ERR_ACCESSDENIED,os_name,oline[os_access_flag]);
		return;
	}
	if(!isreg(av[2])) {
		notice(os_name,src,NS_ERR_NOTREG,av[2]);
		return;
	}
	if(findoper(av[2])) {
		notice(os_name,src,OS_OPER_ERR_EXISTS,av[2]);
		return;
	}
	new_oper(av[2]);
	notice(os_name,src,OS_OPER_ADD_RPL_SUCCESS,av[2]);
	return;
}

/********************************************************************/
/**
 * add a new oper to the oper list
 */
static void new_oper(char *nick) {
	operuser *o = scalloc(sizeof(operuser), 1);
	o->nick = sstrdup(nick);
	o->can_akill = os_can_akill;
	o->can_chatops = os_can_chatops;
	o->can_chghost = os_can_chghost;
	o->can_global = os_can_global;
	o->can_kill = os_can_kill;
	o->can_local = os_can_local;
	o->can_sgline = os_can_sgline;
	o->can_skline = os_can_skline;
	o->can_sqline = os_can_sqline;
	o->can_szline = os_can_szline;
	o->vhost = sstrdup(os_vhost);
	o->next = opers;
	if (opers)
		opers->prev = o;
	opers = o;
}

/********************************************************************/
/**
 * handle the Operserv OPER DEL command
 */
static void os_oper_del(char *src, int ac, char **av) {
	if(ac<3) {
		notice(os_name,src,OS_OPER_DEL_ERR_USAGE);
		notice(os_name,src,OS_RPL_HELP,"OPER DEL");
		return;
	}
	user *u = finduser(src);
	if(u->oper<os_access_flag) {
		notice(os_name,src,OS_ERR_ACCESSDENIED,oline[os_access_flag]);
		return;
	}
	if(!findoper(av[2])) {
		notice(os_name,src,OS_OPER_ERR_NOTFOUND,av[2]);
		return;
	}
	delete_oper(av[2]);
	notice(os_name,src,OS_OPER_DEL_RPL_SUCCESS,av[2]);
	return;
}

/********************************************************************/
/**
 * remove an oper from the oper list
 */
void delete_oper(char *nick) {
	operuser *o = findoper(nick);
	if (o->prev)
		o->prev->next = o->next;
	else
		opers = o->next;
	if (o->next)
		o->next->prev = o->prev;
	free(o);
}

/********************************************************************/
/**
 * handle the Operserv OPER LIST command
 */
static void os_oper_list(char *src, int ac, char **av) {
	if(ac<2) {
		notice(os_name,src,OS_OPER_LIST_ERR_USAGE);
		notice(os_name,src,OS_RPL_HELP,"OPER LIST");
		return;
	}
	user *u = finduser(src);
	if(u->oper<os_access_flag) {
		notice(os_name,src,OS_ERR_ACCESSDENIED,oline[os_access_flag]);
		return;
	}
	int i = 0;
	notice(os_name,src,OS_OPER_LIST_RPL_BEGIN,os_name);
	operuser *o = opers;
	while(o) {
		++i;
		notice(os_name,src,OS_OPER_LIST_RPL_ENTRY,i,o->nick);
		o = o->next;
	}
	if(i==1) {
		notice(os_name,src,OS_LIST_RPL_END1);
	} else {
		notice(os_name,src,OS_LIST_RPL_END2);
	}
}

/********************************************************************/
/**
 * handle the Operserv OPER SET command
 */
static void os_oper_set(char *src, int ac, char **av) {
	if(ac<3) {
		notice(os_name,src,OS_OPER_SET_ERR_USAGE);
		notice(os_name,src,OS_RPL_HELP,"OPER SET");
		return;
	}
	user *u = finduser(src);
	if(u->oper<os_access_flag) {
		notice(os_name,src,OS_ERR_ACCESSDENIED,oline[os_access_flag]);
		return;
	}
	operuser *o = findoper(av[2]);
	if(!o) {
		notice(os_name,src,OS_OPER_ERR_NOTFOUND,av[2]);
		return;
	}
	if(stricmp(av[3],"AKILL")==0) {
		os_oper_set_akill(src,o,av[4]);
	} else if(stricmp(av[3],"CHGHOST")==0) {
		os_oper_set_chghost(src,o,av[4]);
	}  else if(stricmp(av[3],"GLOBAL")==0) {
		os_oper_set_global(src,o,av[4]);
	} else if(stricmp(av[3],"LOCAL")==0) {
		os_oper_set_local(src,o,av[4]);
	} else if(stricmp(av[3],"KILL")==0) {
		os_oper_set_kill(src,o,av[4]);
	} else if(stricmp(av[3],"CHATOPS")==0) {
		os_oper_set_chatops(src,o,av[4]);
	} else if(stricmp(av[3],"SGLINE")==0) {
		os_oper_set_sgline(src,o,av[4]);
	} else if(stricmp(av[3],"SKLINE")==0) {
		os_oper_set_skline(src,o,av[4]);
	} else if(stricmp(av[3],"SQLINE")==0) {
		os_oper_set_sqline(src,o,av[4]);
	} else if(stricmp(av[3],"SZLINE")==0) {
		os_oper_set_szline(src,o,av[4]);
	} else if(stricmp(av[3],"VHOST")==0) {
		os_oper_set_vhost(src,o,av[4]);
	}
}

/********************************************************************/
/**
 * handle the Operserv OPER SET AKILL command
 */
static void os_oper_set_akill(char *src,operuser *o,char *option) {
	if(stricmp(option,"ON")==0) {
		o->can_akill = 1;
		notice(os_name,src,"OS_RPL_SET_SUCCESS",o->nick);
		return;
	} else if(stricmp(option,"OFF")==0) {
		o->can_akill = 0;
		notice(os_name,src,"OS_RPL_SET_SUCCESS",o->nick);
		return;
	} else {
		notice(os_name,src,OS_OPER_SET_OPT_ERR_USAGE,"AKILL");
		return;
	}
}

/********************************************************************/
/**
 * handle the Operserv OPER SET CHATOPS command
 */
static void os_oper_set_chatops(char *src,operuser *o,char *option) {
	if(stricmp(option,"ON")==0) {
		o->can_chatops = 1;
		notice(os_name,src,"OS_RPL_SET_SUCCESS",o->nick);
		return;
	} else if(stricmp(option,"OFF")==0) {
		o->can_chatops = 0;
		notice(os_name,src,"OS_RPL_SET_SUCCESS",o->nick);
		return;
	} else {
		notice(os_name,src,OS_OPER_SET_OPT_ERR_USAGE,"CHATOPS");
		return;
	}
}

/********************************************************************/
/**
 * handle the Operserv OPER SET CHGHOST command
 */
static void os_oper_set_chghost(char *src,operuser *o,char *option) {
	if(stricmp(option,"ON")==0) {
		o->can_chghost = 1;
		notice(os_name,src,"OS_RPL_SET_SUCCESS",o->nick);
		return;
	} else if(stricmp(option,"OFF")==0) {
		o->can_chghost = 0;
		notice(os_name,src,"OS_RPL_SET_SUCCESS",o->nick);
		return;
	} else {
		notice(os_name,src,OS_OPER_SET_OPT_ERR_USAGE,"CHGHOST");
		return;
	}
}

/********************************************************************/
/**
 * handle the Operserv OPER SET GLOBAL command
 */
static void os_oper_set_global(char *src,operuser *o,char *option) {
	if(stricmp(option,"ON")==0) {
		o->can_global = 1;
		notice(os_name,src,"OS_RPL_SET_SUCCESS",o->nick);
		return;
	} else if(stricmp(option,"OFF")==0) {
		o->can_global = 0;
		notice(os_name,src,"OS_RPL_SET_SUCCESS",o->nick);
		return;
	} else {
		notice(os_name,src,OS_OPER_SET_OPT_ERR_USAGE,"GLOBAL");
		return;
	}
}

/********************************************************************/
/**
 * handle the Operserv OPER SET KILL command
 */
static void os_oper_set_kill(char *src,operuser *o,char *option) {
	if(stricmp(option,"ON")==0) {
		o->can_kill = 1;
		notice(os_name,src,"OS_RPL_SET_SUCCESS",o->nick);
		return;
	} else if(stricmp(option,"OFF")==0) {
		o->can_kill = 0;
		notice(os_name,src,"OS_RPL_SET_SUCCESS",o->nick);
		return;
	} else {
		notice(os_name,src,OS_OPER_SET_OPT_ERR_USAGE,"KILL");
		return;
	}
}

/********************************************************************/
/**
 * handle the Operserv OPER SET LOCAL command
 */
static void os_oper_set_local(char *src,operuser *o,char *option) {
	if(stricmp(option,"ON")==0) {
		o->can_local = 1;
		notice(os_name,src,"OS_RPL_SET_SUCCESS",o->nick);
		return;
	} else if(stricmp(option,"OFF")==0) {
		o->can_local = 0;
		o->can_global = 0;
		notice(os_name,src,"OS_RPL_SET_SUCCESS",o->nick);
		return;
	} else {
		notice(os_name,src,OS_OPER_SET_OPT_ERR_USAGE,"LOCAL");
		return;
	}
}

/********************************************************************/
/**
 * handle the Operserv OPER SET SGLINE command
 */
static void os_oper_set_sgline(char *src,operuser *o,char *option) {
	if(stricmp(option,"ON")==0) {
		o->can_sgline = 1;
		notice(os_name,src,"OS_RPL_SET_SUCCESS",o->nick);
		return;
	} else if(stricmp(option,"OFF")==0) {
		o->can_sgline = 0;
		notice(os_name,src,"OS_RPL_SET_SUCCESS",o->nick);
		return;
	} else {
		notice(os_name,src,OS_OPER_SET_OPT_ERR_USAGE,"SGLINE");
		return;
	}
}

/********************************************************************/
/**
 * handle the Operserv OPER SET SKLINE command
 */
static void os_oper_set_skline(char *src,operuser *o,char *option) {
	if(stricmp(option,"ON")==0) {
		o->can_skline = 1;
		notice(os_name,src,"OS_RPL_SET_SUCCESS",o->nick);
		return;
	} else if(stricmp(option,"OFF")==0) {
		o->can_skline = 0;
		o->can_sgline = 0;
		notice(os_name,src,"OS_RPL_SET_SUCCESS",o->nick);
		return;
	} else {
		notice(os_name,src,OS_OPER_SET_OPT_ERR_USAGE,"SKLINE");
		return;
	}
}

/********************************************************************/
/**
 * handle the Operserv OPER SET SQLINE command
 */
static void os_oper_set_sqline(char *src,operuser *o,char *option) {
	if(stricmp(option,"ON")==0) {
		o->can_sqline = 1;
		notice(os_name,src,"OS_RPL_SET_SUCCESS",o->nick);
		return;
	} else if(stricmp(option,"OFF")==0) {
		o->can_sqline = 0;
		notice(os_name,src,"OS_RPL_SET_SUCCESS",o->nick);
		return;
	} else {
		notice(os_name,src,OS_OPER_SET_OPT_ERR_USAGE,"SQLINE");
		return;
	}
}

/********************************************************************/
/**
 * handle the Operserv OPER SET SZLINE command
 */
static void os_oper_set_szline(char *src,operuser *o,char *option) {
	if(stricmp(option,"ON")==0) {
		o->can_szline = 1;
		notice(os_name,src,"OS_RPL_SET_SUCCESS",o->nick);
		return;
	} else if(stricmp(option,"OFF")==0) {
		o->can_szline = 0;
		notice(os_name,src,"OS_RPL_SET_SUCCESS",o->nick);
		return;
	} else {
		notice(os_name,src,OS_OPER_SET_OPT_ERR_USAGE,"SZLINE");
		return;
	}
}

/********************************************************************/
/**
 * handle the Operserv OPER SET VHOST command
 */
static void os_oper_set_vhost(char *src,operuser *o,char *option) {
	o->vhost = sstrdup(option);
	notice(os_name,src,"OS_RPL_SET_SUCCESS",o->nick);
	return;
}
