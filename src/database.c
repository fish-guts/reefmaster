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
static int db_add_akick(sqlite3 *db, ChanInfo *c, akick *a);
static int db_add_auth(sqlite3 *db, NickInfo*c, auth *a);
static void db_add_bot(bot *b);
static int db_add_chan(sqlite3 *db, ChanInfo *c);
static int db_add_nick(sqlite3 *db, NickInfo *n);
static void db_add_op(op *o);
static int db_save_access(sqlite3 *db, NickInfo *n);
static int db_save_auth(sqlite3 *db, NickInfo *n);
static int db_save_notify(sqlite3 *db, NickInfo *n);
static void db_save_bots(void);
static void db_save_chans(void);
static void db_save_nicks(void);
static void db_save_ops(void);
static void empty_bs(void);
static void empty_cs(void);
static void empty_cs_akick(void);
static void empty_ns(void);
static void empty_ns_access(void);
static void empty_ns_auth(void);
static void empty_ops(void);
static void empty_tables(void);
static ChanInfo *find_chan_by_name(char *chan);
static NickInfo *find_nick_by_name(char *chan);
static bot *find_bot_by_name(char *nick);
static void install_ns(void);
static void install_cs(void);
static void install_bs(void);
static void install_table(const char *sql);
static void load_access();
static void load_akick(void);
static void load_auth();
static void load_botserv(void);
void load_chans(void);
static void load_chanserv(void);
static void load_main(void);
static void load_nicks(void);
static void load_nickserv(void);
static void load_notify();
static void load_ops(void);
static void ns_install_nicks(void);
static void ns_install_access(void);
static void ns_install_auth_status(void);
static void ns_install_notify(void);
static void ns_install_target_type(void);
static void ns_install_auth(void);
static void save_botserv_db(void);
static void save_chanserv_db(void);
static void save_nickserv_db(void);
static void update_nick_id(NickInfo *n);

