/*
	script for creating the db schema
*/
DROP TABLE IF EXISTS CS_AKICK;
DROP TABLE IF EXISTS CHANS;
DROP TABLE IF EXISTS BOTS;
DROP TABLE IF EXISTS NS_AUTH;
DROP TABLE IF EXISTS NS_ACCESS;
DROP TABLE IF EXISTS NS_NOTIFY;
DROP TABLE IF EXISTS NICKS;
DROP TABLE IF EXISTS AKILL;
DROP TABLE IF EXISTS OPERS;
DROP TABLE IF EXISTS OP_LIST;

CREATE TABLE NICKS(
   NICK_ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
   NICKNAME VARCHAR(33) NOT NULL,
   PASSWORD VARCHAR(33) NOT NULL,
   MASK VARCHAR(128) NOT NULL,
   REALNAME VARCHAR(256) NULL,
   LAST_SEEN BIGINT NOT NULL,
   REGISTERED BIGINT NOT NULL,
   HIDEMAIL TINYINTNOT NULL,
   MEMOMAX INT NULL,
   URL VARCHAR(128) NULL,
   EMAIL VARCHAR(65) NOT NULL,
   MFORWARD INT NOT NULL,
   NOOP TINYINT NOT NULL,
   NOMEMO TINYINT NOT NULL,
   AUTH_CHAN TINYINT NOT NULL,
   AUTH_NOTIFY TINYINT NOT NULL,
   PROTECT TINYINT NOT NULL,
   MLOCK VARCHAR(33) NULL,
   MNOTIFY TINYINT NOT NULL
);


CREATE TABLE NS_ACCESS (
	ACCESS_ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
	NICK_ID INT NOT NULL,
	MASK VARCHAR(256) NOT NULL,
	FOREIGN KEY (NICK_ID) REFERENCES NICKS(NICK_ID)
);

CREATE TABLE NS_NOTIFY (
	NOTIFY_ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
	NICK_ID INT NOT NULL,
	NOTIFICATION_NICK_ID INT NOT NULL,
	FOREIGN KEY (NICK_ID) REFERENCES NICKS(NICK_ID),
	FOREIGN KEY (NOTIFICATION_NICK_ID) REFERENCES NICKS(NICK_ID)
);

