/*
 *      commands.c - severin
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
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, alBoston,
 *      MA 02110-1301, USA.
 */
#include "main.h"

/* function prototypes */
static void c_nick(char *src,int ac,char **av);
static void handle_chan_mode(char *chan,char *arg,char *mode, int add);
static void handle_chan_mode_a(char *chan, char *nick,int z);
static void handle_chan_mode_h(char *chan, char *nick,int z);
static void handle_chan_mode_o(char *chan, char *nick,int z);
static void handle_chan_mode_q(char *chan, char *nick,int z);
static void handle_chan_mode_v(char *chan, char *nick,int z);


/* global vars */
irc_cmd *find_cmd(const char *name)
{
    irc_cmd *cmd;
    for (cmd = irc_cmds; cmd->name; cmd++)
    {
		if(stricmp(name,cmd->name)==0)
	    	return cmd;
    }
    return NULL;
}
irc_cmd irc_cmds[] = {
	{ "EOS",	  NULL	    },
	{ "ERROR",	  NULL		},
	{ "JOIN",     c_join 	},
	{ "KICK",	  c_kick 	},
	{ "KILL",	  c_kill 	},
	{ "MODE",	  c_mode 	}, 
	{ "NETINFO",  NULL 		},
	{ "NICK",	  c_nick 	},
	{ "PASS",	  NULL 		},
	{ "PART",	  c_part	},
	{ "PRIVMSG",  c_privmsg },
	{ "PROTOCTL", NULL		},
	{ "PING",	  c_ping 	},	
	{ "QUIT",	  c_quit	},
	{ "SERVER",	  NULL 		},
	{ "SMO",	  NULL 		},
	{ "TOPIC",    c_topic 	},
}; 

/********************************************************************/
/**
 * 	handle the server's JOIN command
 */
void c_join(char *src, int ac, char **av) {
	s_join(src,ac,av);
}

/********************************************************************/
/**
 * 	handle the server's JOIN command
 */
void c_part(char *src, int ac, char **av) {
	s_part(src,ac,av);
}

/********************************************************************/
/**
 * 	handle the server's KICK command
 */
void c_kick(char *src, int ac, char **av) {
	if(findbot(av[1])) {
		del_bot(av[0]);
		return;
	} else {
		del_user(finduser(av[1]),findchannel(av[0]));
		return;
	}
}

/********************************************************************/
/**
 * 	handle the server's KILL command
 */
void c_kill(char *src, int ac, char **av) {
	if(isservice(av[0])) {
		set_service_status(av[0],0);
	}
	if(findbot(av[0])) {
		bot *b = findbot(av[0]);
		botchan *bc = b->chanlist;
		while(bc) {
			del_bot(bc->chan);
			bc = bc->next;
		}
		connect_bot(av[0]);

	}
	user *u = finduser(src);
	cancel_user(u);
	return;
}

/********************************************************************/
/**
 * Handles a Server's MODE message
 */
