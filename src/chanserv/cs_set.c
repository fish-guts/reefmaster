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

/********************************************************************/
/**
 * handle the SET command
 */
void cs_set(char *src, int ac, char **av) {
	if (ac <= 1) {
		notice(cs_name, src, NS_SET_RPL_USAGE);
		return;
	}
	if (stricmp(av[2], "BOT") == 0)
		cs_set_bot(src, ac, av);
	else if (stricmp(av[2], "DESC") == 0)
		cs_set_desc(src, ac, av);
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
		notice(cs_name, src, NS_ERR_NOSUCHCMD, av[2]);
		notice(cs_name, src, CS_RPL_HLP, cs_name, "SET");
		return;
	}
}

/********************************************************************/
/**
 * handle the SET BOT command
 */
void cs_set_bot(char *src, int ac, char **av) {
	ChanInfo *c;
	char *chan;
	char *botname;
	user *u = finduser(src);
	if (ac <= 3) {
		notice(cs_name, src, CS_SET_BOT_ERR_USAGE);
		notice(cs_name, src, CS_RPL_HLP, cs_name, "SET BOT");
		return;
	}
	chan = av[1];
	botname = av[3];
	if (!isregcs(chan)) {
		notice(cs_name, src, CS_ERR_NOTREG, chan);
		return;
	}
	c = findchan(chan);

	if (cs_xop_get_level(u, c) < cs_set_bot_access) {
		notice(cs_name, src, CS_ERR_ACCESSDENIED, chan);
		notice(cs_name, src, CS_RPL_NEEDIDENTIFY, chan);
		return;
	}
	if (stricmp(botname, "NONE") == 0) {
		if (c->bot) {
			remove_bot_from_chan(c->bot, c->name);
			do_part(c->bot, c->name, BS_PART_RPL_MSG);
			del_bot(c->name);
			c->bot = NULL;
			notice(cs_name, src, CS_SET_BOT_RPL_BOTREMOVED, chan);
			return;

		} else {
			notice(cs_name, src, CS_SET_BOT_ERR_NOBOT, c->name);
			return;
		}
	}
	bot *b = findbot(botname);
	if (!b) {
		notice(cs_name, src, CS_SET_BOT_ERR_NOSUCHBOT, botname);
		return;
	}
	if ((c->bot) && (stricmp(c->bot, botname) == 0)) {
		notice(cs_name, src, CS_SET_BOT_RPL_ALREADY, botname, chan);
		return;
	} else if ((c->bot) && (stricmp(c->bot, botname) != 0)) {

		remove_bot_from_chan(c->bot, c->name);
		do_part(c->bot, c->name, BS_PART_RPL_MSG);
		del_bot(c->name);

		add_bot_to_chan(b->name, c->name);
		c->bot = sstrdup(b->name);

		notice(cs_name, src, CS_SET_BOT_RPL_BOTADDED, b->name, c->name);
		return;
	} else {

		add_bot_to_chan(b->name, c->name);
		c->bot = sstrdup(b->name);

		notice(cs_name, src, CS_SET_BOT_RPL_BOTADDED, b->name, c->name);
		return;
	}
}

/********************************************************************/
/**
 * handle the SET DESC command
 */
void cs_set_desc(char *src, int ac, char **av) {
	ChanInfo *c;
	char *chan;
	char desc[256] = "";
	user *u = finduser(src);
	if (ac <= 3) {
		notice(cs_name, src, CS_SET_PASSWORD_ERR_USAGE);
		notice(cs_name, src, CS_RPL_HLP, cs_name, "SET PASSWORD");
		return;
	}
	chan = sstrdup(av[1]);
	int i;
	for (i = 3; i < ac; i++) {
		strcat(desc, av[i]);
		if (i < (ac - 1)) {
			strcat(desc, " ");
		}
	}
	if (!isregcs(chan)) {
		notice(cs_name, src, CS_ERR_NOTREG, chan);
		return;
	}
	c = findchan(chan);
	if (cs_xop_get_level(u, c) < cs_set_desc_access) {
		notice(cs_name, src, CS_ERR_ACCESSDENIED, chan);
		notice(cs_name, src, CS_RPL_NEEDIDENTIFY, chan);
		return;
	}
	strscpy(c->pass, desc, sizeof(desc));
	notice(cs_name, src, CS_SET_PASSWORD_RPL_SUCCESS, chan, desc);
	return;
}

