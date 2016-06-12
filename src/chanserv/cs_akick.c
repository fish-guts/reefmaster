/*
 * cs_akick.c
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
 * handle the AKICK command
 */
void cs_akick(char *src, int ac, char **av) {
	if (ac < 3) {
		notice(cs_name, src, CS_AKICK_ERR_USAGE);
		notice(cs_name, src, CS_RPL_HLP, cs_name, "AKICK");
		return;
	}
	if (stricmp(av[2], "ADD") == 0) {
		cs_akick_addmask(src, ac, av);
		return;
	} else if (stricmp(av[2], "DEL") == 0) {
		cs_akick_delmask(src, ac, av);
		return;
	} else if (stricmp(av[2], "LIST") == 0) {
		cs_akick_listentries(src, ac, av);
		return;
	} else if (stricmp(av[2], "WIPE") == 0) {
		cs_akick_wipeall(src, ac, av);
		return;
	} else {
		notice(cs_name, src, NS_ERR_NOSUCHCMD, av[2]);
		notice(cs_name, src, CS_RPL_HLP, cs_name, "AKICK");
		return;
	}
	return;
}

/********************************************************************/
/**
 * add an akick mask to a channel
 */
void cs_akick_addmask(char *src, int ac, char **av) {
	int addacc;
	user *u = finduser(src);
	if (ac < 4) {
		notice(cs_name, src, CS_AKICK_ERR_ADD_USAGE);
		notice(cs_name, src, CS_RPL_HLP, cs_name, "AKICK ADD");
		return;
	}
	char *mask = sstrdup(av[3]);
	char *chan = sstrdup(av[1]);
	char *finalmask = (char*) malloc(sizeof(char*) * 1024);
	char *reason = (char*) malloc(sizeof(char*) * 1024);
	if (ac > 4) {
		strcpy(reason,"");
		int i;
		for (i = 4; i < ac; i++) {
			strcat(reason, av[i]);
			if (i < (ac - 1)) {
				strcat(reason, " ");
			}
		}
	} else {
		free(finalmask);
		free(reason);
	}
	if (!isregcs(chan)) {
		notice(cs_name, src, CS_ERR_NOTREG, chan);
		free(finalmask);
		free(reason);
		return;
	}
	ChanInfo *c = findchan(chan);
	if ((addacc = cs_xop_get_level(u, c)) < cs_akick_add) {
		notice(cs_name, src, CS_XOP_ERR_HIGHERACCESS, get_opacc(cs_akick_add));
		free(finalmask);
		free(reason);
		return;
	}
	if ((!strchr(mask, '!')) && (!strchr(mask, '@'))) {
		sprintf(finalmask, "%s!*@*", mask);
	} else if (stricmp(mask, "*!*@*") == 0) {
		notice(cs_name, src, CS_AKICK_ERR_ADD_NOSENSE, mask);
		free(finalmask);
		free(reason);
		return;
	} else {
		notice(as_name,src,"we're here again");
		if (match(mask,
				"([A-Z0-9a-z\\.\\_\\*\\-]+)!([A-Z0-9a-z\\.\\_\\*\\-]+)@([A-Z0-9a-z\\.\\_\\*\\-]+)")
				!= 1) {
			notice(cs_name, src, CS_AKICK_ERR_ADD_NOSENSE, mask);
			notice(cs_name, src, CS_RPL_HLP, cs_name, "AKICK ADD");
			free(finalmask);
			free(reason);
			return;
		} else {
			sprintf(finalmask, "%s", mask);
		}
	}
	if (cs_isonakicklist(finalmask, chan)) {
		notice(cs_name, src, CS_AKICK_ERR_ALREADYONLIST, finalmask, chan);
		free(finalmask);
		free(reason);
		return;
	} else {
		akick *ak = scalloc(sizeof(akick), 1);
		ak->next = c->akicklist;
		if (c->akicklist) {
			c->akicklist->prev = ak;
		}
		c->akicklist = ak;
		ak->mask = sstrdup(finalmask);
		ak->added_by = sstrdup(u->nick);
		ak->added_by_acc = addacc;
		ak->added_on = time(NULL);
		if(reason) {
			ak->reason = sstrdup(reason);
		}
		notice(as_name,src,"%s added by %s (%i) on %ld (%s)",ak->mask,ak->added_by,ak->added_by_acc,ak->added_on,ak->reason);
		notice(cs_name, src, CS_XOP_RPL_ADDED, finalmask, "Akick", c->name);
		free(finalmask);
		free(reason);
		return;
	}
}

/********************************************************************/
/**
 * remove a mask from a channel's akick list
 */
