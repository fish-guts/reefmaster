#ifndef USER_H_
#define USER_H_

void s_nick(const char *source, int ac, char **av);
void user_add_bot(user *u,bot *b);
user *finduser(const char *nick);
user *finduserbynick(char *src);

#endif /*USER_H_*/
