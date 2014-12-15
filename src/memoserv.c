/*
 *      memoserv.c - severin
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

extern int ms_connect(int sock)
{
	
	char *NICK = (char*) malloc(sizeof(char)*256);
	char *server = s_name;			 		// server to connect to
	char *nickname = ms_name;	 			// nickname of Nickserv 
	char *user = s_user;			 		// user of services server
	char *host = s__host;			 		// host of services server
	char *realname = ms_realname;			 // realname of Nickserv
	sprintf(NICK,SNICK,nickname,user,host,server,realname);
	send(sock,NICK,(int)strlen(NICK),0);
	return 0;
}
