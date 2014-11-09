/*
 *      database.c - severin
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
#include "query.h"

static void bs_install_bots(void);
static void cs_install_chans(void);
static void cs_install_acc_level(void);
static void cs_install_op_list(void);
static void cs_install_op_type(void);
static void install_ns(void);
static void install_cs(void);
static void install_bs(void);
static void install_table(const char *sql);
static void load_botserv(void);
static void load_chanserv(void);
static void load_main(void);
static void load_nicks(void);
static void load_nickserv(void);
static void load_access();
static void load_auth();
static void load_notify();
static void ns_install_nicks(void);
static void ns_install_access(void);
static void ns_install_auth_status(void);
static void ns_install_notify(void);
static void ns_install_target_type(void);
static void ns_install_auth(void);


void install_db(void) {
	install_ns();
	install_bs();
	install_cs();
}
static void bs_install_bots(void) {
	install_table(bs_create_bots_table);
}
static void cs_install_chans(void) {
	install_table(cs_create_chans_table);
}
static void cs_install_acc_level(void) {
	install_table(cs_create_acc_level_table);
}
static void cs_install_op_list(void) {
	install_table(cs_create_op_list_table);
}
static void cs_install_op_type(void) {
	install_table(cs_create_op_type_table);
}
static void install_bs(void) {
	bs_install_bots();
}
static void load_main(void) {

}

static void install_ns() {
	ns_install_nicks();
	ns_install_access();
	ns_install_auth_status();
	ns_install_notify();
	ns_install_target_type();
	ns_install_auth();
}

static void install_table(const char *sql) {
	char *sqlite_err = 0;
	sqlite3 *db;
	int rc;
	if ((rc = sqlite3_open(DB, &db)) == SQLITE_OK) {

		if ((sqlite3_exec(db, sql, 0, 0, &sqlite_err)) != SQLITE_OK) {
			sqlite3_free(sqlite_err);
			addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		}
	}
	sqlite3_close(db);
	return;
}
static void ns_install_access(void) {
	install_table(ns_create_access_table);
}
static void ns_install_auth_status(void) {
	install_table(ns_create_auth_status_table);
}
static void ns_install_auth(void) {
	install_table(ns_create_auth_table);
}
static void ns_install_target_type(void) {
	install_table(ns_create_target_type_table);
}
static void ns_install_notify(void) {
	install_table(ns_create_notify_table);
}
static void ns_install_nicks(void) {
	install_table(ns_create_nicks_table);
}
static void install_cs(void) {
	cs_install_chans();
	cs_install_acc_level();
	cs_install_op_list();
	cs_install_op_type();
}
int dbase_query(sqlite3 *db, char *qry) {
	addlog(1, LOG_DBG_SQLQRY, qry);
	char *sqlite_err = 0;
	if ((sqlite3_exec(db, qry, 0, 0, &sqlite_err)) != SQLITE_OK) {
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		sqlite3_free(sqlite_err);
		sqlite3_close(db);
		return -1;
	} else
		return 0;
}
/**
int db_save_chans(ChanInfo *c) {
	char *sql = (char*) malloc(sizeof(char) * 65565);
	sqlite3 *db;
	int rc;
	if ((rc = sqlite3_open(CS_DB, &db)) == SQLITE_OK) {
		if ((rc = dbase_query(db,"DROP TABLE 'chans'")) != 0) {
			addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
			return -1;
		}
		sqlite3_close(db);
		dbase_install_cs();
	}
	if (!c) {
		return -1;
	}
	if ((rc = sqlite3_open(CS_DB, &db)) == SQLITE_OK) {
		while (c) {
			char *aop = (char*) malloc(sizeof(char*) * 65565);
			char *aop_addedon = (char*) malloc(sizeof(char*) * 65565);
			char *aop_addedby = (char*) malloc(sizeof(char*) * 65565);
			char *aop_addedbyacc = (char*) malloc(sizeof(char*) * 65565);
			char *hop = (char*) malloc(sizeof(char*) * 65565);
			char *hop_addedon = (char*) malloc(sizeof(char*) * 65565);
			char *hop_addedby = (char*) malloc(sizeof(char*) * 65565);
			char *hop_addedbyacc = (char*) malloc(sizeof(char*) * 65565);
			char *sop = (char*) malloc(sizeof(char*) * 65565);
			char *sop_addedon = (char*) malloc(sizeof(char*) * 65565);
			char *sop_addedby = (char*) malloc(sizeof(char*) * 65565);
			char *sop_addedbyacc = (char*) malloc(sizeof(char*) * 65565);
			char *admin = (char*) malloc(sizeof(char*) * 65565);
			char *admin_addedon = (char*) malloc(sizeof(char*) * 65565);
			char *admin_addedby = (char*) malloc(sizeof(char*) * 65565);
			char *admin_addedbyacc = (char*) malloc(sizeof(char*) * 65565);
			char *owner = (char*) malloc(sizeof(char*) * 65565);
			char *owner_addedon = (char*) malloc(sizeof(char*) * 65565);
			char *owner_addedby = (char*) malloc(sizeof(char*) * 65565);
			char *owner_addedbyacc = (char*) malloc(sizeof(char*) * 65565);
			char *uop = (char*) malloc(sizeof(char*) * 65565);
			char *uop_addedon = (char*) malloc(sizeof(char*) * 65565);
			char *uop_addedby = (char*) malloc(sizeof(char*) * 65565);
			char *uop_addedbyacc = (char*) malloc(sizeof(char*) * 65565);
			char *vop = (char*) malloc(sizeof(char*) * 65565);
			char *vop_addedon = (char*) malloc(sizeof(char*) * 65565);
			char *vop_addedby = (char*) malloc(sizeof(char*) * 65565);
			char *vop_addedbyacc = (char*) malloc(sizeof(char*) * 65565);
			char *akick = (char*) malloc(sizeof(char*) * 65565);
			char *akick_addedon = (char*) malloc(sizeof(char*) * 65565);
			char *akick_addedby = (char*) malloc(sizeof(char*) * 65565);
			char *akick_addedbyacc = (char*) malloc(sizeof(char*) * 65565);
			char *akick_reason = (char*) malloc(sizeof(char*) * 1025000);
			char *tmp = (char*) malloc(sizeof(char*) * 256);
			op *o = global_op_list;
			while (o) {
				if (stricmp(c->name, o->chan) == 0) {
					if (o->level == AOP_LIST) {
						strcat(aop, o->nick);
						strcat(aop, ";");
						sprintf(tmp, "%ld;", o->addedon);
						strcat(aop_addedon, tmp);
						strcat(aop_addedby, o->addedby);
						strcat(aop_addedby, ";");
						sprintf(tmp, "%i;", o->addedbyacc);
						strcat(aop_addedbyacc, tmp);
					} else if (o->level == HOP_LIST) {
						strcat(hop, o->nick);
						strcat(hop, ";");
						sprintf(tmp, "%ld;", o->addedon);
						strcat(hop_addedon, tmp);
						strcat(hop_addedby, o->addedby);
						strcat(hop_addedby, ";");
						sprintf(tmp, "%i;", o->addedbyacc);
						strcat(hop_addedbyacc, tmp);
					} else if (o->level == SOP_LIST) {
						strcat(sop, o->nick);
						strcat(sop, ";");
						sprintf(tmp, "%ld;", o->addedon);
						strcat(sop_addedon, tmp);
						strcat(sop_addedby, o->addedby);
						strcat(sop_addedby, ";");
						sprintf(tmp, "%i;", o->addedbyacc);
						strcat(sop_addedbyacc, tmp);
					} else if (o->level == UOP_LIST) {
						strcat(uop, o->nick);
						strcat(uop, ";");
						sprintf(tmp, "%ld;", o->addedon);
						strcat(uop_addedon, tmp);
						strcat(uop_addedby, o->addedby);
						strcat(uop_addedby, ";");
						sprintf(tmp, "%i;", o->addedbyacc);
						strcat(uop_addedbyacc, tmp);
					} else if (o->level == VOP_LIST) {
						strcat(vop, o->nick);
						strcat(vop, ";");
						sprintf(tmp, "%ld;", o->addedon);
						strcat(vop_addedon, tmp);
						strcat(vop_addedby, o->addedby);
						strcat(vop_addedby, ";");
						sprintf(tmp, "%i;", o->addedbyacc);
						strcat(vop_addedbyacc, tmp);
					}else if (o->level == ADMIN_LIST) {
						strcat(admin, o->nick);
						strcat(admin, ";");
						sprintf(tmp, "%ld;", o->addedon);
						strcat(admin_addedon, tmp);
						strcat(admin_addedby, o->addedby);
						strcat(admin_addedby, ";");
						sprintf(tmp, "%i;", o->addedbyacc);
						strcat(admin_addedbyacc, tmp);
					} else if (o->level == OWNER_LIST) {
						strcat(owner, o->nick);
						strcat(owner, ";");
						sprintf(tmp, "%ld;", o->addedon);
						strcat(owner_addedon, tmp);
						strcat(owner_addedby, o->addedby);
						strcat(owner_addedby, ";");
						sprintf(tmp, "%i;", o->addedbyacc);
						strcat(owner_addedbyacc, tmp);
					}else if (o->level == AKICK_LIST) {
						strcat(akick, o->nick);
						strcat(akick, ";");
						sprintf(tmp, "%ld;", o->addedon);
						strcat(akick_addedon, tmp);
						strcat(akick_addedby, o->addedby);
						strcat(akick_addedby, ";");
						sprintf(tmp, "%i;", o->addedbyacc);
						strcat(akick_addedbyacc, tmp);
						sprintf(tmp,"%s;",o->reason);
						strcat(akick_reason,tmp);
					}
				} // if
				o = o->next;
			} // while
			sprintf(sql, "REPLACE INTO 'chans' VALUES("
					"'%s',"
					"'%s',"
					"'%s',"
					"'%ld',"
					"'%i',"
					"'%i',"
					"'%i',"
					"'%i',"
					"'%i',"
					"'%s',"
					"'%s',"
					"'%s',"
					"'%s',"
					"'%s',"
					"'%i',"
					"'%i',"
					"'%i',"
					"'%i',"
					"'%i',"
					"'%i',"
					"'%s',"
					"'%i',"
					"'%s',"
					"'%s',"
					"'%s',"
					"'%s',"
					"'%s',"
					"'%s',"
					"'%s',"
					"'%s',"
					"'%s',"
					"'%s',"
					"'%s',"
					"'%s',"
					"'%s',"
					"'%s',"
					"'%s',"
					"'%s',"
					"'%s',"
					"'%s',"
					"'%s',"
					"'%s',"
					"'%s',"
					"'%s',"
					"'%s',"
					"'%s',"
					"'%s',"
					"'%s',"
					"'%s',"
					"'%s',"
					"'%s',"
					"'%s',"
					"'%s',"
					"'%s',"
					"'%s'"
					");", c->name, c->pass, c->description,c->time_reg, c->aop_enabled,
					c->hop_enabled, c->sop_enabled, c->uop_enabled,
					c->vop_enabled, c->bot, c->founder, c->successor, c->mlock,
					c->topic, c->restricted, c->keeptopic, c->autovop,
					c->memolevel, c->leaveops, c->opwatch, c->url, c->topiclock,
					aop, aop_addedon, aop_addedby, aop_addedbyacc, hop,
					hop_addedon, hop_addedby, hop_addedbyacc, sop, sop_addedon,
					sop_addedby, sop_addedbyacc, uop, uop_addedon, uop_addedby,
					uop_addedbyacc, vop, vop_addedon, vop_addedby,
					vop_addedbyacc, akick, akick_addedon, akick_addedby,
					akick_addedbyacc,akick_reason,admin,admin_addedon,admin_addedby,admin_addedbyacc
					,owner,owner_addedon,owner_addedby,owner_addedbyacc);
			if ((rc = dbase_query(db, sql)) != 0) {
				addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
				return -1;
			}
			c = c->next;
		}
	}
	sqlite3_close(db);
	return 0;

}

int db_save_nicks(NickInfo *n) {
	char *sql = (char*) malloc(sizeof(char) * 1024);
	int i = 1;
	sqlite3 *db;
	int rc;
	if ((rc = sqlite3_open(NS_DB, &db)) == SQLITE_OK) {
		if ((rc = dbase_query(db,"DROP TABLE 'nicks'")) != 0) {
			addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
			return -1;
		}
		sqlite3_close(db);
		dbase_install_ns();
	}

	if (!n)
		return -1;
	if ((rc = sqlite3_open(NS_DB, &db)) == SQLITE_OK) {

		while (n) {
			char *auth_type = (char*) malloc(sizeof(char*) * 65565);
			char *auth_sender = (char*) malloc(sizeof(char*) * 65565);
			char *auth_target = (char*) malloc(sizeof(char*) * 65565);
			char *auth_acctype = (char*) malloc(sizeof(char*) * 65565);
			char *auth_list = (char*) malloc(sizeof(char*) * 65565);
			char *auth_date = (char*) malloc(sizeof(char*) * 65565);
			auth *a = n->authlist;
			while (a) {
				if (a) {
					sprintf(auth_type, "%s;%i", auth_type, a->type);
					sprintf(auth_sender, "%s;%s", auth_sender, a->sender);
					sprintf(auth_target, "%s;%s", auth_target, a->sender);
					sprintf(auth_acctype, "%s;%i", auth_acctype, a->acctype);
					sprintf(auth_list, "%s;%s", auth_list, a->list);
					sprintf(auth_date, "%s;%ld", auth_date, a->date);
				}
				a = a->next;
			}
			char *acc = (char*) malloc(sizeof(char*) * 65565);
			char *nfy = (char*) malloc(sizeof(char*) * 65565);
			for (i = 1; i <= n->accesscount; i++) {
				sprintf(acc, "%s;%s", acc, n->accesslist[i - 1]);
			}
			for (i = 1; i <= n->notifycount; i++) {
				sprintf(nfy, "%s;%s", nfy, n->notifylist[i - 1]);
			}
			sprintf(sql, "REPLACE INTO 'nicks' VALUES("
					"'%s',"
					"'%s',"
					"'%s',"
					"'%s',"
					"'%ld',"
					"'%ld',"
					"'%i',"
					"'%i',"
					"'%s',"
					"'%s',"
					"'%s',"
					"'%i',"
					"'%i',"
					"'%i',"
					"'%i',"
					"'%i',"
					"'%i',"
					"'%s',"
					"'%i',"
					"'%s',"
					"'%s',"
					"'%s',"
					"'%s',"
					"'%s',"
					"'%s',"
					"'%s',"
					"'%s'"
					");", n->nick, n->pass, n->last_usermask, n->last_realname,
					n->last_seen, n->time_reg, n->hidemail, n->memomax, n->url,
					n->email, n->mforward_to, n->mforward, n->noop, n->nomemo,
					n->auth_chan, n->auth_notify, n->protect,n->mlock, n->mnotify, acc,
					nfy, auth_type, auth_sender, auth_target, auth_acctype,
					auth_list, auth_date);
			if ((rc = dbase_query(db, sql)) != 0) {
				addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
				return -1;
			}
			n = n->next;
		}
	}
	addlog(1,"Nickserv data saved");
	sqlite3_close(db);
	return 0;
}
*/