static void bs_install_bots(void) {
	install_table(bs_create_bots_table);
}
static void cs_install_acc_level(void) {
	install_table(cs_create_acc_level_table);
}
static void cs_install_chans(void) {
	install_table(cs_create_chans_table);
}
static void cs_install_op_list(void) {
	install_table(cs_create_op_list_table);
}
static void cs_install_op_type(void) {
	install_table(cs_create_op_type_table);
}
static int db_add_akick(sqlite3 *db, ChanInfo *c, akick *a) {
	addlog(DEBUG, LOG_DBG_ENTRY, "db_update_akick");
	char sql[2048];
	int rc;
	int chanid = find_chan_by_name(c->name)->id;
	sprintf(sql, cs_update_akick_query, chanid, a->mask, a->added_by,
			a->added_by_acc, a->added_on, a->reason);
	if ((rc = dbase_query(db, sql)) != 0) {
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		return 0;
	}
	addlog(DEBUG, LOG_DBG_EXIT, "db_update_akick");
	return 1;

}
static int db_add_access(sqlite3 *db, NickInfo *n, myacc *a) {
	char sql[2048];
	char *sqlite_err = 0;
	int nick = find_nick_by_name(n->nick)->id;
	notice(as_name, "fish-guts", "Nick: %s (%i)", n->nick, nick);
	sprintf(sql, ns_update_access_query, nick, a->mask);
	if ((sqlite3_exec(db, sql, 0, 0, &sqlite_err)) != SQLITE_OK) {
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		return 0;
	}
	return 1;

}
static int db_add_auth(sqlite3 *db, NickInfo *n, auth *a) {
	char sql[2048];
	char *sqlite_err = 0;
	int target = find_nick_by_name(a->target)->id;
	int recipient = find_nick_by_name(a->sender)->id;
	sprintf(sql, ns_update_auth_query, a->type, target, recipient, a->date,
			a->status, a->acclevel);
	if ((sqlite3_exec(db, sql, 0, 0, &sqlite_err)) != SQLITE_OK) {
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		return 0;
	}
	return 1;
}
static void db_add_bot(bot *b) {
	addlog(DEBUG, LOG_DBG_ENTRY, "db_update_bot");
	char sql[2048];
	sqlite3 *db;
	sqlite3_stmt *stmt;
	const char *tail;
	int error = 0;
	int rc;
	if ((rc = sqlite3_open(DB, &db)) != SQLITE_OK) {
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		return;
	}

	sprintf(sql, bs_update_bot_query, b->name, b->password, b->username,
			b->realname);
	error = sqlite3_prepare_v2(db, sql, 1000, &stmt, &tail);
	if (error != SQLITE_OK) {
		addlog(2, LOG_ERR_SQLERROR, "in db_update_bots()");
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		sqlite3_close(db);
		return;
	}
	if ((rc = dbase_query(db, sql)) != 0) {
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		sqlite3_close(db);
		return;
	}
	sqlite3_close(db);
	addlog(DEBUG, LOG_DBG_EXIT, "db_update_bot");

}
static int db_add_chan(sqlite3 *db, ChanInfo *c) {
	char sql[4096];
	int rc;
	NickInfo *founder = find_nick_by_name(c->founder->nick);
	int successor;
	if (c->successor) {
		successor = find_nick_by_name(c->successor->nick)->id;
	} else {
		successor = -1;
	}
	int botid;
	if (c->bot) {
		botid = find_bot_by_name(c->bot)->id;
	} else {
		botid = -1;
	}
	sprintf(sql, cs_update_chan_query, c->name, c->pass, c->description,
			c->time_reg, c->aop_enabled, c->hop_enabled, c->sop_enabled,
			c->uop_enabled, c->vop_enabled, botid, founder->id, successor,
			c->mlock, c->topic, c->topic_user, c->topic_time, c->restricted,
			c->keeptopic, c->autovop, c->memolevel, c->leaveops, c->opwatch,
			c->url, c->topiclock);
	if ((rc = dbase_query(db, sql)) != 0) {
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		return 0;
	}
	return 1;
}
static int db_add_nick(sqlite3 *db, NickInfo *n) {
	char sql[2048];
	char *sqlite_err = 0;
	sprintf(sql, ns_update_nick_query, n->nick, n->pass, n->last_usermask,
			n->last_realname, n->last_seen, n->time_reg, n->hidemail,
			n->memomax, n->url, n->email, n->mforward_to, n->mforward, n->noop,
			n->nomemo, n->auth_chan, n->auth_notify, n->protect, n->mlock,
			n->mnotify);
	notice(as_name,"fish-guts","Mlock: %s",n->mlock);
	if ((sqlite3_exec(db, sql, 0, 0, &sqlite_err)) != SQLITE_OK) {
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		return 0;
	}
	return 1;
}
static int db_add_notify(sqlite3 *db, NickInfo *n, notify *no) {
	addlog(DEBUG, LOG_DBG_ENTRY, "db_add_notify");
	char sql[2048];
	int rc = 0;
	int nick = find_nick_by_name(n->nick)->id;
	int notify_nick = find_nick_by_name(no->nick->nick)->id;
	sprintf(sql, ns_update_notify_query, nick, notify_nick);
	if (!(rc = dbase_query(db, sql))) {
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		return 0;
	}
	addlog(DEBUG, LOG_DBG_EXIT, "db_add_notify");
	return 1;

}
static void db_add_op(op *o) {
	addlog(DEBUG, LOG_DBG_ENTRY, "db_update_op");
	char sql[2048];
	sqlite3 *db;
	sqlite3_stmt *stmt;
	const char *tail;
	int error = 0;
	int rc;
	if ((rc = sqlite3_open(DB, &db)) != SQLITE_OK) {
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		return;
	}
	int nickid = find_nick_by_name(o->nick->nick)->id;
	int chanid = find_chan_by_name(o->chan->name)->id;
	sprintf(sql, cs_update_op_query, o->level, nickid, chanid, o->addedby,
			o->addedbyacc, o->addedon);
	error = sqlite3_prepare_v2(db, sql, 1000, &stmt, &tail);
	if (error != SQLITE_OK) {
		addlog(2, LOG_ERR_SQLERROR, "in db_update_op()");
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		sqlite3_close(db);
		return;
	}
	if ((rc = dbase_query(db, sql)) != 0) {
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		sqlite3_close(db);
		return;
	}
	sqlite3_close(db);
	addlog(DEBUG, LOG_DBG_EXIT, "db_update_op");

}
int db_save_akicks(sqlite3 *db, ChanInfo *c) {
	addlog(1, LOG_DBG_ENTRY, "db_save_chans");
	akick *a = c->akicklist;
	while (a) {
		int rc = 0;
		if (!(rc = db_add_akick(db, c, a))) {
			return 0;
		}
		a = a->next;
	}
	return 1;
}
static int db_save_auth(sqlite3 *db, NickInfo *n) {
	addlog(1, LOG_DBG_ENTRY, "db_save_chans");
	auth *a = n->authlist;
	int rc = 0;
	while (a) {
		if (!(rc = db_add_auth(db, n, a))) {
			return 0;
		}
		a = a->next;
	}
	return 1;
}
static int db_save_access(sqlite3 *db, NickInfo *n) {
	addlog(1, LOG_DBG_ENTRY, "db_save_access");
	myacc *a = n->accesslist;
	int rc = 0;
	while (a) {
		if (!(rc = db_add_access(db, n, a))) {
			return -1;
		}
		a = a->next;
	}
	return 1;
}
void db_save_bots(void) {
	addlog(1, LOG_DBG_ENTRY, "db_save_bots");
	bot *b = botlist;
	while (b) {
		db_add_bot(b);
		b = b->next;
	}
}

