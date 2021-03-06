/*
 *      irc.c - severin
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

/********************************************************************/
/**
 * adds a server ban of the specified type
 */

void addserverban(char *src,char type,char *user,char *host,char *reason,int timestamp) {
	char  buf[1024];
	long expiry = time(NULL) + (timestamp * 60);
	if(type=='Z') {
		sprintf(buf,ZLINE,host,src,expiry,time(NULL),reason);
	} else {
	sprintf(buf,XLINE,type,user,host,src,expiry,time(NULL),reason);
	}
	send(mainsock,buf,strlen(buf),0);
}

/********************************************************************/
/**
 * Place a channel ban
 */
void ban(char *src,const char *target,char *chan) {
	mode(src,target,"+b",chan);
}
/********************************************************************/
/**
 * send a message to all global opers
 */
void chatops(char *src,char *msg,...)
{
	char buf[1024];
	char *buff = (char*)malloc(sizeof(char)*1024);
	va_list va;
	va_start(va,msg);
	vsprintf(buf,msg,va);
	sprintf(buff,CHATOPS,src,buf);
	send(mainsock,buff,(int)strlen(buff),0);
	free(buff);
	va_end(va);
}

/********************************************************************/
/**
 * check for valid nicknames.
 * return 1 if valid
 * return 0 if invalid
 */
int check_valid_nickname(char *nick) {
	if((stricmp(nick,"NONE")==0)
			|| (stricmp(nick,cs_name)==0)
			|| (stricmp(nick,ns_name)==0)
			|| (stricmp(nick,cs_name)==0)
			|| (stricmp(nick,bs_name)==0)
			|| (stricmp(nick,as_name)==0)
			|| (stricmp(nick,os_name)==0)) {
		return 0;
	}
	if(!match(nick,NICK_PATTERN)) {
		return 0;
	}
	return 1;
}

/********************************************************************/
/*
 * change the host of a user
 */
void chghost(char *src,char *target,char *host) {
	char  buf[512];
	sprintf(buf,":%s CHGHOST %s %s\r\n",src,target,host);
	send(mainsock,buf,strlen(buf),0);
}

/********************************************************************/
/**
 * remove the admin status from a user on a channel
 */
void deadmin(char *src,char *target,char *chan) {
	mode(src,target,"-a",chan);
}
/********************************************************************/
/**
 * remove the half-operator status from a user on a channel
 */
void dehop(char *src,char *target,char *chan) {
	mode(src,target,"-h",chan);
}
/********************************************************************/
/**
 * remove the operator status from a user on a channel
 */
void deop(char *src,char *target,char *chan) {
	mode(src,target,"-o",chan);
}
/********************************************************************/
/**
 * remove the owner status from a user on a channel
 */
void deowner(char *src,char *target,char *chan) {
	mode(src,target,"-q",chan);
}
/********************************************************************/
/**
 * remove the voice status from a user on a channel
 */
void devoice(char *src,char *target,char *chan) {
	mode(src,target,"-v",chan);
}
/********************************************************************/
/**
 * grant the admin status to a user on a channel
 */
void do_admin(char *src,char *target,char *chan) {
	mode(src,target,"+a",chan);
}
/********************************************************************/
/**
 * KILL for AKILL purposes
 */
void do_akill(const char *src,char *dest,char *reason)
{
	char buf[512];
	user *u1 = finduser(dest);
	/* for logging purposes only */
	sprintf(buf,KILL,src,dest,src,src,reason);
	if((!isservice(dest)) && (!findbot(dest))) {
		addlog(1,LOG_DBG_IRC_KILL,src,dest,u1->username,u1->hostname,reason);
	}
	send(mainsock,buf,strlen(buf),0);
}
/********************************************************************/
/**
 * grant the operator status to a user on a channel
 */
void do_op(char *src,char *target,char *chan) {
	mode(src,target,"+o",chan);
}
/********************************************************************/
/**
 * grant the owner status to a user on a channel
 */
void do_owner(char *src,char *target,char *chan) {
	mode(src,target,"+q",chan);
}

/********************************************************************/
/**
 * join a channel
 */
void do_join(char *src,char *chan) {
	char buf[512];
	sprintf(buf,JOIN,src,chan);
	send(mainsock,buf,strlen(buf),0);
}

/********************************************************************/
/**
 * leave a channel
 */
void do_part(char *src,char *chan,char *msg) {
	char buf[512];
	sprintf(buf,PART,src,chan,msg);
	send(mainsock,buf,strlen(buf),0);
}

