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
 * ns SET - handle the nickserv SET command
 */
void ns_set(char *src, int ac, char **av) {
	if (ac <= 1) {
		notice(ns_name, src, NS_ERR_SET_USAGE);
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
 * ns SET - handle the nickserv SET AUTHORIZE command
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
		notice(ns_name, src, NS_ERR_SET_AUTH_USAGE);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"SET AUTHORIZE");
		return;
	}
	NickInfo *n = findnick(src);
	if (stricmp(av[2], "CHAN") == 0) {
		if (stricmp(av[3], "ON") == 0) {
			if (n->auth_chan == 0) {
				notice(ns_name, src, NS_RPL_SET_AUTH_SUCCESS1);
			} else {
				notice(ns_name, src, NS_RPL_SET_AUTH_SUCCESS2);
			}
			n->auth_chan = 1;
			return;
		} else if (stricmp(av[3], "OFF") == 0) {
			if (n->auth_chan == 1) {
				notice(ns_name, src, NS_RPL_SET_AUTH_SUCCESS3);
			} else {
				notice(ns_name, src, NS_RPL_SET_AUTH_SUCCESS4);
			}
			n->auth_chan = 0;
			return;
		}
	} else if (stricmp(av[2], "NOTIFY") == 0) {
		if (stricmp(av[3], "ON") == 0) {
			if (n->auth_notify == 0) {
				notice(ns_name, src, NS_RPL_SET_AUTH_SUCCESS5);
			} else {
				notice(ns_name, src, NS_RPL_SET_AUTH_SUCCESS6);
			}
			n->auth_notify = 1;
			return;
		} else if (stricmp(av[3], "OFF") == 0) {
			if (n->auth_notify == 1) {
				notice(ns_name, src, NS_RPL_SET_AUTH_SUCCESS7);
			} else {
				notice(ns_name, src, NS_RPL_SET_AUTH_SUCCESS8);
			}
			n->auth_notify = 0;
			return;
		}
	}
	return;
}
/********************************************************************/
/**
 * ns SET - handle the nickserv SET EMAIL command
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
		notice(ns_name, src, NS_ERR_SET_EMAIL_USAGE);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"SET EMAIL");
		return;
	}
	if (!strchr(av[2], '@')) {
		notice(ns_name, src, NS_ERR_REG_INVALDEMAIL);
		return;
	}
	n->email = sstrdup(av[2]);
	notice(ns_name, src, NS_RPL_SET_EMAILSUCCESS, av[2]);
	return;
}
/********************************************************************/
/**
 * ns SET - handle the nickserv HIDEEMAIL command
 */
void ns_set_hideemail(char *src, int ac, char **av) {
	user *u = finduser(src);
	if (!isreg(src)) {
		notice(ns_name, src, NS_ERR_NOTREG, src);
		return;
	}
	if (ac <= 2) {
		notice(ns_name, src, NS_ERR_SET_HIDEEMAIL_USAGE);
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
		notice(ns_name, src, NS_RPL_SET_HMAIL_SUCCESS1);
		return;
	} else if (stricmp(av[2], "OFF") == 0) {
		n->hidemail = 0;
		notice(ns_name, src, NS_RPL_SET_HMAIL_SUCCESS2);
		return;
	} else {
		notice(ns_name, src, NS_ERR_SET_HIDEEMAIL_USAGE);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"SET HIDEEMAIL");
		return;
	}
	return;
}
/********************************************************************/
/**
 * ns SET - handle the nickserv SET MFORWARD command
 */
void ns_set_mforward(char *src, int ac, char **av) {
	user *u = finduser(src);
	char *nick = av[2];
	if (!isreg(src)) {
		notice(ns_name, src, NS_ERR_NOTREG, src);
		return;
	}
	if (ac <= 2) {
		notice(ns_name, src, NS_ERR_SET_MFWD_USAGE);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"SET MFORWARD");
		return;
	}
	if (hasaccess(u, src) < 0) {
		notice(ns_name, src, NS_ERR_ACCESSDENIED, u->nick);
		notice(ns_name, src, NS_RPL_NEEDIDENTIFY, u->nick);
		return;
	}
	if (stricmp(src, nick) == 0) {
		notice(ns_name, src, NS_ERR_SET_MFWD_SELF);
		return;
	}
	NickInfo *n = findnick(src);
	if (stricmp(av[2], "OFF") == 0) {
		n->mforward = 0;
		free(n->mforward_to);
		notice(ns_name, src, NS_RPL_SET_MFWD_OFF);
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
		notice(ns_name, src, NS_RPL_SET_MFWD_ON, av[2]);
		n->mforward = 1;
		n->mforward_to = sstrdup(nick);
		return;
	}
}
/********************************************************************/
/**
 * ns SET - handle the nickserv SET MLOCK command
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
		notice(ns_name, src, NS_ERR_SET_MLOCK_USAGE);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"SET MLOCK");
		return;
	}
	NickInfo *n = findnick(src);
	n->mlock = sstrdup(av[2]);
	notice(ns_name, src, NS_RPL_SET_MLOCKSUCCESS, av[2]);
	return;
}
/********************************************************************/
/**
 * ns SET - handle the nickserv SET MNOTIFY command
 */
