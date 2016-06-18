/*
 * db_bots.c
 *
 *  Created on: Jun 18, 2016
 *      Author: severin
 */

#include "main.h"
#include "db/db_bots.h"

static void update_bot_ids(void);

/****************************************************************************************/
/**
 * query for adding a bot
 */
static int db_add_bot(sqlite3 *db,bot *b) {
	char sql[2048];
	char *sqlite_err = 0;
	sprintf(sql, bs_update_bot_query, b->name, b->password, b->username,
			b->realname);
	if ((sqlite3_exec(db, sql, 0, 0, &sqlite_err)) != SQLITE_OK) {
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		return 0;
	}
	return 1;

}

/****************************************************************************************/
/**
 * query for saving the bots
 * inserting queries in other function
 * will be commited in the end
 */
void db_save_bots(void) {
	sqlite3 *db;
	if (sqlite3_open(DB, &db) != SQLITE_OK) {
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		return;
	}
	sqlite3_exec(db, "BEGIN", 0, 0, 0);
	sqlite3_exec(db, "DROP TABLE IF EXISTS BOTS", 0, 0, 0);
	sqlite3_exec(db, CREATE_BOTS_QUERY, 0, 0, 0);
	bot *b = botlist;
	while (b) {
		if (db_add_bot(db, b) != SQL_OK) {
			addlog(2, "Error in db_add_bot, rolling back");
			sqlite3_exec(db, "ROLLBACK", 0, 0, 0);
			sqlite3_close(db);
			return;
		}
		b = b->next;
	}
	sqlite3_exec(db, "COMMIT", 0, 0, 0);
	sqlite3_close(db);
	return;
}

/****************************************************************************************/
/**
 * find a bot entry in the database using the specified nickname
 */
static bot *find_bot_by_name(char *nick) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	const char *tail;

	bot *b = scalloc(sizeof(bot), 1);
	if (sqlite3_open(DB, &db) == SQLITE_OK) {
		char sql[256];
		sprintf(sql, "SELECT * FROM BOTS WHERE BOTS.NICKNAME='%s';", nick);
		int error = sqlite3_prepare_v2(db, sql, 1000, &stmt, &tail);
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

/****************************************************************************************/
/**
 * load the botserv table into the memory
 */
void load_botserv(void) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	const char *tail;
	if (sqlite3_open(DB, &db) == SQLITE_OK) {
		int error = sqlite3_prepare_v2(db, "SELECT * FROM BOTS", 1000, &stmt,
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

/****************************************************************************************/
/**
 * save the botserv tables
 */
void save_botserv_db(void) {
	db_save_bots();
	update_bot_ids();
}

/****************************************************************************************/
/**
 * update the bot ids after saving
 */
static void update_bot_ids(void) {
	bot *b = botlist;
	while(b) {
		int id = find_bot_by_name(b->name)->id;
		b->id = id;
		b = b->next;
	}
}