void c_mode(char *src, int ac, char **av) {
	int x = 0;
	int t = 2;
	int y = 2;
	int z = 0;
	channel *c;
	user *u;
	char *ptr;
	if(stricmp(src,s_unreal)!=0) {
		u = finduser(src);
		if(!u)
			return;
	}
	if(strcmp(av[1],"+")==0)
		return;
	/* if it's a channel mode */
	if(strchr(av[0],'#'))
	{
		c = findchannel(av[0]);
		for(ptr = av[1];*ptr;ptr++)
		{

			switch(*ptr)
			{
				case '+':
					z = 1;
					break;
				case '-':
					z = 0;
					break;
				case 'a':
				case 'o':
				case 'h':
				case 'q':
				case 'v':
					handle_chan_mode(c->name,av[t],ptr,z);
					t++;									
					break;
				case 'b':
					if(z)
						channel_add_ban(src,c,av[t]);
					else
						channel_remove_ban(src,c,av[t]);
					break;
				case 'k':
					if(z){
						c->key = sstrdup(av[1]);
					} else	{
						c->key = NULL;
					}
					break;		
				case 'r':
					if(!z)
						mode(cs_name,c->name,"+r",NULL);
					break;
				case 't':
					if(!z)
						mode(cs_name,c->name,"+t",NULL);
					break;
				case 'n':
					if(!z)
						mode(cs_name,c->name,"+n",NULL);
					break;
				default:
					break;
			} /*switch*/
			y++;
		}/*for*/
	}
	/* if it's a usermode */
	else
	{
		u = finduser(src);
		if(strchr(av[1],'+'))
			x = 1;
		else if(strchr(av[1],'-'))
			x = 0;
		if(x)
		{	
			if(strchr(av[1],'S'))
				u->service = 1;
			if(strchr(av[1],'h'))
				u->oper = 1;
			if((strchr(av[1],'o')) || (strchr(av[1],'O')))
				u->oper = 2;
			if(strchr(av[1],'C'))
				u->oper = 3;
			if(strchr(av[1],'A'))
				u->oper = 4;
			if(strchr(av[1],'a'))
				u->oper = 5;
			if(strchr(av[1],'N'))
				u->oper = 6;
			if((!strchr(av[1],'a')) && (!strchr(av[1],'A')) && 
		       (!strchr(av[1],'o')) && (!strchr(av[1],'C')) && 
		       (!strchr(av[1],'N')) && (!strchr(av[1],'h'))) 
				u->oper = 0;
			announce_oper(src,u->oper);
		}
	}
}

/********************************************************************/
/**
 * 	handle the server's NICK message
 */
static void c_nick(char *src,int ac,char **av) {
    if(ac==8) 
    {
		av[6] = av[7];
		ac--;
    }
    if((!*src && ac != 10) || (*src && ac != 2))
		return;	
    if(stricmp(av[0],"guest")==0)
    {
	    char newnick[NICKMAX];
	    long int guestbuf = 0;
	    double x = RAND_MAX + 1.0;
	    int y = 1 + rand() * (99999 / x);
	    guestbuf = y;
	    snprintf (newnick, sizeof (newnick), "Guest%ld", guestbuf);	
	    svsnick(av[0],newnick,time(NULL));
        s_nick(src,ac,av);
        return;
    } 
    else {
        s_nick(src,ac,av);
        return;
    }
}

/********************************************************************/
/**
 * 	handle the server's PRIVMSG message
 */
void c_privmsg(char *src,int ac,char **av) {
	char *pch,*dest;
	/* strip the usermask (@host) if found */
	if(strchr(av[0],'@'))
	{
		pch = strtok(av[0],"@");
		dest = sstrdup(pch);
	}
	else
		dest = av[0];		
	if(stricmp(dest,ns_name)==0)
		nickserv(src,av[1]);
	if(stricmp(dest,cs_name)==0) {
		chanserv(src,av[1]);
	}
	if(stricmp(dest,os_name)==0) {
		operserv(src,av[1]);
	}
	if(stricmp(dest,as_name)==0)
		adminserv(src,av[1]);
	if(stricmp(dest,bs_name)==0)
		botserv(src,av[1]);
}

/********************************************************************/
 /**
  * 	handle the server's PING message
  */
void c_ping(char *src,int ac,char **av) {
	pong();
}

/********************************************************************/
/**
 * 	handle the server's split a message line from the server
 */
int tokenize(char *buf, char ***argv) {
    int argvsize = 8;
    int argc = 0;
    char *pch;
    *argv = smalloc(sizeof(char*) * argvsize);
    while (*buf) 
    {
		if(argc == argvsize) 
		{
		    argvsize += 8;
	    	*argv = srealloc(*argv, sizeof(char*) * argvsize);
		}
		if (*buf == ':') 
		{
		    (*argv)[argc++] = buf+1;
	    	buf = "";
		} 
		else 
		{
		    pch = strpbrk(buf, " ");
	    	if(pch) 
	    	{
				*pch++ = 0;
				while(isspace(*pch))
				{
			    	pch++;
				}
	    	} 
	    	else 
	    	{
				pch = buf + strlen(buf);
	    	}
	    	(*argv)[argc++] = buf;
	    	buf = pch;
		}
    }
    return argc;
}