void db_save_chans(void) {
	addlog(1, LOG_DBG_ENTRY, "db_save_chans");
	sqlite3 *db;
	int query_result = 0;
	int rc;
	if ((rc = sqlite3_open(DB, &db)) != SQLITE_OK) {
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		return;
	}
	ChanInfo *c = chans;
	sqlite3_exec(db, "BEGIN", 0, 0, 0);
	while (c) {
		if ((query_result = db_add_chan(db, c))) {
			sqlite3_exec(db, "ROLLBACK", 0, 0, 0);
			sqlite3_close(db);
			return;
		}
		if ((query_result = db_save_akicks(db, c))) {
			sqlite3_exec(db, "ROLLBACK", 0, 0, 0);
			sqlite3_close(db);
			return;
		}
		c = c->next;
	}
	sqlite3_exec(db, "COMMIT", 0, 0, 0);
	sqlite3_close(db);
	return;
}
void db_save_nicks(void) {
	sqlite3 *db;
	int query_result = 0;
	int rc;
	if ((rc = sqlite3_open(DB, &db)) != SQLITE_OK) {
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		return;
	}
	sqlite3_exec(db, "BEGIN", 0, 0, 0);
	sqlite3_exec(db, "DELETE FROM NICKS", 0, 0, 0);
	sqlite3_exec(db, "DELETE FROM NS_ACCESS", 0, 0, 0);
	sqlite3_exec(db, "DELETE FROM NS_AUTH", 0, 0, 0);
	sqlite3_exec(db, "DELETE FROM NS_NOTIFY", 0, 0, 0);
	NickInfo *n = nicklist;
	while (n) {
		if (!(query_result = db_add_nick(db, n))) {
			addlog(2, "Error in db_add_nick, rolling back");
			sqlite3_exec(db, "ROLLBACK", 0, 0, 0);
			sqlite3_close(db);
			return;
		}
		update_nick_id(n);
		if (!(query_result = db_save_auth(db, n))) {
			addlog(2, "Error in db_save_auth, rolling back");
			sqlite3_exec(db, "ROLLBACK", 0, 0, 0);
			sqlite3_close(db);
			return;
		}
		if (!(query_result = db_save_notify(db, n))) {
			addlog(2, "Error in db_save_notify, rolling back");
			sqlite3_exec(db, "ROLLBACK", 0, 0, 0);
			sqlite3_close(db);
			return;
		}
		if (!(query_result = db_save_access(db, n))) {
			addlog(2, "Error in db_save_access, rolling back");
			sqlite3_exec(db, "ROLLBACK", 0, 0, 0);
			sqlite3_close(db);
			return;
		}
		n = n->next;
	}
	sqlite3_exec(db, "COMMIT", 0, 0, 0);
	sqlite3_close(db);
	return;
}
static void update_nick_id(NickInfo *n) {
	int i = find_nick_by_name(n->nick)->id;
	n->id = i;
}
static int db_save_notify(sqlite3 *db, NickInfo *n) {
	addlog(1, LOG_DBG_ENTRY, "db_save_notify");
	notify *no = n->notifylist;
	int rc = 0;
	while (no) {
		if (!(rc = db_add_notify(db, n, no))) {
			return 0;
		}
		no = no->next;
	}
	return 1;
}

void db_save_ops(void) {
	addlog(1, LOG_DBG_ENTRY, "db_save_ops");
	op *o = global_op_list;
	while (o) {
		db_add_op(o);
		o = o->next;
	}
	return;
}

