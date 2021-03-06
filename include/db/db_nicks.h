/*
 * db_nicks.h
 *
 *  Created on: Jun 18, 2016
 *      Author: severin
 */

#ifndef INCLUDE_DB_DB_NICKS_H_
#define INCLUDE_DB_DB_NICKS_H_


const char *ns_update_nick_query =
		"INSERT INTO 'NICKS' ("
				"NICK_ID,"
				"NICKNAME,"
				"PASSWORD,"
				"MASK,"
				"REALNAME,"
				"LAST_SEEN,"
				"REGISTERED,"
				"HIDEMAIL,"
				"MEMOMAX,"
				"URL,"
				"EMAIL,"
				"MFORWARD,"
				"NOOP,"
				"NOMEMO,"
				"AUTH_CHAN,"
				"AUTH_NOTIFY,"
				"PROTECT,"
				"MLOCK,"
				"MNOTIFY) "
				"VALUES('%i','%s','%s','%s','%s','%ld','%ld','%i','%i','%s','%s','%i','%i','%i','%i','%i','%i','%s','%i');";

const char *ns_update_auth_query = "INSERT INTO 'NS_AUTH' ("
		"TARGET_TYPE,"
		"TARGET,"
		"SENDER,"
		"RECIPIENT,"
		"TIME,"
		"STATUS,"
		"ACCESS) VALUES("
		"%i,"
		"%i,"
		"%i,"
		"%i,"
		"'%ld',"
		"%i,"
		"%i);";

const char *ns_update_access_query = "INSERT INTO 'NS_ACCESS' ("
		"NICK_ID,"
		"MASK) VALUES("
		"%i,"
		"'%s');";

const char *ns_update_notify_query = "INSERT INTO 'NS_NOTIFY' ("
		"NICK_ID,"
		"NOTIFICATION_NICK_ID) VALUES("
		"%i,"
		"%i);";

const char *load_ns_access =
		"SELECT NS_ACCESS.ACCESS_ID,NICKS.NICKNAME,NS_ACCESS.MASK FROM NS_ACCESS"
				" INNER JOIN NICKS ON NS_ACCESS.NICK_ID = NICKS.NICK_ID;";

const char *load_ns_notify =
		"SELECT MYNICK.NICKNAME,NOTIFY.NICKNAME FROM NS_NOTIFY"
				" INNER JOIN NICKS MYNICK ON NS_NOTIFY.NICK_ID = MYNICK.NICK_ID"
				" INNER JOIN NICKS NOTIFY ON NS_NOTIFY.NOTIFICATION_NICK_ID = NOTIFY.NICK_ID;";

const char *load_ns_auth =
		"SELECT NS_AUTH.TARGET_TYPE, "
				"CASE WHEN NS_AUTH.TARGET_TYPE = 0 THEN NOTIFY.NICKNAME ELSE CHANS.NAME END AS TARGET_NAME,"
				"SENDER.NICKNAME, RECIPIENT.NICKNAME,TIME,STATUS,ACCESS "
				"FROM NS_AUTH"
				" INNER JOIN NICKS SENDER ON NS_AUTH.SENDER = SENDER.NICK_ID"
				" INNER JOIN NICKS RECIPIENT ON NS_AUTH.RECIPIENT = RECIPIENT.NICK_ID"
				" LEFT JOIN NICKS NOTIFY ON NS_AUTH.TARGET = NOTIFY.NICK_ID"
				" LEFT JOIN CHANS ON NS_AUTH.TARGET = CHANS.CHAN_ID;";

const char *ns_create_access_table = "CREATE TABLE 'NS_ACCESS'("
		"ACCESS_ID INTEGER PRIMARY KEY AUTOINCREMENT,"
		"NICK_ID INT,"
		"MASK VARCHAR(256),"
		"FOREIGN KEY (NICK_ID) REFERENCES NICKS(NICK_ID)"
		");";

const char *ns_create_auth_table = "CREATE TABLE NS_AUTH ("
		"AUTH_ID INTEGER PRIMARY KEY AUTOINCREMENT,"
		"TARGET_TYPE INT,"
		"TARGET INT,"
		"SENDER INT,"
		"RECIPIENT INT,"
		"TIME DATETIME,"
		"STATUS INT,"
		"ACCESS INT,"
		"FOREIGN KEY (SENDER) REFERENCES NICKS(NICK_ID) ON DELETE CASCADE ON UPDATE CASCADE,"
		"FOREIGN KEY (RECIPIENT) REFERENCES NICKS(NICK_ID) ON DELETE CASCADE ON UPDATE CASCADE"
		");";

const char *ns_create_target_type_table = "CREATE TABLE 'TARGET_TYPE'("
		"TARGET_TYPE_ID INTEGER PRIMARY KEY AUTOINCREMENT,"
		"NAME VARCHAR(32)"
		");";

const char *ns_create_notify_table = "CREATE TABLE 'NS_NOTIFY'("
		"NOTIFY_ID INTEGER PRIMARY KEY AUTOINCREMENT,"
		"NICK_ID INT,"
		"NOTIFICATION_NICK_ID INT,"
		"FOREIGN KEY (NICK_ID) REFERENCES NICKS(NICK_ID),"
		"FOREIGN KEY (NOTIFICATION_NICK_ID) REFERENCES NICKS(NICK_ID)"
		");";

const char *ns_create_nicks_table = "CREATE TABLE 'NICKS'("
		"NICK_ID INTEGER PRIMARY KEY AUTOINCREMENT,"
		"NICKNAME VARCHAR(33),"
		"PASSWORD VARCHAR(33),"
		"MASK VARCHAR(128),"
		"REALNAME VARCHAR(256),"
		"LAST_SEEN DATETIME,"
		"REGISTERED DATETIME,"
		"HIDEMAIL TINYINT,"
		"MEMOMAX INT,"
		"URL VARCHAR(128),"
		"EMAIL VARCHAR(65),"
		"MFORWARD INT,"
		"NOOP TINYINT,"
		"NOMEMO TINYINT,"
		"AUTH_CHAN TINYINT,"
		"AUTH_NOTIFY TINYINT,"
		"PROTECT INT,"
		"MLOCK VARCHAR(33),"
		"MNOTIFY TINYINT"
		");";

const char *ns_load_nicks = "SELECT  * FROM NICKS WHERE NICKS.NICKNAME='%s';";

void db_save_auth(void);
void load_nickserv(void);
void save_nickserv_db(void);

#endif /* INCLUDE_DB_DB_NICKS_H_ */