/********************************************************************/
/*
 * gline a user
 */
void gline(char *src,char *user,char *host,char *reason,int timestamp) {
	addserverban(src,'G',user,host,reason,timestamp);
}

/********************************************************************/
/**
 * send a GLOBOPS command to the server
 */
void globops(char *src,char *msg,...)
{
	char buf[512];
	char *buff = (char*)malloc(sizeof(char)*512);
	va_list va;
	va_start(va,msg);
	vsprintf(buf,msg,va);
	sprintf(buff,":%s GLOBOPS :%s\r\n",src,buf);
	send(mainsock,buff,(int)strlen(buff),0);
	free(buff);
	va_end(va);
}

/********************************************************************/
/**
 * grant the half-operator status to a user on a channel
 */
void hop(char *src,char *target,char *chan) {
	mode(src,target,"+h",chan);
}

/********************************************************************/
/*
 * invite a user to a channel
 */
void invite(char *src,char *target,char *chan) {
	char  buf[512];
	sprintf(buf,":%s INVITE %s %s\r\n",src,target,chan);
	send(mainsock,buf,strlen(buf),0);
}

/********************************************************************/
/*
 * kick a user from a channel
 */
void kick(char *src,const char *target,char *chan,char *reason) {
	char  buf[512];
	sprintf(buf,":%s KICK %s %s :%s\r\n",src,chan,target,reason);
	send(mainsock,buf,strlen(buf),0);
}
/********************************************************************/
/*
 * kline a user
 */
void kline(char *src,char *user,char *host,char *reason,int timestamp) {
	addserverban(src,'k',user,host,reason,timestamp);
}

/********************************************************************/
/**
 * send a LOCOPS command to the server
 */
void locops(char *src,char *msg,...)
{
	char buf[512];
	char *buff = (char*)malloc(sizeof(char)*512);
	va_list va;
	va_start(va,msg);
	vsprintf(buf,msg,va);
	sprintf(buff,":%s LOCOPS :%s\r\n",src,buf);
	send(mainsock,buff,(int)strlen(buff),0);
	free(buff);
	va_end(va);
}

/********************************************************************/
/**
 * change a mode on IRC
 */
void mode(const char *src,const char *target,char *modes,char *chan)
{
	char buf[512];
	if(chan)
		sprintf(buf,CHANMODE,src,chan,modes,target,time(NULL));
	else
		sprintf(buf,USERMODE,src,target,modes);
	send(mainsock,buf,strlen(buf),0);
}

/********************************************************************/
/**
 * Send an IRC notice
 */
void notice(const char *src,char *dest,char *msg, ...)
{
	char buf[8196];
	char *buff = (char*)malloc(sizeof(char)*8196);
	va_list va;
	va_start(va,msg);
	vsprintf(buf,msg,va);
	sprintf(buff,NOTICE,src,dest,buf);
	send(mainsock,buff,(int)strlen(buff),0);
	free(buff);
	va_end(va);
}

/********************************************************************/
/**
 * Send an IRC message
 */
void privmsg(const char *src,char *dest,char *msg, ...)
{
	char buf[512];
	char *buff = (char*)malloc(sizeof(char)*512);
	va_list va;
	va_start(va,msg);
	vsprintf(buf,msg,va);
	sprintf(buff,PRIVMSG,src,dest,buf);
	send(mainsock,buff,(int)strlen(buff),0);
	free(buff);
	va_end(va);
}

/********************************************************************/
/**
 * 	send a PONG message to server
 */
void pong(void)
{
	s_send(PONG,s_name,s_unreal);
}

/********************************************************************/
/**
 * add a q:line for the specified nickname
 */
void qline(char *src,char *nick,char *reason) {
	char  buf[512];
	sprintf(buf,":%s c %s :%s\r\n",src,nick,reason);
	send(mainsock,buf,strlen(buf),0);
}

/********************************************************************/
/**
 * send a QUIT message to server
 */
void quit(char *nick)
{
	char *buf = (char*)malloc(sizeof(char)*128);
	sprintf(buf,QUIT,nick);
	send(mainsock,buf,(int)strlen(buf),0);
	return;
}

/********************************************************************/
/**
 * lift a server ban of the specified type against the specified mask
 * Valid types:
 * 	- K indicates a K:Line (local server ban)
 * 	- G indicates a G:Line (global server ban)
 * 	- Q indicates a Q:Line (nick ban)
 * 	- Z indicates a Z:Line (IP Address ban)
 */
