#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#undef stricmp
#define _stricmp stricmp

timer *add_timeout(int delay, void (*code)(timer *), int repeat);
int check_nick(user *u,char *pass);
void check_bots(void);
void check_services(void);
void check_timeouts(void);
void check_save(void);

void del_timeout(timer *t);
unsigned long get_duration(char *dur);
int hasaccess(user *u,char *nick);
int ifmatch_0(const char *pattern, const char *str);
int ifmatch_1(const char *pattern, const char *str);
char *internal_strrep(const char *str, const char *find, const char *rep, size_t newsize, size_t index);
int isbool(int value);
int ismatch(user *u,char *mask);
int isnum(char *value);
int isoper(user *u);
int isreg(const char *src);
int isregbot(const char *src);
int isregcs(const char *chan);
int isservice(char *src);
char *mask(char *src,char *host);
int match(char *str, char *pattern);
char* remove_dup(char * input);
int remove_from_array(char **array, char *str);
void set_service_status(char *service,int status);
void set_timer(time_t secs);
char *strscpy(char *d, const char *s, size_t len);
void *scalloc(long elsize, long els);
void *smalloc(long size);
void *srealloc(void *oldptr, long newsize);
char *sstrdup(const char *s);
int _stricmp(const char *str1,const char *str2);
char *strrep(const char* str,const char *find, const char *x);
char *str_replace (const char *string, const char *substr, const char *replacement);
char *strlower(char *str);
int search_dup(char *str, char item);
void timer_event_handler(int sigid);

#endif /*FUNCTIONS_H_*/
