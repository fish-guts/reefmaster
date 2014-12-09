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


void addserverban(char type,char *user,char *host,char *reason,int timestamp) {
	char  buf[1024];
	long expiry = time(NULL) + (timestamp * 60);
	if(type=='Z') {
		sprintf(buf,"BD + Z %s %s %ld %ld :%s\r\n",host,ns_name,expiry,time(NULL),reason);
	} else {
	sprintf(buf,"BD + %c %s %s %s %ld %ld :%s\r\n",type,user,host,ns_name,expiry,time(NULL),reason);
	}
	notice(cs_name,"Fish-Guts",buf);
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
	sprintf(buff,":%s CHATOPS : %s\r\n",src,buf);
	send(mainsock,buff,(int)strlen(buff),0);
	free(buff);
	va_end(va);
}

int check_valid_nickname(char *nick) {
	if((stricmp(nick,"NONE")==0)
			|| (stricmp(nick,cs_name)==0)
			|| (stricmp(nick,ns_name)==0)
			|| (stricmp(nick,ms_name)==0)
			|| (stricmp(nick,cs_name)==0)
			|| (stricmp(nick,bs_name)==0)
			|| (stricmp(nick,as_name)==0)
			|| (stricmp(nick,os_name)==0)) {
		return 0;
	}
	notice(as_name,"fish-guts","Pattern: %s",NICK_PATTERN);
	if(!match(nick,NICK_PATTERN)) {
		notice(as_name,"fish-guts","not ok umlaut");
		return 0;
	}
	return 1;
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
void do_join(char *src,char *chan) {
	char buf[512];
	sprintf(buf,":%s JOIN %s\r\n",src,chan);
	send(mainsock,buf,strlen(buf),0);
}
void do_part(char *src,char *chan,char *msg) {
	char buf[512];
	sprintf(buf,":%s PART %s :%s\r\n",src,chan,msg);
	send(mainsock,buf,strlen(buf),0);
}
/********************************************************************/
/*
 * gline a user
 */
void gline(char *user,char *host,char *reason,int timestamp) {
	addserverban('G',user,host,reason,timestamp);
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
 * kick a user from a channel
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
void kline(char *user,char *host,char *reason,int timestamp) {
	addserverban('k',user,host,reason,timestamp);
}

/********************************************************************/
/**
 * change a mode on IRC
 */
void mode(const char *src,const char *target,char *modes,char *chan)
{
	char buf[512];
	if(chan)
		sprintf(buf,":%s MODE %s %s %s %ld\r\n",src,chan,modes,target,time(NULL));
	else
		sprintf(buf,":%s MODE %s %s\r\n",src,target,modes);
	send(mainsock,buf,strlen(buf),0);
}
/********************************************************************/
/**
 * Send an IRC notice
 */
void notice(const char *src,char *dest,char *msg, ...)
{
	char buf[512];
	char *buff = (char*)malloc(sizeof(char)*512);
	va_list va;
	va_start(va,msg);
	vsprintf(buf,msg,va);
	sprintf(buff,":%s NOTICE %s :%s\r\n",src,dest,buf);
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
	s_send("PONG %s :%s\r\n",s_name,s_unreal);
}
/********************************************************************/
/**
 * send a QUIT message to server
 */
void quit(char *nick)
{
	char *buf = (char*)malloc(sizeof(char)*128);
	sprintf(buf,":%s QUIT :Quit: Leaving\r\n",nick);
	send(mainsock,buf,(int)strlen(buf),0);
	return;
}
/********************************************************************/
/**
 * send a KILL command to the server
 */
void s_kill(const char *src,char *dest,char *reason)
{
	char buf[512];
	user *u1 = finduser(dest);  	/* for logging purposes only */
	sprintf(buf,":%s KILL %s :%s!%s %s\r\n",src,dest,src,src,reason);
	addlog(1,LOG_DBG_IRC_KILL,src,dest,u1->username,u1->hostname,reason);
	send(mainsock,buf,strlen(buf),0);
}
/********************************************************************/
/**
 * send a line to the server
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
		sprintf(buf,":%s SVSMODE %s %s %s\r\n",src,chan,modes,target);
	else
		sprintf(buf,":%s SVSMODE %s %s\r\n",src,target,modes);
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
		sprintf(buf,":%s SVS2MODE %s %s %s\r\n",src,chan,modes,target);
	else
		sprintf(buf,":%s SVS2MODE %s %s\r\n",src,target,modes);

	send(mainsock,buf,strlen(buf),0);	
}
/********************************************************************/
/**
 * send a SVSNICK command to the server
 */
void svsnick(char *src,char *newnick,time_t t)
{
	char  buf[512];
	sprintf(buf,"SVSNICK %s %s :%lu\r\n",src,newnick,t);
	send(mainsock,buf,strlen(buf),0);
}
void topic(char *src, char *chan,char *nick,time_t timestamp,char *topic) {
	char buf[2048];
	sprintf(buf,":%s ) %s %s %ld :%s\r\n",src,chan,nick,timestamp,topic);
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
	sprintf(buff,":%s WALLOPS :%s\r\n",src,buf);
	send(mainsock,buff,(int)strlen(buff),0);
	free(buff);
	va_end(va);
}
void zline(char *user, char *host, char *reason, int timestamp) {
	addserverban('Z',user,host,reason,timestamp);
}
/* EOF */
