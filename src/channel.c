/*
 *      channel.c - severin
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

static void chan_adduser(user *u, channel *c);
static channel *join_user_update(user *u, channel *c, char *name);
static channel *new_channel(const char *chan);

channel *chanlist = NULL;
int chan_count;

/********************************************************************/
/**
 * add a bot to a channel
 */
void add_bot(char *chan, char *bot) {
	channel *c = findchannel(chan);
	if(!c)
		c = new_channel(chan);
	c->bot = sstrdup(bot);
}

/********************************************************************/
/**
 * add a status to a user on a channel
 */
void add_status(channel *c, user *u, int status) {
	userchan *uc;
	for (uc = u->chans; uc; uc = uc->next) {
		if (uc->chan == c) {
			uc->status |= status;
			break;
		}
	}
}

/********************************************************************/
/**
 * add a user/channel assginment
 */
static void chan_adduser(user *u, channel *c) {
	chanuser *cu = scalloc(sizeof(chanuser), 1);
	userchan *uc = scalloc(sizeof(userchan), 1);

	cu->next = c->users;
	if (c->users)
		c->users->prev = cu;
	c->users = cu;
	cu->u = u;

	uc->next = u->chans;
	if (u->chans)
		u->chans->prev = uc;
	u->chans = uc;
	uc->chan = c;
	c->ucnt++;
	return;
}

/********************************************************************/
/**
 * add a channel/ban assignment
 */
void channel_add_ban(char *src,channel *c, char *mask) {
	chanban *b = scalloc(sizeof(chanban),1);
	b->next = c->banlist;
	if(c->banlist)
		c->banlist->prev = b;
	c->banlist = b;
	b->mask = sstrdup(mask);
	b->from = sstrdup(src);
	return;
}

/********************************************************************/
/**
 * remove a channel from the channel list
 */
void chan_delete(channel *c) {
	if (c->prev) {
		c->prev->next = c->next;
	} else {
		chanlist = c->next;
	}
	if (c->next) {
		c->next->prev = c->prev;
	}
	free(c);
}

/********************************************************************/
/**
 * remove a channel/ban assignment
 */
void channel_remove_ban(char *src,channel *c, char *mask) {
	chanban *b = c->banlist;
	while (b) {
		if (stricmp(mask,b->mask) == 0) {
			if (b->prev)
				b->prev->next = b->next;
			else
				c->banlist = b->next;
			if (b->next)
				b->next->prev = b->prev;
			free(b);
		}
		b = b->next;
	}
}

/********************************************************************/
/**
 * the user's status on a channel
 */
void check_status(channel *c, user *u) {
	if (isregcs(c->name)) {
		ChanInfo *cs = findchan(c->name);
		if (isreg(u->nick)) {
			NickInfo *n = findnick(u->nick);
			int level = cs_xop_get_level(u, cs);
			if (level >= AOP_LIST) {
				if (n->noop)  {
					return;
				}
				do_op(cs_name, u->nick, c->name);
				add_status(c, u, OP);
				return;

			} else if (level >= HOP_LIST) {
				if (n->noop) {
					return;
				}
				hop(cs_name, u->nick, c->name);
				return;
			} else if (level >= VOP_LIST) {
				if (!cs->autovop)
					return;
				voice(cs_name, u->nick, c->name);
				return;
			}
		}
		akick *ak = cs_akick_match(u, cs);
		if (ak) {
			char *reason = (char*) malloc(sizeof(char*) * 256);
			sprintf(reason, CS_AKICK_RPL_KICKREASON, ak->reason);
			kick(cs_name, u->nick, cs->name, reason);
			ban(cs_name, ak->mask, cs->name);
		}
	}
}

/********************************************************************/
/**
 * remove a bot from a channel
 */
void del_bot(char *chan) {
	channel *c = findchannel(chan);
	c->bot = NULL;
}

/********************************************************************/
/**
 * remove a user's status on a channel
 */
void del_status(channel *c, user *u, int status) {
	userchan *uc;
	for (uc = u->chans; uc; uc = uc->next) {
		if (uc->chan == c) {
			uc->status &= ~status;
			break;
		}
	}
}

/********************************************************************/
/**
 * remove a user from a channel
 */
