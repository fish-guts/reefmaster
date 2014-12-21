/*
 * cs_set.h
 *
 *  Created on: Oct 23, 2014
 *      Author: severin
 */

#ifndef CS_SET_H_
#define CS_SET_H_


void cs_set(char *src,int ac,char **av);
void cs_set_bot(char *src,int ac,char **av);
void cs_set_desc(char *src,int ac,char **av);
void cs_set_founder(char *src,int ac,char **av);
void cs_set_keeptopic(char *src,int ac,char **av);
void cs_set_leaveops(char *src,int ac,char **av);
void cs_set_memolevel(char *src,int ac,char **av);
void cs_set_mlock(char *src,int ac,char **av);
void cs_set_opwatch(char *src,int ac,char **av);
void cs_set_password(char *src,int ac,char **av);
void cs_set_restricted(char *src,int ac,char **av);
void cs_set_successor(char *src,int ac,char **av);
void cs_set_topiclock(char *src,int ac,char **av);

#endif /* CS_SET_H_ */
