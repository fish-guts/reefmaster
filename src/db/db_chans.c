/*
 * db_chans.c

 *
 *  Created on: Jun 18, 2016
 *      Author: severin
 */

#include "main.h"
#include "db/db_chans.h"

static int db_add_akick(sqlite3 *db, ChanInfo *c, akick *a);
static int db_add_op(sqlite3 *db,op *o);
static void load_ops(void);
static void load_akick(void);
static void db_save_ops(void);
static void db_save_chans(void);

/****************************************************************************************/
/**
 * load the akill table into the memory
 */
void load_akills(void) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	const char *tail;
	if (sqlite3_open(DB, &db) == SQLITE_OK) {
		int error = sqlite3_prepare_v2(db, "select * from AKILL", 1000, &stmt,
				&tail);
		if (error != SQLITE_OK) {
			addlog(2, LOG_ERR_SQLERROR, "in load_akills()");
			addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		}
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			operuser *o = scalloc(sizeof(operuser), 1);
			o->nick = sstrdup((const char *)sqlite3_column_text(stmt, 1));
			o->can_chatops = 1;
			o->can_akill = sqlite3_column_int(stmt,2);
			o->can_chghost = sqlite3_column_int(stmt,3);
			o->can_local  = sqlite3_column_int(stmt,4);
			o->can_global =  sqlite3_column_int(stmt,5);
			o->can_kick = sqlite3_column_int(stmt,6);
			o->can_kill = sqlite3_column_int(stmt,7);
			o->can_sgline = sqlite3_column_int(stmt,8);
			o->can_skline = sqlite3_column_int(stmt,9);
			o->can_sqline = sqlite3_column_int(stmt,10);
			o->can_svsnick = sqlite3_column_int(stmt,11);
			o->can_szline = sqlite3_column_int(stmt,12);

			o->next = opers;
			if (opers)
				opers->prev = o;
			opers = o;
		}
	}
	sqlite3_close(db);
}


/****************************************************************************************/
/**
 * query for adding an akick entry
 */
static int db_add_akick(sqlite3 *db, ChanInfo *c, akick *a) {
	char sql[2048];
	char *sqlite_err = 0;
	int chanid = c->id;
	sprintf(sql, cs_update_akick_query, chanid, a->mask, a->added_by,
			a->added_by_acc, a->added_on, a->reason);
	if ((sqlite3_exec(db, sql, 0, 0, &sqlite_err)) != SQLITE_OK) {
		addlog(2, "Error in function db_add_kick");
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		return 0;
	}
	return 1;
}


/****************************************************************************************/
/**
 * load the chans table into the memory
 */