void del_user(user *u, channel *c) {
	chanuser *cu;
	userchan *uc;

	cu = c->users;
	if (cu->prev) {
		cu->prev->next = cu->next;
	} else {
		c->users = cu->next;
	}

	if (cu->next) {
		cu->next->prev = cu->prev;
	}
	free(cu);
	c->ucnt--;

	uc = u->chans;
	if (uc->prev) {
		uc->prev->next = uc->next;

	} else {
		u->chans = uc->next;
	}
	if (uc->next) {
		uc->next->prev = uc->prev;
	}
	free(uc);
	u->chan_count--;

	if(!c->users) {
		chan_delete(c);
	}

}

/********************************************************************/
/**
 * find a channel in the channel list
 */
channel *findchannel(const char *chan) {
	channel *c = chanlist;

	while (c && stricmp(c->name, chan) != 0) {
		c = c->next;
	}
	return c;
}

/********************************************************************/
/**
 * check whether the specified bot is on the specified channel
 */
int is_bot_on_chan(char *botname,char *chan) {
	channel *c = findchannel(chan);
	if((c) && (c->bot) && (stricmp(c->bot,botname)==0)) {
		return 1;
	}
	return 0;
}

/********************************************************************/
/**
 * check whether a user is on a channel
 */
int ison(channel *c, user *u) {
	userchan *uc;
	for (uc = u->chans; uc; uc = uc->next)
		if (uc->chan == c)
			return 1;
	return 0;
}

/********************************************************************/
/**
 * check whether a user has operator status on a channel
 */
int isop(channel *c, user *u) {
	userchan *uc;
	for (uc = u->chans; uc; uc = uc->next) {
		if (uc->chan == c) {
			if ((uc->status == OP) || (uc->status == OWNER)
					|| (uc->status == ADMIN))
				return 1;
		}
	}
	return 0;
}

/********************************************************************/
/**
 * update on join
 */
static channel *join_user_update(user *u, channel *c, char *name) {
	/* If it's a new channel, we need to create it first. */
	if (!c) {
		c = new_channel(name);
	}
	chan_adduser(u, c);
	return c;
}

/********************************************************************/
/**
 * create a new channel and add it to the list
 */
static channel *new_channel(const char *chan) {
	channel *c;
	c = scalloc(sizeof(channel), 1);
	if (!chan)
		chan = "";
	c->name = sstrdup(chan);
	c->next = chanlist;
	c->ops = 0;
	c->vops = 0;
	c->pus = 0;
	c->owners = 0;
	c->ucnt = 0;
	c->topic = "";
	if (chanlist)
		chanlist->prev = c;
	chanlist = c;
	chan_count++;
	if (isregcs(chan)) {
		ChanInfo *c2 = findchan(chan);
		mode(cs_name, c->name, "+rtn", NULL);
		if(c2->topic) {
			topic(cs_name,c2->name,c2->topic_user,c2->topic_time,c2->topic);
			c->topic = sstrdup(c2->topic);
			c->topic_user = sstrdup(c2->topic_user);
			c->topic_time = c2->topic_time;
		}
		if(c2->bot_id > 0) {
			add_bot_to_chan(find_bot_by_id(c2->bot_id)->name,c2->name);
		}
	}
	return c;
}

/********************************************************************/
/**
 * handle the server's JOIN command
 */
void s_join(char *src, int ac, char **av) {
	user *u;
	char *s, *t;
	u = finduser(src);
	if (!u) {
		addlog(2, LOG_DBG_JOINNONEXIST, s_unreal, src);
		return;
	}
	t = av[0];
	while (*(s = t)) {
		t = s + strcspn(s, ",");
		if (*t) {
			*t++ = 0;
		}
		join_user_update(u, findchannel(s), s);
		if(isregcs(s)) {
			mode(cs_name,s,"+rtn",s);
			if(u->is_bot) {
				do_op(cs_name,u->nick,s);
			}
		}
		check_status(findchannel(s),u);
	}
}

/********************************************************************/
/**
 * handle the Server's PART command
 */
void s_part(char *src, int ac, char **av) {
	user *u = finduser(src);
	del_user(u,findchannel(av[0]));

}
/* EOF */
