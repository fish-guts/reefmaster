/*
 *      main.c - severin
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

char ircbuf[IRCBUF_SIZE];
int TCHECK = 2;
int quitting = 0;
int check_ping = 0;

static void daemonize(void);


/****************************************************************************************/
/**
 * daemonize the process
 */
static void daemonize(void)
{
	mainsock = -1;

	pid_t pid, sid;
	if (getppid()==1) {
    	return;

	}
    pid = fork();

    if(pid<0) {
    	exit(EXIT_FAILURE);
    }

    if(pid>0) {
        exit(EXIT_SUCCESS);
    }

    umask(0);
    sid = setsid();

    if(sid<0) {
        exit(EXIT_FAILURE);
    }

    /* load the application */
    int rc;
	if((rc = load_app()) != LOAD_OK)
	{
		print_msg(APP_ERR_LOADINGFAILED,rc);
		exit(EXIT_FAILURE);
	} else {

		if((chdir("/"))<0) {
			exit(EXIT_FAILURE);
		}

		if(!freopen("/dev/null", "r", stdin)) {
			exit(EXIT_FAILURE);
		}

		if(!freopen("/dev/null", "w", stdout)) {
			exit(EXIT_FAILURE);
		}

		if(!freopen("/dev/null", "w", stderr)) {
			exit(EXIT_FAILURE);
		}
	}
}

/****************************************************************************************/
/**
 * load the program
 */
int load_app(void) {
	int rc;
	print_welcome_msg();
	/* loads the configuration */
	if((rc=config_load(CONFIG_FILE))==0) {
		start_app();
	}
	return rc;
}

/****************************************************************************************/
/**
 * the application's main method
 */
int main(int argc,char **argv)
{
	if(!argv[1]) {
		printf(APP_DBG_UNKNOWN_CMD);
		exit(EXIT_FAILURE);
	}
	else if(strcmp(argv[1],"start")==0)	{
		daemonize();
	}
	else if(strcmp(argv[1],"stop")==0)
		exit(EXIT_SUCCESS);
	else
	{
		printf(APP_DBG_UNKNOWN_CMD);
		exit(EXIT_FAILURE);
	}
	return -1;
}

/****************************************************************************************/
/**
 * start the app and print some error on failure
 */
void start_app(void) {
	char buf[100000];
	if(signal(SIGALRM, timer_event_handler)==SIG_ERR)
	{
		printf("Error message: %s\n", strerror(errno));
		addlog(2,"Error in signal()\n");
		return;
	}
	set_timer(2);
	load_database();
	next_save = time(NULL) + 1200;
	addlog(1,"Services successfully started");
	// start the socket
	mainsock = sock_connect();

	if(mainsock<0) {
		printf("Error message: %s\n", strerror(errno));
	}

	load_modules(mainsock);
	connect_bots();
	/* this is the main loop */
	while(!quitting) {
		int s = recv(mainsock,buf, sizeof(ircbuf),0);

		if(s) {
			buf[s] = 0;
			/* use CRLF as separator */
			char *pch = strtok(buf,"\r\n");
			while(pch!=NULL) {
				strcpy(ircbuf,pch);
				process();
				ircbuf[s]=0;
				pch = strtok(NULL,"\r\n");
				addlog(1,ircbuf);
			}
		}
	}
}

/****************************************************************************************/
/**
 * print a formatted message
 */
void print_msg(char *msg, ...)
{
	va_list	va;
	char buf[1024];
	va_start(va,msg);
	vsprintf(buf,msg,va);
	va_end(va);
	printf("*** %s",buf);
}

/****************************************************************************************/
/**
 * the application's startup message
 */
void print_welcome_msg(void)
{
	printf("###################################################################\n");
	printf("#   _____           _____                       __                #\n");
	printf("#  /  __ \\         /  __/		       |  |               #\n");
	printf("#  | |_/ /___  ___ | |_  __ ___ __   __ _ _____|  |_  ___  _ ___  #\n");
	printf("#  |    // _ \\/ _ \\|  _|/ /'\\ /'\\ \\ / _` |\\  _\\|   _|/ _ \\| '__/  #\n");
	printf("#  | |\\ \\| __/  __/| |  | | | | | |/ (_| |_\\ \\ |  |  | __/| |     #\n");
	printf("#  |_| \\_\\___|\\___||_|  |_| |_| | | \\__,_|____\\|__|  \\___|| |     #\n");
	printf("#                       IRC Services v 1.0                        #\n");
	printf("###################################################################\n");
}

 /* EOF */