/********************************************************************/
/**
 * 	handle the server's QUIT message
 */
 void c_quit(char *src, int ac, char **av) {
 	user *u = finduser(src);
 	if(u)
 	{
 		ns_checknotify(u,NOTIFY_OFFLINE);
 		cancel_user(u);
 	}
}

/********************************************************************/
/**
 * handle the server's TOPIC message
 */
void c_topic(char *src, int ac, char **av)
{
	if(isservice(src))  {
		return;
	}
	channel *c = findchannel(av[0]);
	char *oldtopic = (char*)malloc(sizeof(char*)*1024);
	if(c->topic) {
		oldtopic = sstrdup(c->topic);
	} else {
		oldtopic = NULL;
	}
	c->topic = sstrdup(av[3]);
	cs_check_topiclock(src,c,oldtopic);
}

/********************************************************************/
/**
 * handle a channel mode
 */
static void handle_chan_mode(char *chan,char *arg,char *mode, int add) {
	switch(*mode) {
		case 'o':
			handle_chan_mode_o(chan,arg,add);
			break;
		case 'v':
			handle_chan_mode_v(chan,arg,add);
			break;
		case 'h':
			handle_chan_mode_h(chan,arg,add);
			break;
		case 'a':
			handle_chan_mode_a(chan,arg,add);
			break;
		case 'q':
			handle_chan_mode_q(chan,arg,add);
			break;
		}
}

/********************************************************************/
/**
 * handle channel mode o
 */
static void handle_chan_mode_o(char *chan,char *nick,int z)
{
	user *u = finduser(nick);
	channel *c = findchannel(chan);
	if(z) {
		if(cs_check_opwatch(c->name,u)) {
			deop(cs_name,u->nick,c->name);
			return;
		}
		c->ops++;
		add_status(c,u,OP);
	} else {
		if(c->ops>0)
		c->ops--;
		del_status(c,u,OP);
	}
}

/********************************************************************/
/**
 * handle channel mode v
 */
static void handle_chan_mode_v(char *chan, char *nick,int z) {
	user *u = finduser(nick);
	channel *c = findchannel(chan);
	if(z)
	{
		c->vops++;
		add_status(c,u,VOP);
	}
	else
	{
		if(c->vops>0)
			c->vops--;
		del_status(c,u,VOP);
	}
}

/********************************************************************/
/**
 * handle channel mode h
 */
static void handle_chan_mode_h(char *chan, char *nick, int z) {
	user *u = finduser(nick);
	channel *c = findchannel(chan);
	if(z)
	{
		if(cs_check_opwatch(c->name,u)) {
			dehop(cs_name,u->nick,c->name);
			return;
		}
		c->hops++;
		add_status(c,u,HOP);
	}
	else
	{
		if(c->hops>0)
			c->hops--;
		del_status(c,u,HOP);
	}
}

/********************************************************************/
/**
 * handle channel mode a
 */
static void handle_chan_mode_a(char *chan, char *nick, int z) {
	user *u = finduser(nick);
	channel *c = findchannel(chan);
	if(z)
	{
		if(cs_check_opwatch(c->name,u)) {
			deadmin(cs_name,u->nick,c->name);
			return;
		}
		c->pus++;
		add_status(c,u,ADMIN);
	}
	else
	{
		if(c->pus>0)
			c->pus--;
		del_status(c,u,ADMIN);
	}
}

/********************************************************************/
/**
 * handle channel mode q
 */
void handle_chan_mode_q(char *chan, char *nick, int z) {
	channel *c = findchannel(chan);
	if(isregbot(nick)) {
		if(!z)
			do_owner(nick,nick,c->name);
		return;
	}
	user *u = finduser(nick);
	if(z)
	{
		if(cs_check_opwatch(c->name,u)) {
			deowner(cs_name,u->nick,c->name);
			return;
		}
		c->owners++;
		add_status(c,u,OWNER);
	}
	else
	{
		if(c->owners>0)
			c->owners--;
		del_status(c,u,OWNER);
	}
}
/* EOF */
