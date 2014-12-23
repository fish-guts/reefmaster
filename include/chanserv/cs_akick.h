/*
 * cs_akick.h
 *
 *  Created on: Oct 23, 2014
 *      Author: severin
 */

#ifndef CS_AKICK_H_
#define CS_AKICK_H_


void cs_akick(char *src,int ac,char **av);
void cs_akick_addmask(char *src, int ac,char **av);
void cs_akick_delmask(char *src, int ac, char **av);
void cs_akick_listentries(char *src, int ac,char **av);
akick *cs_akick_match(user *u,ChanInfo *c);
void cs_akick_wipeall(char *src, int ac,char **av);


#endif /* CS_AKICK_H_ */