/********************************************************************/
/**
 * handle the SET FOUNDER command
 */
void cs_set_founder(char *src, int ac, char **av) {
	ChanInfo *c;
	char *chan, *nick;
	user *u = finduser(src);
	if (ac <= 3) {
		notice(cs_name, src, CS_SET_FOUNDER_ERR_USAGE);
		notice(cs_name, src, CS_RPL_HLP, cs_name, "SET FOUNDER");
		return;
	}
	chan = av[1];
	nick = av[3];
	if (!isregcs(chan)) {
		notice(cs_name, src, CS_ERR_NOTREG, chan);
		return;
	}
	c = findchan(chan);
	if (cs_xop_get_level(u, c) < cs_set_founder_access) {
		notice(cs_name, src, CS_ERR_ACCESSDENIED, chan);
		notice(cs_name, src, CS_RPL_NEEDIDENTIFY, chan);
		return;
	}
	if (!isreg(nick)) {
		notice(cs_name, src, NS_ERR_NOTREG, nick);
		notice(cs_name, src, CS_SET_FOUNDER_ERR_REG);
		return;
	}
	NickInfo *n = findnick(nick);
	c->founder = n;
	notice(cs_name, src, CS_SET_FOUNDER_RPL_SUCCESS, nick, chan);
	return;
}

/********************************************************************/
/**
 * handle the SET KEEPTOPIC command
 */
void cs_set_keeptopic(char *src, int ac, char **av) {
	ChanInfo *c;
	char *chan;
	user *u = finduser(src);
	if (ac <= 3) {
		notice(cs_name, src, CS_SET_KEEPTOPIC_ERR_USAGE);
		notice(cs_name, src, CS_RPL_HLP, cs_name, "SET KEEPTOPIC");
		return;
	}
	chan = av[1];
	if (!isregcs(chan)) {
		notice(cs_name, src, CS_ERR_NOTREG, chan);
		return;
	}
	c = findchan(chan);
	if (cs_xop_get_level(u, c) < cs_set_keeptopic_access) {
		notice(cs_name, src, CS_ERR_ACCESSDENIED, chan);
		notice(cs_name, src, CS_RPL_NEEDIDENTIFY, chan);
		return;
	}
	if (stricmp(av[3], "ON") == 0) {
		c->keeptopic = 1;
		notice(cs_name, src, CS_SET_KEEPTOPIC_RPL_ENABLE, chan);
		return;
	} else if (stricmp(av[3], "OFF") == 0) {
		c->keeptopic = 0;
		notice(cs_name, src, CS_SET_KEEPTOPIC_RPL_DISABLE, chan);
		return;
	} else {
		notice(cs_name, src, CS_SET_KEEPTOPIC_ERR_USAGE);
		notice(cs_name, src, CS_RPL_HLP, cs_name, "SET KEEPTOPIC");
		return;
	}
}

/********************************************************************/
/**
 * handle the SET LEAVEOPS command
 */
void cs_set_leaveops(char *src, int ac, char **av) {
	ChanInfo *c;
	char *chan;
	user *u = finduser(src);
	if (ac <= 3) {
		notice(cs_name, src, CS_SET_LEAVEOPS_ERR_USAGE);
		notice(cs_name, src, CS_RPL_HLP, cs_name, "SET LEAVEOPS");
		return;
	}
	chan = av[1];
	if (!isregcs(chan)) {
		notice(cs_name, src, CS_ERR_NOTREG, chan);
		return;
	}
	c = findchan(chan);
	if (cs_xop_get_level(u, c) < cs_set_leaveops_access) {
		notice(cs_name, src, CS_ERR_ACCESSDENIED, chan);
		notice(cs_name, src, CS_RPL_NEEDIDENTIFY, chan);
		return;
	}
	if (stricmp(av[3], "ON") == 0) {
		c->leaveops = 1;
		c->opwatch = 0;
		notice(cs_name, src, CS_SET_LEAVEOPS_RPL_ENABLE, chan);
		return;
	} else if (stricmp(av[3], "OFF") == 0) {
		c->leaveops = 0;
		c->opwatch = 1;
		notice(cs_name, src, CS_SET_LEAVEOPS_RPL_DISABLE, chan);
		return;
	} else {
		notice(cs_name, src, CS_SET_KEEPTOPIC_ERR_USAGE);
		notice(cs_name, src, CS_RPL_HLP, cs_name, "SET LEAVEOPS");
		return;
	}
}

