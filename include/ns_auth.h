/*
 * ns_auth.h
 *
 *  Created on: Oct 22, 2014
 *      Author: severin
 */

#ifndef NS_AUTH_H_
#define NS_AUTH_H_


void accept_auth(char *src, auth *a,int i);
void accept_auth_chan(char *src,auth *a);
void accept_auth_notify(char *src,auth *a);
int has_open_auth(NickInfo *n);
void ns_auth(char *src,int ac,char **av);
void ns_auth_accept(char *src,int ac,char **av);
void ns_auth_decline(char *src,int ac,char **av);
void ns_auth_list(char *src,int ac,char **av);
void ns_auth_read(char *src,int ac,char **av);
void remove_auth(char *src, auth *a);

#endif /* NS_AUTH_H_ */
