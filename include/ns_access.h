/*
 * ns_access.h
 *
 *  Created on: Oct 22, 2014
 *      Author: severin
 */

#ifndef NS_ACCESS_H_
#define NS_ACCESS_H_

void ns_access(char *src,int ac,char **av);
void ns_access_add(char *src,char *nick,char *mask);
void ns_access_del(char *src,char *nick,char *mask);
void ns_access_list(char *src,char *nick);
void ns_access_wipe(char *src,char *nick);

#endif /* NS_ACCESS_H_ */