CREATE TABLE NS_AUTH (
	AUTH_ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
	TARGET_TYPE INT NOT NULL,
	TARGET INT NOT NULL,
	SENDER INT NOT NULL,
	RECIPIENT INT NOT NULL,
	TIME DATETIME NOT NULL,
	STATUS INT NOT NULL,
	ACCESS INT NOT NULL,
	FOREIGN KEY (SENDER) REFERENCES NICKS(NICK_ID) ON DELETE CASCADE ON UPDATE CASCADE,
	FOREIGN KEY (RECIPIENT) REFERENCES NICKS(NICK_ID) ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE TABLE BOTS (
	BOT_ID INTEGER PRIMARY KEY AUTOINCREMENT,
	NICKNAME VARCHAR(32) NOT NULL,
	PASSWORD VARCHAR(32) NOT NULL,
	USERNAME VARCHAR(32) NOT NULL,
	REALNAME VARCHAR(32) NOT NULL
);

CREATE TABLE CHANS
(
   CHAN_ID INTEGER PRIMARY KEY AUTOINCREMENT,
   NAME VARCHAR(33) NOT NULL,
   PASSWORD VARCHAR(33) NOT NULL,
   DESCRIPTION VARCHAR(256) NOT NULL,
   TIME_REG BIGINT NOT NULL,
   BOT INT NULL,
   FOUNDER INT NOT NULL,
   SUCCESSOR INT NULL,
   MLOCK VARCHAR(33) NULL,
   TOPIC VARCHAR(1025) NULL,
   TOPIC_USER VARCHAR(33) NULL,
   TOPIC_TIME BIGINT NULL,
   RESTRICTED TINYINT NOT NULL,
   KEEPTOPIC TINYINT NOT NULL,
   AUTOVOP TINYINT NOT NULL,
   MEMOLEVEL INT NOT NULL,
   LEAVEOPS TINYINT NOT NULL,
   OPWATCH TINYINT NOT NULL,
   URL VARCHAR(64) NULL,
   TOPICLOCK INT NULL,
   FOREIGN KEY (BOT) REFERENCES BOTS(BOT_ID) ON DELETE CASCADE ON UPDATE CASCADE,
   FOREIGN KEY (FOUNDER) REFERENCES NICKS(NICK_ID) ON DELETE CASCADE ON UPDATE CASCADE,
   FOREIGN KEY (SUCCESSOR) REFERENCES NICKS(NICK_ID) ON DELETE CASCADE ON UPDATE CASCADE,
   FOREIGN KEY (MEMOLEVEL) REFERENCES OP_TYPE(OP_TYPE_ID) ON DELETE CASCADE ON UPDATE CASCADE, 
   FOREIGN KEY (TOPICLOCK) REFERENCES OP_TYPE(OP_TYPE_ID) ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE TABLE CS_AKICK (
	AKICK_ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
	CHAN INT NOT NULL NOT NULL,
	MASK VARCHAR(256) NOT NULL,
	ADDED_BY VARCHAR(32) NOT NULL,
	ADDED_BY_ACC INT NOT NULL,
	ADDED_ON BIGINT NOT NULL,
	REASON VARCHAR(512) NULL,
	FOREIGN KEY (CHAN) REFERENCES CHANS(CHAN_ID) ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE TABLE OP_LIST (
	OP_LIST_ID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT NOT NULL,
	TYPE INT NOT NULL,
	NICK INT NOT NULL,
	CHAN INT NOT NULL,
	ADDED_BY VARCHAR(32) NOT NULL,
	ADDED_BY_ACC INT NOT NULL,
	ADDED_ON BIGINT,
	FOREIGN KEY (TYPE) REFERENCES OP_TYPE(OP_TYPE_ID) ON DELETE CASCADE ON UPDATE CASCADE,
	FOREIGN KEY (NICK) REFERENCES NICKS(NICK_ID) ON DELETE CASCADE ON UPDATE CASCADE,
	FOREIGN KEY (CHAN) REFERENCES CHANS(CHAN_ID) ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE TABLE AKILL (
	AKILL_ID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT NOT NULL,
	HOST VARCHAR(256) NOT NULL,
	EXPIRY BIGINT NULL,
	ADDED_BY VARCHAR(256) NOT NULL,
	REASON VARCHAR(1024)
);

CREATE TABLE OPERS (
	USER_ID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT NOT NULL,
	NICKNAME INT NOT NULL,
	CAN_AKILL TINYINT NOT NULL,
	CAN_CHGHOST TINYINT NOT NULL,
	CAN_GLOBAL TINYINT NOT NULL,
	CAN_LOCAL TINYINT NOT NULL,
	CAN_KICK TINYINT NOT NULL,
	CAN_KILL TINYINT NOT NULL,
	CAN_SGLINE TINYINT NOT NULL,
	CAN_SKLINE TINYINT NOT NULL,
	CAN_SQLINE TINYINT NOT NULL,
	CAN_SVSNICK TINYINT NOT NULL,
	CAN_SZLINE TINYINT NOT NULL
);


INSERT INTO BOTS (NICKNAME,PASSWORD,USERNAME,REALNAME) VALUES ("Chanbot","hoppus123","chanserv","Channel Bot");
INSERT INTO BOTS (NICKNAME,PASSWORD,USERNAME,REALNAME) VALUES ("Wulfbot","hoppus123","chanserv","Channel Bot");
INSERT INTO BOTS (NICKNAME,PASSWORD,USERNAME,REALNAME) VALUES ("X","hoppus123","chanserv","Channel Bot");


INSERT INTO NICKS VALUES(1, "Fish-Guts",	"hoppus123","fish-guts@reefmaster.ch",	"Fish-Guts",		1415474819,1415474819,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(2,"FG",		"hoppus123","fish-guts@reefmaster.ch",	"FG",			1415474819,1415474819,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(3,"SNoX",		"snox123",  "snox@reefmaster.ch",	"SnOX",			1415474819,1415474819,1,10,"www.reefmaster.ch","snox@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(4,"S",			"snox123",  "snox@reefmaster.ch",	"Snox",			1415474819,1415474819,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(5,"}SpIoN{",		"snox123",  "snox@reefmaster.ch",	"Snox",			1415474819,1415474819,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(6,"ventura",		"hoppus123","ventura@reefmaster.ch",	"ventura",		1415474819,1415474819,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(7,"mk",		"hoppus123","mk@reefmaster.ch",		"Fish-Guts",		1415474819,1415474819,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(8,"ll4mat",		"hoppus123","ll4mat@reefmaster.ch",	"ll4mat",		1415474819,1415474819,1,10,"www.reefmaster.ch","snox@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(9,"ake",		"hoppus123","ake@reefmaster.ch",	"ake",			1415474819,1415474819,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(10,"Jamc",		"hoppus123","jamc@reefmaster.ch",	"Jamc",			1415474819,1415474819,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(11,"CgIMaN",		"hoppus123","cgiman@reefmaster.ch",	"CgiMaN",		1415474819,1415474819,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(12,"red-dog",		"hoppus123","red-dog@reefmaster.ch",	"fido-rosso",		1415474819,1415474819,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(13,"V",		"hoppus123","vi@reefmaster.ch",		"V",			1415474819,1415474819,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(14,"Delfin",		"hoppus123","delfin@reefmaster.ch",	"Delfin",		1415474819,1415474819,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(15,"waterlily",	"hoppus123","waterlily@reefmaster.ch",	"waterlily",		1415474819,1415474819,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(16,"YJ",		"hoppus123","bnfh@reefmaster.ch",	"BNFH",			1415474819,1415474819,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(17,"neo",		"hoppus123","neo@reefmaster.ch",	"Neo",			1415474819,1415474819,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(18,"leota",		"hoppus123","leota@reefmaster.ch",	"leota",		1415474819,1415474819,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(19,"Schwan",		"hoppus123","schwan@reefmaster.ch",	"schwan",		1415474819,1415474819,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(20,"pixel",		"hoppus123","pixel@reefmaster.ch",	"pixel",		1415474819,1415474819,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(21,"Gargo",		"hoppus123","gargo@reefmaster.ch",	"Gargo",		1415474819,1415474819,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(22,"dungeon_lady",	"hoppus123","dragonia@reefmaster.ch",	"dl",			1415474819,1415474819,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(23,"Angel",		"hoppus123","angel@reefmaster.ch",	"Angel",		1415474819,1415474819,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(24,"FischerZH",	"hoppus123","fisher@reefmaster.ch",	"Kenny Fischer",	1415474819,1415474819,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(25,"JiLe",		"hoppus123","juuls@reefmaster.ch",	"JuLchen",		1415474819,1415474819,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(26,"Earthworm",	"hoppus123","ew@reefmaster.ch",		"Jonas",		1415474819,1415474819,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(27,"Valentin",		"hoppus123","valentin@reefmaster.ch",	"Valentin",		1415474819,1415474819,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(28,"Kane",		"hoppus123","dark_kane@reefmaster.ch",	"Kane",			1415474819,1415474819,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(29,"lemon_w",		"hoppus123","limone@reefmaster.ch",	"lämän",		1415474819,1415474819,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(30,"Audrey",		"hoppus123","audrey@reefmaster.ch",	"Audrey",		1415474819,1415474819,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(31,"Adler",		"hoppus123","adler@reefmaster.ch",	"Adler",		1415474819,1415474819,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(32,"rockoli",		"hoppus123","rockoli@reefmaster.ch",	"rockoli",		1415474819,1415474819,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(33,"Atlas",		"hoppus123","Atlas@reefmaster.ch",	"Atlas",		1415474819,1415474819,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(34,"Carol",		"hoppus123","carol@reefmaster.ch",	"Carol",		1415474819,1415474819,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(35,"moendli",		"hoppus123","moendli@reefmaster.ch",	"moendli",		1415474819,1415474819,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(36,"opso",		"hoppus123","opso@reefmaster.ch",	"opso",			1415474819,1415474819,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(37,"Noise",		"hoppus123","bucky@reefmaster.ch",	"Noise",		1415474819,1415474819,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(38,"Pazzolina",	"hoppus123","pazzolina@reefmaster.ch",	"Pazzolina",		1415474819,1415474819,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(39,"liesel",		"hoppus123","liesel@reefmaster.ch",	"liesel",		1415474819,1415474819,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(40,"Xenon",		"hoppus123","xenon@reefmaster.ch",	"Xenon",		1415474819,1415474819,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(41,"Sting",		"hoppus123","Sting@reefmaster.ch",	"Sting",		1415474819,1415474819,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(42,"Topi",		"hoppus123","topi@reefmaster.ch",	"Topi",			1415474819,1415474819,1,10,"www.reefmaster.ch","snox@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(43,"ChuckyB",		"hoppus123","chuckyb@reefmaster.ch",	"ChuckyB",		1415474819,1415474819,1,10,"www.reefmaster.ch","snox@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(44,"ErnIe",		"hoppus123","ernie@reefmaster.ch",	"Ernie",		1415474819,1415474819,1,10,"www.reefmaster.ch","snox@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(45,"SEV-Y",		"hoppus123","sevi@reefmaster.ch",	"Sevi",			1415474819,1415474819,1,10,"www.reefmaster.ch","snox@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(46,"Indy",		"hoppus123","indy@reefmaster.ch",	"Indy",			1415474819,1415474819,1,10,"www.reefmaster.ch","snox@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(47,"Raverin17",	"hoppus123","silence@reefmaster.ch",	"silence",		1415474819,1415474819,1,10,"www.reefmaster.ch","snox@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(48,"Zitroenchen",	"hoppus123","zit@reefmaster.ch",	"zitro",		1415474819,1415474819,1,10,"www.reefmaster.ch","snox@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(49,"wulf",		"hoppus123","wulf@reefmaster.ch",	"wulf",			1415474819,1415474819,1,10,"www.reefmaster.ch","snox@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(50,"eS",		"hoppus123","es@reefmaster.ch",		"es",			1415474819,1415474819,1,10,"www.reefmaster.ch","snox@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(51,"Hologram",		"hoppus123","hg@reefmaster.ch",		"HG",			1415474819,1415474819,1,10,"www.reefmaster.ch","snox@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(52,"triplesensor",	"hoppus123","trip@reefmaster.ch",	"trip",			1415474819,1415474819,1,10,"www.reefmaster.ch","snox@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(53,"gIL",		"hoppus123","gil@reefmaster.ch",	"Gil",			1415474819,1415474819,1,10,"www.reefmaster.ch","snox@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(54,"Ah-lee-yah",	"hoppus123","liyah@reefmaster.ch",	"Liyah",		1415474819,1415474819,1,10,"www.reefmaster.ch","snox@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(55,"Gizmo",		"hoppus123","gizmo@reefmaster.ch",	"Gizmo",		1415474819,1415474819,1,10,"www.reefmaster.ch","snox@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(56,"Athlon",		"hoppus123","athlon@reefmaster.ch",	"Athlon",		1415474819,1415474819,1,10,"www.reefmaster.ch","snox@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(57,"moebius",		"moebius123","moebius@reefmaster.ch",	"Moebius",		1415474819,1415474819,1,10,"www.reefmaster.ch","snox@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(58,"McViperly",	"hoppus123","viper@reefmaster.ch",	"Viper",		1415474819,1415474819,1,10,"www.reefmaster.ch","snox@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);


INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (1,"BluePanther!*@*.bluewin.ch","Fish-Guts",8,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (1,"SilverBird!*@*.bluewin.ch","Fish-Guts",8,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (1,"stskeeps!*@*.verizon.com","Fish-Guts",8,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (1,"alfred!*@*.redwave.route0.net","Fish-Guts",8,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (1,"aka*!*@*.bluewin.ch","Fish-Guts",8,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (1,"pilz!*@*.bluewin.ch","Fish-Guts",8,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (1,"foo!*@*.bluewin.ch","Fish-Guts",8,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (1,"bar!*@*.bluewin.ch","Fish-Guts",8,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (2,"BluePanther!*@*.bluewin.ch","FG",5,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (2,"SilverBird!*@*.bluewin.ch","ventura",4,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (2,"aka*!*@*.bluewin.ch","Jamc",4,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (3,"BluePanther!*@*.bluewin.ch","V",4,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (3,"chuckyB!*@*.hispeed.ch","V",4,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (3,"SilverBird!*@*.bluewin.ch","V",4,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (4,"BluePanther!*@*.bluewin.ch","CgIMan",8,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (4,"chuckyB!*@*.hispeed.ch","CgIMan",8,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (4,"SilverBird!*@*.bluewin.ch","CgIMan",8,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (5,"BluePanther!*@*.bluewin.ch","FG",5,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (5,"chuckyB!*@*.bluewin.ch","FG",5,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (5,"poltergeist!*@*.hispeed.ch","FG",5,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (5,"aka*!*@*.bluewin.ch","FG",5,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (6,"chuckyB!*@*.bluewin.ch","FG",5,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (6,"BluePanther!*@*.bluewin.ch","Jamc",4,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (7,"BluePanther!*@*.bluewin.ch","Jamc",4,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (7,"chuckyB!*@*.bluewin.ch","Jamc",4,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (7,"SilverBird!*@*.bluewin.ch","Jamc",4,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (7,"aka*!*@*.bluewin.ch","ventura",4,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (8,"BluePanther!*@*.bluewin.ch","Fish-Guts",8,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (8,"chuckyB!*@*.bluewin.ch","Fish-Guts",8,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (8,"SilverBird!*@*.bluewin.ch","Fish-Guts",8,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (8,"pinopierre!*@*.bluewin.ch","Fish-Guts",8,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (9,"BluePanther!*@*.bluewin.ch","Fish-Guts",8,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (9,"SilverBird!*@*.bluewin.ch","Fish-Guts",8,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (10,"BluePanther!*@*.bluewin.ch","Fish-Guts",8,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (10,"chuckyB!*@*.bluewin.ch","Fish-Guts",8,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (10,"SilverBird!*@*.bluewin.ch","Fish-Guts",8,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (10,"pinopierre!*@*.bluewin.ch","Fish-Guts",8,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (10,"aka*!*@*.bluewin.ch","Fish-Guts",8,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (10,"tripolis!*@*.bluewin.ch","Fish-Guts",8,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (11,"BluePanther!*@*.bluewin.ch","Fish-Guts",8,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (11,"chuckyB!*@*.bluewin.ch","Fish-Guts",8,1415474819,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (11,"SilverBird!*@*.bluewin.ch","Fish-Guts",8,1415474819,"You are banned for misbehaving");


INSERT INTO CHANS VALUES(1, "#ircops",			"hoppus123","The IRC Operator Channel",	1415474819,		1,1,2,		"ertn-k",	"IRCOps: soon a new bot",	"Fish-Guts",	1415474819,0,1,0,4,1,1,"www.ircops.ch",5);
INSERT INTO CHANS VALUES(2, "#cservice",		"hoppus123","Operator Service",		1415474819,		1,1,3,		"ertn-k",	"Hallo",					"Fish-Guts",	1415474819,0,1,0,4,1,1,"www.ircops.ch",3);
INSERT INTO CHANS VALUES(3, "#schaffhausen",		"hoppus123","Schaffhausen",		1415474819,		1,1,3, 		"ertn-k",	"Hallo",					"ventura",		1415474819,0,1,0,4,1,1,"www.ircops.ch",3);
INSERT INTO CHANS VALUES(4, "#zuerich",			"hoppus123","Operator Service",		1415474819,		1,1,3, 		"ertn-k",	"Hallo",					"ventura",		1415474819,0,1,0,4,1,1,"www.ircops.ch",3);
INSERT INTO CHANS VALUES(5, "#basel",			"hoppus123","Basel",			1415474819,		1,1,-1,		"ertn-k",	"Hallo",					"mk",			1415474819,0,1,0,4,1,1,"www.ircops.ch",3);
INSERT INTO CHANS VALUES(6, "#zug",			"hoppus123","Zug",			1415474819,		1,1,-1,		"ertn-k",	"Hallo",					"mk",			1415474819,0,1,0,4,1,1,"www.ircops.ch",3);
INSERT INTO CHANS VALUES(7, "#thurgau",			"hoppus123","Thurgau",			1415474819,		1,1,-1,		"ertn-k",	"Hallo",					"FG",			1415474819,0,1,0,4,1,1,"www.ircops.ch",3);
INSERT INTO CHANS VALUES(8, "#stgallen",		"hoppus123","St. Gallen",		1415474819,		1,1,-1,		"ertn-k",	"Hallo",					"mk",			1415474819,0,1,0,4,1,1,"www.ircops.ch",4);
INSERT INTO CHANS VALUES(9, "#aargau",			"hoppus123","Aargau",			1415474819,		1,1,-1,		"ertn-k",	"Hallo",					"Fish-Guts",	1415474819,0,1,0,4,1,1,"www.ircops.ch",3);
INSERT INTO CHANS VALUES(10,"#bern",			"hoppus123","Bern",			1415474819,		1,37,1,		"ertn-k",	"Hallo",					"V",			1415474819,0,1,0,4,1,1,"www.ircops.ch",5);
INSERT INTO CHANS VALUES(11,"#wallis",			"hoppus123","Wallis",			1415474819,		1,37,1,		"ertn-k",	"Hallo",					"V",			1415474819,0,1,0,4,1,1,"www.ircops.ch",5);
INSERT INTO CHANS VALUES(12,"#vaud",			"hoppus123","Vaud/Waadt",		1415474819,		1,37,1,		"ertn-k",	"Hallo",					"FG",			1415474819,0,1,0,4,1,1,"www.ircops.ch",5);
INSERT INTO CHANS VALUES(13,"#glarus",			"hoppus123","Glarus",			1415474819,		1,37,1,		"ertn-k",	"Hallo",					"Fish-Guts",	1415474819,0,1,0,4,1,1,"www.ircops.ch",5);
INSERT INTO CHANS VALUES(14,"#schwyz",			"hoppus123","Schwyz",			1415474819,		1,37,1,		"ertn-k",	"Hallo",					"Fish-Guts",	1415474819,0,1,0,4,1,1,"www.ircops.ch",5);
INSERT INTO CHANS VALUES(15,"#graubuenden",		"hoppus123","Bündnerland",		1415474819,		1,37,1,		"ertn-k",	"Hallo",					"Fish-Guts",	1415474819,0,1,0,4,1,1,"www.ircops.ch",5);
INSERT INTO CHANS VALUES(16, "#ticino",			"hoppus123","Ticino",			1415474819,		1,3,1,		"ertn-k",	"Hallo",					"Fish-Guts",	1415474819,0,1,0,4,1,1,"www.ircops.ch",5);	
INSERT INTO CHANS VALUES(17,"#uri",			"hoppus123","Uri",			1415474819,		1,3,1,		"ertn-k",	"Hallo",					"Valentin",		1415474819,0,1,0,4,1,1,"www.ircops.ch",5);
INSERT INTO CHANS VALUES(18,"#obwalden",		"hoppus123","Obwalden",			1415474819,		1,3,1,		"ertn-k",	"Hallo",					"Valentin",		1415474819,0,1,0,4,1,1,"www.ircops.ch",5);
INSERT INTO CHANS VALUES(19,"#nidwalden",		"hoppus123","Nidwalden",		1415474819,		1,3,1,		"ertn-k",	"Hallo",					"Valentin",		1415474819,0,1,0,4,1,1,"www.ircops.ch",5);
INSERT INTO CHANS VALUES(20,"#genf",			"hoppus123","Genève",			1415474819,		1,3,1,		"ertn-k",	"Hallo",					"Valentin",		1415474819,0,1,0,4,1,1,"www.ircops.ch",5);
INSERT INTO CHANS VALUES(21,"#fribourg",		"hoppus123","Fribourg",			1415474819,		1,3,1,		"ertn-k",	"Hallo",					"Valentin",		1415474819,0,1,0,4,1,1,"www.ircops.ch",5);
INSERT INTO CHANS VALUES(22,"#luzern",			"hoppus123","Luzern",			1415474819,		1,3,1,		"ertn-k",	"Hallo",					"Valentin",		1415474819,0,1,0,4,1,1,"www.ircops.ch",5);
INSERT INTO CHANS VALUES(23,"#jura",			"hoppus123","Jura",			1415474819,		1,3,1,		"ertn-k",	"Hallo",					"Valentin",		1415474819,0,1,0,4,1,1,"www.ircops.ch",5);
INSERT INTO CHANS VALUES(24,"#solothurn",		"hoppus123","Solothurn",		1415474819,		1,3,1,		"ertn-k",	"Hallo",					"Valentin",		1415474819,0,1,0,4,1,1,"www.ircops.ch",5);
INSERT INTO CHANS VALUES(25,"#neuchatel",		"hoppus123","Neuchatel",		1415474819,		1,3,1,		"ertn-k",	"Hallo",					"Valentin",		1415474819,0,1,0,4,1,1,"www.ircops.ch",5);
INSERT INTO CHANS VALUES(26,"#appenzell",		"hoppus123","Appenzell",		1415474819,		1,3,1,		"ertn-k",	"Hallo",					"Valentin",		1415474819,0,1,0,4,1,1,"www.ircops.ch",5);
INSERT INTO CHANS VALUES(27,"#teentalk",		"hoppus123","Teentalk",			1415474819,		1,37,1,		"ertn-k",	"Hallo",					"CgIMaN",		1415474819,0,1,0,4,1,1,"www.ircops.ch",5);
INSERT INTO CHANS VALUES(28,"#kidstalk",		"hoppus123","Kidstask",			1415474819,		1,37,1,		"ertn-k",	"Hallo",					"ventura",		1415474819,0,1,0,4,1,1,"www.ircops.ch",5);
INSERT INTO CHANS VALUES(29,"#reefmaster",		"hoppus123","Reefmaster Main Channel",	1415474819,		1,37,1,		"ertn-k",	"Hallo",					"Fish-Guts",	1415474819,0,1,0,4,1,1,"www.ircops.ch",5);
INSERT INTO CHANS VALUES(30,"#flirt20plus",		"hoppus123","flirt 20 plus",		1415474819,		1,1,-1,		"ertn-k",	"Hallo",					"FG",			1415474819,0,1,0,4,1,1,"www.ircops.ch",6);
INSERT INTO CHANS VALUES(31,"#flirt30plus",		"hoppus123","flirt 30 plus",		1415474819,		1,1,-1,		"ertn-k",	"Hallo",					"ventura",		1415474819,0,1,0,4,1,1,"www.ircops.ch",5);
INSERT INTO CHANS VALUES(32,"#flirt40plus",		"hoppus123","flirt 40 plus",		1415474819,		1,1,-1,		"ertn-k",	"Hallo",					"V",			1415474819,0,1,0,4,1,1,"www.ircops.ch",5);
INSERT INTO CHANS VALUES(33,"#flirt50plus",		"hoppus123","flirt 50 plus",		1415474819,		1,1,-1,		"ertn-k",	"Hallo",					"mk",			1415474819,0,1,0,4,1,1,"www.ircops.ch",5);
INSERT INTO CHANS VALUES(34,"#flirt60plus",		"hoppus123","flirt 60 plus",		1415474819,		1,1,-1,		"ertn-k",	"Hallo",					"Fish-Guts",	1415474819,0,1,0,4,1,1,"www.ircops.ch",5);
INSERT INTO CHANS VALUES(35,"#linux",			"hoppus123","for Linux Fans",		1415474819,		1,1,-1,		"ertn-k",	"Hallo",					"FG",			1415474819,0,1,0,4,1,1,"www.ircops.ch",3);
INSERT INTO CHANS VALUES(36,"#quiz",			"hoppus123","Quiz Channel",		1415474819,		1,1,-1,		"ertn-k",	"Hallo",					"Fish-Guts",	1415474819,0,1,0,4,1,1,"www.ircops.ch",5);
INSERT INTO CHANS VALUES(37,"#counter-strike",		"hoppus123","CS",			1415474819,		1,1,-1,		"ertn-k",	"Hallo",					"V",			1415474819,0,1,0,4,1,1,"www.ircops.ch",3);
INSERT INTO CHANS VALUES(38,"#menonly",			"hoppus123","Gay Channel",		1415474819,		1,3,1,		"ertn-k",	"Hallo",					"Valentin",		1415474819,0,1,0,4,1,1,"www.ircops.ch",5);


-- Level 1 Uop 2 Vop 3 Hop 4 Aop 5 Sop 6 Cop 7 Qop 8 Successor 9 Founder
-- Added additionally 10 Full Founder, 11 ServiceRootAdmin

-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17) 

-- #ircops
-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,1,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,1,"Fish-Guts",11,1415474819);

-- Qop

-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,10,1,"Fish-Guts",11,1415174819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,11,1,"Fish-Guts",11,1415374819);

-- Sop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (5,12,1,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (5,15,8,"FG",7,1415474819);

-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,1,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,1,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,1,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,1,"FG",7,1415474819);

-- #cservice

-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,2,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,2,"Fish-Guts",11,1415474819);

-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,10,2,"Fish-Guts",11,1415174819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,11,2,"Fish-Guts",11,1415374819);

-- Sop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (5,12,2,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (5,15,2,"Jamc",6,1415474819);

-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,2,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,2,"waterlily",5,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,2,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,2,"FG",7,1415474819);



-- #schaffhausen

-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17) 

-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,3,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,3,"Fish-Guts",11,1415474819);

-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,10,3,"Fish-Guts",11,1415174819);

-- Sop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (5,57,3,"Fish-Guts",11,1415474819);


-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,3,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,3,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,3,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,3,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,3,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,3,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,3,"Fish-Guts",11,1415474819);



-- #zurich

-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17) 

-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,4,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,4,"Fish-Guts",11,1415474819);

-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,10,4,"Fish-Guts",11,1415174819);

-- Sop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (5,57,4,"Fish-Guts",11,1415474819);


-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,4,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,4,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,4,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,4,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,4,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,4,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,4,"Fish-Guts",11,1415474819);

-- #basel

-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17) 

-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,5,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,5,"Fish-Guts",11,1415474819);

-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (7,15,5,"Fish-Guts",11,1415174819);

-- Sop

-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,5,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,5,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,5,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,5,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,5,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,5,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,5,"Fish-Guts",11,1415474819);

-- #zug

-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17) 

-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,6,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,6,"Fish-Guts",11,1415474819);

-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (7,17,6,"Fish-Guts",11,1415174819);

-- Sop

-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,6,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,6,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,6,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,6,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,6,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,6,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,6,"Fish-Guts",11,1415474819);

-- #thurgau

-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17) 

-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,7,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,7,"Fish-Guts",11,1415474819);

-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,12,7,"Fish-Guts",11,1415174819);

-- Sop

-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,7,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,7,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,7,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,7,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,7,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,7,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,7,"Fish-Guts",11,1415474819);



-- #stgallen

-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17) 

-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,8,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,8,"Fish-Guts",11,1415474819);

-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,12,8,"Fish-Guts",11,1415174819);

-- Sop

-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,8,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,8,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,8,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,8,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,8,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,8,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,8,"Fish-Guts",11,1415474819);


-- #aargau

-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17) 

-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,9,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,9,"Fish-Guts",11,1415474819);

-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,16,9,"Fish-Guts",11,1415174819);

-- Sop

-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,9,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,9,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,9,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,9,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,9,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,9,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,9,"Fish-Guts",11,1415474819);


-- #bern

-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17) 

-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,10,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,10,"Fish-Guts",11,1415474819);

-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,11,10,"Fish-Guts",11,1415174819);

-- Sop

-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,10,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,10,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,10,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,10,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,10,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,10,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,10,"Fish-Guts",11,1415474819);

-- #wallis

-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17) 

-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,11,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,11,"Fish-Guts",11,1415474819);

-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,13,11,"Fish-Guts",11,1415174819);

-- Sop

-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,11,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,11,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,11,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,11,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,11,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,11,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,11,"Fish-Guts",11,1415474819);

-- #vaud

-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17) 

-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,12,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,12,"Fish-Guts",11,1415474819);

-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,13,12,"Fish-Guts",11,1415174819);

-- Sop

-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,12,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,12,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,12,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,12,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,12,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,12,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,12,"Fish-Guts",11,1415474819);

-- #glarus

-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17) 

-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,13,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,13,"Fish-Guts",11,1415474819);

-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,14,13,"Fish-Guts",11,1415174819);

-- Sop

-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,13,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,13,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,13,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,13,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,13,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,13,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,13,"Fish-Guts",11,1415474819);

-- #schwyz

-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17) 

-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,14,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,14,"Fish-Guts",11,1415474819);

-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,14,14,"Fish-Guts",11,1415174819);

-- Sop

-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,14,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,14,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,14,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,14,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,14,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,14,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,14,"Fish-Guts",11,1415474819);

-- #graubuenden

-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17) 

-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,15,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,15,"Fish-Guts",11,1415474819);

-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (7,14,15,"Fish-Guts",11,1415174819);

-- Sop

-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,15,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,15,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,15,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,15,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,15,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,15,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,15,"Fish-Guts",11,1415474819);

-- #ticino

-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17) 

-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,16,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,16,"Fish-Guts",11,1415474819);

-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,13,16,"Fish-Guts",11,1415174819);

-- Sop

-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,16,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,16,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,16,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,16,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,16,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,16,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,16,"Fish-Guts",11,1415474819);

-- #uri

-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17) 

-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,17,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,17,"Fish-Guts",11,1415474819);

-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,17,17,"Fish-Guts",11,1415174819);

-- Sop

-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,17,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,17,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,17,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,17,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,17,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,17,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,17,"Fish-Guts",11,1415474819);


-- #obwalden

-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17) 

-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,18,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,18,"Fish-Guts",11,1415474819);

-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,17,18,"Fish-Guts",11,1415174819);

-- Sop

-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,18,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,18,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,18,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,18,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,18,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,18,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,18,"Fish-Guts",11,1415474819);

-- #nidwalden

-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17) 

-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,19,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,19,"Fish-Guts",11,1415474819);

-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,17,19,"Fish-Guts",11,1415174819);

-- Sop

-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,19,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,19,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,19,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,19,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,19,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,19,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,19,"Fish-Guts",11,1415474819);

-- #genf

-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17) 

-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,20,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,20,"Fish-Guts",11,1415474819);

-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,13,20,"Fish-Guts",11,1415174819);

-- Sop

-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,20,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,20,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,20,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,20,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,20,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,20,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,20,"Fish-Guts",11,1415474819);


-- #fribourg

-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17) 

-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,21,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,21,"Fish-Guts",11,1415474819);

-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,13,21,"Fish-Guts",11,1415174819);

-- Sop

-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,21,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,21,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,21,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,21,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,21,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,21,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,21,"Fish-Guts",11,1415474819);


-- #luzern

-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17) 

-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,22,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,22,"Fish-Guts",11,1415474819);

-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,17,22,"Fish-Guts",11,1415174819);

-- Sop

-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,22,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,22,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,22,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,22,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,22,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,22,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,22,"Fish-Guts",11,1415474819);



-- #jura

-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17) 

-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,23,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,23,"Fish-Guts",11,1415474819);

-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,15,23,"Fish-Guts",11,1415174819);

-- Sop

-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,23,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,23,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,23,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,23,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,23,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,23,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,23,"Fish-Guts",11,1415474819);

-- #solothurn

-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17) 

-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,24,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,24,"Fish-Guts",11,1415474819);

-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,15,24,"Fish-Guts",11,1415174819);

-- Sop

-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,24,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,24,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,24,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,24,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,24,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,24,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,24,"Fish-Guts",11,1415474819);