void load_chans(void) {
	addlog(DEBUG, LOG_DBG_ENTRY, "load_chans");
	sqlite3 *db;
	sqlite3_stmt *stmt;
	const char *tail;

	if (sqlite3_open(DB, &db) == SQLITE_OK) {
		int error = sqlite3_prepare_v2(db, load_cs_chans, 1000, &stmt, &tail);

		if (error != SQLITE_OK) {
			addlog(2, LOG_ERR_SQLERROR, "in load_chans()");
			addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		}

		while (sqlite3_step(stmt) == SQLITE_ROW) {
			ChanInfo *c = scalloc(sizeof(ChanInfo), 1);
			c->id = sqlite3_column_int(stmt, CHAN_ID);
			strscpy(c->name, (char*) sqlite3_column_text(stmt, CHAN_NAME), NICKMAX);
			strscpy(c->pass, (char*) sqlite3_column_text(stmt, CHAN_PASS), PASSMAX);
			strscpy(c->description, (char*) sqlite3_column_text(stmt, CHAN_DESC),DESCMAX);
			c->time_reg = sqlite3_column_int(stmt, CHAN_TIME_REG);
			c->bot_id = sqlite3_column_int(stmt, CHAN_BOT);
			c->founder = sqlite3_column_int(stmt, CHAN_FOUNDER);
			c->successor = sqlite3_column_int(stmt, CHAN_SUCCESSOR);
			c->mlock = sstrdup((char*) sqlite3_column_text(stmt, CHAN_MLOCK));
			if (sqlite3_column_text(stmt, CHAN_TOPIC)) {
				c->topic = sstrdup((char*) sqlite3_column_text(stmt, CHAN_TOPIC));
			}
			if (sqlite3_column_text(stmt, CHAN_TOPIC_USER)) {
				c->topic_user = sstrdup((char*) sqlite3_column_text(stmt, CHAN_TOPIC_USER));
			}
			if (sqlite3_column_int(stmt, CHAN_TOPIC_TIME)) {
				c->topic_time = sqlite3_column_int(stmt, CHAN_TOPIC_TIME);
			}
			c->restricted = sqlite3_column_int(stmt, CHAN_RESTRICTED);
			c->keeptopic = sqlite3_column_int(stmt,CHAN_KEEPTOPIC);
			c->autovop = sqlite3_column_int(stmt, CHAN_AUTOVOP);
			c->memolevel = sqlite3_column_int(stmt, CHAN_MEMOLEVEL);
			c->leaveops = sqlite3_column_int(stmt, CHAN_LEAVEOPS);
			c->opwatch = sqlite3_column_int(stmt, CHAN_OPWATCH);
			c->url = sstrdup((char*) sqlite3_column_text(stmt, CHAN_URL));
			c->topiclock = sqlite3_column_int(stmt, CHAN_TOPICLOCK);
			c->aop_count = 0;
			c->hop_count = 0;
			c->sop_count = 0;
			c->uop_count = 0;
			c->vop_count = 0;
			c->akicklist = NULL;
			max_cs_id = c->id;
			c->next = chans;
			if (chans) {
				chans->prev = c;
			}
			chans = c;
		}
	}
	sqlite3_close(db);
	addlog(DEBUG, LOG_DBG_EXIT, "load_chans");
}

/****************************************************************************************/
/**
 * load the chanserv tables
 */
void load_chanserv(void) {
	load_chans();
	load_akick();
	load_ops();
}

/****************************************************************************************/
/**
 * load the global ops table into the memory
 */
static void load_ops(void) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	const char *tail;

	if (sqlite3_open(DB, &db) == SQLITE_OK) {
		int error = sqlite3_prepare_v2(db, "select * from OP_LIST", 1000, &stmt,
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
			ChanInfo *c = o->chan;
			if(o->level==AUTH_AOP) {
				c->aop_count++;
			} else if(o->level==AUTH_HOP) {
				c->hop_count++;
			}  else if(o->level==AUTH_SOP) {
				c->sop_count++;
			} else if(o->level==AUTH_UOP) {
				c->uop_count++;
			}  else if(o->level==AUTH_VOP) {
				c->vop_count++;
			}
			o->next = global_op_list;
			if (global_op_list)
				global_op_list->prev = o;
			global_op_list = o;
		}
	}
	sqlite3_close(db);
}

/****************************************************************************************/
/**
 * query for saving the akicks
 * inserting queries in other function
 * will be commited in the end
 */
static void db_save_akicks(void) {
	sqlite3 *db;
	if (sqlite3_open(DB, &db) != SQLITE_OK) {
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		return;
	}
	sqlite3_exec(db, "BEGIN", 0, 0, 0);
	sqlite3_exec(db, "DROP TABLE IF EXISTS CS_AKICK", 0, 0, 0);
	sqlite3_exec(db, create_cs_akick_table, 0, 0, 0);
	ChanInfo *c = chans;
	while (c) {
		akick *a = c->akicklist;
		while(a) {
			if (db_add_akick(db, c, a) != 0) {
			addlog(2, "Error in db_add_akick, rolling back");
			sqlite3_exec(db, "ROLLBACK", 0, 0, 0);
			sqlite3_close(db);
			return;
		}
			a = a->next;
		}
		c = c->next;
	}
	sqlite3_exec(db, "COMMIT", 0, 0, 0);
	sqlite3_close(db);
	return;
}


