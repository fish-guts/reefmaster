/*
 * cs_xop.h
 *
 *  Created on: Oct 23, 2014
 *      Author: severin
 */

#ifndef CS_XOP_H_
#define CS_XOP_H_

void add_auth_entry(char *nick,char *chan,int list,char *src,int listacc);
void add_to_list(char *nick, char *chan, int level, char *addnick, int addlevel);
void cs_aop(char *src,int ac,char **av);
void cs_hop(char *src,int ac,char **av);
void cs_sop(char *src,int ac,char **av);
void cs_vop(char *src,int ac,char **av);
void cs_uop(char *src,int ac,char **av);
void cs_xop_add(char *src,char *chan,int list,char *nick);
void cs_xop_del(char *src,char *chan,int list,char *nick);
int cs_xop_get_level(user *u,ChanInfo *c);
void cs_xop_list(char *src,char *chan,int list);
void cs_xop_wipe(char *src,char *chan,int list);
auth *find_auth_entry(char *nick,char *chan);
op *find_list_entry(char *nick,char *chan,int level);
int get_access_for_nick(ChanInfo *c, NickInfo *n);
void move_in_list(char *nick, char *chan, int level, int existing_level, char *addnick, int addlevel);
void remove_from_list(op *o);

#endif /* CS_XOP_H_ */