-- #neuchatel

-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17) 

-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,25,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,25,"Fish-Guts",11,1415474819);

-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,15,25,"Fish-Guts",11,1415174819);

-- Sop

-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,25,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,25,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,25,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,25,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,25,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,25,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,25,"Fish-Guts",11,1415474819);

-- #appenzell

-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17) 

-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,26,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,26,"Fish-Guts",11,1415474819);

-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,14,26,"Fish-Guts",11,1415174819);

-- Sop

-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,26,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,26,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,26,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,26,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,26,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,26,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,26,"Fish-Guts",11,1415474819);


-- #teentalk

-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17) 

-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,27,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,27,"Fish-Guts",11,1415474819);

-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,16,27,"Fish-Guts",11,1415174819);

-- Sop

-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,27,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,27,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,27,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,27,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,27,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,27,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,27,"Fish-Guts",11,1415474819);

-- #kidstalk

-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17) 

-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,28,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,28,"Fish-Guts",11,1415474819);

-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,16,28,"Fish-Guts",11,1415174819);

-- Sop

-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,28,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,28,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,28,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,28,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,28,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,28,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,28,"Fish-Guts",11,1415474819);

-- #reefmaster

-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17) 

-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,29,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,29,"Fish-Guts",11,1415474819);

-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,16,29,"Fish-Guts",11,1415174819);

