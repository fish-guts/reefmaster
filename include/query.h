/*
 * query.h
 *
 *  Created on: Nov 7, 2014
 *      Author: severin
 */

#ifndef QUERY_H_
#define QUERY_H_

const char *bs_create_bots_table = "CREATE TABLE 'BOTS' ("
		"BOT_ID INTEGER PRIMARY KEY AUTOINCREMENT,"
		"NICKNAME VARCHAR(32) NOT NULL,"
		"PASSWORD VARCHAR(32) NOT NULL,"
		"USERNAME VARCHAR(32) NOT NULL,"
		"REALNAME VARCHAR(32) NOT NULL"
		");";

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

const char *create_cs_akick_table = "CREATE TABLE CS_AKICK ("
	"AKICK_ID INTEGER PRIMARY KEY AUTOINCREMENT,"
	"CHAN INT NOT NULL,"
	"MASK VARCHAR(256) NOT NULL,"
	"ADDED_BY VARCHAR(32) NOT NULL,"
	"ADDED_BY_ACC INT NOT NULL,"
	"ADDED_ON BIGINT,"
	"REASON VARCHAR(512) NULL,"
	"FOREIGN KEY (CHAN) REFERENCES CHANS(CHAN_ID) ON DELETE CASCADE ON UPDATE CASCADE"
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
		"MFORWARD_TO VARCHAR(33),"
		"MFORWARD INT,"
		"NOOP TINYINT,"
		"NOMEMO TINYINT,"
		"AUTH_CHAN TINYINT,"
		"AUTH_NOTIFY TINYINT,"
		"PROTECT INT,"
		"MLOCK VARCHAR(33),"
		"MNOTIFY TINYINT"
		");";

const char *cs_create_acc_level_table = "CREATE TABLE 'ACC_LEVEL' ("
		"ACC_LEVEL_ID INTEGER PRIMARY KEY AUTOINCREMENT,"
		"NAME VARCHAR(32)"
		");";

const char *cs_create_op_type_table = "CREATE TABLE OP_TYPE ("
		"OP_TYPE_ID INTEGER PRIMARY KEY AUTOINCREMENT,"
		"NAME VARCHAR(16)"
		");";

const char *cs_create_op_list_table =
		"CREATE TABLE OP_LIST ("
			"OP_LIST_ID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
			"TYPE INT NOT NULL,"
			"NICK INT NOT NULL,"
			"CHAN INT NOT NULL,"
			"ADDED_BY VARCHAR(32) NOT NULL,"
			"ADDED_BY_ACC INT NOT NULL,"
			"ADDED_ON BIGINT,"
			"FOREIGN KEY (TYPE) REFERENCES OP_TYPE(OP_TYPE_ID) ON DELETE CASCADE ON UPDATE CASCADE,"
			"FOREIGN KEY (NICK) REFERENCES NICKS(NICK_ID) ON DELETE CASCADE ON UPDATE CASCADE,"
			"FOREIGN KEY (CHAN) REFERENCES CHANS(CHAN_ID) ON DELETE CASCADE ON UPDATE CASCADE"
		");";

const char *cs_create_chans_table =
		"CREATE TABLE CHANS ("
				"CHAN_ID INTEGER PRIMARY KEY AUTOINCREMENT,"
				"NAME VARCHAR(33),"
				"PASSWORD VARCHAR(33),"
				"DESCRIPTION VARCHAR(256),"
				"TIME_REG DATETIME,"
				"AOP_ENABLED TINYINT,"
				"HOP_ENABLED TINYINT,"
				"SOP_ENABLED TINYINT,"
				"UOP_ENABLED TINYINT,"
				"VOP_ENABLED TINYINT,"
				"BOT INT NULL,"
				"FOUNDER INT NOT NULL,"
				"SUCCESSOR INT NULL,"
				"MLOCK VARCHAR(33),"
				"TOPIC VARCHAR(1024),"
		   	   	"TOPIC_USER VARCHAR(33),"
		   	    "TOPIC_TIME BIGINT,"
				"RESTRICTED TINYINT,"
				"KEEPTOPIC TINYINT,"
				"AUTOVOP TINYINT ,"
				"MEMOLEVEL INT NOT NULL,"
				"LEAVEOPS TINYINT,"
				"OPWATCH TINYINT,"
				"URL VARCHAR(64),"
				"TOPICLOCK INT,"
				"FOREIGN KEY (BOT) REFERENCES BOTS(BOT_ID) ON DELETE CASCADE ON UPDATE CASCADE,"
				"FOREIGN KEY (FOUNDER) REFERENCES NICKS(NICK_ID) ON DELETE CASCADE ON UPDATE CASCADE,"
				"FOREIGN KEY (SUCCESSOR) REFERENCES NICKS(NICK_ID) ON DELETE CASCADE ON UPDATE CASCADE,"
				"FOREIGN KEY (MEMOLEVEL) REFERENCES OP_TYPE(OP_TYPE_ID) ON DELETE CASCADE ON UPDATE CASCADE,"
				"FOREIGN KEY (TOPICLOCK) REFERENCES OP_TYPE(OP_TYPE_ID) ON DELETE CASCADE ON UPDATE CASCADE"
				");";

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

