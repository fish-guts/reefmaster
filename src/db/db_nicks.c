/*
 * db_nicks.c
 *
 *  Created on: Jun 18, 2016
 *      Author: severin
 */

#include "main.h"
#include "db/db_nicks.h"

static int db_add_access(sqlite3 *db, NickInfo *n, myacc *a);
static int db_add_auth(sqlite3 *db, NickInfo *n, auth *a);
static int db_add_nick(sqlite3 *db, NickInfo *n);
static int db_add_notify(sqlite3 *db, NickInfo *n, notify *no);
static void db_save_access(void);
static void load_notify(void);
static void load_access(void);

/****************************************************************************************/
/**
 * query for adding a nickname
 */
static int db_add_nick(sqlite3 *db, NickInfo *n) {
	char sql[2048];
	char *sqlite_err = 0;
	sprintf(sql,
			ns_update_nick_query,
			n->id,
			n->nick,
			n->pass,
			n->last_usermask,
			n->last_realname,
			n->last_seen,
			n->time_reg,
			n->hidemail,
			n->memomax,
			n->url,
			n->email,
			n->mforward,
			n->noop,
			n->nomemo,
			n->auth_chan,
			n->auth_notify,
			n->protect,
			n->mlock,
			n->mnotify);
	if ((sqlite3_exec(db, sql, 0, 0, &sqlite_err)) != SQLITE_OK) {
		addlog(LOG_ERROR, "Error in Function db_add_nick");
		addlog(LOG_ERROR, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		return SQL_ERROR;
	}
	return SQL_OK;
}

/****************************************************************************************/
/**
 * query for adding an access entry
 */
static int db_add_access(sqlite3 *db, NickInfo *n, myacc *a) {
	char sql[2048];
	char *sqlite_err = 0;
	sprintf(sql, ns_update_access_query, n->id, a->mask);
	if ((sqlite3_exec(db, sql, 0, 0, &sqlite_err)) != SQLITE_OK) {
		addlog(LOG_ERROR, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		return SQL_ERROR;
	}
	return SQL_OK;
}

/****************************************************************************************/
/**
 * query for adding an auth entry
 */
static int db_add_auth(sqlite3 *db, NickInfo *n, auth *a) {
	char sql[2048];
	char *sqlite_err = 0;
	int target = 0;
	if(a->type==0) {
		target = findnick(a->target)->id;
	} else {
		target = findchan(a->target)->id;
	}
	int recipient = findnick(a->sender)->id;
	sprintf(sql, ns_update_auth_query, a->type, target,n->id, recipient, a->date,
			a->status, a->acclevel);
	if ((sqlite3_exec(db, sql, 0, 0, &sqlite_err)) != SQLITE_OK) {
		addlog(LOG_ERROR, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		return SQL_ERROR;
	}
	return SQL_OK;
}

/****************************************************************************************/
/**
 * query for adding a notify entry
 */
static int db_add_notify(sqlite3 *db, NickInfo *n, notify *no) {
	char sql[2048];
	char *sqlite_err = 0;
	int notify_nick = findnick(no->nick->nick)->id;
	sprintf(sql, ns_update_notify_query, n->id, notify_nick);
	if ((sqlite3_exec(db, sql, 0, 0, &sqlite_err)) != SQLITE_OK) {
		addlog(LOG_ERROR, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		return SQL_ERROR;
	}
	return SQL_OK;
}

/****************************************************************************************/
/**
 * query for saving the access entries
 * inserting queries in other function
 * will be commited in the end
 */
static void db_save_access(void) {
	addlog(LOG_DEBUG, LOG_DBG_ENTRY, "db_save_access");
	sqlite3 *db;
	if (sqlite3_open(DB, &db) != SQLITE_OK) {
		addlog(LOG_ERROR, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		return;
	}
	sqlite3_exec(db, "BEGIN", 0, 0, 0);
	sqlite3_exec(db, "DROP TABLE IF EXISTS NS_ACCESS", 0, 0, 0);
	sqlite3_exec(db, ns_create_access_table, 0, 0, 0);
	NickInfo *n = nicklist;
	while (n) {
		myacc *a = n->accesslist;
		while(a) {
			if (db_add_access(db, n, a) != SQL_OK) {
			addlog(LOG_ERROR, "Error in db_add_access, rolling back");
			sqlite3_exec(db, "ROLLBACK", 0, 0, 0);
			sqlite3_close(db);
			return;
		}
			a = a->next;
		}
		n = n->next;
	}
	sqlite3_exec(db, "COMMIT", 0, 0, 0);
	sqlite3_close(db);
	return;
}

/****************************************************************************************/
/**
 * query for saving the notify entries
 * inserting queries in other function
 * will be commited in the end
 */
static void db_save_notify(void) {

	sqlite3 *db;
	if (sqlite3_open(DB, &db) != SQLITE_OK) {
		addlog(LOG_ERROR, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		return;
	}
	sqlite3_exec(db, "BEGIN", 0, 0, 0);
	sqlite3_exec(db, "DROP TABLE IF EXISTS NS_NOTIFY", 0, 0, 0);
	sqlite3_exec(db, ns_create_notify_table, 0, 0, 0);
	NickInfo *n = nicklist;
	while (n) {
		notify *no = n->notifylist;
		while(no) {
			if (db_add_notify(db, n, no) != SQL_OK) {
			addlog(LOG_ERROR, "Error in db_add_notify, rolling back");
			sqlite3_exec(db, "ROLLBACK", 0, 0, 0);
			sqlite3_close(db);
			return;
		}
			no = no->next;
		}
		n = n->next;
	}
	sqlite3_exec(db, "COMMIT", 0, 0, 0);
	sqlite3_close(db);
	return;
}


/****************************************************************************************/
/**
 * query for saving the nicks
 * inserting queries in other function
 * will be commited in the end
 */
void db_save_nicks(void) {
	sqlite3 *db;
	if (sqlite3_open(DB, &db) != SQLITE_OK) {
		addlog(LOG_ERROR, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		return;
	}
	sqlite3_exec(db, "BEGIN", 0, 0, 0);
	sqlite3_exec(db, "DROP TABLE IF EXISTS NICKS", 0, 0, 0);
	sqlite3_exec(db, ns_create_nicks_table, 0, 0, 0);
	NickInfo *n = nicklist;
	int rc;
	while (n) {
		if ((rc = db_add_nick(db, n) != SQL_OK)) {
			addlog(LOG_ERROR, "Error in db_add_nick, rolling back");
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

/****************************************************************************************/
/**
 * load the access table into the memory
 */
static void load_access(void) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	const char *tail;
	if (sqlite3_open(DB, &db) == SQLITE_OK) {
		int error = sqlite3_prepare_v2(db, load_ns_access, 1000, &stmt, &tail);
		if (error != SQLITE_OK) {
			addlog(LOG_ERROR, LOG_ERR_SQLERROR, "in load_access()");
			addlog(LOG_ERROR, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
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

/****************************************************************************************/
/**
 * load the auth table into the memory
 */
static void load_auth(void) {
	addlog(LOG_DEBUG, LOG_DBG_ENTRY, "load_auth");
	sqlite3 *db;
	sqlite3_stmt *stmt;
	const char *tail;
	if (sqlite3_open(DB, &db) == SQLITE_OK) {
		int error = sqlite3_prepare_v2(db, load_ns_auth, 1000, &stmt, &tail);
		if (error != SQLITE_OK) {
			addlog(LOG_ERROR, LOG_ERR_SQLERROR, "in load_auth()");
			addlog(LOG_ERROR, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
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

/****************************************************************************************/
/**
 * load nickserv tables
 */
static void load_nicks(void) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	const char *tail;

	if (sqlite3_open(DB, &db) == SQLITE_OK) {
		int error = sqlite3_prepare_v2(db, "select * from nicks ORDER BY NICKS.NICK_ID ASC", 1000, &stmt,
				&tail);
		if (error != SQLITE_OK) {
			addlog(LOG_ERROR, LOG_ERR_SQLERROR, "in load_nicks()");
			addlog(LOG_ERROR, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		}
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			NickInfo *n = scalloc(sizeof(NickInfo), 1);
			n->id = sqlite3_column_int(stmt, NICK_ID);
			strscpy(n->nick, (char*) sqlite3_column_text(stmt, NICK_NICKNAME), NICKMAX);
			strscpy(n->pass, (char*) sqlite3_column_text(stmt, NICK_PASSWORD), PASSMAX);
			n->last_usermask = sstrdup((char*) sqlite3_column_text(stmt, NICK_MASK));
			n->last_realname = sstrdup((char*) sqlite3_column_text(stmt, NICK_REALNAME));
			n->last_seen = sqlite3_column_int(stmt, NICK_LAST_SEEN);
			n->time_reg = sqlite3_column_int(stmt, NICK_REGISTERED);
			n->hidemail = sqlite3_column_int(stmt, NICK_HIDEMAIL);
			n->memomax = sqlite3_column_int(stmt, NICK_MEMOMAX);
			n->url = sstrdup((char*) sqlite3_column_text(stmt, NICK_URL));
			n->email = sstrdup((char*) sqlite3_column_text(stmt, NICK_EMAIL));
			n->mforward = sqlite3_column_int(stmt, NICK_MFORWARD);
			n->noop = sqlite3_column_int(stmt, NICK_NOOP);
			n->nomemo = sqlite3_column_int(stmt, NICK_NOMEMO);
			n->auth_chan = sqlite3_column_int(stmt, NICK_AUTH_CHAN);
			n->auth_notify = sqlite3_column_int(stmt, NICK_AUTH_NOTIFY);
			n->protect = sqlite3_column_int(stmt, NICK_PROTECT);
			n->mlock = sstrdup((char*) sqlite3_column_text(stmt, NICK_MLOCK));
			n->mnotify = sqlite3_column_int(stmt, NICK_MNOTIFY);
			n->notifylist = NULL;
			n->accesslist = NULL;
			n->next = nicklist;
			max_ns_id = n->id;
			if (nicklist) {
				nicklist->prev = n;
			}
			nicklist = n;

		} /* while */
	}
	sqlite3_close(db);
}


/****************************************************************************************/
/**
 * load the rest of the nickserv tables
 */
void load_nickserv(void) {
	load_nicks();
	load_access();
	load_auth();
	load_notify();
}

/****************************************************************************************/
/**
 * load the notify table into the memory
 */
static void load_notify(void) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	const char *tail;

	if (sqlite3_open(DB, &db) == SQLITE_OK) {
		int error = sqlite3_prepare_v2(db, load_ns_notify, 1000, &stmt, &tail);
		if (error != SQLITE_OK) {
			addlog(LOG_ERROR, LOG_ERR_SQLERROR, "in load_notify()");
			addlog(LOG_ERROR, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
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

/****************************************************************************************/
/**
 * save the nickserv tables
 */
void save_nickserv_db(void) {
	db_save_nicks();
	db_save_notify();
	db_save_access();
}



/****************************************************************************************/
/**
 * query for saving the auth entries
 * inserting queries in other function
 * will be commited in the end
 */
void db_save_auth(void) {
	addlog(LOG_DEBUG, LOG_DBG_ENTRY, "db_save_auth");
	sqlite3 *db;
	if (sqlite3_open(DB, &db) != SQLITE_OK) {
		addlog(LOG_ERROR, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		return;
	}
	sqlite3_exec(db, "BEGIN", 0, 0, 0);
	sqlite3_exec(db, "DROP TABLE IF EXISTS NS_AUTH", 0, 0, 0);
	sqlite3_exec(db, ns_create_auth_table, 0, 0, 0);
	NickInfo *n = nicklist;
	while (n) {
		auth *a = n->authlist;
		while(a) {
			if (db_add_auth(db, n, a) != 0) {
			addlog(LOG_ERROR, "Error in db_add_auth, rolling back");
			sqlite3_exec(db, "ROLLBACK", 0, 0, 0);
			sqlite3_close(db);
			return;
		}
			a = a->next;
		}
		n = n->next;
	}
	sqlite3_exec(db, "COMMIT", 0, 0, 0);
	sqlite3_close(db);
	return;
}
