/*
 *      sock.c - severin
 *      
 *      Copyright 2014 Severin Mueller <severin.mueller@reefmaster.org>
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

/****************************************************************************************/
/**
 * load the services
 */
void load_modules(int sock) {
	if (ns_enabled) {
		printf(APP_DBG_CONNECTINGCLIENT, ns_name);
		if(ns_connect(sock) >= 0) {
			printf(OK);
			ns_status = 1;
		} else {
			printf(FAIL);
			printf("\x1b[35;1mError message: %s\n", strerror(errno));
			ns_status = 0;
		}
	}
	if (cs_enabled) {
		printf(APP_DBG_CONNECTINGCLIENT, cs_name);
		if(cs_connect(sock) >= 0) {
			printf(KGRN OK KDEF);
			cs_status = 1;
		} else {
			printf(KRED FAIL KDEF);
			printf("Error message: %s\n", strerror(errno));
			cs_status = 0;
		}
	}
	if (os_enabled) {
		printf(APP_DBG_CONNECTINGCLIENT, os_name);
		if(os_connect(sock) >= 0) {
			printf(KGRN OK KDEF);
			os_status = 1;
		} else {
			printf(KRED FAIL KDEF);
			printf("Error message: %s\n", strerror(errno));
			os_status = 0;
		}
	}
	if (bs_enabled) {
		printf(APP_DBG_CONNECTINGCLIENT, bs_name);
		if(bs_connect(sock) >= 0) {
			printf(KGRN OK KDEF);
			bs_status = 1;
		} else {
			printf(KRED FAIL KDEF);
			printf("Error message: %s\n", strerror(errno));
			bs_status = 0;
		}
	}
	if (as_enabled) {
		printf(APP_DBG_CONNECTINGCLIENT, as_name);
		if(as_connect(sock) >= 0) {
			printf(KGRN OK KDEF);
			as_status = 1;
		} else {
			printf(KRED FAIL KDEF);
			printf("Error message: %s\n", strerror(errno));
			as_status = 0;
		}
	}
}


/****************************************************************************************/
/**
 * process a line from the server and put the argument in an array
 */
void process(void) {
	char source[1024];
	char cmd[1024];
	char buf[1024];
	char *pch;
	int ac;
	char **av;
	irc_cmd *ic;
	strscpy(buf, ircbuf, sizeof(buf));
	if (*buf == ':') {
		pch = strpbrk(buf, " ");
		if (!pch)
			return;
		*pch = 0;
		while (isspace(*++pch))
			;
		strscpy(source, buf + 1, sizeof(source));
		strscpy(buf, pch,sizeof(buf));

	} else {
		*source = 0;
	}
	if (!*buf)
		return;
	pch = strpbrk(buf, " ");
	if (pch) {
		*pch = 0;
		while (isspace(*++pch))
			;
	} else
		pch = buf + strlen(buf);
	strscpy(cmd, buf, sizeof(cmd));
	ac = tokenize(pch, &av);
	if ((ic = find_cmd(cmd))) {
		if (ic->func)
			ic->func(source, ac, av);
		if (strcmp(buf, "PING") != 0)
			addlog(1, LOG_DBG_SERVERMSG, s_unreal, ircbuf);
	} else
		addlog(2, APP_ERR_UNKNOWNMSG, ircbuf);
	free(av);
}


/****************************************************************************************/
/**
 * create the socket and establish the connection
 */
int sock_connect(void) {
	int sock, port;
	char serverip[20];
	/* server address in config file */
	char *server = s_address;
	 /* server password in config file */
	char *password = s_password;
	/* server description in config file */
	char *description = s_description;
	/* server name in config file */
	char *servername = s_name;
	struct sockaddr_in addr; /* server address; */
	struct hostent *dns;
	port = s_port; /* server port in config file */
	dns = gethostbyname(server);
	/* resolving host to an IP address; */
	sprintf(serverip, "%u.%u.%u.%u", (unsigned char) dns->h_addr_list[0][0],
			(unsigned char) dns->h_addr_list[0][1],
			(unsigned char) dns->h_addr_list[0][2],
			(unsigned char) dns->h_addr_list[0][3]);
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		printf(APP_ERR_SOCKET);
		return -1;
	}
	printf(APP_DBG_CONNECTINGTOSERVER, s_unreal);
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons((unsigned short) port);
	addr.sin_addr.s_addr = inet_addr(serverip);
	if (connect(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
		printf(FAIL);
		printf(APP_ERR_CONNECTIONERROR, s_unreal);
		printf("Error message: %s\n", strerror(errno));
		return -1;
	}
	printf(OK);
	printf(APP_DBG_REGISTERINGSRV, s_unreal);
	char *SRV = (char*) malloc(sizeof(char) * 128);
	char *PASS = (char*) malloc(sizeof(char) * 64);
	sprintf(PASS, "PASS %s\r\n", password);
	sprintf(SRV, "SERVER %s 1 :[%s] %s\r\n", servername, servername,
			description);
	char *PROT = "PROTOCTL NICKv2\r\n";
	send(sock, PROT, (int) strlen(PROT), 0);
	send(sock, PASS, (int) strlen(PASS), 0);
	send(sock, SRV, (int) strlen(SRV), 0);
	printf(OK);
	return sock;
}



/* EOF */