/****************************************************************************************/
/**
 * load the akick table into the memory
 */
static void load_akick(void) {
	addlog(DEBUG, LOG_DBG_ENTRY, "load_akick");
	sqlite3 *db;
	sqlite3_stmt *stmt;
	const char *tail;
	if (sqlite3_open(DB, &db) == SQLITE_OK) {
		int error = sqlite3_prepare_v2(db, cs_load_akick, 1000, &stmt, &tail);
		if (error != SQLITE_OK) {
			addlog(2, LOG_ERR_SQLERROR, "in load_akick()");
			addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
			return;
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

/****************************************************************************************/
/**
 * save the chanserv tables
 */
void save_chanserv_db(void) {
	db_save_chans();
	db_save_akicks();
	db_save_ops();
	db_save_auth();
}


/****************************************************************************************/
/**
 * query for adding a channel
 */
static int db_add_chan(sqlite3 *db, ChanInfo *c) {
	char sql[4096];
	char *sqlite_err = 0;

	sprintf(sql, cs_update_chan_query, c->id, c->name, c->pass, c->description,
			c->time_reg, c->bot_id, c->founder, c->successor,
			c->mlock, c->topic, c->topic_user, c->topic_time, c->restricted,
			c->keeptopic, c->autovop, c->memolevel, c->leaveops, c->opwatch,
			c->url, c->topiclock);

	if ((sqlite3_exec(db, sql, 0, 0, &sqlite_err)) != SQLITE_OK) {
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		return 0;
	}
	return 1;
}

/****************************************************************************************/
/**
 * query for adding a global op list entry
 */
static int db_add_op(sqlite3 *db,op *o) {
	char sql[2048];
	char *sqlite_err = 0;
	int nickid = findnick(o->nick->nick)->id;
	int chanid = findchan(o->chan->name)->id;
	sprintf(sql, cs_update_op_query, o->level, nickid, chanid, o->addedby,
			o->addedbyacc, o->addedon);
	if ((sqlite3_exec(db, sql, 0, 0, &sqlite_err)) != SQLITE_OK) {
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		return 0;
	}
	return 1;
}

/****************************************************************************************/
/**
 * query for saving the chans
 * inserting queries in other function
 * will be commited in the end
 */
static void db_save_chans(void) {
	addlog(1, LOG_DBG_ENTRY, "db_save_chans");
	sqlite3 *db;
	if (sqlite3_open(DB, &db) != SQLITE_OK) {
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		return;
	}
	ChanInfo *c = chans;
	sqlite3_exec(db, "BEGIN", 0, 0, 0);
	sqlite3_exec(db, "DROP TABLE IF EXISTS CHANS", 0, 0, 0);
	sqlite3_exec(db, cs_create_chans_table, 0, 0, 0);
	while (c) {
		if (db_add_chan(db, c) != SQL_OK) {
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


/****************************************************************************************/
/**
 * query for saving the global operator list
 * inserting queries in other function
 * will be commited in the end
 */
static void db_save_ops(void) {
	sqlite3 *db;
	if (sqlite3_open(DB, &db) != SQLITE_OK) {
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		return;
	}
	sqlite3_exec(db, "BEGIN", 0, 0, 0);
	sqlite3_exec(db, "DROP TABLE IF EXISTS OP_LIST", 0, 0, 0);
	sqlite3_exec(db, cs_create_op_list_table, 0, 0, 0);
	op *o = global_op_list;
	while (o) {
		if (db_add_op(db,o) != SQL_OK) {
			sqlite3_exec(db, "ROLLBACK", 0, 0, 0);
			sqlite3_close(db);
		}
		o = o->next;
	}
	sqlite3_exec(db, "COMMIT", 0, 0, 0);
	return;
}
