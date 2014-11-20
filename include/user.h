#ifndef USER_H_
#define USER_H_

void s_nick(const char *source, int ac, char **av);
user *finduser(const char *nick);
user *finduserbynick(char *src);

#endif /*USER_H_*/