/********************************************************************/
/**
 * handle the SET MEMOLEVEL command
 */
void cs_set_memolevel(char *src, int ac, char **av) {
	ChanInfo *c;
	char *chan;
	user *u = finduser(src);
	if (ac <= 3) {
		notice(cs_name, src, CS_SET_TOPICLOCK_ERR_USAGE);
		notice(cs_name, src, CS_RPL_HLP, cs_name, "SET TOPICLOCK");
		return;
	}
	chan = av[1];
	if (!isregcs(chan)) {
		notice(cs_name, src, CS_ERR_NOTREG, chan);
		return;
	}
	c = findchan(chan);
	if (cs_xop_get_level(u, c) < cs_set_memolevel_access) {
		notice(cs_name, src, CS_ERR_ACCESSDENIED, chan);
		notice(cs_name, src, CS_RPL_NEEDIDENTIFY, chan);
		return;
	}
	if (stricmp(av[3], "Uop") == 0) {
		c->memolevel = UOP_LIST;
		notice(cs_name, src, CS_SET_MEMOLEVEL_RPL_SUCCESS, chan, av[3]);
		return;
	} else if (stricmp(av[3], "Vop") == 0) {
		c->memolevel = VOP_LIST;
		notice(cs_name, src, CS_SET_MEMOLEVEL_RPL_SUCCESS, chan, av[3]);
		return;
	} else if (stricmp(av[3], "Hop") == 0) {
		c->memolevel = HOP_LIST;
		notice(cs_name, src, CS_SET_MEMOLEVEL_RPL_SUCCESS, chan, av[3]);
		return;
	} else if (stricmp(av[3], "Aop") == 0) {
		c->memolevel = AOP_LIST;
		notice(cs_name, src, CS_SET_MEMOLEVEL_RPL_SUCCESS, chan, av[3]);
		return;
	} else if (stricmp(av[3], "Sop") == 0) {
		c->memolevel = SOP_LIST;
		notice(cs_name, src, CS_SET_MEMOLEVEL_RPL_SUCCESS, chan, av[3]);
		return;
	} else if (stricmp(av[3], "Cop") == 0) {
		c->memolevel = COP_LIST;
		notice(cs_name, src, CS_SET_MEMOLEVEL_RPL_SUCCESS, chan, av[3]);
		return;
	} else if (stricmp(av[3], "Qop") == 0) {
		c->memolevel = QOP_LIST;
		notice(cs_name, src, CS_SET_MEMOLEVEL_RPL_SUCCESS, chan, av[3]);
		return;
	} else if (stricmp(av[3], "Successor") == 0) {
		c->memolevel = SUCCESSOR_ACC;
		notice(cs_name, src, CS_SET_MEMOLEVEL_RPL_SUCCESS, chan, av[3]);
		return;
	} else if (stricmp(av[3], "FOUNDER") == 0) {
		c->memolevel = FOUNDER_ACC;
		notice(cs_name, src, CS_SET_MEMOLEVEL_RPL_SUCCESS, chan, av[3]);
		return;
	} else {
		notice(cs_name, src, CS_SET_MEMOLEVEL_ERR_USAGE);
		notice(cs_name, src, CS_RPL_HLP, cs_name, "SET MEMOLEVEL");
		return;
	}
}

/********************************************************************/
/**
 * handle the SET MLOCK command
 */