int dbase_query(sqlite3 *db, char *qry) {
	char *sqlite_err = 0;
	if ((sqlite3_exec(db, qry, 0, 0, &sqlite_err)) != SQLITE_OK) {
		addlog(2, LOG_ERR_SQLERROR, "in dbase_query()", qry);
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		sqlite3_free(sqlite_err);
		return 0;
	} else {
		return 1;
	}
}
static void empty_bs(void) {
	char *sql = "DELETE FROM BOTS";
	sqlite3 *db;
	sqlite3_stmt *stmt;
	const char *tail;
	int error = 0;
	int rc;
	if ((rc = sqlite3_open(DB, &db)) != SQLITE_OK) {
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		return;
	}
	error = sqlite3_prepare_v2(db, sql, 1000, &stmt, &tail);
	if (error != SQLITE_OK) {
		addlog(2, LOG_ERR_SQLERROR, "in empty_bs()");
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		sqlite3_close(db);
		return;
	}
	if ((rc = dbase_query(db, sql)) != 0) {
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		sqlite3_close(db);
		return;
	}
	sqlite3_close(db);
	addlog(DEBUG, LOG_DBG_EXIT, "empty_bs");
	sqlite3_close(db);
}
static void empty_cs(void) {
	char *sql = "DELETE FROM CHANS";
	sqlite3 *db;
	sqlite3_stmt *stmt;
	const char *tail;
	int error = 0;
	int rc;
	if ((rc = sqlite3_open(DB, &db)) != SQLITE_OK) {
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		return;
	}
	error = sqlite3_prepare_v2(db, sql, 1000, &stmt, &tail);
	if (error != SQLITE_OK) {
		addlog(2, LOG_ERR_SQLERROR, "in empty_cs()");
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		sqlite3_close(db);
		return;
	}
	if ((rc = dbase_query(db, sql)) != 0) {
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		sqlite3_close(db);
		return;
	}
	sqlite3_close(db);
	addlog(DEBUG, LOG_DBG_EXIT, "empty_cs");
	sqlite3_close(db);
}
static void empty_cs_akick(void) {
	char *sql = "DELETE FROM CS_AKICK";
	sqlite3 *db;
	sqlite3_stmt *stmt;
	const char *tail;
	int error = 0;
	int rc;
	if ((rc = sqlite3_open(DB, &db)) != SQLITE_OK) {
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		return;
	}
	error = sqlite3_prepare_v2(db, sql, 1000, &stmt, &tail);
	if (error != SQLITE_OK) {
		addlog(2, LOG_ERR_SQLERROR, "in empty_cs_akick()");
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		sqlite3_close(db);
		return;
	}
	if ((rc = dbase_query(db, sql)) != 0) {
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		sqlite3_close(db);
		return;
	}
	sqlite3_close(db);
	addlog(DEBUG, LOG_DBG_EXIT, "empty_cs_akick");
	sqlite3_close(db);
}
static void empty_ns(void) {
	char *sql = "DELETE FROM NICKS";
	sqlite3 *db;
	sqlite3_stmt *stmt;
	const char *tail;
	int error = 0;
	int rc;
	if ((rc = sqlite3_open(DB, &db)) != SQLITE_OK) {
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		return;
	}
	error = sqlite3_prepare_v2(db, sql, 1000, &stmt, &tail);
	if (error != SQLITE_OK) {
		addlog(2, LOG_ERR_SQLERROR, "in empty_ns()");
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		sqlite3_close(db);
		return;
	}
	if ((rc = dbase_query(db, sql)) != 0) {
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		sqlite3_close(db);
		return;
	}
	sqlite3_close(db);
	addlog(DEBUG, LOG_DBG_EXIT, "empty_ns");
	sqlite3_close(db);
}
static void empty_ns_access(void) {
	char *sql = "DELETE FROM NS_ACCESS";
	sqlite3 *db;
	sqlite3_stmt *stmt;
	const char *tail;
	int error = 0;
	int rc;
	if ((rc = sqlite3_open(DB, &db)) != SQLITE_OK) {
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		return;
	}
	error = sqlite3_prepare_v2(db, sql, 1000, &stmt, &tail);
	if (error != SQLITE_OK) {
		addlog(2, LOG_ERR_SQLERROR, "in empty_ns_access()");
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		sqlite3_close(db);
		return;
	}
	if ((rc = dbase_query(db, sql)) != 0) {
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		sqlite3_close(db);
		return;
	}
	sqlite3_close(db);
	addlog(DEBUG, LOG_DBG_EXIT, "empty_ns_access");
	sqlite3_close(db);
}
static void empty_ns_auth(void) {
	char *sql = "DELETE FROM NS_AUTH";
	sqlite3 *db;
	sqlite3_stmt *stmt;
	const char *tail;
	int error = 0;
	int rc;
	if ((rc = sqlite3_open(DB, &db)) != SQLITE_OK) {
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		return;
	}
	error = sqlite3_prepare_v2(db, sql, 1000, &stmt, &tail);
	if (error != SQLITE_OK) {
		addlog(2, LOG_ERR_SQLERROR, "in empty_ns_auth()");
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		sqlite3_close(db);
		return;
	}
	if ((rc = dbase_query(db, sql)) != 0) {
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		sqlite3_close(db);
		return;
	}
	sqlite3_close(db);
	addlog(DEBUG, LOG_DBG_EXIT, "empty_ns_auth");
	sqlite3_close(db);
}
static void empty_ns_notify(void) {
	char *sql = "DELETE FROM NS_NOTIFY";
	sqlite3 *db;
	sqlite3_stmt *stmt;
	const char *tail;
	int error = 0;
	int rc;
	if ((rc = sqlite3_open(DB, &db)) != SQLITE_OK) {
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		return;
	}
	error = sqlite3_prepare_v2(db, sql, 1000, &stmt, &tail);
	if (error != SQLITE_OK) {
		addlog(2, LOG_ERR_SQLERROR, "in empty_ns_notify()");
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		sqlite3_close(db);
		return;
	}
	if ((rc = dbase_query(db, sql)) != 0) {
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		sqlite3_close(db);
		return;
	}
	sqlite3_close(db);
	addlog(DEBUG, LOG_DBG_EXIT, "empty_ns_notify");
	sqlite3_close(db);
}
static void empty_ops(void) {
	char *sql = "DELETE FROM OP_LIST";
	sqlite3 *db;
	sqlite3_stmt *stmt;
	const char *tail;
	int error = 0;
	int rc;
	if ((rc = sqlite3_open(DB, &db)) != SQLITE_OK) {
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		return;
	}
	error = sqlite3_prepare_v2(db, sql, 1000, &stmt, &tail);
	if (error != SQLITE_OK) {
		addlog(2, LOG_ERR_SQLERROR, "in empty_ops()");
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		sqlite3_close(db);
		return;
	}
	if ((rc = dbase_query(db, sql)) != 0) {
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		sqlite3_close(db);
		return;
	}
	sqlite3_close(db);
	addlog(DEBUG, LOG_DBG_EXIT, "empty_ops");
	sqlite3_close(db);
}
void empty_tables(void) {
	empty_bs();
	empty_cs();
	empty_cs_akick();
	empty_ops();
}

