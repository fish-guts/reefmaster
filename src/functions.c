/*
 *      functions.c - severin
 *      
 *      Copyright (c) 2014 Severin Mueller <severin.mueller@reefmaster.org>
 *      
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *      
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *      
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

#include "main.h"

volatile int sig_flag = 0;
static timer *timeouts = NULL;
int save_interval = 60;
static int ifmatch(const char *pattern, const char *str, int mode);
static void check_expiry(void);
static void check_ns_expiry(void);

unsigned long get_duration(char *dur) {

	if(isnum(dur)) {
		return atol(dur);
	}
	if(match(dur,TIME_FORMAT_H)) {
		return (atol(dur) * MINUTES_PER_HOUR);
	} else if(match(dur,TIME_FORMAT_D)) {
		return (atol(dur) * MINUTES_PER_DAY);
	} else if(match(dur,TIME_FORMAT_W)) {
		return (atol(dur) * MINUTES_PER_WEEK);
	} else if(match(dur,TIME_FORMAT_M)) {
		return (atol(dur) * MINUTES_PER_MONTH);
	} else if(match(dur,TIME_FORMAT_Y)) {
		return (atol(dur) * MINUTES_PER_YEAR);
	}
	return 0;
}

int _stricmp(const char *str1, const char *str2) {
	register signed char __res;
	while (1) {
		if ((__res = toupper(*str1) - toupper(*str2++)) != 0 || !*str1++)
			break;
	}
	return __res;
}
const char *_stristr(const char *str1, const char *str2) {
	if (!*str2)
		return str1;
	for (; *str1; ++str1) {
		if (toupper(*str1) == toupper(*str2)) {
			const char *h, *n;
			for (h = str1, n = str2; *h && *n; ++h, ++n) {
				if (toupper(*h) != toupper(*n))
					break;
			}
			if (!*n)
				return str1;
		}
	}
	return 0;
}

timer *add_timeout(int delay, void (*code)(timer *), int repeat) {
	timer *t = smalloc(sizeof(timer));
	t->settime = time(NULL);
	t->timeout = t->settime + delay;
	t->code = code;
	t->repeat = repeat;
	t->next = timeouts;
	t->prev = NULL;
	if (timeouts)
		timeouts->prev = t;
	timeouts = t;
	return t;
}
void check_akills(void) {
	akill *a = akills;
	while(a) {
		user *u = userlist;
		while(u) {
			char mask[256];
			char final_reason[1024];
			sprintf(mask,"%s@%s",u->username,u->hostname);
			if(ifmatch(a->mask,mask,0)) {
				if(a->expires==0) {
					sprintf(final_reason,"You are banned from this Network. %s",a->reason);
					do_akill(s_name,u->nick,final_reason);
				} else {
					sprintf(final_reason,"You are temporarily banned from this Network. %s",a->reason);
					do_akill(s_name,u->nick,final_reason);
				}
			}
			u = u->next;
		}
		a = a->next;
	}
}
void check_bots() {
	bot *b = botlist;
	while(b) {
		botchan *bc = b->chanlist;
		while(bc) {
			if(!is_bot_on_chan(b->name,bc->chan)) {
				do_join(b->name,bc->chan);
				do_owner(b->name,b->name,bc->chan);
				add_bot(bc->chan,b->name);
			}
			bc = bc->next;
		}
		b = b->next;
	}
}
void check_services(void) {
	if(!ns_status) {
		ns_connect(mainsock);
		ns_status = 1;
	} else if(!cs_status) {
		cs_connect(mainsock);
		cs_status = 1;
	} else if(!bs_status) {
		bs_connect(mainsock);
		bs_status = 1;
	} else if(!os_status) {
		os_connect(mainsock);
		os_status = 1;
	} else if(!as_status) {
		as_connect(mainsock);
		as_status = 1;
	}
}
void check_connections(void) {
	check_services();
	check_bots();
}
static void check_expiry(void) {
	check_ns_expiry();
}

static void check_ns_expiry(void) {
	long expiration = time(NULL) - (ns_expiry * 86400);
	NickInfo *n = nicklist;
	while(n) {
		if(n->last_seen < expiration) {
			delete_nick(n);
			addlog(1, NS_LOG_NICK_DROPPED, n->nick);
		}
		n = n->next;
	}
}
void check_save(void) {
	time_t now = time(NULL);
	if(now >= next_save) {
		save_database();
		next_save = now + (save_interval);
	}
}
void check_timeouts(void) {
	timer *t1, *t2;
	time_t t = time(NULL);
	t1 = timeouts;
	while (t1) {
		if (t < t1->timeout) {
			t1 = t1->next;
			continue;
		}
		t1->code(t1);
		if (t1->repeat) {
			t1 = t1->next;
			continue;
		}
		t2 = t1->next;
		if (t1->next)
			t1->next->prev = t1->prev;
		if (t1->prev)
			t1->prev->next = t1->next;
		else
			timeouts = t1->next;
		free(t1);
		t1 = t2;
	}
}
void del_timeout(timer *t) {
	timer *ptr;
	for (ptr = timeouts; ptr; ptr = ptr->next) {
		if (ptr == t)
			break;
	}
	if (!ptr)
		return;
	if (t->prev)
		t->prev->next = t->next;
	else
		timeouts = t->next;
	if (t->next)
		t->next->prev = t->prev;
	free(t);
}

int hasaccess(user *u, char *nick) {
	char *mask = (char*) malloc(sizeof(char*) * 256);
	sprintf(mask, "%s@%s", u->username, u->hostname);
	if (isidentified(u, nick)) {
		return 2;
	} else if (ismatch(u, mask) == 1) {
		return 1;
	} else if (u->oper >= ns_admin)
		return 3;
	else
		return -1;
}

static int ifmatch(const char *pattern, const char *str, int mode) {
	char c;
	const char *ptr;
	for (;;) {
		switch (c = *pattern++) {
		case 0:
			if (!*str)
				return 1;
			return 0;
		case '?':
			if (!*str)
				return 0;
			str++;
			break;
		case '*':
			if (!*pattern)
				return 1; /* trailing '*' matches everything else */
			ptr = str;
			while (*ptr) {
				if ((mode ?
						(*ptr == *pattern) :
						(tolower(*ptr) == tolower(*pattern)))
						&& ifmatch(pattern, ptr, mode))
					return 1;
				ptr++;
			}
			break;
		default:
			if (mode ? (*str++ != c) : (tolower(*str++) != tolower(c)))
				return 0;
			break;
		} /* switch */
	} /* for */
	return -1;
}
int ifmatch_1(const char *pattern, const char *str) {
	return ifmatch(pattern, str, 1);
}

