/*
 * cs_unban.h
 *
 *      Author: severin
 */

#ifndef CS_UNBAN_H_
#define CS_UNBAN_H_

void cs_unban(char *src, int ac, char **av);
chanban *match_ban(char *mask,channel *c);

#endif /* CS_UNBAN_H_ */