-- Sop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (5,57,29,"Fish-Guts",11,1415174819);

-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,29,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,29,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,29,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,29,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,29,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,29,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,29,"Fish-Guts",11,1415474819);

-- #flirt20plus

-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17) 

-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,30,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,30,"Fish-Guts",11,1415474819);

-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,14,30,"Fish-Guts",11,1415174819);

-- Sop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (5,57,30,"Fish-Guts",11,1415174819);

-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,30,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,30,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,30,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,30,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,30,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,30,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,30,"Fish-Guts",11,1415474819);

-- #flirt30plus

-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17) 

-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,31,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,31,"Fish-Guts",11,1415474819);

-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,14,31,"Fish-Guts",11,1415174819);

-- Sop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (5,57,31,"Fish-Guts",11,1415174819);

-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,31,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,31,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,31,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,31,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,31,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,31,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,31,"Fish-Guts",11,1415474819);

-- #flirt40plus

-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17) 

-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,32,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,32,"Fish-Guts",11,1415474819);

-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,14,32,"Fish-Guts",11,1415174819);

-- Sop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (5,57,32,"Fish-Guts",11,1415174819);

-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,32,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,32,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,32,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,32,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,32,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,32,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,32,"Fish-Guts",11,1415474819);

-- #flirt50plus

