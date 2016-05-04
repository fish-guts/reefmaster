/*
 * ns_set.c
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
 * ns SET - handle the Nickserv SET command
 * Possible subcommands are:
 * AUTHORIZE  	Set whether your explicit authorization is required
 *				before some can add you to channel access or notify lists
 *	EMAIL 		Set your e-mail address
 *	HIDEEMAIl	Prevent your e-mail address from showing up in the INFO command
 *	MFORWARD	Forward your memos to another registered nickname
 *	MLOCK		Set a set of usermodes that are set automatically upon identification
 *	MNOTIFY		Enable / Disable notifications about new memos
 *	NOMEMO		Disabled Memos for your nickname
 *	NOOP		Prevent Chanserv from automatically opping you in channels you have access to.
 *	PASSWORD	Set a new password
 *	PROTECT		Set the nickname protection level
 *	URL			Set your homepage's URL
 *
 */
void ns_set(char *src, int ac, char **av) {
	if (ac <= 1) {
		notice(ns_name, src, NS_SET_RPL_USAGE);
		return;
	}
	if (stricmp(av[1], "AUTHORIZE") == 0)
		ns_set_authorize(src, ac, av);
	else if (stricmp(av[1], "EMAIL") == 0)
		ns_set_email(src, ac, av);
	else if (stricmp(av[1], "HIDEEMAIL") == 0)
		ns_set_hideemail(src, ac, av);
	else if (stricmp(av[1], "MFORWARD") == 0)
		ns_set_mforward(src, ac, av);
	else if (stricmp(av[1], "MNOTIFY") == 0)
		ns_set_mnotify(src, ac, av);
	else if (stricmp(av[1], "NOMEMO") == 0)
		ns_set_nomemo(src, ac, av);
	else if (stricmp(av[1], "NOOP") == 0)
		ns_set_noop(src, ac, av);
	else if (stricmp(av[1], "PASSWORD") == 0)
		ns_set_password(src, ac, av);
	else if (stricmp(av[1], "PROTECT") == 0)
		ns_set_protect(src, ac, av);
	else if (stricmp(av[1], "URL") == 0)
		ns_set_url(src, ac, av);
}
/********************************************************************/
/**
 * handle the Nickserv SET AUTHORIZE command
 * Usage: set [CHAN|NOTIFY] [on|off]
 */
void ns_set_authorize(char *src, int ac, char **av) {
	user *u = finduser(src);
	if (!isreg(src)) {
		notice(ns_name, src, NS_ERR_NOTREG, src);
		return;
	}
	if (hasaccess(u, src) < 0) {
		notice(ns_name, src, NS_ERR_ACCESSDENIED, src);
		notice(ns_name, src, NS_RPL_NEEDIDENTIFY, src);
		return;
	}
	if (ac <= 3) {
		notice(ns_name, src, NS_SET_AUTH_RPL_USAGE);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"SET AUTHORIZE");
		return;
	}
	NickInfo *n = findnick(src);
	if (stricmp(av[2], "CHAN") == 0) {
		if (stricmp(av[3], "ON") == 0) {
			if (n->auth_chan == 0) {
				notice(ns_name, src, NS_SET_AUTH_RPL_SUCCESS1);
			} else {
				notice(ns_name, src, NS_SET_AUTH_RPL_SUCCESS2);
			}
			n->auth_chan = 1;
			return;
		} else if (stricmp(av[3], "OFF") == 0) {
			if (n->auth_chan == 1) {
				notice(ns_name, src, NS_SET_AUTH_RPL_SUCCESS3);
			} else {
				notice(ns_name, src, NS_SET_AUTH_RPL_SUCCESS4);
			}
			n->auth_chan = 0;
			return;
		}
	} else if (stricmp(av[2], "NOTIFY") == 0) {
		if (stricmp(av[3], "ON") == 0) {
			if (n->auth_notify == 0) {
				notice(ns_name, src, NS_SET_AUTH_RPL_SUCCESS5);
			} else {
				notice(ns_name, src, NS_SET_AUTH_RPL_SUCCESS6);
			}
			n->auth_notify = 1;
			return;
		} else if (stricmp(av[3], "OFF") == 0) {
			if (n->auth_notify == 1) {
				notice(ns_name, src, NS_SET_AUTH_RPL_SUCCESS7);
			} else {
				notice(ns_name, src, NS_SET_AUTH_RPL_SUCCESS8);
			}
			n->auth_notify = 0;
			return;
		}
	}
	return;
}
/********************************************************************/
/**
 * handle the Nickserv SET EMAIL command
 */