void load_database(void) {
	load_main();
	if(bs_enabled)
		load_botserv();
	if (ns_enabled)
		load_nickserv();
	if(cs_enabled)
		load_chanserv();
}

static void load_nickserv(void) {
	load_nicks();
	printf("muahahaha98\n");
	load_access();
	printf("muahahaha97\n");
	load_auth();
	printf("muahahaha96\n");
	load_notify();
	printf("muahahaha95\n");
}
void load_botserv(void) {

}
static void load_access(void) {
	sqlite3 *db;
	sqlite3_stmt *res;
	const char *tail;
	int error = 0;
	int rc;
	if ((rc = sqlite3_open(DB, &db)) == SQLITE_OK) {
		error = sqlite3_prepare_v2(db,load_ns_access, 1000, &res,
				&tail);
		if (error != SQLITE_OK) {
			addlog(1, "SQL ERROR: %i", error);
		}
		while (sqlite3_step(res) == SQLITE_ROW) {
			NickInfo *n = findnick((const char*)sqlite3_column_text(res, 0));
			accesslist *a = scalloc(sizeof(accesslist), 1);
			a->next = n->al;
			if (n->al)
				n->al->prev = a;
			n->al = a;
			a->mask = sstrdup((const char*)sqlite3_column_text(res, 1));
		}
	}
	sqlite3_close(db);
}