-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17) 

-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,33,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,33,"Fish-Guts",11,1415474819);

-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,14,33,"Fish-Guts",11,1415174819);

-- Sop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (5,57,33,"Fish-Guts",11,1415174819);

-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,33,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,33,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,33,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,33,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,33,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,33,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,33,"Fish-Guts",11,1415474819);

-- #flirt60plus

-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17) 

-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,34,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,34,"Fish-Guts",11,1415474819);

-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,14,34,"Fish-Guts",11,1415174819);

-- Sop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (5,57,34,"Fish-Guts",11,1415174819);

-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,34,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,34,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,34,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,34,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,34,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,34,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,34,"Fish-Guts",11,1415474819);

-- #linux

-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17) 

-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,35,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,35,"Fish-Guts",11,1415474819);

-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,11,35,"Fish-Guts",11,1415174819);

-- Sop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (5,57,35,"Fish-Guts",11,1415174819);

-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,35,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,35,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,35,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,35,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,35,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,35,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,35,"Fish-Guts",11,1415474819);

-- #quiz

-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17) 

-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,36,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,36,"Fish-Guts",11,1415474819);

-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,16,36,"Fish-Guts",11,1415174819);

-- Sop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (5,57,36,"Fish-Guts",11,1415174819);

-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,36,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,36,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,36,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,36,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,36,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,36,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,36,"Fish-Guts",11,1415474819);

