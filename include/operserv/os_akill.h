#ifndef OS_AKILL_H
#define OS_AKILL_H


void os_akill(char *src, int ac, char **av);
void delete_akill(char *mask);
akill *findakill(const char *mask);

#endif /*OS_AKILL_H*/
