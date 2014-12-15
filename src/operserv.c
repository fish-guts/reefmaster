/*
 *      operserv.c - severin
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

static char *aoper[] = {
	OS_RPL_ISNOWHELPOP,				
	OS_RPL_ISNOWIRCOP,
	OS_RPL_ISNOWCOADMIN,
	OS_RPL_ISNOWADMIN,
	OS_RPL_ISNOWSA,
	OS_RPL_ISNOWNETADMIN
};

extern int os_connect(int sock)
{
	char *nick = (char*) malloc(sizeof(char)*256);
	sprintf(nick,SNICK,os_name,s_user,s__host,s_name,os_realname);
	send(sock,nick,(int)strlen(nick),0);
	return 0;
}

void announce_oper(char *oper,int lvl)
{
	chatops(os_name,aoper[lvl-1],oper);
}