void remove_serverban(char *src,char type, char *username,char *hostname) {
	char buf[1024];
	sprintf(buf,RXLINE,type,username,hostname,src);
	send(mainsock,buf,strlen(buf),0);
}

/********************************************************************/
/**
 * remove a G:line
 */
void rgline(char *src,char *username,char *hostname) {
	remove_serverban(src,'G',username,hostname);
}

/********************************************************************/
/**
 * remove a K:line
 */
void rkline(char *src,char *username,char *hostname) {
	remove_serverban(src,'K',username,hostname);
}

/********************************************************************/
/**
 * remove a Q:line
 */
void rsqline(char *src,char *hold,char *nickname) {
	remove_serverban(src,'Q',hold,nickname);
}

/********************************************************************/
/**
 * remove a Z:line
 */
void rzline(char *src,char *user, char *host) {
	remove_serverban(src,'Z',user,host);
}

/********************************************************************/
/**
 * send a KILL command to the server
 */
void s_kill(const char *src,char *dest,char *reason)
{
	char buf[512];
	user *u1 = finduser(dest);  	/* for logging purposes only */
	sprintf(buf,KILL,src,dest,src,src,reason);
	if((!isservice(dest)) && (!findbot(dest))) {
		addlog(1,LOG_DBG_IRC_KILL,src,dest,u1->username,u1->hostname,reason);
	}
	send(mainsock,buf,strlen(buf),0);
}

/********************************************************************/
/*
 * sqline a nickname
 */
void sqline(char *src,char *hold,char *nickname,char *reason,int timestamp) {
	addserverban(src,'Q',hold,nickname,reason,timestamp);
}

/********************************************************************/
/**
 * special implementation of send, only used for pong
 */
void s_send(char *cmd, ...)
{
	char buf[512];
	va_list va;
	va_start(va,cmd);
	vsprintf(buf,cmd,va);
	va_end(va);
	send(mainsock,buf,(int)strlen(buf),0);
}

/********************************************************************/
/**
 * send a SVSMODE command to the server
 */
void svsmode(const char *src,char *target,char *modes,char *chan)
{
	char buf[512];
	if((chan!=NULL) && (target!=NULL))
		sprintf(buf,SVSMODE,src,chan,modes,target);
	else
		sprintf(buf,SVSUMODE,src,target,modes);
	send(mainsock,buf,strlen(buf),0);	
}

/********************************************************************/
/**
 * send a SVS2MODE command to the server
 */
void svs2mode(const char *src,char *target,char *modes,char *chan)
{
	char buf[512];
	if(chan)
		sprintf(buf,SVS2MODE,src,chan,modes,target);
	else
		sprintf(buf,SVS2UMODE,src,target,modes);

	send(mainsock,buf,strlen(buf),0);	
}

/********************************************************************/
/**
 * send a SVSNICK command to the server
 */
void svsnick(char *src,char *newnick,time_t t)
{
	char  buf[512];
	sprintf(buf,SVSNICK,src,newnick,t);
	send(mainsock,buf,strlen(buf),0);
}

/********************************************************************/
/**
 * change the topic of a channel.
 */

void topic(char *src, char *chan,char *nick,time_t timestamp,char *topic) {
	char buf[2048];
	sprintf(buf,TOPIC,src,chan,nick,timestamp,topic);
	send(mainsock,buf,strlen(buf),0);
}

/********************************************************************/
/**
 * remove a permanent q:line from the server
 */
void unqline(char *src, char *nick) {
	char  buf[512];
	sprintf(buf,":%s d %s\r\n",src,nick);
	send(mainsock,buf,strlen(buf),0);
}

/********************************************************************/
/**
 * grant the voice status to a user on a channel
 */
void voice(char *src,char *target,char *chan) {
	mode(src,target,"+v",chan);
}

/********************************************************************/
/**
 * send a WALLOPS command to the server
 */
void wallops(char *src,char *msg,...)
{
	char buf[512];
	char *buff = (char*)malloc(sizeof(char)*512);
	va_list va;
	va_start(va,msg);
	vsprintf(buf,msg,va);
	sprintf(buff,WALLOPS,src,buf);
	send(mainsock,buff,(int)strlen(buff),0);
	free(buff);
	va_end(va);
}

/********************************************************************/
/**
 * send a z:line to the server
 */
void zline(char *src,char *mask, char *reason, int timestamp) {
	addserverban(src,'Z',NULL,mask,reason,timestamp);
}
/* EOF */