int ifmatch_0(const char *pattern, const char *str) {
	return ifmatch(pattern, str, 0);
}
char *internal_strrep(const char *str, const char *find, const char *rep,
		size_t newsize, size_t index) {
	size_t replen = strlen(rep), findlen = strlen(find);
	char *nextpos, *newstring;

	if (findlen && (nextpos = strstr(str, find))) {
		size_t delta = nextpos - str;
		newsize += replen - findlen;
		newstring = internal_strrep(nextpos + findlen, find, rep, newsize,
				index + delta + replen);
		if (!newstring)
			return NULL;
		memcpy(newstring + index + delta, rep, replen);
		memcpy(newstring + index, str, delta);
	} else {
		size_t len = strlen(str), newindex;
		newstring = malloc(newsize + 1);
		if (!newstring)
			return NULL;
		newindex = newsize - len;
		strcpy(newstring + newindex, str);
	}
	return newstring;
}

int isbool(int value) {
	if ((value < 0) || (value > 1))
		return 0;
	else
		return 1;
}
int ismatch(user *u, char *mask) {
	if (!isreg(u->nick))
		return 0;
	if (isidentified(u, u->nick)) {
		return 2;
	}
	NickInfo *n = findnick(u->nick);
	myacc *a = n->accesslist;
	while (a) {
		if (ifmatch(a->mask, mask, 0)) {
			return 1;
		}
		a = a->next;
	}
	return 0;
}
int isnum(char *value) {
	char *ptr;
	for (ptr = value; *ptr; ptr++) {
		if (!isdigit(*ptr))
			return 0;
	}
	return 1;
}
int isoper(user *u) {
	if (u->oper > 0)
		return 1;
	else
		return 0;
}
/* returns the registration level for a nickname (0 = not registered, 1 or above = registered) */
int isreg(const char *src) {
	NickInfo *n;
	n = findnick(src);
	if (n) {
		return n->protect;
	}
	return 0;
}
int isregbot(const char *src) {
	bot *b;
	b = findbot(src);
	if (b) {
		return 1;
	} else {
		return 0;
	}
}
int isregcs(const char *chan) {
	ChanInfo *c = findchan(chan);
	if (c) {
		return 1;
	}
	return 0;
}
int isservice(char *src) {
	if((stricmp(src,ns_name)==0) ||
	   (stricmp(src,cs_name)==0) ||
	   (stricmp(src,bs_name)==0) ||
	   (stricmp(src,os_name)==0) ||
	   (stricmp(src,as_name)==0)) {
		return 1;
	}
	return 0;
}
char *mask(char *src, char *host) {
	user *u1 = finduser(src);
	if (isoper(u1))
		return host;
	int ncnt = 0;
	int acnt = 0;
	int pcnt = 0;
	char *ptr;
	char *tmphost = (char*) malloc(sizeof(char*) * 256);
	char *pch;
	if (!strchr(host, '.')) {
		strcpy(tmphost, "*");
	} else {
		for (ptr = host; *ptr; ptr++) {
			if (isdigit(*ptr))
				ncnt++;
			if (isalpha(*ptr))
				acnt++;
			if (*ptr == '.')
				pcnt++;
		}
		if ((pcnt >= 1) && (acnt > 0)) {
			char phost[64];
			strcpy(phost, host);
			int d = 0;
			for (ptr = phost; *ptr != '.'; ptr++)
				d++;
			memset(phost, '*', d);
			memcpy(phost + 1, phost + d, strlen(phost));
			tmphost = phost;
		} else if ((acnt == 0) && (ncnt >= 4)) {
			char tmp[64];
			strcpy(tmp, host);
			pch = strtok(host, ".");
			tmphost = strrep(tmp, pch, "*");
		} else {
			pch = strtok(host, "@");
			tmphost = strrep(strtok(pch, "."), pch, "*");
		}
	}
	return tmphost;
}
void set_service_status(char *service,int status) {
	if(stricmp(ns_name,service)==0) {
		ns_status = status;
	} else if(stricmp(cs_name,service)==0) {
		cs_status = status;
	} if(stricmp(os_name,service)==0) {
		os_status = status;
	} if(stricmp(bs_name,service)==0) {
		bs_status = status;
	} if(stricmp(as_name,service)==0) {
		as_status = status;
	}
}
void *scalloc(long size, long l) {
	void *buf;
	if ((!size) || (!l)) {
		size = l = 1;
	}
	buf = calloc(size, l);
	if (!buf)
		raise(SIGUSR1);
	return buf;
}
void *smalloc(long size) {
	void *buf;
	if (!size)
		size = 1;
	buf = malloc(size);
	if (!buf)
		raise(SIGUSR1);
	return buf;
}
void *srealloc(void *oldptr, long newsize) {
	void *buf;
	if (!newsize) {
		//log("srealloc: Illegal attempt to allocate 0 bytes");
		newsize = 1;
	}
	buf = realloc(oldptr, newsize);
	if (!buf)
		raise(SIGUSR1);
	return buf;
}
char *sstrdup(const char *s) {
	char *t = strdup(s);
	if (!t)
		raise(SIGUSR1);
	return t;
}
char *strrep(const char* str, const char *find, const char *x) {
	const char *c = strstr(str, find);
	char *r;
	if (c != NULL) {
		r = malloc(strlen(str) + strlen(x) - strlen(find) + 1);
		strncpy(r, str, c - str);
		r[c - str] = '\0';
		strcat(r, x);
		strcat(r, c + strlen(find));
	} else {
		r = malloc(strlen(str) + 1);
		strcpy(r, str);
	}
	return r;
}
char *strscpy(char *d, const char *s, size_t len) {
	char *d_orig = d;
	if (!len)
		return d;
	while (--len && (*d++ = *s++))
		;
	*d = 0;
	return d_orig;
}

