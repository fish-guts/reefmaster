/*
 * ns_notify.h
 *
 *  Created on: Oct 22, 2014
 *      Author: severin
 */

#ifndef NS_NOTIFY_H_
#define NS_NOTIFY_H_

void add_notify(char *src,char *nick);
void add_notify_auth_entry(char *src,char *nick);
notify *find_notify(char *src, char *dest);
void ns_notify(char *src,int ac,char **av);
void ns_notify_add(char *src,int ac,char **av);
void ns_notify_del(char *src,int ac,char **av);
void ns_notify_list(char *src,int ac,char **av);
void ns_notify_wipe(char *src,int ac,char **av);


#endif /* NS_NOTIFY_H_ */
