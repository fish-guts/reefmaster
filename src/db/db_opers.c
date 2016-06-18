/*
 * db_opers.c
 *
 *  Created on: Jun 18, 2016
 *      Author: severin
 */


#include "main.h"

/****************************************************************************************/
/**
 * load the opers table into the memory
 */
void load_opers(void) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	const char *tail;

	if (sqlite3_open(DB, &db) == SQLITE_OK) {
		int error = sqlite3_prepare_v2(db, "select * from OPERS", 1000, &stmt,
				&tail);
		if (error != SQLITE_OK) {
			addlog(2, LOG_ERR_SQLERROR, "in load_opers()");
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