-- #counter-strike

-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17) 

-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,37,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,37,"Fish-Guts",11,1415474819);

-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,16,37,"Fish-Guts",11,1415174819);

-- Sop

-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,37,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,37,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,37,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,37,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,37,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,37,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,37,"Fish-Guts",11,1415474819);


-- #menonly

-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17) 

-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,38,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,38,"Fish-Guts",11,1415474819);

-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,16,38,"Fish-Guts",11,1415174819);

-- Sop

-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,38,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,38,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,38,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,38,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,38,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,38,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,38,"Fish-Guts",11,1415474819);





INSERT INTO NS_ACCESS(NICK_ID,MASK) VALUES (1,"fish-guts@*");
INSERT INTO NS_ACCESS(NICK_ID,MASK) VALUES (1,"FG@*");
INSERT INTO NS_ACCESS(NICK_ID,MASK) VALUES (1,"pennywise@*");
INSERT INTO NS_ACCESS(NICK_ID,MASK) VALUES (2,"FG@*");
INSERT INTO NS_ACCESS(NICK_ID,MASK) VALUES (3,"jamc@*");
INSERT INTO NS_ACCESS(NICK_ID,MASK) VALUES (3,"jamc2@*");
INSERT INTO NS_ACCESS(NICK_ID,MASK) VALUES (4,"test1@*");
INSERT INTO NS_ACCESS(NICK_ID,MASK) VALUES (5,"test2@*");
INSERT INTO NS_ACCESS(NICK_ID,MASK) VALUES (6,"test3@*");
INSERT INTO NS_ACCESS(NICK_ID,MASK) VALUES (7,"test4@*");