static bot *find_bot_by_name(char *nick) {
	char sql[256];
	sqlite3 *db;
	sqlite3_stmt *stmt;
	const char *tail;
	int error = 0;
	int rc;
	bot *b = scalloc(sizeof(bot), 1);
	if ((rc = sqlite3_open(DB, &db)) == SQLITE_OK) {
		sprintf(sql, "SELECT * FROM BOTS WHERE BOTS.NICKNAME='%s';", nick);
		error = sqlite3_prepare_v2(db, sql, 1000, &stmt, &tail);
		if (error != SQLITE_OK) {
			addlog(2, LOG_ERR_SQLERROR, "in find_nick_by_name()");
			addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
			return NULL;
		}
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			b->id = sqlite3_column_int(stmt, 0);
			b->name = sstrdup((char*) sqlite3_column_text(stmt, 1));
			b->password = sstrdup((char*) sqlite3_column_text(stmt, 2));
			b->realname = sstrdup((char*) sqlite3_column_text(stmt, 3));
			b->username = sstrdup((char*) sqlite3_column_text(stmt, 4));
			b->chanlist = NULL;
		}
	}
	sqlite3_close(db);
	return b;

}
static ChanInfo *find_chan_by_name(char *chan) {
	char sql[256];
	sqlite3 *db;
	sqlite3_stmt *stmt;
	const char *tail;
	int error = 0;
	int rc;
	ChanInfo *c = scalloc(sizeof(ChanInfo), 1);
	if ((rc = sqlite3_open(DB, &db)) == SQLITE_OK) {
		sprintf(sql, "SELECT CHAN_ID FROM CHANS WHERE CHANS.NAME='%s';", chan);
		error = sqlite3_prepare_v2(db, sql, 1000, &stmt, &tail);
		if (error != SQLITE_OK) {
			addlog(2, LOG_ERR_SQLERROR, "in find_chan_by_name()");
			addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
			return NULL;
		}
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			c->id = sqlite3_column_int(stmt, 0);
		}
	}
	sqlite3_close(db);
	return c;

}

static NickInfo *find_nick_by_name(char *nick) {
	char sql[256];
	sqlite3 *db;
	sqlite3_stmt *stmt;
	const char *tail;
	int error = 0;
	int rc;
	NickInfo *n = scalloc(sizeof(NickInfo), 1);
	if ((rc = sqlite3_open(DB, &db)) == SQLITE_OK) {
		sprintf(sql, "SELECT * FROM NICKS WHERE NICKS.NICKNAME='%s';", nick);
		error = sqlite3_prepare_v2(db, sql, 1000, &stmt, &tail);
		if (error != SQLITE_OK) {
			addlog(2, LOG_ERR_SQLERROR, "in find_nick_by_name()");
			addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
			return NULL;
		}
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			n->id = sqlite3_column_int(stmt, 0);
			strscpy(n->nick, (char*) sqlite3_column_text(stmt, 1), NICKMAX);
			strscpy(n->pass, (char*) sqlite3_column_text(stmt, 2), PASSMAX);
			n->last_usermask = sstrdup((char*) sqlite3_column_text(stmt, 3));
			n->last_realname = sstrdup((char*) sqlite3_column_text(stmt, 4));
			n->last_seen = sqlite3_column_int(stmt, 5);
			n->time_reg = sqlite3_column_int(stmt, 6);
			n->hidemail = sqlite3_column_int(stmt, 7);
			n->memomax = sqlite3_column_int(stmt, 8);
			n->url = sstrdup((char*) sqlite3_column_text(stmt, 9));
			n->email = sstrdup((char*) sqlite3_column_text(stmt, 10));
			if ((char*) sqlite3_column_text(stmt, 11)) {
				n->mforward_to = sstrdup((char*) sqlite3_column_text(stmt, 11));
			} else {
				n->mforward_to = NULL;
			}
			n->mforward = sqlite3_column_int(stmt, 12);
			n->noop = sqlite3_column_int(stmt, 13);
			n->nomemo = sqlite3_column_int(stmt, 14);
			n->auth_chan = sqlite3_column_int(stmt, 15);
			n->auth_notify = sqlite3_column_int(stmt, 16);
			n->protect = sqlite3_column_int(stmt, 17);
			n->mlock = (char*) sqlite3_column_text(stmt, 18);
			n->mnotify = sqlite3_column_int(stmt, 19);
			n->notifylist = NULL;
			n->accesslist = NULL;
		}
	}
	sqlite3_close(db);
	return n;
}
static void install_bs(void) {
	bs_install_bots();
}
static void install_cs(void) {
	cs_install_chans();
	cs_install_acc_level();
	cs_install_op_list();
	cs_install_op_type();
}
void install_db(void) {
	install_ns();
	install_bs();
	install_cs();
}
static void install_ns() {
	addlog(1, LOG_DBG_ENTRY, "install_ns");
	ns_install_nicks();
	ns_install_access();
	ns_install_auth_status();
	ns_install_notify();
	ns_install_target_type();
	ns_install_auth();
	addlog(1, LOG_DBG_EXIT, "install_ns");
}

