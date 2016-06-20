/*
 * db_chans.h
 *
 *  Created on: Jun 18, 2016
 *      Author: severin
 */

#ifndef INCLUDE_DB_DB_CHANS_H_
#define INCLUDE_DB_DB_CHANS_H_


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
				"BOT INT NULL,"
				"FOUNDER INT NOT NULL,"
				"SUCCESSOR INT NOT NULL,"
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

const char *load_cs_chans = "SELECT * FROM CHANS ORDER BY CHANS.CHAN_ID ASC";

const char *cs_load_akick = "SELECT * FROM CS_AKICK;";

const char *cs_update_chan_query = "INSERT INTO 'CHANS' ( "
		"CHAN_ID,"
		"NAME,"
		"PASSWORD,"
		"DESCRIPTION,"
		"TIME_REG,"
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
		"'%i',"
		"'%s',"
		"'%s',"
		"'%s',"
		"'%ld',"
		"'%i',"
		"'%i',"
		"'%i',"
		"'%s',"
		"'%s',"
		"'%s',"
		"'%ld',"
		"'%i',"
		"'%i',"
		"'%i',"
		"'%i',"
		"'%i',"
		"'%i',"
		"'%s',"
		"'%i');";

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

#endif /* INCLUDE_DB_DB_CHANS_H_ */
