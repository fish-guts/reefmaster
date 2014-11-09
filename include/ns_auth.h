/*
 * ns_auth.h
 *
 *  Created on: Oct 22, 2014
 *      Author: severin
 */

#ifndef NS_AUTH_H_
#define NS_AUTH_H_

void ns_auth(char *src,int ac,char **av);
void ns_auth_accept(char *src,int ac,char **av);
void ns_auth_decline(char *src,int ac,char **av);
void ns_auth_list(char *src,int ac,char **av);
void ns_auth_read(char *src,int ac,char **av);

#endif /* NS_AUTH_H_ */