const char *load_cs_chans = "SELECT "
		"CHANS.CHAN_ID,"
		"CHANS.NAME,"
		"CHANS.PASSWORD,"
		"CHANS.TIME_REG,"
		"CHANS.AOP_ENABLED,"
		"CHANS.HOP_ENABLED,"
		"CHANS.SOP_ENABLED,"
		"CHANS.UOP_ENABLED,"
		"CHANS.VOP_ENABLED,"
		"BOTS.NICKNAME,"
		"FOUNDER.NICKNAME,"
		"SUCCESSOR.NICKNAME,"
		"CHANS.MLOCK,"
		"CHANS.TOPIC,"
		"CHANS.TOPIC_USER,"
		"CHANS.TOPIC_TIME,"
		"CHANS.RESTRICTED,"
		"CHANS.KEEPTOPIC,"
		"CHANS.AUTOVOP,"
		"CHANS.MEMOLEVEL,"
		"CHANS.LEAVEOPS,"
		"CHANS.OPWATCH,"
		"CHANS.URL,"
		"CHANS.TOPICLOCK,"
		"CHANS.DESCRIPTION"
		" FROM CHANS"
		" LEFT JOIN BOTS ON CHANS.BOT = BOTS.BOT_ID"
		" INNER JOIN NICKS FOUNDER ON CHANS.FOUNDER = FOUNDER.NICK_ID"
		" LEFT JOIN NICKS SUCCESSOR ON CHANS.SUCCESSOR = SUCCESSOR.NICK_ID;";

const char *cs_load_akick = "SELECT * FROM CS_AKICK;";

const char *cs_update_chan_query = "INSERT INTO 'CHANS' ( "
		"NAME,"
		"PASSWORD,"
		"DESCRIPTION,"
		"TIME_REG,"
		"AOP_ENABLED,"
		"HOP_ENABLED,"
		"SOP_ENABLED,"
		"UOP_ENABLED,"
		"VOP_ENABLED,"
		"BOT,"
		"FOUNDER,"
		"SUCCESSOR,"
		"MLOCK,"
		"TOPIC,"
		"TOPIC_USER,"
		"TOPIC_TIME,"
		"RESTRICTED,"
		"KEEPTOPIC,"
		"AUTOVOP,"
		"MEMOLEVEL,"
		"LEAVEOPS,"
		"OPWATCH,"
		"URL,"
		"TOPICLOCK) VALUES("
		"'%s',"
		"'%s',"
		"'%s',"
		"'%ld',"
		"%i,"
		"%i,"
		"%i,"
		"%i,"
		"%i,"
		"%i,"
		"%i,"
		"%i,"
		"'%s',"
		"'%s',"
		"'%s',"
		"'%ld',"
		"%i,"
		"%i,"
		"%i,"
		"%i,"
		"%i,"
		"%i,"
		"'%s',"
		"%i);";

const char *ns_update_nick_query =
		"INSERT INTO 'NICKS' ("
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
				"MFORWARD_TO,"
				"MFORWARD,"
				"NOOP,"
				"NOMEMO,"
				"AUTH_CHAN,"
				"AUTH_NOTIFY,"
				"PROTECT,"
				"MLOCK,"
				"MNOTIFY) "
				"VALUES('%s','%s','%s','%s','%ld','%ld','%i','%i','%i','%s','%i','%i','%i','%i','%i','%i','%i','%s','%i');";

const char *bs_update_bot_query = "INSERT INTO 'BOTS' ("
		"NICKNAME,"
		"PASSWORD,"
		"USERNAME,"
		"REALNAME) VALUES("
		"'%s',"
		"'%s',"
		"'%s',"
		"'%s');";

const char *cs_update_akick_query = "INSERT INTO 'CS_AKICK' ("
		"CHAN,"
		"MASK,"
		"ADDED_BY,"
		"ADDED_BY_ACC,"
		"ADDED_ON,"
		"REASON) VALUES("
		"%i,"
		"'%s',"
		"'%s',"
		"'%i',"
		"'%ld',"
		"'%s');";

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

const char *cs_update_op_query = "INSERT INTO 'OP_LIST' ( "
		"TYPE,"
		"NICK,"
		"CHAN,"
		"ADDED_BY,"
		"ADDED_BY_ACC,"
		"ADDED_ON) VALUES ("
		"%i,"
		"%i,"
		"%i,"
		"'%s',"
		"%i,"
		"'%ld');";

const char *os_load_ops_query = "SELECT * FROM OPERS";

const char *os_load_akicks_query = "SELECT * FROM AKILL";


#endif /* QUERY_H_ */
