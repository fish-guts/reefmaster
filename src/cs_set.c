/*
 * cs_set.c
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

void cs_set(char *src,int ac,char **av) {
	if (ac <= 1) {
		notice(cs_name, src, NS_ERR_SET_USAGE);
		return;
	}
	if (stricmp(av[2], "BOT") == 0)
		cs_set_bot(src, ac, av);
	else if (stricmp(av[2], "FOUNDER") == 0)
		cs_set_founder(src, ac, av);
	else if (stricmp(av[2], "OPWATCH") == 0)
		cs_set_opwatch(src, ac, av);
	else if (stricmp(av[2], "LEAVEOPS") == 0)
		cs_set_leaveops(src, ac, av);
	else if (stricmp(av[2], "KEEPTOPIC") == 0)
		cs_set_keeptopic(src, ac, av);
	else if (stricmp(av[2], "MEMOLEVEL") == 0)
		cs_set_memolevel(src, ac, av);
	else if (stricmp(av[2], "MLOCK") == 0)
		cs_set_mlock(src, ac, av);
	else if (stricmp(av[2], "PASSWORD") == 0)
		cs_set_password(src, ac, av);
	else if (stricmp(av[2], "RESTRICTED") == 0)
		cs_set_restricted(src, ac, av);
	else if (stricmp(av[2], "SUCCESSOR") == 0)
		cs_set_successor(src, ac, av);
	else if (stricmp(av[2], "TOPICLOCK") == 0)
		cs_set_topiclock(src, ac, av);
	else {
		notice(cs_name,src,NS_ERR_NOSUCHCMD,av[2]);
		notice(cs_name,src,CS_RPL_HLP,cs_name,"SET");
		return;
	}
}
void cs_set_bot(char *src,int ac,char **av) {
	ChanInfo *c;
	char *chan;
	char *botname;
	bot *b,*b1;
	user *u = finduser(src);
	if (ac <= 3) {
		notice(cs_name, src, CS_ERR_SET_BOT_USAGE);
		notice(cs_name,src,CS_RPL_HLP,cs_name,"SET BOT");
		return;
	}
	chan = av[1];
	botname = av[3];
	if(!isregcs(chan)) {
		notice(cs_name,src,CS_ERR_NOTREG,chan);
		return;
	}
	c = findchan(chan);
	if(cs_xop_get_level(u,c)<FOUNDER) {
		notice(cs_name,src,CS_ERR_ACCESSDENIED,chan);
		notice(cs_name,src,CS_RPL_NEEDIDENTIFY,chan);
		return;
	}
	b1 = findbot_onchan(c->name);
	if(stricmp(botname,"NONE")==0) {
		if(!b1) {
			notice(cs_name,src,CS_ERR_SET_BOT_NOBOT,c->name);
			return;
		} else {
			do_part(b1->name,c->name,BS_RPL_PART_MSG);
			bot_del_chan(b1,c->name);
			notice(cs_name,src,CS_RPL_SET_BOT_BOTREMOVED,c->name);
			return;
		}
	}
	if(b1) {
		if(stricmp(b1->name,botname)==0) {
			notice(cs_name,src,CS_RPL_SET_BOT_ALREADY,b1->name,chan);
			return;
		} else {
			do_part(b1->name,c->name,BS_RPL_PART_MSG);
			bot_del_chan(b1,c->name);
		}
	}
	b = findbot(botname);
	if(!b) {
		notice(cs_name,src,CS_ERR_SET_BOT_NOSUCHBOT,botname);
		return;
	}
	notice(cs_name,src,CS_RPL_SET_BOT_BOTADDED,botname,c->name);
	bot_add_chan(b,c->name);
	do_join(b->name,c->name);
	do_owner(b->name,b->name,c->name);

}
void cs_set_founder(char *src,int ac,char **av) {
	ChanInfo *c;
	char *chan,*nick;
	user *u = finduser(src);
	if (ac <= 3) {
		notice(cs_name, src, CS_ERR_SET_FOUNDER_USAGE);
		notice(cs_name,src,CS_RPL_HLP,cs_name,"SET FOUNDER");
		return;
	}
	chan = av[1];
	nick = av[3];
	if(!isregcs(chan)) {
		notice(cs_name,src,CS_ERR_NOTREG,chan);
		return;
	}
	c = findchan(chan);
	if(cs_xop_get_level(u,c)<FOUNDER) {
		notice(cs_name,src,CS_ERR_ACCESSDENIED,chan);
		notice(cs_name,src,CS_RPL_NEEDIDENTIFY,chan);
		return;
	}
	if(!isreg(nick)) {
		notice(cs_name,src,NS_ERR_NOTREG,nick);
		notice(cs_name,src,CS_ERR_SET_FOUNDER_REG);
		return;
	}
	NickInfo *n = findnick(nick);
	c->founder = n;
	notice(cs_name,src,CS_RPL_SET_FOUNDER_SUCCESS,nick,chan);
	return;
}
void cs_set_keeptopic(char *src,int ac,char **av) {
	ChanInfo *c;
	char *chan;
	user *u = finduser(src);
	if (ac <= 3) {
		notice(cs_name, src, CS_ERR_SET_KEEPTOPIC_USAGE);
		notice(cs_name,src,CS_RPL_HLP,cs_name,"SET KEEPTOPIC");
		return;
	}
	chan = av[1];
	if(!isregcs(chan)) {
		notice(cs_name,src,CS_ERR_NOTREG,chan);
		return;
	}
	c = findchan(chan);
	if(cs_xop_get_level(u,c)<FOUNDER) {
		notice(cs_name,src,CS_ERR_ACCESSDENIED,chan);
		notice(cs_name,src,CS_RPL_NEEDIDENTIFY,chan);
		return;
	}
	if(stricmp(av[3],"ON")==0) {
		c->keeptopic = 1;
		notice(cs_name,src,CS_RPL_SET_KEEPTOPIC_ENABLE,chan);
		return;
	} else if(stricmp(av[3],"OFF")==0) {
		c->keeptopic = 0;
		notice(cs_name,src,CS_RPL_SET_KEEPTOPIC_DISABLE,chan);
		return;
	} else {
		notice(cs_name, src, CS_ERR_SET_KEEPTOPIC_USAGE);
		notice(cs_name,src,CS_RPL_HLP,cs_name,"SET KEEPTOPIC");
		return;
	}
}
void cs_set_leaveops(char *src,int ac,char **av) {
	ChanInfo *c;
	char *chan;
	user *u = finduser(src);
	if (ac <= 3) {
		notice(cs_name, src, CS_ERR_SET_LEAVEOPS_USAGE);
		notice(cs_name,src,CS_RPL_HLP,cs_name,"SET LEAVEOPS");
		return;
	}
	chan = av[1];
	if(!isregcs(chan)) {
		notice(cs_name,src,CS_ERR_NOTREG,chan);
		return;
	}
	c = findchan(chan);
	if(cs_xop_get_level(u,c)<FOUNDER) {
		notice(cs_name,src,CS_ERR_ACCESSDENIED,chan);
		notice(cs_name,src,CS_RPL_NEEDIDENTIFY,chan);
		return;
	}
	if(stricmp(av[3],"ON")==0) {
		c->leaveops = 1;
		c->opwatch = 0;
		notice(cs_name,src,CS_RPL_SET_LEAVEOPS_ENABLE,chan);
		return;
	} else if(stricmp(av[3],"OFF")==0) {
		c->leaveops = 0;
		c->opwatch = 1;
		notice(cs_name,src,CS_RPL_SET_LEAVEOPS_DISABLE,chan);
		return;
	} else {
		notice(cs_name, src, CS_ERR_SET_KEEPTOPIC_USAGE);
		notice(cs_name,src,CS_RPL_HLP,cs_name,"SET LEAVEOPS");
		return;
	}
}
void cs_set_memolevel(char *src,int ac,char **av) {
	ChanInfo *c;
	char *chan;
	user *u = finduser(src);
	if (ac <= 3) {
		notice(cs_name, src, CS_ERR_SET_TOPICLOCK_USAGE);
		notice(cs_name,src,CS_RPL_HLP,cs_name,"SET TOPICLOCK");
		return;
	}
	chan = av[1];
	if(!isregcs(chan)) {
		notice(cs_name,src,CS_ERR_NOTREG,chan);
		return;
	}
	c = findchan(chan);
	if(cs_xop_get_level(u,c)<FOUNDER) {
		notice(cs_name,src,CS_ERR_ACCESSDENIED,chan);
		notice(cs_name,src,CS_RPL_NEEDIDENTIFY,chan);
		return;
	}
	if(stricmp(av[3],"Uop")==0) {
		c->memolevel = UOP_LIST;
		notice(cs_name,src,CS_RPL_SET_MEMOLEVEL_SUCCESS,chan,av[3]);
		return;
	} else if(stricmp(av[3],"Vop")==0) {
		c->memolevel = VOP_LIST;
		notice(cs_name,src,CS_RPL_SET_MEMOLEVEL_SUCCESS,chan,av[3]);
		return;
	} else if(stricmp(av[3],"Hop")==0) {
		c->memolevel = HOP_LIST;
		notice(cs_name,src,CS_RPL_SET_MEMOLEVEL_SUCCESS,chan,av[3]);
		return;
	} else if(stricmp(av[3],"Aop")==0) {
		c->memolevel = AOP_LIST;
		notice(cs_name,src,CS_RPL_SET_MEMOLEVEL_SUCCESS,chan,av[3]);
		return;
	} else if(stricmp(av[3],"Sop")==0) {
		c->memolevel = SOP_LIST;
		notice(cs_name,src,CS_RPL_SET_MEMOLEVEL_SUCCESS,chan,av[3]);
		return;
	} else if(stricmp(av[3],"Admin")==0) {
		c->memolevel = ADMIN_LIST;
		notice(cs_name,src,CS_RPL_SET_MEMOLEVEL_SUCCESS,chan,av[3]);
		return;
	} else if(stricmp(av[3],"Owner")==0) {
		c->memolevel = OWNER_LIST;
		notice(cs_name,src,CS_RPL_SET_MEMOLEVEL_SUCCESS,chan,av[3]);
		return;
	} else if(stricmp(av[3],"Successor")==0) {
		c->memolevel = SUCCESSOR_ACC;
		notice(cs_name,src,CS_RPL_SET_MEMOLEVEL_SUCCESS,chan,av[3]);
		return;
	} else if(stricmp(av[3],"FOUNDER")==0) {
		c->memolevel = FOUNDER_ACC;
		notice(cs_name,src,CS_RPL_SET_MEMOLEVEL_SUCCESS,chan,av[3]);
		return;
	} else {
		notice(cs_name, src, CS_ERR_SET_MEMOLEVEL_USAGE);
		notice(cs_name,src,CS_RPL_HLP,cs_name,"SET MEMOLEVEL");
		return;
	}
}

void cs_set_mlock(char *src,int ac,char **av) {
	ChanInfo *c;
	char *chan;
	char *mode = (char*)malloc(sizeof(char*)*128);
	user *u = finduser(src);
	if (ac <= 3) {
		notice(cs_name, src, CS_ERR_SET_MLOCK_USAGE);
		notice(cs_name,src,CS_RPL_HLP,cs_name,"SET MLOCK");
		return;
	}
	chan = sstrdup(av[1]);
	mode = sstrdup(av[3]);
	if(!isregcs(chan)) {
		notice(cs_name,src,CS_ERR_NOTREG,chan);
		return;
	}
	c = findchan(chan);
	if(cs_xop_get_level(u,c)<FOUNDER) {
		notice(cs_name,src,CS_ERR_ACCESSDENIED,chan);
		notice(cs_name,src,CS_RPL_NEEDIDENTIFY,chan);
		return;
	}
	/* those modes must not be removed from modelock */
	if(!strchr(mode,'r')) {
		strcat(mode,"r");
	}
	if(!strchr(mode,'t')) {
		strcat(mode,"t");
	}
	if(!strchr(mode,'n')) {
		strcat(mode,"n");
	}
	c->mlock = sstrdup(mode);
	notice(cs_name,src,CS_RPL_SET_MLOCK_SUCCESS,chan,mode);
	return;
}
void cs_set_opwatch(char *src,int ac,char **av) {
	ChanInfo *c;
	char *chan;
	user *u = finduser(src);
	if (ac <= 3) {
		notice(cs_name, src, CS_ERR_SET_OPWATCH_USAGE);
		notice(cs_name,src,CS_RPL_HLP,cs_name,"SET OPWATCH");
		return;
	}
	chan = av[1];
	if(!isregcs(chan)) {
		notice(cs_name,src,CS_ERR_NOTREG,chan);
		return;
	}
	c = findchan(chan);
	if(cs_xop_get_level(u,c)<FOUNDER) {
		notice(cs_name,src,CS_ERR_ACCESSDENIED,chan);
		notice(cs_name,src,CS_RPL_NEEDIDENTIFY,chan);
		return;
	}
	if(stricmp(av[3],"ON")==0) {
		c->opwatch = 1;
		c->leaveops = 0;
		notice(cs_name,src,CS_RPL_SET_OPWATCH_ENABLE,chan);
		return;
	} else if(stricmp(av[3],"OFF")==0) {
		c->opwatch = 0;
		c->leaveops = 1;
		notice(cs_name,src,CS_RPL_SET_OPWATCH_DISABLE,chan);
		return;
	} else {
		notice(cs_name, src, CS_ERR_SET_OPWATCH_USAGE);
		notice(cs_name,src,CS_RPL_HLP,cs_name,"SET OPWATCH");
		return;
	}
}
void cs_set_password(char *src,int ac,char **av) {
	ChanInfo *c;
	char *chan;
	char *pass;
	user *u = finduser(src);
	if (ac <= 3) {
		notice(cs_name, src, CS_ERR_SET_PASSWORD_USAGE);
		notice(cs_name,src,CS_RPL_HLP,cs_name,"SET PASSWORD");
		return;
	}
	chan = sstrdup(av[1]);
	pass = sstrdup(av[3]);
	if(!isregcs(chan)) {
		notice(cs_name,src,CS_ERR_NOTREG,chan);
		return;
	}
	c = findchan(chan);
	if(cs_xop_get_level(u,c)<FOUNDER) {
		notice(cs_name,src,CS_ERR_ACCESSDENIED,chan);
		notice(cs_name,src,CS_RPL_NEEDIDENTIFY,chan);
		return;
	}
	if (strlen(pass) < 5) {
		notice(ns_name, src, NS_ERR_REG_PASSTOOSHORT);
		notice(ns_name, src, CS_RPL_HLP, cs_name,"SET PASSWORD");
		return;
	}
	/* the password shouldn't be the same as the channel */
	if (stricmp(pass, chan) == 0) {
		notice(ns_name, src, CS_ERR_REG_PASSSAMEASCHAN);
		notice(ns_name, src, CS_RPL_HLP, cs_name,"SET PASSWORD");
		return;
	}
	strscpy(c->pass,pass,PASSMAX);
	notice(cs_name,src,CS_RPL_SET_PASS_SUCCESS,chan,pass);
	return;
}
void cs_set_restricted(char *src,int ac,char **av) {
	ChanInfo *c;
	char *chan;
	user *u = finduser(src);
	if (ac <= 3) {
		notice(cs_name, src, CS_ERR_SET_RESTRICTED_USAGE);
		notice(cs_name,src,CS_RPL_HLP,cs_name,"SET RESTRICTED");
		return;
	}
	chan = av[1];
	if(!isregcs(chan)) {
		notice(cs_name,src,CS_ERR_NOTREG,chan);
		return;
	}
	c = findchan(chan);
	if(cs_xop_get_level(u,c)<FOUNDER) {
		notice(cs_name,src,CS_ERR_ACCESSDENIED,chan);
		notice(cs_name,src,CS_RPL_NEEDIDENTIFY,chan);
		return;
	}
	if(stricmp(av[3],"ON")==0) {
		c->restricted = 1;
		notice(cs_name,src,CS_RPL_SET_RESTRICTED_ENABLE,chan);
		return;
	} else if(stricmp(av[3],"OFF")==0) {
		c->restricted = 0;
		notice(cs_name,src,CS_RPL_SET_RESTRICTED_DISABLE,chan);
		return;
	} else {
		notice(cs_name, src, CS_ERR_SET_KEEPTOPIC_USAGE);
		notice(cs_name,src,CS_RPL_HLP,cs_name,"SET RESTRICTED");
		return;
	}
}
void cs_set_successor(char *src,int ac,char **av) {
	ChanInfo *c;
	char *chan,*nick;
	user *u = finduser(src);
	if (ac <= 3) {
		notice(cs_name, src, CS_ERR_SET_SUCCESSOR_USAGE);
		notice(cs_name,src,CS_RPL_HLP,cs_name,"SET SUCCESSOR");
		return;
	}
	chan = av[1];
	nick = av[3];
	if(!isregcs(chan)) {
		notice(cs_name,src,CS_ERR_NOTREG,chan);
		return;
	}
	c = findchan(chan);
	if(cs_xop_get_level(u,c)<FOUNDER) {
		notice(cs_name,src,CS_ERR_ACCESSDENIED,chan);
		notice(cs_name,src,CS_RPL_NEEDIDENTIFY,chan);
		return;
	}
	if(!isreg(nick)) {
		notice(cs_name,src,NS_ERR_NOTREG,nick);
		notice(cs_name,src,CS_ERR_SET_SUCC_REG);
		return;
	}
	NickInfo *n = findnick(nick);
	c->successor = n;
	notice(cs_name,src,CS_RPL_SET_SUCC_SUCCESS,nick,chan);
	return;
}
void cs_set_topiclock(char *src,int ac,char **av) {
	ChanInfo *c;
	char *chan;
	user *u = finduser(src);
	if (ac <= 3) {
		notice(cs_name, src, CS_ERR_SET_TOPICLOCK_USAGE);
		notice(cs_name,src,CS_RPL_HLP,cs_name,"SET TOPICLOCK");
		return;
	}
	chan = av[1];
	if(!isregcs(chan)) {
		notice(cs_name,src,CS_ERR_NOTREG,chan);
		return;
	}
	c = findchan(chan);
	if(cs_xop_get_level(u,c)<FOUNDER) {
		notice(cs_name,src,CS_ERR_ACCESSDENIED,chan);
		notice(cs_name,src,CS_RPL_NEEDIDENTIFY,chan);
		return;
	}
	if(stricmp(av[3],"Uop")==0) {
		c->topiclock = UOP_LIST;
		notice(cs_name,src,CS_RPL_SET_TOPICLOCK_SUCCESS,chan,av[3]);
		return;
	} else if(stricmp(av[3],"Vop")==0) {
		c->topiclock = VOP_LIST;
		notice(cs_name,src,CS_RPL_SET_TOPICLOCK_SUCCESS,chan,av[3]);
		return;
	} else if(stricmp(av[3],"Hop")==0) {
		c->topiclock = HOP_LIST;
		notice(cs_name,src,CS_RPL_SET_TOPICLOCK_SUCCESS,chan,av[3]);
		return;
	} else if(stricmp(av[3],"Aop")==0) {
		c->topiclock = AOP_LIST;
		notice(cs_name,src,CS_RPL_SET_TOPICLOCK_SUCCESS,chan,av[3]);
		return;
	} else if(stricmp(av[3],"Sop")==0) {
		c->topiclock = SOP_LIST;
		notice(cs_name,src,CS_RPL_SET_TOPICLOCK_SUCCESS,chan,av[3]);
		return;
	} else if(stricmp(av[3],"Admin")==0) {
		c->topiclock = ADMIN_LIST;
		notice(cs_name,src,CS_RPL_SET_TOPICLOCK_SUCCESS,chan,av[3]);
		return;
	} else if(stricmp(av[3],"Owner")==0) {
		c->topiclock = OWNER_LIST;
		notice(cs_name,src,CS_RPL_SET_TOPICLOCK_SUCCESS,chan,av[3]);
		return;
	} else if(stricmp(av[3],"Successor")==0) {
		c->topiclock = SUCCESSOR_ACC;
		notice(cs_name,src,CS_RPL_SET_TOPICLOCK_SUCCESS,chan,av[3]);
		return;
	} else if(stricmp(av[3],"FOUNDER")==0) {
		c->topiclock = FOUNDER_ACC;
		notice(cs_name,src,CS_RPL_SET_TOPICLOCK_SUCCESS,chan,av[3]);
		return;
	} else if(stricmp(av[3],"Off")==0) {
		c->topiclock = 0;
		notice(cs_name,src,CS_RPL_SET_TOPICLOCK_DISABLE,chan);
		return;
	} else {
		notice(cs_name, src, CS_ERR_SET_KEEPTOPIC_USAGE);
		notice(cs_name,src,CS_RPL_HLP,cs_name,"SET TOPICLOCK");
		return;
	}
}

