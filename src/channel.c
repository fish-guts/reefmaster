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

static channel *new_channel(const char *chan);
static void chan_adduser(user *u, channel *c);
static channel *join_user_update(user *u, channel *c, char *name);

static channel *chanlist = NULL;

int chan_count;

channel *findchannel(const char *chan) {
	channel *c = chanlist;
	while (c && stricmp(c->name, chan) != 0)
		c = c->next;
	return c;
}
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
	if (isreg(chan) >= 0)
		mode(cs_name, c->name, "+rtn", NULL);
	return c;
}

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
		if (*t)
			*t++ = 0;
		join_user_update(u, findchannel(s), s);
		check_status(findchannel(s),u);
	}
}

static void chan_adduser(user *u, channel *c) {
	struct chanusers *cu;
	struct userchans *uc;
	cu = scalloc(sizeof(struct chanusers), 1);
	uc = scalloc(sizeof(struct userchans), 1);
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
void check_status(channel *c, user *u) {
	if (isregcs(c->name)) {
		ChanInfo *cs = findchan(c->name);
		if (isreg(u->nick)) {
			NickInfo *n = findnick(u->nick);
			int level = cs_xop_get_level(u, cs);
			if (level >= OWNER_LIST) {
				if (n->noop)
					return;
				do_owner(cs_name, u->nick, c->name);
				add_status(c, u, OWNER);
			} else if (level >= ADMIN_LIST) {
				if (n->noop)
					return;
				do_admin(cs_name, u->nick, c->name);
				add_status(c, u, OWNER);
			} else if (level >= AOP_LIST) {
				if (n->noop)
					return;
				do_op(cs_name, u->nick, c->name);
				add_status(c, u, OP);
				return;
			} else if (level >= HOP_LIST) {
				if (n->noop)
					return;
				hop(cs_name, u->nick, c->name);
				return;
			} else if (level >= VOP_LIST) {
				if (!cs->autovop)
					return;
				voice(cs_name, u->nick, c->name);
				return;
			}
		}
		op *o = cs_akick_match(u, cs);
		if (o) {
			char *reason = (char*) malloc(sizeof(char*) * 256);
			sprintf(reason, CS_RPL_AKICK_KICKREASON, o->reason);
			kick(cs_name, u->nick, cs->name, reason);
			ban(cs_name, o->nick, cs->name);
		}
	}
}
int ison(channel *c, user *u) {
	struct userchans *uc;
	for (uc = u->chans; uc; uc = uc->next)
		if (uc->chan == c)
			return 1;
	return 0;

}
int isop(channel *c, user *u) {
	struct userchans *uc;
	for (uc = u->chans; uc; uc = uc->next) {
		if (uc->chan == c) {
			if ((uc->status == OP) || (uc->status == OWNER)
					|| (uc->status == POP))
				return 1;
		}
	}
	return 0;
}
void add_status(channel *c, user *u, int status) {
	struct userchans *uc;
	for (uc = u->chans; uc; uc = uc->next) {
		if (uc->chan == c) {
			uc->status |= status;
			break;
		}
	}
}
void del_status(channel *c, user *u, int status) {
	struct userchans *uc;
	for (uc = u->chans; uc; uc = uc->next) {
		if (uc->chan == c) {
			uc->status &= ~status;
			break;
		}
	}
}
static channel *join_user_update(user *u, channel *c, char *name) {
	/* If it's a new channel, we need to create it first. */
	if (!c)
		c = new_channel(name);
	chan_adduser(u, c);
	return c;
}
void s_part(char *src, int ac, char **av) {
	del_user(finduser(src),findchannel(av[0]));
}
void del_user(user *u, channel *c) {
	struct chanusers *cu;
	struct userchans *uc;
	cu = c->users;
	uc = u->chans;
	if (cu->prev)
		cu->prev->next = cu->next;
	else
		c->users = cu->next;
	if (cu->next)
		cu->next->prev = cu->prev;
	free(cu);
	c->ucnt--;

	if (uc->prev)
		uc->prev->next = uc->next;
	else
		u->chans = uc->next;
	if (uc->next)
		uc->next->prev = uc->prev;
	free(uc);
	u->chan_count--;


	if(!c->users)
	 chan_delete(c);
}
void chan_delete(channel *c) {
	if (c->prev)
		c->prev->next = c->next;
	else
		chanlist = c->next;
	if (c->next)
		c->next->prev = c->prev;
	free(c);
}
/* EOF */
