#ifndef COMMANDS_H_
#define COMMANDS_H_

#include "struct.h"

/* these are the IRC commands handled by the server */

extern irc_cmd irc_cmds[];

irc_cmd *find_cmd(const char *name);
int tokenize(char *buf, char ***argv);
void c_join(char *src, int ac, char **av);
void c_kick(char *src, int ac, char **av);
void c_kill(char *src, int ac, char **av);
void c_mode(char *src, int ac, char **av);
void c_part(char *src, int ac, char **av);
void c_ping(char *src, int ac, char **av);
void c_privmsg(char *src, int ac, char **av);
void c_quit(char *src, int ac, char **av);
void c_topic(char *src, int ac, char **av);

#endif /*COMMANDS_H_*/