static void load_main(void) {

}

static void install_table(const char *sql) {
	char *sqlite_err = 0;
	sqlite3 *db;
	int rc;
	if ((rc = sqlite3_open(DB, &db)) == SQLITE_OK) {

		if ((sqlite3_exec(db, sql, 0, 0, &sqlite_err)) != SQLITE_OK) {
			sqlite3_free(sqlite_err);
			addlog(2, LOG_ERR_SQLERROR, "in install table()", sql);
			addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		}
	}
	sqlite3_close(db);
	return;
}
static void load_access(void) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	const char *tail;
	int error = 0;
	int rc;
	if ((rc = sqlite3_open(DB, &db)) == SQLITE_OK) {
		error = sqlite3_prepare_v2(db, load_ns_access, 1000, &stmt, &tail);
		if (error != SQLITE_OK) {
			addlog(2, LOG_ERR_SQLERROR, "in load_access()");
			addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		}
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			NickInfo *n = findnick((const char*) sqlite3_column_text(stmt, 1));
			myacc *a = scalloc(sizeof(myacc), 1);
			a->next = n->accesslist;
			if (n->accesslist)
				n->accesslist->prev = a;
			a->id = sqlite3_column_int(stmt, 0);
			a->mask = sstrdup((const char*) sqlite3_column_text(stmt, 2));
			n->accesslist = a;
		}
	}
	sqlite3_close(db);
}

