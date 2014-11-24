/*
 *      nickserv.h - severin - 02/28/08
 *      
 *      Copyright 2008 Severin Mueller <severin.mueller@reefmaster.org>
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
 
#ifndef NICKSERV_H_
#define NICKSERV_H_

#include "ns_access.h"
#include "ns_acc.h"
#include "ns_auth.h"
#include "ns_drop.h"
#include "ns_getpass.h"
#include "ns_ghost.h"
#include "ns_help.h"
#include "ns_identify.h"
#include "ns_info.h"
#include "ns_list.h"
#include "ns_listchans.h"
#include "ns_notify.h"
#include "ns_register.h"
#include "ns_release.h"
#include "ns_set.h"
#include "ns_setpass.h"

extern NickInfo *nicklist;

void add_identified(user *u,char *nick);
void cancel_user(user *u);
void delete_nick(NickInfo *n);
int findauth_chan(char *src, char *nick,char *chan,int level);
auth *findauth_notify(char *src, char *nick);
NickInfo *findnick(const char *nick);
NickInfo *find_nick_by_id(int id);
int isidentified(user *u,char *nick);
void nickserv(char *src,char *av);
int ns_checkmask(char *src,char *mask);
void ns_checknotify(user *u, int mode);
extern int ns_connect(int sock);
int ns_checkpass(char *src,char *pass);
void ns_enforce(char *src);
void ns_fnick(char *src);
void ns_ghost(char *src,int ac,char **av);
void ns_invalid(char *src,int ac,char **av);
int ns_notifylist(char *src,char *dest);
void ns_passlimit(user *u);
void remove_timeout(user *u, int type);
void save_nickserv_db(void);
void validate_user(user *u);
NickInfo *register_nick(const char *src, const char *password,char *email);
#endif /*NICKSERV_H_*/
