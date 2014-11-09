#ifndef SOCK_H_
#define SOCK_H_


int sock_init(void);
int sock_connect(void);
int start_winsock(void);
void parse(void);
void load_modules(int sock);

#endif /*SOCK_H_*/