void ns_set_email(char *src, int ac, char **av) {
	user *u = finduser(src);
	if (!isreg(src)) {
		notice(ns_name, src, NS_ERR_NOTREG, src);
		return;
	}
	NickInfo *n = findnick(src);
	if (hasaccess(u, src) < 0) {
		notice(ns_name, src, NS_ERR_ACCESSDENIED, src);
		notice(ns_name, src, NS_RPL_NEEDIDENTIFY, src);
		return;
	}
	if (ac <= 2) {
		notice(ns_name, src, NS_SET_EMAIL_RPL_USAGE);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"SET EMAIL");
		return;
	}
	if (!strchr(av[2], '@')) {
		notice(ns_name, src, NS_REGISTER_ERR_INVALDEMAIL);
		return;
	}
	n->email = sstrdup(av[2]);
	notice(ns_name, src, NS_SET_EMAIL_RPL_SUCCESS, av[2]);
	return;
}
/********************************************************************/
/**
 * handle the Nickserv HIDEEMAIL command
 */
void ns_set_hideemail(char *src, int ac, char **av) {
	user *u = finduser(src);
	if (!isreg(src)) {
		notice(ns_name, src, NS_ERR_NOTREG, src);
		return;
	}
	if (ac <= 2) {
		notice(ns_name, src, NS_SET_HIDEEMAIL_RPL_USAGE);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"SET HIDEEMAIL");
		return;
	}
	if (hasaccess(u, src) < 0) {
		notice(ns_name, src, NS_ERR_ACCESSDENIED, u->nick);
		notice(ns_name, src, NS_RPL_NEEDIDENTIFY, u->nick);
		return;
	}
	NickInfo *n = findnick(src);
	if (stricmp(av[2], "ON") == 0) {
		n->hidemail = 1;
		notice(ns_name, src, NS_SET_HIDEEMAIL_RPL_SUCC1);
		return;
	} else if (stricmp(av[2], "OFF") == 0) {
		n->hidemail = 0;
		notice(ns_name, src, NS_SET_HIDEEMAIL_RPL_SUCC2);
		return;
	} else {
		notice(ns_name, src, NS_SET_HIDEEMAIL_RPL_USAGE);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"SET HIDEEMAIL");
		return;
	}
	return;
}

/********************************************************************/
/**
 * handle the Nickserv SET MFORWARD command
 */
void ns_set_mforward(char *src, int ac, char **av) {
	user *u = finduser(src);
	char *nick = av[2];
	if (!isreg(src)) {
		notice(ns_name, src, NS_ERR_NOTREG, src);
		return;
	}
	if (ac <= 2) {
		notice(ns_name, src, NS_SET_MFORWARD_ERR_USAGE);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"SET MFORWARD");
		return;
	}
	if (hasaccess(u, src) < 0) {
		notice(ns_name, src, NS_ERR_ACCESSDENIED, u->nick);
		notice(ns_name, src, NS_RPL_NEEDIDENTIFY, u->nick);
		return;
	}
	if (stricmp(src, nick) == 0) {
		notice(ns_name, src, NS_SET_MFORWARD_ERR_SELF);
		return;
	}
	NickInfo *n = findnick(src);
	if (stricmp(av[2], "OFF") == 0) {
		n->mforward = 0;
		free(n->mforward_to);
		notice(ns_name, src, NS_SET_MFORWARD_RPL_OFF);
		return;
	} else {
		if (!isreg(nick)) {
			notice(ns_name, src, NS_ERR_NOTREG, av[2]);
			return;
		}
		if (hasaccess(u, nick) < 0) {
			notice(ns_name, src, NS_ERR_ACCESSDENIED, av[2]);
			notice(ns_name, src, NS_RPL_NEEDIDENTIFY, av[2]);
			return;
		}
		notice(ns_name, src, NS_SET_MFORWARD_RPL_ON, av[2]);
		n->mforward = 1;
		n->mforward_to = sstrdup(nick);
		return;
	}
}

/********************************************************************/
/**
 * handle the Nickserv SET MLOCK command
 */