static void load_akick(void) {
	addlog(DEBUG, LOG_DBG_ENTRY, "load_akick");
	sqlite3 *db;
	sqlite3_stmt *stmt;
	const char *tail;
	int error = 0;
	int rc;
	if ((rc = sqlite3_open(DB, &db)) == SQLITE_OK) {
		error = sqlite3_prepare_v2(db, cs_load_akick, 1000, &stmt, &tail);
		if (error != SQLITE_OK) {
			addlog(2, LOG_ERR_SQLERROR, "in load_akick()");
			addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		}
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			ChanInfo *c = find_chan_by_id(sqlite3_column_int(stmt, 1));
			akick *ak = scalloc(sizeof(akick), 1);
			ak->next = c->akicklist;
			if (c->akicklist)
				c->akicklist->prev = ak;

			c->akicklist = ak;
			ak->id = sqlite3_column_int(stmt, 0);
			ak->mask = sstrdup((const char*) sqlite3_column_text(stmt, 2));
			ak->added_by = sstrdup((const char*) sqlite3_column_text(stmt, 3));
			ak->added_by_acc = sqlite3_column_int(stmt, 4);
			ak->added_on = sqlite3_column_int(stmt, 5);
			ak->reason = sstrdup((const char*) sqlite3_column_text(stmt, 6));
		}
	}
	addlog(DEBUG, LOG_DBG_EXIT, "load_akick");
	sqlite3_close(db);
}
static void load_auth(void) {
	addlog(1, LOG_DBG_ENTRY, "load_auth");
	sqlite3 *db;
	sqlite3_stmt *stmt;
	const char *tail;
	int error = 0;
	int rc = 0;
	if ((rc = sqlite3_open(DB, &db)) == SQLITE_OK) {
		error = sqlite3_prepare_v2(db, load_ns_auth, 1000, &stmt, &tail);
		if (error != SQLITE_OK) {
			addlog(2, LOG_ERR_SQLERROR, "in load_auth()");
			addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		}
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			NickInfo *n = findnick((const char*) sqlite3_column_text(stmt, 3));
			auth *a = scalloc(sizeof(auth), 1);
			a->next = n->authlist;
			if (n->authlist)
				n->authlist->prev = a;
			n->authlist = a;
			a->type = sqlite3_column_int(stmt, 0);
			a->target = sstrdup((const char*) sqlite3_column_text(stmt, 1));
			a->sender = sstrdup((const char*) sqlite3_column_text(stmt, 2));
			a->date = sqlite3_column_int(stmt, 4);
			a->status = sqlite3_column_int(stmt, 5);
			a->acclevel = sqlite3_column_int(stmt, 6);
		}
	}
	sqlite3_close(db);
}
void load_botserv(void) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	const char *tail;
	int error = 0;
	int rc;
	if ((rc = sqlite3_open(DB, &db)) == SQLITE_OK) {
		error = sqlite3_prepare_v2(db, "SELECT * FROM BOTS", 1000, &stmt,
				&tail);
		if (error != SQLITE_OK) {
			addlog(2, LOG_ERR_SQLERROR, "in load_botserv()");
			addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		}
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			int id = sqlite3_column_int(stmt, 0);
			char *name = sstrdup((const char*) sqlite3_column_text(stmt, 1));
			char *password = sstrdup(
					(const char*) sqlite3_column_text(stmt, 2));
			char *username = sstrdup(
					(const char*) sqlite3_column_text(stmt, 3));
			char *realname = sstrdup(
					(const char*) sqlite3_column_text(stmt, 4));
			load_bot(id, name, password, username, realname);
		}
	}
	sqlite3_close(db);
}
void load_chans(void) {
	addlog(DEBUG, LOG_DBG_ENTRY, "load_chans");
	sqlite3 *db;
	sqlite3_stmt *stmt;
	const char *tail;
	int error = 0;
	int rc;
	if ((rc = sqlite3_open(DB, &db)) == SQLITE_OK) {
		error = sqlite3_prepare_v2(db, load_cs_chans, 1000, &stmt, &tail);
		if (error != SQLITE_OK) {
			addlog(2, LOG_ERR_SQLERROR, "in load_chans()");
			addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		}
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			ChanInfo *c = scalloc(sizeof(ChanInfo), 1);
			c->id = sqlite3_column_int(stmt, 0);
			strscpy(c->name, (char*) sqlite3_column_text(stmt, 1), NICKMAX);
			strscpy(c->pass, (char*) sqlite3_column_text(stmt, 2), PASSMAX);
			c->time_reg = sqlite3_column_int(stmt, 3);
			c->aop_enabled = sqlite3_column_int(stmt, 4);
			c->hop_enabled = sqlite3_column_int(stmt, 5);
			c->sop_enabled = sqlite3_column_int(stmt, 6);
			c->uop_enabled = sqlite3_column_int(stmt, 7);
			c->vop_enabled = sqlite3_column_int(stmt, 8);
			if (sqlite3_column_text(stmt, 9)) {
				c->bot = sstrdup((char*) sqlite3_column_text(stmt, 9));
				add_bot_to_chan(c->bot, c->name);
				add_bot(c->name, c->name);
			} else {
				c->bot = NULL;
			}
			c->founder = findnick((char*) sqlite3_column_text(stmt, 10));
			if (sqlite3_column_text(stmt, 11)) {
				c->successor = findnick((char*) sqlite3_column_text(stmt, 11));
			} else {
				c->successor = NULL;
			}
			c->mlock = sstrdup((char*) sqlite3_column_text(stmt, 12));
			if (sqlite3_column_text(stmt, 13)) {
				c->topic = sstrdup((char*) sqlite3_column_text(stmt, 13));
			}
			if (sqlite3_column_text(stmt, 14)) {
				c->topic_user = sstrdup((char*) sqlite3_column_text(stmt, 14));
			}
			if (sqlite3_column_int(stmt, 15)) {
				c->topic_time = sqlite3_column_int(stmt, 15);
			}
			c->restricted = sqlite3_column_int(stmt, 16);
			c->keeptopic = sqlite3_column_int(stmt, 17);
			c->autovop = sqlite3_column_int(stmt, 18);
			c->memolevel = sqlite3_column_int(stmt, 19);
			c->leaveops = sqlite3_column_int(stmt, 20);
			c->opwatch = sqlite3_column_int(stmt, 21);
			c->url = sstrdup((char*) sqlite3_column_text(stmt, 22));
			c->topiclock = sqlite3_column_int(stmt, 23);
			strscpy(c->description, (char*) sqlite3_column_text(stmt, 24),
			DESCMAX);
			c->akicklist = NULL;
			c->next = chans;
			if (chans)
				chans->prev = c;
			chans = c;
		}
	}
	sqlite3_close(db);
	addlog(DEBUG, LOG_DBG_EXIT, "load_chans");
}
void load_chanserv(void) {
	load_chans();
	load_akick();
	load_ops();
}

void load_database(void) {
	addlog(1, LOG_DBG_ENTRY, "load_database");
	load_main();
	if (bs_enabled) {
		load_botserv();
	}
	if (ns_enabled) {
		load_nickserv();
	}
	if (cs_enabled) {
		load_chanserv();
	}
	addlog(1, LOG_DBG_EXIT, "load_database");
}

