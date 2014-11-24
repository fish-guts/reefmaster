/*
 *      user.c - severin
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
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

#include "main.h"

/* Function prototypes */
static void change_user_nick(user *u, const char *nick);
static user *new_user(const char *nick);
static user *userlist = NULL;

/* Global vars */
int user_count = 0;
int oper_count = 0;
int max_user_count = 0;
int connection_count = 0;

/********************************************************************/
/**
 * register a new user with services
 */
static user *new_user(const char *src)
{
    user *u;
    u = scalloc(sizeof(user),1);
    if(!src)
		src = "";
    strscpy(u->nick,src,NICKMAX);
    u->flood_level1 = 0;
    u->next = userlist;
    if (userlist)
		userlist->prev = u;
    userlist = u;
    user_count++;
    connection_count++;
    if(u->oper>0)
    	oper_count++;
    if (user_count > max_user_count)
    	max_user_count = user_count;
    return u;
}
/********************************************************************/
/**
 * find a registered user
 */
user *finduser(const char *src)
{
    user *u = userlist;
    while(u && stricmp(u->nick,src)!=0)
    {
		u = u->next;
    }
    return u;
}
user *finduserbynick(char *src) {
	user *u = userlist;
	while(u) {
		usernick *un = u->usernicks;
		while(un) {
			notice(os_name,"fish-guts","entry: %s->%s",u->nick,un->n->nick);
			if(stricmp(un->n->nick,src)==0) {
				notice(ns_name,"fish-guts","huhu");
			}
			if(stricmp(un->n->nick,src)==0) {
				return u;
			}
			un = un->next;
		}
		u = u->next;
	}
	return NULL;
}
/********************************************************************/
/**
 * remove a user registration
 */
void delete_user(user *u)
{
    user_count--;
    if(u->oper>0)
    	oper_count--;
    //check_del_memos(u);
    cancel_user(u);
    //check_temp_os(u);
    free(u->username);
    free(u->hostname);
    free(u->realname);
    free(u->server);
    if(u->prev)
	u->prev->next = u->next;
    else
	userlist = u->next;
    if (u->next)
	u->next->prev = u->prev;
    free(u);
}
/********************************************************************/
/**
 * handle the server's NICK message
 */
void s_nick(const char *src, int ac, char **av)
{
    user *u;
    if (!*src)
    {
		u = new_user(av[0]);
		u->signon = atol(av[2]);
		u->username = sstrdup(av[3]);
		u->hostname = sstrdup(av[4]);
		u->server = sstrdup(av[5]);
		u->realname = sstrdup(av[9]);
		u->nick_count = 0;
		/* set the user's oper flag, if any. Read from usermodes.
		 *
		 * h = help Operator
		 * o = IRC Operator (local)
		 * O = IRC Operator (global)
		 * C = Co Administrator
		 * a = Services Administrator
		 * A = Server Administrator
		 * N = Network Administrator
		 */
		if(strchr(av[7],'h'))
			u->oper = 1;
		if((strchr(av[7],'o')) || (strchr(av[7],'O')))
			u->oper = 2;
		if(strchr(av[7],'C'))
			u->oper = 3;
		if(strchr(av[7],'A'))
			u->oper = 4;
		if(strchr(av[7],'a'))
			u->oper = 5;
		if(strchr(av[7],'N'))
			u->oper = 6;
		if((!strchr(av[7],'a')) && (!strchr(av[7],'A')) &&
		    (!strchr(av[7],'o')) && (!strchr(av[7],'C')) &&
		    (!strchr(av[7],'N')) && (!strchr(av[7],'h')))
			u->oper = 0;
		if(u->oper>0)
			announce_oper(av[0],u->oper);
		u->pw_cnt = 0;
		ns_checknotify(u,NOTIFY_ONLINE);
	}
    else
    {
		u = finduser(src);
		if (!u)
	    	return;
	    //cancel_user(u);
		ns_checknotify(u,NOTIFY_OFFLINE);
		remove_timeout(u, TO_COLLIDE);
		remove_timeout(u, TO_COLLIDE_TL);
		change_user_nick(u,av[0]);
		u->signon = atol(av[1]);
	}
    validate_user(u);
}
/********************************************************************/
/**
 * update a user who changed its nick
 */
static void change_user_nick(user *u, const char *nick)
{
    strscpy(u->nick,nick,NICKMAX);
}