void ns_set_mlock(char *src, int ac, char **av) {
	user *u = finduser(src);
	if (!isreg(src)) {
		notice(ns_name, src, NS_ERR_NOTREG, src);
		return;
	}
	if (hasaccess(u, src) < 0) {
		notice(ns_name, src, NS_ERR_ACCESSDENIED, src);
		notice(ns_name, src, NS_RPL_NEEDIDENTIFY, src);
		return;
	}
	if (ac <= 2) {
		notice(ns_name, src, NS_SET_MLOCK_RPL_USAGE);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"SET MLOCK");
		return;
	}
	NickInfo *n = findnick(src);
	n->mlock = sstrdup(av[2]);
	notice(ns_name, src, NS_SET_MLOCK_RPL_SUCCESS, av[2]);
	return;
}

/********************************************************************/
/**
 * handle the Nickserv SET MNOTIFY command
 */
void ns_set_mnotify(char *src, int ac, char **av) {
	user *u = finduser(src);
	if (!isreg(src)) {
		notice(ns_name, src, NS_ERR_NOTREG, src);
		return;
	}
	if (ac <= 2) {
		notice(ns_name, src, NS_SET_MNOTIFY_RPL_USAGE);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"SET MNOTIFY");
		return;
	}
	if (hasaccess(u, src) < 0) {
		notice(ns_name, src, NS_ERR_ACCESSDENIED, u->nick);
		notice(ns_name, src, NS_RPL_NEEDIDENTIFY, u->nick);
		return;
	}
	NickInfo *n = findnick(src);
	if (stricmp(av[2], "ON") == 0) {
		n->mnotify = 1;
		notice(ns_name, src, NS_SET_MNOTIFY_RPL_SUCCESS2);
		return;
	} else if (stricmp(av[2], "OFF") == 0) {
		n->mnotify = 0;
		notice(ns_name, src, NS_SET_MNOTIFY_RPL_SUCCESS);
		return;
	} else {
		notice(ns_name, src, NS_SET_MNOTIFY_RPL_USAGE);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"SET MNOTIFY");
		return;
	}
}

/********************************************************************/
/**
 * handle the Nickserv SET NOMEMO command
 */
void ns_set_nomemo(char *src, int ac, char **av) {
	user *u = finduser(src);
	if (!isreg(src)) {
		notice(ns_name, src, NS_ERR_NOTREG, src);
		return;
	}
	if (ac <= 2) {
		notice(ns_name, src, NS_SET_NOMEMO_RPL_USAGE);
		notice(ns_name, src, NS_SET_NOMEMO_RPL_HLP, ns_name);
		return;
	}
	if (hasaccess(u, src) < 0) {
		notice(ns_name, src, NS_ERR_ACCESSDENIED, u->nick);
		notice(ns_name, src, NS_RPL_NEEDIDENTIFY, u->nick);
		return;
	}
	NickInfo *n = findnick(src);
	if (stricmp(av[2], "ON") == 0) {
		n->nomemo = 1;
		notice(ns_name, src, NS_SET_NOMEMO_RPL_SUCCESS2);
		return;
	} else if (stricmp(av[2], "OFF") == 0) {
		n->nomemo = 0;
		notice(ns_name, src, NS_SET_NOMEMO_RPL_SUCCESS);
		return;
	} else {
		notice(ns_name, src, NS_SET_NOMEMO_RPL_USAGE);
		notice(ns_name, src, NS_SET_NOMEMO_RPL_HLP, ns_name);
		return;
	}
}

/********************************************************************/
/**
 * handle the Nickserv SET NOOP command
 */
void ns_set_noop(char *src, int ac, char **av) {
	user *u = finduser(src);
	if (!isreg(src)) {
		notice(ns_name, src, NS_ERR_NOTREG, src);
		return;
	}
	if (ac <= 2) {
		notice(ns_name, src, NS_SET_NOOP_RPL_USAGE);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"SET NOOP");
		return;
	}
	if (hasaccess(u, src) < 0) {
		notice(ns_name, src, NS_ERR_ACCESSDENIED, u->nick);
		notice(ns_name, src, NS_RPL_NEEDIDENTIFY, u->nick);
		return;
	}
	NickInfo *n = findnick(src);
	if (stricmp(av[2], "ON") == 0) {
		if (n->noop == 1)
			notice(ns_name, src, NS_SET_NOOP_RPL_SUCCESS2);
		else {
			notice(ns_name, src, NS_SET_NOOP_RPL_SUCCESS);
		}
		n->noop = 1;
		return;
	} else if (stricmp(av[2], "OFF") == 0) {
		if (n->noop == 0)
			notice(ns_name, src, NS_SET_NOOP_RPL_SUCCESS4);
		else {
			notice(ns_name, src, NS_SET_NOOP_RPL_SUCCESS3);
		}
		n->noop = 0;
		return;
	} else {
		notice(ns_name, src, NS_SET_NOOP_RPL_USAGE);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"SET NOOP");
		return;
	}
	return;
}