char *str_replace (const char *string, const char *substr, const char *replacement) {
	char *tok = NULL;
	char *newstr = NULL;
	char *oldstr = NULL;
	/* if either substr or replacement is NULL, duplicate string a let caller handle it */
	if ( substr == NULL || replacement == NULL ) {
		return strdup (string);
	}
	newstr = strdup (string);
	while ((tok = strstr (newstr, substr))) {
		oldstr = newstr;
		newstr = malloc (strlen(oldstr) - strlen (substr) + strlen (replacement) + 1);
		/*failed to alloc mem, free old string and return NULL */
		if ( newstr == NULL ) {
			free (oldstr);
			return NULL;
		}
		memcpy ( newstr, oldstr, tok - oldstr );
		memcpy ( newstr + (tok - oldstr), replacement, strlen ( replacement ) );
		memcpy ( newstr + (tok - oldstr) + strlen( replacement ), tok + strlen ( substr ), strlen ( oldstr ) - strlen ( substr ) - ( tok - oldstr ) );
		memset ( newstr + strlen ( oldstr ) - strlen ( substr ) + strlen ( replacement ) , 0, 1 );
		free (oldstr);
	}
	return newstr;
}

void set_timer(time_t period_in_secs) {

	struct itimerval timer_val;
	bzero(&timer_val, sizeof(timer_val));
	timer_val.it_value.tv_sec = period_in_secs;
	timer_val.it_interval.tv_sec = period_in_secs;
	if (setitimer(ITIMER_REAL, &timer_val, NULL) != 0)
		perror("Error in setitimer()");

}
void timer_event_handler(int sigid) {
	if (sigid == SIGALRM) {
		check_timeouts();
		check_connections();
		check_expiry();
		check_akills();
		check_save();
	}
}

int match(char *str, char *pattern) {
	int status;
    regex_t re;
    if (regcomp(&re, pattern, REG_ICASE | REG_EXTENDED | REG_NOSUB) != 0) {
        /* Report error. */
    	return 1;
    }
    status = regexec(&re, str, (size_t) 0, NULL, 0);
    regfree(&re);
    if (status != 0) {
        /* Report error. */
    	return 0;
    }
    return 1;
}


char *strlower(char *str) {
	int i = 0;
	for(i = 0; str[i]; i++){
	  str[i] = tolower(str[i]);
	}
	return str;
}
char *remove_dup(char *input)
{
	static int chars[127];
    char *ptr;
    char *str = (char*)malloc(sizeof(char*)*256);
    for(ptr = input;*ptr;ptr++) {
    	int i = 0;
    	for(i = 0; i< sizeof(chars);i++) {
    		if(i==*ptr) {
    			if(chars[i]==0) {
    				chars[i] = 1;
    				char *s = (char*)malloc(2);
    				sprintf(s,"%c",*ptr);
    				strcat(str,s);
    				continue;
    			} else {
    				continue;
    			}
    		}
    	}
    }
    return str;
}