void ns_set_mnotify(char *src, int ac, char **av) {
	user *u = finduser(src);
	if (!isreg(src)) {
		notice(ns_name, src, NS_ERR_NOTREG, src);
		return;
	}
	if (ac <= 2) {
		notice(ns_name, src, NS_ERR_SET_MFY_USAGE);
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
		notice(ns_name, src, NS_RPL_SET_MFY_SUCCESS2);
		return;
	} else if (stricmp(av[2], "OFF") == 0) {
		n->mnotify = 0;
		notice(ns_name, src, NS_RPL_SET_MFY_SUCCESS);
		return;
	} else {
		notice(ns_name, src, NS_ERR_SET_MFY_USAGE);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"SET MNOTIFY");
		return;
	}
}
/********************************************************************/
/**
 * ns SET - handle the nickserv SET NOMEMO command
 */
void ns_set_nomemo(char *src, int ac, char **av) {
	user *u = finduser(src);
	if (!isreg(src)) {
		notice(ns_name, src, NS_ERR_NOTREG, src);
		return;
	}
	if (ac <= 2) {
		notice(ns_name, src, NS_ERR_SET_NOMEMO_USAGE);
		notice(ns_name, src, NS_RPL_SET_NOMEMO_HLP, ns_name);
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
		notice(ns_name, src, NS_RPL_SET_NOMEMO_SUCCESS2);
		return;
	} else if (stricmp(av[2], "OFF") == 0) {
		n->nomemo = 0;
		notice(ns_name, src, NS_RPL_SET_NOMEMO_SUCCESS);
		return;
	} else {
		notice(ns_name, src, NS_ERR_SET_NOMEMO_USAGE);
		notice(ns_name, src, NS_RPL_SET_NOMEMO_HLP, ns_name);
		return;
	}
}
/********************************************************************/
/**
 * ns SET - handle the nickserv SET NOOP command
 */
void ns_set_noop(char *src, int ac, char **av) {
	user *u = finduser(src);
	if (!isreg(src)) {
		notice(ns_name, src, NS_ERR_NOTREG, src);
		return;
	}
	if (ac <= 2) {
		notice(ns_name, src, NS_ERR_SET_NOOP_USAGE);
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
			notice(ns_name, src, NS_RPL_SET_NOOP_SUCCESS2);
		else {
			notice(ns_name, src, NS_RPL_SET_NOOP_SUCCESS);
		}
		n->noop = 1;
		return;
	} else if (stricmp(av[2], "OFF") == 0) {
		if (n->noop == 0)
			notice(ns_name, src, NS_RPL_SET_NOOP_SUCCESS4);
		else {
			notice(ns_name, src, NS_RPL_SET_NOOP_SUCCESS3);
		}
		n->noop = 0;
		return;
	} else {
		notice(ns_name, src, NS_ERR_SET_NOOP_USAGE);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"SET NOOP");
		return;
	}
	return;
}
/********************************************************************/
/**
 * ns SET - handle the nickserv SET PASSWORD command
 */
void ns_set_password(char *src, int ac, char **av) {
	user *u = finduser(src);
	if (ac <= 2) {
		notice(ns_name, src, NS_ERR_SET_PASS_USAGE);
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
		notice(ns_name, src, NS_ERR_REG_PASSTOOSHORT);
		return;
	}
	if (stricmp(pass, src) == 0) {
		notice(ns_name, src, NS_ERR_REG_PASSSAMEASNICK);
		return;
	}
	NickInfo *n = findnick(src);
	strscpy(n->pass, pass, PASSMAX);
	notice(ns_name, src, NS_RPL_SET_PASS_SUCCESS, av[2]);
	return;
}
/********************************************************************/
/**
 * ns SET - handle the nickserv SET PROTECT command
 */
void ns_set_protect(char *src, int ac, char **av) {
	user *u = finduser(src);
	if (ac <= 2) {
		notice(ns_name, src, NS_ERR_SET_PROTECT_USAGE);
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
			notice(ns_name, src, NS_RPL_SET_PROTECT_SUCCESS2);
		else {
			notice(ns_name, src, NS_RPL_SET_PROTECT_SUCCESS);
		}
		n->protect = 1;
		return;
	} else if (stricmp(av[2], "NORMAL") == 0) {
		if (n->protect == 2)
			notice(ns_name, src, NS_RPL_SET_PROTECT_SUCCESS4);
		else {
			notice(ns_name, src, NS_RPL_SET_PROTECT_SUCCESS3);
		}
		n->protect = 2;
		return;
	} else if (stricmp(av[2], "HIGH") == 0) {
		if (n->protect == 3)
			notice(ns_name, src, NS_RPL_SET_PROTECT_SUCCESS6);
		else {
			notice(ns_name, src, NS_RPL_SET_PROTECT_SUCCESS5);
		}
		n->protect = 3;
		return;
	} else {
		notice(ns_name, src, NS_ERR_SET_PROTECT_USAGE);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"SET PROTECT");
		return;
	}
	return;
}
/********************************************************************/
/**
 * ns SET - handle the nickserv SET URL command
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
		notice(ns_name, src, NS_ERR_SET_URL_USAGE);
		notice(ns_name, src, NS_RPL_HLP, ns_name,"SET URL");
		return;
	}
	if (!strchr(av[2], '@')) {
		notice(ns_name, src, NS_ERR_REG_INVALDEMAIL);
		return;
	}
	NickInfo *n = findnick(src);
	n->url = sstrdup(av[2]);
	notice(ns_name, src, NS_RPL_SET_URL_SUCCESS, av[2]);
	return;
}