/********************************************************************/
/**
 * handle the Nickserv SET PASSWORD command
 */
void ns_set_password(char *src, int ac, char **av) {
	user *u = finduser(src);
	if (ac <= 2) {
		notice(ns_name, src, NS_SET_PASS_RPL_USAGE);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"SET PASSWORD");
		return;
	}
	char *pass = sstrdup(av[2]);
	if (!isreg(src)) {
		notice(ns_name, src, NS_ERR_NOTREG, src);
		return;
	}
	if (hasaccess(u, src) < 0) {
		notice(ns_name, src, NS_ERR_ACCESSDENIED, u->nick);
		notice(ns_name, src, NS_RPL_NEEDIDENTIFY, u->nick);
		return;
	}
	if (strlen(pass) < 5) {
		notice(ns_name, src, NS_REGISTER_ERR_PASSTOOSHORT);
		return;
	}
	if (stricmp(pass, src) == 0) {
		notice(ns_name, src, NS_REGISTER_ERR_PASSSAMEASNICK);
		return;
	}
	NickInfo *n = findnick(src);
	strscpy(n->pass, pass, PASSMAX);
	notice(ns_name, src, NS_SET_PASS_RPL_SUCCESS, av[2]);
	return;
}

/********************************************************************/
/**
 * handle the Nickserv SET PROTECT command
 */
void ns_set_protect(char *src, int ac, char **av) {
	user *u = finduser(src);
	if (ac <= 2) {
		notice(ns_name, src, NS_SET_PROTECT_ERR_USAGE);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"SET PROTECT");
		return;
	}
	if (!isreg(src)) {
		notice(ns_name, src, NS_ERR_NOTREG, src);
		return;
	}
	if (hasaccess(u, src) < 0) {
		notice(ns_name, src, NS_ERR_ACCESSDENIED, u->nick);
		notice(ns_name, src, NS_RPL_NEEDIDENTIFY, u->nick);
		return;
	}
	NickInfo *n = findnick(src);
	if (stricmp(av[2], "OFF") == 0) {
		if (n->protect == 1)
			notice(ns_name, src, NS_SET_PROTECT_RPL_SUCCESS2);
		else {
			notice(ns_name, src, NS_SET_PROTECT_RPL_SUCCESS);
		}
		n->protect = 1;
		return;
	} else if (stricmp(av[2], "NORMAL") == 0) {
		if (n->protect == 2)
			notice(ns_name, src, NS_SET_PROTECT_RPL_SUCCESS4);
		else {
			notice(ns_name, src, NS_SET_PROTECT_RPL_SUCCESS3);
		}
		n->protect = 2;
		return;
	} else if (stricmp(av[2], "HIGH") == 0) {
		if (n->protect == 3)
			notice(ns_name, src, NS_SET_PROTECT_RPL_SUCCESS6);
		else {
			notice(ns_name, src, NS_SET_PROTECT_RPL_SUCCESS5);
		}
		n->protect = 3;
		return;
	} else {
		notice(ns_name, src, NS_SET_PROTECT_ERR_USAGE);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"SET PROTECT");
		return;
	}
	return;
}

/********************************************************************/
/**
 * handle the Nickserv SET URL command
 */
void ns_set_url(char *src, int ac, char **av) {
	user *u = finduser(src);
	if (!isreg(src)) {
		notice(ns_name, src, NS_ERR_NOTREG, src);
		return;
	}
	if (hasaccess(u, src) < 0) {
		notice(ns_name, src, NS_ERR_ACCESSDENIED, src);
		notice(ns_name, src, NS_RPL_NEEDIDENTIFY, src);
		return;
	}
	if (ac <= 2) {
		notice(ns_name, src, NS_SET_URL_RPL_USAGE);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"SET URL");
		return;
	}
	if (!strchr(av[2], '@')) {
		notice(ns_name, src, NS_REGISTER_ERR_INVALDEMAIL);
		return;
	}
	NickInfo *n = findnick(src);
	n->url = sstrdup(av[2]);
	notice(ns_name, src, NS_SET_URL_RPL_SUCCESS, av[2]);
	return;
}