INSERT INTO NS_NOTIFY(NICK_ID,NOTIFICATION_NICK_ID) VALUES (1,2);
INSERT INTO NS_NOTIFY(NICK_ID,NOTIFICATION_NICK_ID) VALUES (1,3);
INSERT INTO NS_NOTIFY(NICK_ID,NOTIFICATION_NICK_ID) VALUES (1,4);
INSERT INTO NS_NOTIFY(NICK_ID,NOTIFICATION_NICK_ID) VALUES (1,5);
INSERT INTO NS_NOTIFY(NICK_ID,NOTIFICATION_NICK_ID) VALUES (1,6);
INSERT INTO NS_NOTIFY(NICK_ID,NOTIFICATION_NICK_ID) VALUES (1,7);
INSERT INTO NS_NOTIFY(NICK_ID,NOTIFICATION_NICK_ID) VALUES (1,8);
INSERT INTO NS_NOTIFY(NICK_ID,NOTIFICATION_NICK_ID) VALUES (1,9);
INSERT INTO NS_NOTIFY(NICK_ID,NOTIFICATION_NICK_ID) VALUES (1,10);
INSERT INTO NS_NOTIFY(NICK_ID,NOTIFICATION_NICK_ID) VALUES (1,11);
INSERT INTO NS_NOTIFY(NICK_ID,NOTIFICATION_NICK_ID) VALUES (1,12);
INSERT INTO NS_NOTIFY(NICK_ID,NOTIFICATION_NICK_ID) VALUES (1,13);
INSERT INTO NS_NOTIFY(NICK_ID,NOTIFICATION_NICK_ID) VALUES (1,14);
INSERT INTO NS_NOTIFY(NICK_ID,NOTIFICATION_NICK_ID) VALUES (1,15);
INSERT INTO NS_NOTIFY(NICK_ID,NOTIFICATION_NICK_ID) VALUES (1,16);
INSERT INTO NS_NOTIFY(NICK_ID,NOTIFICATION_NICK_ID) VALUES (2,1);
INSERT INTO NS_NOTIFY(NICK_ID,NOTIFICATION_NICK_ID) VALUES (2,3);
INSERT INTO NS_NOTIFY(NICK_ID,NOTIFICATION_NICK_ID) VALUES (2,4);
INSERT INTO NS_NOTIFY(NICK_ID,NOTIFICATION_NICK_ID) VALUES (2,5);
INSERT INTO NS_NOTIFY(NICK_ID,NOTIFICATION_NICK_ID) VALUES (2,6);
INSERT INTO NS_NOTIFY(NICK_ID,NOTIFICATION_NICK_ID) VALUES (2,7);
INSERT INTO NS_NOTIFY(NICK_ID,NOTIFICATION_NICK_ID) VALUES (2,8);
INSERT INTO NS_NOTIFY(NICK_ID,NOTIFICATION_NICK_ID) VALUES (2,9);
INSERT INTO NS_NOTIFY(NICK_ID,NOTIFICATION_NICK_ID) VALUES (2,10);
INSERT INTO NS_NOTIFY(NICK_ID,NOTIFICATION_NICK_ID) VALUES (2,11);
INSERT INTO NS_NOTIFY(NICK_ID,NOTIFICATION_NICK_ID) VALUES (2,12);
INSERT INTO NS_NOTIFY(NICK_ID,NOTIFICATION_NICK_ID) VALUES (2,13);
INSERT INTO NS_NOTIFY(NICK_ID,NOTIFICATION_NICK_ID) VALUES (2,14);
INSERT INTO NS_NOTIFY(NICK_ID,NOTIFICATION_NICK_ID) VALUES (2,22);
INSERT INTO NS_NOTIFY(NICK_ID,NOTIFICATION_NICK_ID) VALUES (2,24);
INSERT INTO NS_NOTIFY(NICK_ID,NOTIFICATION_NICK_ID) VALUES (2,23);
INSERT INTO NS_NOTIFY(NICK_ID,NOTIFICATION_NICK_ID) VALUES (2,25);
INSERT INTO NS_NOTIFY(NICK_ID,NOTIFICATION_NICK_ID) VALUES (2,26);
INSERT INTO NS_NOTIFY(NICK_ID,NOTIFICATION_NICK_ID) VALUES (2,27);

