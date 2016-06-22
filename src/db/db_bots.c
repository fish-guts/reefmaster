/*
 * db_bots.c
 *
 *  Created on: Jun 18, 2016
 *      Author: severin
 */

#include "main.h"
#include "db/db_bots.h"

/****************************************************************************************/
/**
 * query for adding a bot
 */
static int db_add_bot(sqlite3 *db,bot *b) {
	char sql[2048];
	char *sqlite_err = 0;
	sprintf(sql, bs_update_bot_query, b->id,b->name, b->password, b->username,b->realname);
	if ((sqlite3_exec(db, sql, 0, 0, &sqlite_err)) != SQLITE_OK) {
		addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		return SQL_ERROR;
	}
	return SQL_OK;
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
 * load the botserv table into the memory
 */
void load_botserv(void) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	const char *tail;
	if (sqlite3_open(DB, &db) == SQLITE_OK) {
		int error = sqlite3_prepare_v2(db, "SELECT * FROM BOTS ORDER BY BOTS.BOT_ID ASC", 1000, &stmt,
				&tail);
		if (error != SQLITE_OK) {
			addlog(2, LOG_ERR_SQLERROR, "in load_botserv()");
			addlog(2, LOG_ERR_SQLERROR, sqlite3_errmsg(db));
		}
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			int id = sqlite3_column_int(stmt, BOT_ID);
			char *name = sstrdup((const char*) sqlite3_column_text(stmt, BOT_NAME));
			char *password = sstrdup((const char*) sqlite3_column_text(stmt, BOT_PASS));
			char *username = sstrdup((const char*) sqlite3_column_text(stmt, BOT_USER));
			char *realname = sstrdup((const char*) sqlite3_column_text(stmt, BOT_REALNAME));
			load_bot(id, name, password, username, realname);
			max_bs_id = id;
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
}
