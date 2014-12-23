/*
 * cs_info.c
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

void cs_info(char *src,int ac, char **av) {
	ChanInfo *c;
	char *chan;
	char *options = (char*)malloc(sizeof(char*)*4096);
	char *topiclock = (char*)malloc(sizeof(char*)*32);
	time_t cur = time(NULL);
	char str_now[256], str_reg[80];
	if(ac<2) {
		notice(cs_name,src,CS_ERR_INF_USAGE);
		notice(cs_name,src,CS_RPL_HLP,"INFO");
		return;
	}
	chan = sstrdup(av[1]);
	if(!isregcs(chan)) {
		notice(cs_name,src,CS_ERR_NOTREG,chan);
		return;
	}

	c = findchan(chan);
	strftime(str_reg, 100, "%d/%m/%Y %T %Z", localtime(&c->time_reg));
	strftime(str_now, 100, "%d/%m/%Y %T %Z", localtime(&cur));
	if(c->opwatch)
		strcat(options,"OpWatch");
	if(c->leaveops) {
		if(strlen(options)>1)
			strcat(options,", ");
		strcat(options,"Leaveops");
	}
	if(c->keeptopic) {
		if(strlen(options)>1)
			strcat(options,", ");
		strcat(options,"KeepTopic");
	}
	if(c->autovop) {
		if(strlen(options)>1)
			strcat(options,", ");
		strcat(options,"AutoVop");
	}
	if(c->restricted) {
		if(strlen(options)>1)
			strcat(options,", ");
		strcat(options,"Restricted");
	}
	if(c->topiclock) {
		sprintf(topiclock,"\2%s\2 TopicLock",get_opacc(c->topiclock));
		if(strlen(options)>1)
			strcat(options,", ");
		strcat(options,topiclock);
	}
	notice(cs_name,src,CS_RPL_INF_ENTRY1,c->name,c->description);
	notice(cs_name,src,CS_RPL_INF_ENTRY2,c->founder->nick);
	if((c->successor!=NULL) && (stricmp(c->successor->nick,"(null)")!=0))
		notice(cs_name,src,CS_RPL_INF_ENTRY3,c->successor->nick);
	if((c->topic!=NULL) && (stricmp(c->topic,"")!=0))
		notice(cs_name,src,CS_RPL_INF_ENTRY4,c->topic);
	notice(cs_name,src,CS_RPL_INF_ENTRY5,str_reg);
	notice(cs_name,src,CS_RPL_INF_ENTRY6,str_now);
	notice(cs_name,src,CS_RPL_INF_ENTRY7,c->mlock);
	notice(cs_name,src,CS_RPL_INF_ENTRY8,options);
	notice(cs_name,src,CS_RPL_INF_ENTRY9,get_opacc(c->memolevel));
	free(options);
	return;

}