static void load_notify(void) {
	sqlite3 *db;
	sqlite3_stmt *res;
	const char *tail;
	int error = 0;
	int rc;
	if ((rc = sqlite3_open(DB, &db)) == SQLITE_OK) {
		error = sqlite3_prepare_v2(db,load_ns_notify, 1000, &res,&tail);
		if (error != SQLITE_OK) {
			addlog(1, "SQL ERROR: %i", error);
		}
		while (sqlite3_step(res) == SQLITE_ROW) {
			NickInfo *n = findnick((const char*)sqlite3_column_text(res, 0));
			notify *no = scalloc(sizeof(notify), 1);
			no->next = n->notifylist;
			if (n->notifylist)
				n->notifylist->prev = no;
			n->notifylist = no;
			no->nick = findnick((const char*)sqlite3_column_text(res, 1));
		}
	}
	sqlite3_close(db);
}
static void load_auth(void) {
	sqlite3 *db;
	sqlite3_stmt *res;
	const char *tail;
	int error = 0;
	int rc = 0;
	if ((rc = sqlite3_open(DB, &db)) == SQLITE_OK) {
		error = sqlite3_prepare_v2(db,load_ns_auth, 1000, &res,
				&tail);
		if (error != SQLITE_OK) {
			addlog(1, "SQL ERROR: %i", error);
		}
		while (sqlite3_step(res) == SQLITE_ROW) {
			NickInfo *n = findnick((const char*)sqlite3_column_text(res, 3));
			auth *a = scalloc(sizeof(auth), 1);
			a->next = n->authlist;
			if (n->authlist)
				n->authlist->prev = a;
			n->authlist = a;
			a->type = sqlite3_column_int(res,0);
			a->target = sstrdup((const char*)sqlite3_column_text(res,1));
			a->sender = sstrdup((const char*)sqlite3_column_text(res, 2));
			a->date = sqlite3_column_int(res,4);
			a->status = sqlite3_column_int(res,5);
		}
	}
	sqlite3_close(db);
}
static void load_nicks(void) {
	sqlite3 *db;
	sqlite3_stmt *res;
	const char *tail;
	int error = 0;
	int rc;
	if ((rc = sqlite3_open(DB, &db)) == SQLITE_OK) {
		error = sqlite3_prepare_v2(db, "select * from nicks", 1000, &res,
				&tail);
		if (error != SQLITE_OK) {
			addlog(1, "SQL ERROR: %i", error);
		}
		while (sqlite3_step(res) == SQLITE_ROW) {
			NickInfo *n = scalloc(sizeof(NickInfo), 1);
			strscpy(n->nick, (char*) sqlite3_column_text(res, 1), NICKMAX);
			strscpy(n->pass, (char*) sqlite3_column_text(res, 2), PASSMAX);
			n->last_usermask = sstrdup((char*) sqlite3_column_text(res, 3));
			n->last_realname = sstrdup((char*) sqlite3_column_text(res, 4));
			n->last_seen = sqlite3_column_int(res, 5);
			n->time_reg = sqlite3_column_int(res, 6);
			n->hidemail = sqlite3_column_int(res, 7);
			n->memomax = sqlite3_column_int(res, 8);
			n->url = sstrdup((char*) sqlite3_column_text(res, 9));
			n->email = sstrdup((char*) sqlite3_column_text(res, 10));
			if((char*) sqlite3_column_text(res, 11)) {
				n->mforward_to = sstrdup((char*) sqlite3_column_text(res, 11));
			} else {
				n->mforward_to = NULL;
			}
			n->mforward = sqlite3_column_int(res, 12);
			n->noop = sqlite3_column_int(res, 13);
			n->nomemo = sqlite3_column_int(res, 14);
			n->auth_chan = sqlite3_column_int(res, 15);
			n->auth_notify = sqlite3_column_int(res, 16);
			n->protect = sqlite3_column_int(res, 17);
			n->mlock = (char*) sqlite3_column_text(res,18);
			n->mnotify = sqlite3_column_int(res, 19);
			n->next = nicklist;
			if (nicklist)
				nicklist->prev = n;
			nicklist = n;
		}
	}
	sqlite3_close(db);
}

void load_chanserv(void) {

}

/* EOF */