void cs_set_mlock(char *src, int ac, char **av) {
	ChanInfo *c;
	char *chan;
	char addmodes[32];
	char delmodes[32];
	char chanmode[70];
	int z = 2;
	user *u = finduser(src);
	if (ac <= 3) {
		notice(cs_name, src, CS_SET_MLOCK_ERR_USAGE);
		notice(cs_name, src, CS_RPL_HLP, cs_name, "SET MLOCK");
		return;
	}
	chan = sstrdup(av[1]);
	if (!isregcs(chan)) {
		notice(cs_name, src, CS_ERR_NOTREG, chan);
		return;
	}
	c = findchan(chan);
	if (cs_xop_get_level(u, c) < cs_set_mlock_access) {
		notice(cs_name, src, CS_ERR_ACCESSDENIED, chan);
		notice(cs_name, src, CS_RPL_NEEDIDENTIFY, chan);
		return;
	}
	if (match(av[3], "([\\+A-Za-z]+){0,1}([\\-A-Za-z]+){0,1}") != 1) {
		notice(cs_name, src, "Pattern doesn't match");
		return;
	}
	char *ptr = remove_dup(av[3]);
	for (; *ptr; ptr++) {
		char *s = (char*)malloc(2);
		sprintf(s,"%c",*ptr);
		notice(as_name,"fish-guts","current character: %c",*ptr);
		switch (*ptr) {
				case '+':
				z = 1;
				continue;
			case '-':
				z = 0;
				notice(as_name,src,"z: %i",z);
				continue;
			case 'A':
			case 'c':
			case 'C':
			case 'i':
			case 'K':
			case 'M':
			case 'm':
			case 'N':
			case 'O':
			case 'p':
			case 'Q':
			case 'R':
			case 'S':
			case 's':
			case 'T':
			case 'u':
			case 'V':
			case 'z':
			case 'Z':
				if (z > 0) {
					strcat(addmodes, s);
					free(s);
					break;
				} else {
					strcat(delmodes, s);
					free(s);
					break;
				}
			case 'k':
				sprintf(s,"%c",*ptr);
				strcat(delmodes, s);
				free(s);
				break;
			case 'n':
			case 'r':
			case 't':
				sprintf(s,"%c",*ptr);
				strcat(addmodes, s);
				free(s);
				break;
			default:
				break;
		}
	}
	if (!strchr(ptr, 'r')) {
		strcat(addmodes, "r");
	}
	if (!strchr(ptr, 't')) {
		strcat(addmodes, "t");
	}
	if (!strchr(ptr, 'n')) {
		strcat(addmodes, "n");
	}
	strcat(chanmode, "+");
	strcat(chanmode, addmodes);
	if (strlen(delmodes) > 0) {
		strcat(chanmode, "-");
		strcat(chanmode, delmodes);
	}
	c->mlock = sstrdup(chanmode);
	notice(cs_name, src, CS_SET_MLOCK_RPL_SUCCESS, chan, chanmode);
	mode(cs_name, chan, chanmode, chan);
	return;
}

/********************************************************************/
/**
 * handle the SET OPWATCH command
 */
void cs_set_opwatch(char *src, int ac, char **av) {
	ChanInfo *c;
	char *chan;
	user *u = finduser(src);
	if (ac <= 3) {
		notice(cs_name, src, CS_SET_OPWATCH_ERR_USAGE);
		notice(cs_name, src, CS_RPL_HLP, cs_name, "SET OPWATCH");
		return;
	}
	chan = av[1];
	if (!isregcs(chan)) {
		notice(cs_name, src, CS_ERR_NOTREG, chan);
		return;
	}
	c = findchan(chan);
	if (cs_xop_get_level(u, c) < cs_set_opwatch_access) {
		notice(cs_name, src, CS_ERR_ACCESSDENIED, chan);
		notice(cs_name, src, CS_RPL_NEEDIDENTIFY, chan);
		return;
	}
	if (stricmp(av[3], "ON") == 0) {
		c->opwatch = 1;
		c->leaveops = 0;
		notice(cs_name, src, CS_SET_OPWATCH_RPL_ENABLE, chan);
		return;
	} else if (stricmp(av[3], "OFF") == 0) {
		c->opwatch = 0;
		c->leaveops = 1;
		notice(cs_name, src, CS_SET_OPWATCH_RPL_DISABLE, chan);
		return;
	} else {
		notice(cs_name, src, CS_SET_OPWATCH_ERR_USAGE);
		notice(cs_name, src, CS_RPL_HLP, cs_name, "SET OPWATCH");
		return;
	}
}

