/*
 * ns_set.h
 *
 *  Created on: Oct 22, 2014
 *      Author: severin
 */

#ifndef NS_SET_H_
#define NS_SET_H_

void ns_set(char *src,int ac,char **av);
void ns_set_authorize(char *src,int ac,char **av);
void ns_set_email(char *src,int ac,char **av);
void ns_set_hideemail(char *src,int ac,char **av);
void ns_set_mforward(char *src,int ac,char **av);
void ns_set_mnotify(char *src,int ac,char **av);
void ns_set_nomemo(char *src,int ac,char **av);
void ns_set_noop(char *src,int ac,char **av);
void ns_set_password(char *src,int ac,char **av);
void ns_set_protect(char *src,int ac, char **av);
void ns_set_url(char *src,int ac, char **av);

#endif /* NS_SET_H_ */
