/*
 * db_bots.h
 *
 *  Created on: Jun 18, 2016
 *      Author: severin
 */

#ifndef INCLUDE_DB_DB_BOTS_H_
#define INCLUDE_DB_DB_BOTS_H_

#define CREATE_BOTS_QUERY "CREATE TABLE 'BOTS' ("\
		"BOT_ID INTEGER PRIMARY KEY AUTOINCREMENT,"\
		"NICKNAME VARCHAR(32) NOT NULL,"\
		"PASSWORD VARCHAR(32) NOT NULL,"\
		"USERNAME VARCHAR(32) NOT NULL,"\
		"REALNAME VARCHAR(32) NOT NULL"\
		");"

const char *bs_update_bot_query = "INSERT INTO 'BOTS' ("
		"BOT_ID,"
		"NICKNAME,"
		"PASSWORD,"
		"USERNAME,"
		"REALNAME) VALUES("
		"'%i',"
		"'%s',"
		"'%s',"
		"'%s',"
		"'%s');";

void load_botserv(void);
void save_botserv_db(void);


#endif /* INCLUDE_DB_DB_BOTS_H_ */