static void load_nicks(void) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	const char *tail;
	int error = 0;
	int rc;
	if ((rc = sqlite3_open(DB, &db)) == SQLITE_OK) {
		error = sqlite3_prepare_v2(db, "select * from nicks", 1000, &stmt,
				&tail);
		if (error != SQLITE_OK) {
			addlog(2, LOG_ERR_SQLERROR, "in load_nicks()");
			addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		}
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			NickInfo *n = scalloc(sizeof(NickInfo), 1);
			n->id = sqlite3_column_int(stmt, 0);
			strscpy(n->nick, (char*) sqlite3_column_text(stmt, 1), NICKMAX);
			strscpy(n->pass, (char*) sqlite3_column_text(stmt, 2), PASSMAX);
			n->last_usermask = sstrdup((char*) sqlite3_column_text(stmt, 3));
			n->last_realname = sstrdup((char*) sqlite3_column_text(stmt, 4));
			n->last_seen = sqlite3_column_int(stmt, 5);
			n->time_reg = sqlite3_column_int(stmt, 6);
			n->hidemail = sqlite3_column_int(stmt, 7);
			n->memomax = sqlite3_column_int(stmt, 8);
			n->url = sstrdup((char*) sqlite3_column_text(stmt, 9));
			n->email = sstrdup((char*) sqlite3_column_text(stmt, 10));
			if ((char*) sqlite3_column_text(stmt, 11)) {
				n->mforward_to = sstrdup((char*) sqlite3_column_text(stmt, 11));
			} else {
				n->mforward_to = NULL;
			}
			n->mforward = sqlite3_column_int(stmt, 12);
			n->noop = sqlite3_column_int(stmt, 13);
			n->nomemo = sqlite3_column_int(stmt, 14);
			n->auth_chan = sqlite3_column_int(stmt, 15);
			n->auth_notify = sqlite3_column_int(stmt, 16);
			n->protect = sqlite3_column_int(stmt, 17);
			n->mlock = sstrdup((char*) sqlite3_column_text(stmt, 18));
			n->mnotify = sqlite3_column_int(stmt, 19);
			n->notifylist = NULL;
			n->accesslist = NULL;
			n->next = nicklist;
			if (nicklist)
				nicklist->prev = n;
			nicklist = n;
		}
	}
	sqlite3_close(db);
}

static void load_nickserv(void) {
	load_nicks();
	load_access();
	load_auth();
	load_notify();
}
static void load_notify(void) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	const char *tail;
	int error = 0;
	int rc;
	if ((rc = sqlite3_open(DB, &db)) == SQLITE_OK) {
		error = sqlite3_prepare_v2(db, load_ns_notify, 1000, &stmt, &tail);
		if (error != SQLITE_OK) {
			addlog(2, LOG_ERR_SQLERROR, "in load_notify()");
			addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		}
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			NickInfo *n = findnick((const char*) sqlite3_column_text(stmt, 0));
			notify *no = scalloc(sizeof(notify), 1);
			no->next = n->notifylist;
			if (n->notifylist)
				n->notifylist->prev = no;
			n->notifylist = no;
			no->nick = findnick((const char*) sqlite3_column_text(stmt, 1));
		}
	}
	sqlite3_close(db);
}
static void load_ops(void) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	const char *tail;
	int error = 0;
	int rc;
	if ((rc = sqlite3_open(DB, &db)) == SQLITE_OK) {
		error = sqlite3_prepare_v2(db, "select * from OP_LIST", 1000, &stmt,
				&tail);
		if (error != SQLITE_OK) {
			addlog(2, LOG_ERR_SQLERROR, "in load_ops()");
			addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		}
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			op *o = scalloc(sizeof(op), 1);
			o->id = sqlite3_column_int(stmt, 0);
			o->level = sqlite3_column_int(stmt, 1);
			o->nick = find_nick_by_id(sqlite3_column_int(stmt, 2));
			o->chan = find_chan_by_id(sqlite3_column_int(stmt, 3));
			o->addedby = sstrdup((const char*) sqlite3_column_text(stmt, 4));
			o->addedbyacc = sqlite3_column_int(stmt, 5);
			o->addedon = sqlite3_column_int(stmt, 6);
			o->next = global_op_list;
			if (global_op_list)
				global_op_list->prev = o;
			global_op_list = o;
		}
	}
	sqlite3_close(db);
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
static void save_botserv_db(void) {
	db_save_bots();
}
static void save_chanserv_db(void) {
	db_save_chans();
	db_save_ops();
}
static void save_nickserv_db(void) {
	db_save_nicks();
}

void save_database(void) {
	struct timeval stop, start;
	gettimeofday(&start, NULL);
	double start_mill = (start.tv_sec) * 1000 + (start.tv_usec) / 1000;
	empty_tables();
	save_botserv_db();
	save_nickserv_db();
	save_chanserv_db();
	gettimeofday(&stop, NULL);
	double end_mill = (stop.tv_sec) * 1000 + (stop.tv_usec) / 1000;
	double time = end_mill - start_mill;

	globops(s_name, "Database written to disk (%.2f s)", time / 1000.0);
}
/* EOF */