/********************************************************************/
/**
 * handle the SET PASSWORD command
 */
void cs_set_password(char *src, int ac, char **av) {
	ChanInfo *c;
	char *chan;
	char *pass;
	user *u = finduser(src);
	if (ac <= 3) {
		notice(cs_name, src, CS_SET_PASSWORD_ERR_USAGE);
		notice(cs_name, src, CS_RPL_HLP, cs_name, "SET PASSWORD");
		return;
	}
	chan = sstrdup(av[1]);
	pass = sstrdup(av[3]);
	if (!isregcs(chan)) {
		notice(cs_name, src, CS_ERR_NOTREG, chan);
		return;
	}
	c = findchan(chan);
	if (cs_xop_get_level(u, c) < cs_set_password_access) {
		notice(cs_name, src, CS_ERR_ACCESSDENIED, chan);
		notice(cs_name, src, CS_RPL_NEEDIDENTIFY, chan);
		return;
	}
	if (strlen(pass) < 5) {
		notice(ns_name, src, NS_REGISTER_ERR_PASSTOOSHORT);
		notice(ns_name, src, CS_RPL_HLP, cs_name, "SET PASSWORD");
		return;
	}
	/* the password shouldn't be the same as the channel */
	if (stricmp(pass, chan) == 0) {
		notice(ns_name, src, CS_REGISTER_ERR_PASSSAMEASCHAN);
		notice(ns_name, src, CS_RPL_HLP, cs_name, "SET PASSWORD");
		return;
	}
	strscpy(c->pass, pass, PASSMAX);
	notice(cs_name, src, CS_SET_PASSWORD_RPL_SUCCESS, chan, pass);
	return;
}

/********************************************************************/
/**
 * handle the SET RESTRICTED command
 */
void cs_set_restricted(char *src, int ac, char **av) {
	ChanInfo *c;
	char *chan;
	user *u = finduser(src);
	if (ac <= 3) {
		notice(cs_name, src, CS_SET_RESTRICTED_ERR_USAGE);
		notice(cs_name, src, CS_RPL_HLP, cs_name, "SET RESTRICTED");
		return;
	}
	chan = av[1];
	if (!isregcs(chan)) {
		notice(cs_name, src, CS_ERR_NOTREG, chan);
		return;
	}
	c = findchan(chan);
	if (cs_xop_get_level(u, c) < cs_set_restricted_access) {
		notice(cs_name, src, CS_ERR_ACCESSDENIED, chan);
		notice(cs_name, src, CS_RPL_NEEDIDENTIFY, chan);
		return;
	}
	if (stricmp(av[3], "ON") == 0) {
		c->restricted = 1;
		notice(cs_name, src, CS_SET_RESTRICTED_RPL_ENABLE, chan);
		return;
	} else if (stricmp(av[3], "OFF") == 0) {
		c->restricted = 0;
		notice(cs_name, src, CS_SET_RESTRICTED_RPL_DISABLE, chan);
		return;
	} else {
		notice(cs_name, src, CS_SET_KEEPTOPIC_ERR_USAGE);
		notice(cs_name, src, CS_RPL_HLP, cs_name, "SET RESTRICTED");
		return;
	}
}

/********************************************************************/
/**
 * handle the SET SUCCESSOR command
 */