void cs_akick_delmask(char *src, int ac, char **av) {
	if (ac <= 3) {
		notice(cs_name, src, CS_AKICK_ERR_DEL_USAGE);
		notice(cs_name, src, CS_RPL_HLP, cs_name, "AKICK DEL");
		return;
	}
	user *u = finduser(src);
	char *mask = sstrdup(av[3]);
	char *chan = sstrdup(av[1]);
	if (!isregcs(chan)) {
		notice(cs_name, src, CS_ERR_NOTREG, chan);
		return;
	}
	ChanInfo *c = findchan(chan);
	if (cs_xop_get_level(u, c) < cs_akick_del) {
		notice(cs_name, src, CS_XOP_ERR_HIGHERACCESS, get_opacc(cs_akick_del));
		return;
	}
	char *finalmask;
	if ((!strchr(mask, '!')) && (!strchr(mask, '@'))) {
		 finalmask = (char*) malloc(sizeof(char*) * 256);
		sprintf(finalmask, "%s!*@*", mask);
	} else {
		finalmask = sstrdup(mask);
	}
	if (!cs_isonakicklist(finalmask, chan)) {

		notice(cs_name, src, CS_XOP_ERR_NOTONLIST, finalmask, "Akick", chan);
		return;
	}
	akick *ak = c->akicklist;
	while (ak) {
		if (stricmp(finalmask,ak->mask) == 0) {
			if (ak->prev)
				ak->prev->next = ak->next;
			else
				c->akicklist = ak->next;
			if (ak->next)
				ak->next->prev = ak->prev;
			free(ak);
			notice(cs_name, src, CS_XOP_RPL_DELETED, finalmask, "Akick",
					chan);
			return;
		}
		ak = ak->next;
	}
}

/********************************************************************/
/**
 * list all akick entries of the specified channel
 */
void cs_akick_listentries(char *src, int ac, char **av) {
	static char *addedby_lvl[] = { "0", "1", "2", "3", "4", "5", "6", "7","8","\2ServiceRootAdmin\2" };
	user *u = finduser(src);
	char *chan = sstrdup(av[1]);
	if (!isregcs(chan)) {
		notice(cs_name, src, CS_ERR_NOTREG, chan);
		return;
	}
	ChanInfo *c = findchan(chan);
	if (cs_xop_get_level(u, c) < cs_akick_list) {
		notice(cs_name, src, CS_XOP_ERR_HIGHERACCESS, get_opacc(cs_akick_list));
		return;
	}
	int i = 0;
	char str[128];
	akick *ak = c->akicklist;
	notice(cs_name, src, CS_XOP_RPL_LIST_BEGIN, "Akick", chan);
	while (ak) {
		i++;
		strftime(str, 100, "%d/%m/%Y %T %Z", localtime(&ak->added_on));
		if(ak->reason)
			notice(cs_name, src, CS_AKICK_RPL_LIST,i,ak->mask,addedby_lvl[ak->added_by_acc],ak->added_by, str,ak->reason);
		else
			notice(cs_name, src, CS_AKICK_RPL_LIST2, i,ak->mask,addedby_lvl[ak->added_by_acc],ak->added_by, str);
		ak = ak->next;
	}
	if ((i > 1) || (i == 0)) {
		notice(cs_name, src, CS_XOP_RPL_LIST_COMPLETE1, i);
	} else {
		notice(cs_name, src, CS_XOP_RPL_LIST_COMPLETE2);
	}
}
akick *cs_akick_match(user *u,ChanInfo *c) {
	akick *ak = c->akicklist;
	char *mask = (char*)malloc(sizeof(char*)*1024);
	sprintf(mask,"%s!%s@%s",u->nick,u->username,u->hostname);
	while(ak) {
		if(ifmatch_0(ak->mask,mask)) {
			return ak;
		}
		ak = ak->next;
	}
	return NULL;
}
/********************************************************************/
/**
 * remove all akick entries from the specified channel
 */
void cs_akick_wipeall(char *src, int ac, char **av) {
	user *u = finduser(src);
	char *chan = sstrdup(av[1]);
	if (!isregcs(chan)) {
		notice(cs_name, src, CS_ERR_NOTREG, chan);
		return;
	}
	ChanInfo *c = findchan(chan);
	if (cs_xop_get_level(u, c) < cs_akick_wipe) {
		notice(cs_name, src, CS_XOP_ERR_HIGHERACCESS, get_opacc(cs_akick_wipe));
		return;
	}
	int i = 0;

	akick *ak = c->akicklist;
	while (ak) {
		i++;
		if (ak->prev) {
			ak->prev->next = ak->next;
		} else {
			c->akicklist = ak->next;
		}
		if (ak->next) {
			ak->next->prev = ak->prev;
		}
		ak = ak->next;
	}
	free(ak);
	if (i == 1)
		notice(cs_name, src, CS_XOP_RPL_WIPED1, "Akick", chan);
	else
		notice(cs_name, src, CS_XOP_RPL_WIPED2, "Akick", chan, i);
	return;
}