INSERT INTO NS_AUTH(TARGET_TYPE,TARGET,SENDER,RECIPIENT,TIME,STATUS,ACCESS) VALUES(0,24,1,24,1415474819,1,0);
INSERT INTO NS_AUTH(TARGET_TYPE,TARGET,SENDER,RECIPIENT,TIME,STATUS,ACCESS) VALUES(0,25,1,25,1415474819,1,0);
INSERT INTO NS_AUTH(TARGET_TYPE,TARGET,SENDER,RECIPIENT,TIME,STATUS,ACCESS) VALUES(0,26,1,26,1415474819,1,0);
INSERT INTO NS_AUTH(TARGET_TYPE,TARGET,SENDER,RECIPIENT,TIME,STATUS,ACCESS) VALUES(0,27,1,27,1415474819,1,0);
INSERT INTO NS_AUTH(TARGET_TYPE,TARGET,SENDER,RECIPIENT,TIME,STATUS,ACCESS) VALUES(1,2,2,4,1415474819,1,6);
INSERT INTO NS_AUTH(TARGET_TYPE,TARGET,SENDER,RECIPIENT,TIME,STATUS,ACCESS) VALUES(1,2,2,3,1415474819,1,6);
INSERT INTO NS_AUTH(TARGET_TYPE,TARGET,SENDER,RECIPIENT,TIME,STATUS,ACCESS) VALUES(1,2,2,4,1415474819,1,6);
INSERT INTO NS_AUTH(TARGET_TYPE,TARGET,SENDER,RECIPIENT,TIME,STATUS,ACCESS) VALUES(1,2,2,5,1415474819,2,6);
INSERT INTO NS_AUTH(TARGET_TYPE,TARGET,SENDER,RECIPIENT,TIME,STATUS,ACCESS) VALUES(1,2,2,6,1415474819,1,6);
INSERT INTO NS_AUTH(TARGET_TYPE,TARGET,SENDER,RECIPIENT,TIME,STATUS,ACCESS) VALUES(1,2,2,7,1415474819,1,6);
INSERT INTO NS_AUTH(TARGET_TYPE,TARGET,SENDER,RECIPIENT,TIME,STATUS,ACCESS) VALUES(2,1,1,8,1415474819,1,6);
INSERT INTO NS_AUTH(TARGET_TYPE,TARGET,SENDER,RECIPIENT,TIME,STATUS,ACCESS) VALUES(2,2,1,9,1415474819,1,6);
INSERT INTO NS_AUTH(TARGET_TYPE,TARGET,SENDER,RECIPIENT,TIME,STATUS,ACCESS) VALUES(2,3,1,10,1415474819,2,6);
INSERT INTO NS_AUTH(TARGET_TYPE,TARGET,SENDER,RECIPIENT,TIME,STATUS,ACCESS) VALUES(3,4,1,11,1415474819,1,6);
INSERT INTO NS_AUTH(TARGET_TYPE,TARGET,SENDER,RECIPIENT,TIME,STATUS,ACCESS) VALUES(3,5,1,12,1415474819,1,6);
INSERT INTO NS_AUTH(TARGET_TYPE,TARGET,SENDER,RECIPIENT,TIME,STATUS,ACCESS) VALUES(3,5,1,8,1415474819,2,6);
INSERT INTO NS_AUTH(TARGET_TYPE,TARGET,SENDER,RECIPIENT,TIME,STATUS,ACCESS) VALUES(4,5,1,14,1415474819,1,6);
INSERT INTO NS_AUTH(TARGET_TYPE,TARGET,SENDER,RECIPIENT,TIME,STATUS,ACCESS) VALUES(4,5,1,15,1415474819,1,6);
INSERT INTO NS_AUTH(TARGET_TYPE,TARGET,SENDER,RECIPIENT,TIME,STATUS,ACCESS) VALUES(4,6,1,16,1415474819,1,6);


INSERT INTO OPERS(NICKNAME,CAN_AKILL,CAN_CHGHOST,CAN_GLOBAL, CAN_LOCAL,CAN_KICK,CAN_KILL,CAN_SGLINE,CAN_SKLINE,CAN_SQLINE,CAN_SVSNICK,CAN_SZLINE) VALUES(4,1,1,1,1,1,1,1,1,1,1,1);
INSERT INTO OPERS(NICKNAME,CAN_AKILL,CAN_CHGHOST,CAN_GLOBAL, CAN_LOCAL,CAN_KICK,CAN_KILL,CAN_SGLINE,CAN_SKLINE,CAN_SQLINE,CAN_SVSNICK,CAN_SZLINE) VALUES(5,1,1,0,1,1,1,0,1,1,1,1);
INSERT INTO OPERS(NICKNAME,CAN_AKILL,CAN_CHGHOST,CAN_GLOBAL, CAN_LOCAL,CAN_KICK,CAN_KILL,CAN_SGLINE,CAN_SKLINE,CAN_SQLINE,CAN_SVSNICK,CAN_SZLINE) VALUES(6,1,1,0,1,1,1,0,1,1,1,1);


INSERT INTO AKILL (HOST,EXPIRY,ADDED_BY,REASON) VALUES('bill@gates',1414674819,'severin','nope');