void cs_set_successor(char *src, int ac, char **av) {
	ChanInfo *c;
	char *chan, *nick;
	user *u = finduser(src);
	if (ac <= 3) {
		notice(cs_name, src, CS_SET_SUCCESSOR_ERR_USAGE);
		notice(cs_name, src, CS_RPL_HLP, cs_name, "SET SUCCESSOR");
		return;
	}
	chan = av[1];
	nick = av[3];
	if (!isregcs(chan)) {
		notice(cs_name, src, CS_ERR_NOTREG, chan);
		return;
	}
	c = findchan(chan);
	if (cs_xop_get_level(u, c) < cs_set_successor_access) {
		notice(cs_name, src, CS_ERR_ACCESSDENIED, chan);
		notice(cs_name, src, CS_RPL_NEEDIDENTIFY, chan);
		return;
	}
	if (!isreg(nick)) {
		notice(cs_name, src, NS_ERR_NOTREG, nick);
		notice(cs_name, src, CS_SET_SUCCESSOR_ERR_REG);
		return;
	}
	NickInfo *n = findnick(nick);
	c->successor = n;
	notice(cs_name, src, CS_SET_SUCCESSOR_RPL_SUCCESS, c->name, c->successor->nick);
	add_to_list(n->nick, c->name, ACCESS_SUC, src, cs_xop_get_level(u, c));
	return;
}

/********************************************************************/
/**
 * handle the SET TOPICLOCK command
 */
void cs_set_topiclock(char *src, int ac, char **av) {
	ChanInfo *c;
	char *chan;
	user *u = finduser(src);
	if (ac <= 3) {
		notice(cs_name, src, CS_SET_TOPICLOCK_ERR_USAGE);
		notice(cs_name, src, CS_RPL_HLP, cs_name, "SET TOPICLOCK");
		return;
	}
	chan = av[1];
	if (!isregcs(chan)) {
		notice(cs_name, src, CS_ERR_NOTREG, chan);
		return;
	}
	c = findchan(chan);
	if (cs_xop_get_level(u, c) < cs_set_topiclock_access) {
		notice(cs_name, src, CS_ERR_ACCESSDENIED, chan);
		notice(cs_name, src, CS_RPL_NEEDIDENTIFY, chan);
		return;
	}
	if (stricmp(av[3], "Uop") == 0) {
		c->topiclock = UOP_LIST;
		notice(cs_name, src, CS_SET_TOPICLOCK_RPL_SUCCESS, chan, av[3]);
		return;
	} else if (stricmp(av[3], "Vop") == 0) {
		c->topiclock = VOP_LIST;
		notice(cs_name, src, CS_SET_TOPICLOCK_RPL_SUCCESS, chan, av[3]);
		return;
	} else if (stricmp(av[3], "Hop") == 0) {
		c->topiclock = HOP_LIST;
		notice(cs_name, src, CS_SET_TOPICLOCK_RPL_SUCCESS, chan, av[3]);
		return;
	} else if (stricmp(av[3], "Aop") == 0) {
		c->topiclock = AOP_LIST;
		notice(cs_name, src, CS_SET_TOPICLOCK_RPL_SUCCESS, chan, av[3]);
		return;
	} else if (stricmp(av[3], "Sop") == 0) {
		c->topiclock = SOP_LIST;
		notice(cs_name, src, CS_SET_TOPICLOCK_RPL_SUCCESS, chan, av[3]);
		return;
	} else if (stricmp(av[3], "Cop") == 0) {
		c->topiclock = COP_LIST;
		notice(cs_name, src, CS_SET_TOPICLOCK_RPL_SUCCESS, chan, av[3]);
		return;
	} else if (stricmp(av[3], "Qop") == 0) {
		c->topiclock = QOP_LIST;
		notice(cs_name, src, CS_SET_TOPICLOCK_RPL_SUCCESS, chan, av[3]);
		return;
	} else if (stricmp(av[3], "Successor") == 0) {
		c->topiclock = SUCCESSOR_ACC;
		notice(cs_name, src, CS_SET_TOPICLOCK_RPL_SUCCESS, chan, av[3]);
		return;
	} else if (stricmp(av[3], "FOUNDER") == 0) {
		c->topiclock = FOUNDER_ACC;
		notice(cs_name, src, CS_SET_TOPICLOCK_RPL_SUCCESS, chan, av[3]);
		return;
	} else if (stricmp(av[3], "Off") == 0) {
		c->topiclock = 0;
		notice(cs_name, src, CS_SET_TOPICLOCK_RPL_DISABLE, chan);
		return;
	} else {
		notice(cs_name, src, CS_SET_KEEPTOPIC_ERR_USAGE);
		notice(cs_name, src, CS_RPL_HLP, cs_name, "SET TOPICLOCK");
		return;
	}
}

