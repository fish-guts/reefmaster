/*
	script for creating the db schema
	created by fish-guts
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


INSERT INTO BOTS VALUES (1,"Chanbot","hoppus123","chanserv","Channel Bot");
INSERT INTO BOTS VALUES (2,"Wulfbot","hoppus123","chanserv","Channel Bot");
INSERT INTO BOTS VALUES (3,"X","hoppus123","chanserv","Channel Bot");
INSERT INTO BOTS VALUES (4,"Musicbot","hoppus123","chanserv","Channel Bot");
INSERT INTO BOTS VALUES (5,"Regiobot","hoppus123","chanserv","Channel Bot");
INSERT INTO BOTS VALUES (6,"Englishbot","hoppus123","chanserv","Channel Bot");
INSERT INTO BOTS VALUES (7,"Romandbot","hoppus123","chanserv","Channel Bot");

 
INSERT INTO NICKS VALUES(1, "Fish-Guts",	"hoppus123","fish-guts@reefmaster.ch",	"Fish-Guts",		982007912,1466715992,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(2,"FG",		"hoppus123","fish-guts@reefmaster.ch",	"FG",			982007912,1415474819,1,10,"www.reefmaster.ch","fish-guts@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(3,"SNoX",		"snox123",  "snox@reefmaster.ch",	"SnOX",			1282007912,1415474819,1,10,"www.reefmaster.ch","snox@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(4,"S",			"snox123",  "snox@reefmaster.ch",	"Snox",			1282007912,1415474819,1,10,"www.reefmaster.ch","snox@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(5,"}SpIoN{",		"hoppus123","ohcysp@reefmaster.ch",	"Snox",			1282007912,1415474819,1,10,"www.reefmaster.ch","ohcysp@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(6,"ventura",		"hoppus123","ventura@reefmaster.ch",	"ventura",		1282007912,1415474819,1,10,"www.reefmaster.ch","ventura@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(7,"mk",		"hoppus123","mk@reefmaster.ch",		"Fish-Guts",		1282007912,1415474819,1,10,"www.reefmaster.ch","mk@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(8,"ll4mat",		"hoppus123","ll4mat@reefmaster.ch",	"ll4mat",		1282007912,1415474819,1,10,"www.reefmaster.ch","ll4mat@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(9,"ake",		"hoppus123","ake@reefmaster.ch",	"ake",			1282007912,1415474819,1,10,"www.reefmaster.ch","ake@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(10,"Jamc",		"hoppus123","jamc@reefmaster.ch",	"Jamc",			1282007912,1415474819,1,10,"www.reefmaster.ch","jamc@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(11,"CgIMaN",		"hoppus123","cgiman@reefmaster.ch",	"CgiMaN",		1282007912,1282007912,1,10,"www.reefmaster.ch","cgiman@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(12,"red-dog",		"hoppus123","red-dog@reefmaster.ch",	"fido-rosso",		1282007912,1282007912,1,10,"www.reefmaster.ch","red-dog@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(13,"V",		"hoppus123","vi@reefmaster.ch",		"V",			1282007912,1415474819,1,10,"www.reefmaster.ch","vi@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(14,"Delfin",		"hoppus123","delfin@reefmaster.ch",	"Delfin",		1282007912,1415474819,1,10,"www.reefmaster.ch","delfin@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(15,"waterlily",	"hoppus123","waterlily@reefmaster.ch",	"waterlily",		1282007912,1282007912,1,10,"www.reefmaster.ch","waterlily@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(16,"YJ",		"hoppus123","bnfh@reefmaster.ch",	"BNFH",			1415474819,1415474819,1,10,"www.reefmaster.ch","bnfh@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(17,"neo",		"hoppus123","neo@reefmaster.ch",	"Neo",			1415474819,1415474819,1,10,"www.reefmaster.ch","neo@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(18,"leota",		"hoppus123","leota@reefmaster.ch",	"leota",		1466715992,1415474819,1,10,"www.reefmaster.ch","leota@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(19,"Schwan",		"hoppus123","schwan@reefmaster.ch",	"schwan",		1466715992,1415474819,1,10,"www.reefmaster.ch","schwan@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(20,"pixel",		"hoppus123","pixel@reefmaster.ch",	"pixel",		1282007912,1415474819,1,10,"www.reefmaster.ch","pixel@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(21,"Gargo",		"hoppus123","gargo@reefmaster.ch",	"Gargo",		1282007912,1415474819,1,10,"www.reefmaster.ch","gargo@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(22,"dungeon_lady",	"hoppus123","dragonia@reefmaster.ch",	"dl",			1282007912,1415474819,1,10,"www.reefmaster.ch","dragonia@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(23,"Angel",		"hoppus123","angel@reefmaster.ch",	"Angel",		1415474819,1415474819,1,10,"www.reefmaster.ch","angel@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(24,"FischerZH",	"hoppus123","fisher@reefmaster.ch",	"Kenny Fischer",	1282007912,1415474819,1,10,"www.reefmaster.ch","fisher@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(25,"JiLe",		"hoppus123","juuls@reefmaster.ch",	"JuLchen",		1415474819,1415474819,1,10,"www.reefmaster.ch","juuls@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(26,"Earthworm",	"hoppus123","ew@reefmaster.ch",		"Jonas",		1282007912,1415474819,1,10,"www.reefmaster.ch","ew@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(27,"Valentin",		"hoppus123","valentin@reefmaster.ch",	"Valentin",		1466715992,1466715992,1,10,"www.reefmaster.ch","valentin@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(28,"Kane",		"hoppus123","dark_kane@reefmaster.ch",	"Kane",			1466715992,1466715992,1,10,"www.reefmaster.ch","dark_kane@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(29,"lemon_w",		"hoppus123","CHallo@reefmaster.ch",	"lämän",		1466715992,1466715992,1,10,"www.reefmaster.ch","CHallo@reefmaster.ch",-1,1,0,0,1,2,"ntr",0);
INSERT INTO NICKS VALUES(30,"Audrey",		"hoppus123","audrey@reefmaster.ch",	"Audrey",		1466715992,1466715992,1,10,"www.reefmaster.ch","audrey@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(31,"Adler",		"hoppus123","adler@reefmaster.ch",	"Adler",		1466715992,1466715992,1,10,"www.reefmaster.ch","adler@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(32,"rockoli",		"hoppus123","rockoli@reefmaster.ch",	"rockoli",		1466715992,1466715992,1,10,"www.reefmaster.ch","rockoli@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(33,"Atlas",		"hoppus123","Atlas@reefmaster.ch",	"Atlas",		1466715992,1466715992,1,10,"www.reefmaster.ch","Atlas@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(34,"Carol",		"hoppus123","carol@reefmaster.ch",	"Carol",		1466715992,1466715992,1,10,"www.reefmaster.ch","carol@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(35,"moendli",		"hoppus123","moendli@reefmaster.ch",	"moendli",		1466715992,1466715992,1,10,"www.reefmaster.ch","moendli@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(36,"opso",		"hoppus123","opso@reefmaster.ch",	"opso",			1466715992,1466715992,1,10,"www.reefmaster.ch","opso@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(37,"Noise",		"hoppus123","noise@reefmaster.ch",	"Noise",		1466715992,1466715992,1,10,"www.reefmaster.ch","noise@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(38,"Pazzolina",	"hoppus123","pazzolina@reefmaster.ch",	"Pazzolina",		1466715992,1466715992,1,10,"www.reefmaster.ch","pazzolina@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(39,"liesel",		"hoppus123","liesel@reefmaster.ch",	"liesel",		1466715992,1466715992,1,10,"www.reefmaster.ch","liesel@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(40,"Xenon",		"hoppus123","xenon@reefmaster.ch",	"Xenon",		1466715992,1466715992,1,10,"www.reefmaster.ch","xenon@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(41,"Sting",		"hoppus123","Sting@reefmaster.ch",	"Sting",		1466715992,1466715992,1,10,"www.reefmaster.ch","Sting@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(42,"Topi",		"hoppus123","topi@reefmaster.ch",	"Topi",			1466715992,1466715992,1,10,"www.reefmaster.ch","topi@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(43,"ChuckyB",		"hoppus123","chuckyb@reefmaster.ch",	"ChuckyB",		1466715992,1466715992,1,10,"www.reefmaster.ch","chuckyb@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(44,"ErnIe",		"hoppus123","ernie@reefmaster.ch",	"Ernie",		1466715992,1466715992,1,10,"www.reefmaster.ch","ernie@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(45,"SEV-Y",		"hoppus123","sevi@reefmaster.ch",	"Sevi",			1466715992,1466715992,1,10,"www.reefmaster.ch","sevi@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(46,"Indy",		"hoppus123","indy@reefmaster.ch",	"Indy",			1466715992,1466715992,1,10,"www.reefmaster.ch","indy@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(47,"Raverin17",	"hoppus123","silence@reefmaster.ch",	"silence",		1466715992,1466715992,1,10,"www.reefmaster.ch","silence@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(48,"Zitroenchen",	"hoppus123","zit@reefmaster.ch",	"zitro",		1466715992,1466715992,1,10,"www.reefmaster.ch","zit@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(49,"wulf",		"hoppus123","wulf@reefmaster.ch",	"wulf",			1466715992,1466715992,1,10,"www.reefmaster.ch","wulf@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(50,"eS",		"hoppus123","es@reefmaster.ch",		"es",			1466715992,1466715992,1,10,"www.reefmaster.ch","snox@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(51,"Hologram",		"hoppus123","hg@reefmaster.ch",		"HG",			1466715992,1466715992,1,10,"www.reefmaster.ch","hg@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(52,"triplesensor",	"hoppus123","trip@reefmaster.ch",	"trip",			1466715992,1466715992,1,10,"www.reefmaster.ch","trip@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(53,"gIL",		"hoppus123","gil@reefmaster.ch",	"Gil",			1466715992,1466715992,1,10,"www.reefmaster.ch","gil@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(54,"Ah-lee-yah",	"hoppus123","liyah@reefmaster.ch",	"Liyah",		1466715992,1466715992,1,10,"www.reefmaster.ch","liyah@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(55,"Gizmo",		"hoppus123","gizmo@reefmaster.ch",	"Gizmo",		1466715992,1466715992,1,10,"www.reefmaster.ch","gizmo@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(56,"Athlon",		"hoppus123","athlon@reefmaster.ch",	"Athlon",		1466715992,1466715992,1,10,"www.reefmaster.ch","athlon@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(57,"moebius",		"moebius123","moebius@reefmaster.ch",	"Moebius",		1466715992,1466715992,1,10,"www.reefmaster.ch","moebius@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(58,"McViperly",	"hoppus123","viper@reefmaster.ch",	"Viper",		1466715992,1466715992,1,10,"www.reefmaster.ch","viper@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(59,"Ombra_m",		"hoppus123","gio@reefmaster.ch",	"Gio",			1466715992,1466715992,1,10,"www.reefmaster.ch","gio@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(60,"Snowblind",	"hoppus123","dark-snow@reefmaster.ch",	"Snow",			1466715992,1466715992,1,10,"www.reefmaster.ch","dark-snow@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(61,"fallen-angel",	"hoppus123","fa@reefmaster.ch",		"Fallen",		1466715992,1466715992,1,10,"www.reefmaster.ch","fa@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(62,"Iron",		"hoppus123","iron@reefmaster.ch",	"iron",			1466715992,1466715992,1,10,"www.reefmaster.ch","iron@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(63,"b4tt3l-droid",	"hoppus123","bd@reefmaster.ch",		"b4ttel",		1466715992,1466715992,1,10,"www.reefmaster.ch","bd@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(64,"clubi",		"hoppus123","clubi@reefmaster.ch",	"clubi",		1466715992,1466715992,1,10,"www.reefmaster.ch","clubi@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(65,"the_least_w",	"hoppus123","least@reefmaster.ch",	"least",		1466715992,1466715992,1,10,"www.reefmaster.ch","least@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(66,"MiSs_TiGeRLaDy",	"hoppus123","mf@reefmaster.ch",		"Tiger",		1466715992,1466715992,1,10,"www.reefmaster.ch","mf@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(67,"SuN-LaDy",		"hoppus123","SuN-LaDy@reefmaster.ch",	"SuN-LaDy",		1466715992,1466715992,1,10,"www.reefmaster.ch","SuN-LaDy@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(68,"Whity",		"hoppus123","Whity@reefmaster.ch",	"Whity",		1466715992,1466715992,1,10,"www.reefmaster.ch","Whity@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(69,"harris",		"hoppus123","harris@reefmaster.ch",	"harris",		1466715992,1466715992,1,10,"www.reefmaster.ch","harris@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(70,"ZSC-Webby",	"hoppus123","ZSC-Webby@reefmaster.ch",	"harris",		1466715992,1466715992,1,10,"www.reefmaster.ch","ZSC-Webby@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);
INSERT INTO NICKS VALUES(71,"TheCrow",		"hoppus123","TheCrow@reefmaster.ch",	"harris",		1466715992,1466715992,1,10,"www.reefmaster.ch","TheCrow@reefmaster.ch",-1,1,0,1,1,2,"ntr",0);


INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (1,"BluePanther!*@*.bluewin.ch","Fish-Guts",8,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (1,"SilverBird!*@*.bluewin.ch","Fish-Guts",8,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (1,"stskeeps!*@*.verizon.com","Fish-Guts",8,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (1,"alfred!*@*.redwave.route0.net","Fish-Guts",8,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (1,"aka*!*@*.bluewin.ch","Fish-Guts",8,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (1,"pilz!*@*.bluewin.ch","Fish-Guts",8,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (1,"foo!*@*.bluewin.ch","Fish-Guts",8,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (1,"bar!*@*.bluewin.ch","Fish-Guts",8,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (2,"BluePanther!*@*.bluewin.ch","FG",5,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (2,"SilverBird!*@*.bluewin.ch","ventura",4,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (2,"aka*!*@*.bluewin.ch","Jamc",4,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (3,"BluePanther!*@*.bluewin.ch","V",4,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (3,"chuckyB!*@*.hispeed.ch","V",4,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (3,"SilverBird!*@*.bluewin.ch","V",4,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (4,"BluePanther!*@*.bluewin.ch","CgIMan",8,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (4,"chuckyB!*@*.hispeed.ch","CgIMan",8,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (4,"SilverBird!*@*.bluewin.ch","CgIMan",8,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (5,"BluePanther!*@*.bluewin.ch","FG",5,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (5,"chuckyB!*@*.bluewin.ch","FG",5,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (5,"poltergeist!*@*.hispeed.ch","FG",5,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (5,"aka*!*@*.bluewin.ch","FG",5,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (6,"chuckyB!*@*.bluewin.ch","FG",5,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (6,"BluePanther!*@*.bluewin.ch","Jamc",4,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (7,"BluePanther!*@*.bluewin.ch","Jamc",4,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (7,"chuckyB!*@*.bluewin.ch","Jamc",4,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (7,"SilverBird!*@*.bluewin.ch","Jamc",4,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (7,"aka*!*@*.bluewin.ch","ventura",4,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (8,"BluePanther!*@*.bluewin.ch","Fish-Guts",8,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (8,"chuckyB!*@*.bluewin.ch","Fish-Guts",8,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (8,"SilverBird!*@*.bluewin.ch","Fish-Guts",8,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (8,"pinopierre!*@*.bluewin.ch","Fish-Guts",8,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (9,"BluePanther!*@*.bluewin.ch","Fish-Guts",8,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (9,"SilverBird!*@*.bluewin.ch","Fish-Guts",8,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (10,"BluePanther!*@*.bluewin.ch","Fish-Guts",8,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (10,"chuckyB!*@*.bluewin.ch","Fish-Guts",8,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (10,"SilverBird!*@*.bluewin.ch","Fish-Guts",8,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (10,"pinopierre!*@*.bluewin.ch","Fish-Guts",8,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (10,"aka*!*@*.bluewin.ch","Fish-Guts",8,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (10,"tripolis!*@*.bluewin.ch","Fish-Guts",8,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (11,"BluePanther!*@*.bluewin.ch","Fish-Guts",8,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (11,"chuckyB!*@*.bluewin.ch","Fish-Guts",8,982007912,"You are banned for misbehaving");
INSERT INTO CS_AKICK (CHAN,MASK,ADDED_BY,ADDED_BY_ACC,ADDED_ON,REASON) VALUES (11,"SilverBird!*@*.bluewin.ch","Fish-Guts",8,982007912,"You are banned for misbehaving");



INSERT INTO CHANS VALUES(1, "#ircops",			"hoppus123","The IRC Operator Channel",			982007912,		1,1,2,		"ertn-k",	"12% 0,12%¸ 2,12`% 12,2%¸ 1,2% 2,1% 0,1 -= Reefmaster IRC Operators =- 2,1`% 1,2%¸ 12,2`% 2,12%¸ 0,12`% 12,%-",						"Fish-Guts",	1282007912,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(2, "#cservice",		"hoppus123","Operator Service",					982007912,		1,1,3,		"ertn-k",	"9,0æ 0,9æ 3,9æ 9,3æ 1,3æ 3,1æ 9,1 #cservice,1æ 1,3æ 9,3æ 3,9æ 0,9æ 9,0æ",																"Fish-Guts",	1382007912,0,1,0,4,1,1,"www.reefmaster.ch",3);
INSERT INTO CHANS VALUES(3, "#schaffhausen",	"hoppus123","Schaffhausen",						982007912,		1,1,3, 		"ertn-k",	"12% 0,12%¸ 2,12`% 12,2%¸ 1,2% 2,1% 0,1 -= #schaffhausen =- 2,1`% 1,2%¸ 12,2`% 2,12%¸ 0,12`% 12,%-",									"ventura",		1266715992,0,1,0,4,1,1,"www.reefmaster.ch",3);
INSERT INTO CHANS VALUES(4, "#zuerich",			"hoppus123","Zuerich",							982007912,		1,1,3, 		"ertn-k",	"12% 0,12%¸ 2,12`% 12,2%¸ 1,2% 2,1% 0,1 -= #zuerich =- 2,1`% 1,2%¸ 12,2`% 2,12%¸ 0,12`% 12,%-",										"ventura",		1182007912,0,1,0,4,1,1,"www.reefmaster.ch",3);
INSERT INTO CHANS VALUES(5, "#basel",			"hoppus123","Basel",							982007912,		1,1,-1,		"ertn-k",	"12% 0,12%¸ 2,12`% 12,2%¸ 1,2% 2,1% 0,1 -= #basel =- 2,1`% 1,2%¸ 12,2`% 2,12%¸ 0,12`% 12,%-",											"mk",			1182007912,0,1,0,4,1,1,"www.reefmaster.ch",3);
INSERT INTO CHANS VALUES(6, "#zug",				"hoppus123","Zug",								982007912,		1,1,-1,		"ertn-k",	"9,0æ 0,9æ 3,9æ 9,3æ 1,3æ 3,1æ 9,1 #zug3,1æ 1,3æ 9,3æ 3,9æ 0,9æ 9,0æ",																	"mk",			1222007912,0,1,0,4,1,1,"www.reefmaster.ch",3);
INSERT INTO CHANS VALUES(7, "#thurgau",			"hoppus123","Thurgau",							982007912,		1,1,-1,		"ertn-k",	"12% 0,12%¸ 2,12`% 12,2%¸ 1,2% 2,1% 0,1 -= #zuerich =- 2,1`% 1,2%¸ 12,2`% 2,12%¸ 0,12`% 12,%-",										"FG",			1256715992,0,1,0,4,1,1,"www.reefmaster.ch",3);
INSERT INTO CHANS VALUES(8, "#stgallen",		"hoppus123","St. Gallen",						982007912,		1,1,-1,		"ertn-k",	"12% 0,12%¸ 2,12`% 12,2%¸ 1,2% 2,1% 0,1 -= #stgallen =- 2,1`% 1,2%¸ 12,2`% 2,12%¸ 0,12`% 12,%-",										"mk",			982007912,0,1,0,4,1,1,"www.reefmaster.ch",4);
INSERT INTO CHANS VALUES(9, "#aargau",			"hoppus123","Aargau",							982007912,		1,1,-1,		"ertn-k",	"9,0æ 0,9æ 3,9æ 9,3æ 1,3æ 3,1æ 9,1 #aargau3,1æ 1,3æ 9,3æ 3,9æ 0,9æ 9,0æ",																"Fish-Guts",	982007912,0,1,0,4,1,1,"www.reefmaster.ch",3);
INSERT INTO CHANS VALUES(10,"#bern",			"hoppus123","Bern",								982007912,		1,37,1,		"ertn-k",	"9,0æ 0,9æ 3,9æ 9,3æ 1,3æ 3,1æ 9,1 #bern3,1æ 1,3æ 9,3æ 3,9æ 0,9æ 9,0æ",																"V",			982007912,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(11,"#wallis",			"hoppus123","Wallis",							982007912,		1,37,1,		"ertn-k",	"12% 0,12%¸ 2,12`% 12,2%¸ 1,2% 2,1% 0,1 -= #wallis =- 2,1`% 1,2%¸ 12,2`% 2,12%¸ 0,12`% 12,%-",											"V",			1246715992,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(12,"#vaud",			"hoppus123","Vaud/Waadt",						982007912,		1,37,1,		"ertn-k",	"7,4% 0,4% 4,4 5,4% 4,5% 5,5 1,5% 5,1% 1,1 15,1 #vaud 5,1% 1,5% 5,5 4,5% 5,4% 4,4 1,4% 7,4%",								"FG",			1466715992,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(13,"#glarus",			"hoppus123","Glarus",							982007912,		1,37,1,		"ertn-k",	"7,4% 0,4% 4,4 5,4% 4,5% 5,5 1,5% 5,1% 1,1 15,1 #glarus 5,1% 1,5% 5,5 4,5% 5,4% 4,4 1,4% 7,4%",								"Fish-Guts",	1466715992,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(14,"#schwyz",			"hoppus123","Schwyz",							982007912,		1,37,1,		"ertn-k",	"7,4% 0,4% 4,4 5,4% 4,5% 5,5 1,5% 5,1% 1,1 15,1 #schwyz 5,1% 1,5% 5,5 4,5% 5,4% 4,4 1,4% 7,4%",								"Fish-Guts",	1466715992,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(15,"#graubuenden",		"hoppus123","Bündnerland",						982007912,		1,37,1,		"ertn-k",	"7,4% 0,4% 4,4 5,4% 4,5% 5,5 1,5% 5,1% 1,1 15,1 #graubuenden 5,1% 1,5% 5,5 4,5% 5,4% 4,4 1,4% 7,4%",						"Fish-Guts",	1466715992,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(16, "#ticino",			"hoppus123","Ticino",							982007912,		1,3,1,		"ertn-k",	"9,0æ 0,9æ 3,9æ 9,3æ 1,3æ 3,1æ 9,1 #ticino3,1æ 1,3æ 9,3æ 3,9æ 0,9æ 9,0æ",																"Fish-Guts",	1466715992,0,1,0,4,1,1,"www.reefmaster.ch",5);	
INSERT INTO CHANS VALUES(17,"#uri",				"hoppus123","Uri",								982007912,		1,3,1,		"ertn-k",	"9,0æ 0,9æ 3,9æ 9,3æ 1,3æ 3,1æ 9,1 #uri3,1æ 1,3æ 9,3æ 3,9æ 0,9æ 9,0æ",																	"Fish-Guts",	1466715992,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(18,"#obwalden",		"hoppus123","Obwalden",							982007912,		1,3,1,		"ertn-k",	"7,4% 0,4% 4,4 5,4% 4,5% 5,5 1,5% 5,1% 1,1 15,1 #obwalden 5,1% 1,5% 5,5 4,5% 5,4% 4,4 1,4% 7,4%",							"Fish-Guts",	1466715992,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(19,"#nidwalden",		"hoppus123","Nidwalden",						982007912,		1,3,1,		"ertn-k",	"8,0% 0,8æ 7,8% 8,7% 4,7% 7,4% 5,4% 4,5% 1,5% 5,1% 8,1 #nidwalden5,1% 1,5% 4,5% 5,4% 7,4% 4,7% 8,7% 7,8% 0,8% 8,0%",	"FG",			1466715992,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(20,"#genf",			"hoppus123","Genève",							982007912,		1,3,1,		"ertn-k",	"8,0% 0,8æ 7,8% 8,7% 4,7% 7,4% 5,4% 4,5% 1,5% 5,1% 8,1 #genf5,1% 1,5% 4,5% 5,4% 7,4% 4,7% 8,7% 7,8% 0,8% 8,0%",		"Valentin",		1466715992,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(21,"#fribourg",		"hoppus123","Fribourg",							982007912,		1,3,1,		"ertn-k",	"8,0% 0,8æ 7,8% 8,7% 4,7% 7,4% 5,4% 4,5% 1,5% 5,1% 8,1 #fribourg5,1% 1,5% 4,5% 5,4% 7,4% 4,7% 8,7% 7,8% 0,8% 8,0%",	"FG",			1466715992,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(22,"#luzern",			"hoppus123","Luzern",							982007912,		1,3,1,		"ertn-k",	"9,0æ 0,9æ 3,9æ 9,3æ 1,3æ 3,1æ 9,1 #luzern3,1æ 1,3æ 9,3æ 3,9æ 0,9æ 9,0æ",																"Valentin",		1466715992,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(23,"#jura",			"hoppus123","Jura",								982007912,		1,3,1,		"ertn-k",	"8,0% 0,8æ 7,8% 8,7% 4,7% 7,4% 5,4% 4,5% 1,5% 5,1% 8,1 #jura5,1% 1,5% 4,5% 5,4% 7,4% 4,7% 8,7% 7,8% 0,8% 8,0%",		"ventura",		1466715992,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(24,"#solothurn",		"hoppus123","Solothurn",						982007912,		1,3,1,		"ertn-k",	"12% 0,12%¸ 2,12`% 12,2%¸ 1,2% 2,1% 0,1 -= #solothurn =- 2,1`% 1,2%¸ 12,2`% 2,12%¸ 0,12`% 12,%-",										"CgIMaN",		1466715992,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(25,"#neuchatel",		"hoppus123","Neuchatel",						982007912,		1,3,1,		"ertn-k",	"8,0% 0,8æ 7,8% 8,7% 4,7% 7,4% 5,4% 4,5% 1,5% 5,1% 8,1 #neuchatel5,1% 1,5% 4,5% 5,4% 7,4% 4,7% 8,7% 7,8% 0,8% 8,0%",	"HG",			1466715992,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(26,"#appenzell",		"hoppus123","Appenzell",						982007912,		1,3,1,		"ertn-k",	"8,0% 0,8æ 7,8% 8,7% 4,7% 7,4% 5,4% 4,5% 1,5% 5,1% 8,1 #appenzell5,1% 1,5% 4,5% 5,4% 7,4% 4,7% 8,7% 7,8% 0,8% 8,0%",	"Valentin",		1466715992,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(27,"#teentalk",		"hoppus123","Teentalk",							982007912,		1,37,1,		"ertn-k",	"12% 0,12%¸ 2,12`% 12,2%¸ 1,2% 2,1% 0,1 -= #teentalk =- 2,1`% 1,2%¸ 12,2`% 2,12%¸ 0,12`% 12,%-",										"CgIMaN",		1466715992,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(28,"#kidstalk",		"hoppus123","Kidstalk",							982007912,		1,37,1,		"ertn-k",	"9,0æ 0,9æ 3,9æ 9,3æ 1,3æ 3,1æ 9,1 #kidstalk3,1æ 1,3æ 9,3æ 3,9æ 0,9æ 9,0æ",															"ventura",		982007912,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(29,"#reefmaster",		"hoppus123","Reefmaster Main Channel",			982007912,		1,37,1,		"ertn-k",	"12% 0,12%¸ 2,12`% 12,2%¸ 1,2% 2,1% 0,1 -= #reefmaster =- 2,1`% 1,2%¸ 12,2`% 2,12%¸ 0,12`% 12,%-",										"Fish-Guts",	1466715992,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(30,"#flirt20plus",		"hoppus123","flirt 20 plus",					982007912,		1,1,-1,		"ertn-k",	"12% 0,12%¸ 2,12`% 12,2%¸ 1,2% 2,1% 0,1 -= #flirt20plus =- 2,1`% 1,2%¸ 12,2`% 2,12%¸ 0,12`% 12,%-",									"FG",			1266712492,0,1,0,4,1,1,"www.reefmaster.ch",6);
INSERT INTO CHANS VALUES(31,"#flirt30plus",		"hoppus123","flirt 30 plus",					982007912,		1,1,-1,		"ertn-k",	"12% 0,12%¸ 2,12`% 12,2%¸ 1,2% 2,1% 0,1 -= #flirt30plus =- 2,1`% 1,2%¸ 12,2`% 2,12%¸ 0,12`% 12,%-",									"ventura",		1266715992,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(32,"#flirt40plus",		"hoppus123","flirt 40 plus",					982007912,		1,1,-1,		"ertn-k",	"12% 0,12%¸ 2,12`% 12,2%¸ 1,2% 2,1% 0,1 -= #flirt40plus =- 2,1`% 1,2%¸ 12,2`% 2,12%¸ 0,12`% 12,%-",									"V",			982007912,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(33,"#flirt50plus",		"hoppus123","flirt 50 plus",					982007912,		1,1,-1,		"ertn-k",	"12% 0,12%¸ 2,12`% 12,2%¸ 1,2% 2,1% 0,1 -= #flirt50plus =- 2,1`% 1,2%¸ 12,2`% 2,12%¸ 0,12`% 12,%-",									"mk",			1266712792,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(34,"#flirt60plus",		"hoppus123","flirt 60 plus",					982007912,		1,1,-1,		"ertn-k",	"12% 0,12%¸ 2,12`% 12,2%¸ 1,2% 2,1% 0,1 -= #flirt60plus =- 2,1`% 1,2%¸ 12,2`% 2,12%¸ 0,12`% 12,%-",									"Fish-Guts",	1366715992,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(35,"#linux",			"hoppus123","for Linux Fans",					982007912,		1,1,-1,		"ertn-k",	"9,0æ 0,9æ 3,9æ 9,3æ 1,3æ 3,1æ 9,1 #linux3,1æ 1,3æ 9,3æ 3,9æ 0,9æ 9,0æ",																"FG",			1266265992,0,1,0,4,1,1,"www.reefmaster.ch",3);
INSERT INTO CHANS VALUES(36,"#quiz",			"hoppus123","Quiz Channel",						982007912,		1,1,-1,		"ertn-k",	"12% 0,12%¸ 2,12`% 12,2%¸ 1,2% 2,1% 0,1 -= #quiz =- 2,1`% 1,2%¸ 12,2`% 2,12%¸ 0,12`% 12,%-",											"Fish-Guts",	1266715992,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(37,"#counter-strike",	"hoppus123","CS",								982007912,		1,1,-1,		"ertn-k",	"9,0æ 0,9æ 3,9æ 9,3æ 1,3æ 3,1æ 9,1 #counter-strike3,1æ 1,3æ 9,3æ 3,9æ 0,9æ 9,0æ",														"V",			1266715992,0,1,0,4,1,1,"www.reefmaster.ch",3);
INSERT INTO CHANS VALUES(38,"#menonly",			"hoppus123","Gay Channel",						982007912,		1,3,1,		"ertn-k",	"8,0% 0,8æ 7,8% 8,7% 4,7% 7,4% 5,4% 4,5% 1,5% 5,1% 8,1 #menonly5,1% 1,5% 4,5% 5,4% 7,4% 4,7% 8,7% 7,8% 0,8% 8,0%",	"Fish-Guts",	1366285992,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(39,"#punk",			"hoppus123","Punk Rock",						982007912,		1,3,1,		"ertn-k",	"8,0% 0,8æ 7,8% 8,7% 4,7% 7,4% 5,4% 4,5% 1,5% 5,1% 8,1 #punk5,1% 1,5% 4,5% 5,4% 7,4% 4,7% 8,7% 7,8% 0,8% 8,0%",		"ventura",		1266715992,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(40,"#rock",			"hoppus123","Rock",								982007912,		1,3,1,		"ertn-k",	"12% 0,12%¸ 2,12`% 12,2%¸ 1,2% 2,1% 0,1 -= #rock =- 2,1`% 1,2%¸ 12,2`% 2,12%¸ 0,12`% 12,%-",											"Fish-Guts",	1266715992,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(41,"#gabber",			"hoppus123","gabber-gandalf",					982007912,		1,3,1,		"ertn-k",	"12% 0,12%¸ 2,12`% 12,2%¸ 1,2% 2,1% 0,1 -= #gabber =- 2,1`% 1,2%¸ 12,2`% 2,12%¸ 0,12`% 12,%-",											"Fish-Guts",	1415474819,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(42,"#trance",			"hoppus123","trance",							982007912,		1,3,1,		"ertn-k",	"12% 0,12%¸ 2,12`% 12,2%¸ 1,2% 2,1% 0,1 -= #trance =- 2,1`% 1,2%¸ 12,2`% 2,12%¸ 0,12`% 12,%-",											"Neo",			1415474819,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(43,"#pop",				"hoppus123","pop",								982007912,		1,3,1,		"ertn-k",	"12% 0,12%¸ 2,12`% 12,2%¸ 1,2% 2,1% 0,1 -= #pop =- 2,1`% 1,2%¸ 12,2`% 2,12%¸ 0,12`% 12,%-",											"Neo",			1415284819,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(44,"#indie",			"hoppus123","indie",							982007912,		1,3,1,		"ertn-k",	"9,0æ 0,9æ 3,9æ 9,3æ 1,3æ 3,1æ 9,1 #indie3,1æ 1,3æ 9,3æ 3,9æ 0,9æ 9,0æ",																"Neo",			1415474819,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(45,"#hip-hop",			"hoppus123","Hip Hop",							982007912,		1,3,1,		"ertn-k",	"12% 0,12%¸ 2,12`% 12,2%¸ 1,2% 2,1% 0,1 -= #hip-hop =- 2,1`% 1,2%¸ 12,2`% 2,12%¸ 0,12`% 12,%-",										"Neo",			1415474819,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(46,"#dnb",				"hoppus123","Drum n Base",						982007912,		1,3,1,		"ertn-k",	"12% 0,12%¸ 2,12`% 12,2%¸ 1,2% 2,1% 0,1 -= #dnb =- 2,1`% 1,2%¸ 12,2`% 2,12%¸ 0,12`% 12,%-",											"Neo",			1415474819,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(47,"#fcb",				"hoppus123","FC Basel",							982007912,		1,3,1,		"ertn-k",	"12% 0,12%¸ 2,12`% 12,2%¸ 1,2% 2,1% 0,1 -= #fcb =- 2,1`% 1,2%¸ 12,2`% 2,12%¸ 0,12`% 12,%-",											"Fish-Guts",	1415354819,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(48,"#fca",				"hoppus123","FC Aarau",							982007912,		1,3,1,		"ertn-k",	"12% 0,12%¸ 2,12`% 12,2%¸ 1,2% 2,1% 0,1 -= #fca =- 2,1`% 1,2%¸ 12,2`% 2,12%¸ 0,12`% 12,%-",											"Fish-Guts",	1415474819,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(49,"#yb",				"hoppus123","Young Boys",						982007912,		1,3,1,		"ertn-k",	"9,0æ 0,9æ 3,9æ 9,3æ 1,3æ 3,1æ 9,1 #yb3,1æ 1,3æ 9,3æ 3,9æ 0,9æ 9,0æ",																	"Neo",			1415474819,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(50,"#gc",				"hoppus123","Grasshoppers",						982007912,		1,3,1,		"ertn-k",	"9,0æ 0,9æ 3,9æ 9,3æ 1,3æ 3,1æ 9,1 #gc3,1æ 1,3æ 9,3æ 3,9æ 0,9æ 9,0æ",																	"Neo",			1415284819,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(51,"#fcl",				"hoppus123","FC Luzern",						982007912,		1,3,1,		"ertn-k",	"9,0æ 0,9æ 3,9æ 9,3æ 1,3æ 3,1æ 9,1 #fcl3,1æ 1,3æ 9,3æ 3,9æ 0,9æ 9,0æ",																	"Fish-Guts",	1415474819,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(52,"#fcz",				"hoppus123","FC Zürich",						982007912,		1,3,1,		"ertn-k",	"12% 0,12%¸ 2,12`% 12,2%¸ 1,2% 2,1% 0,1 -= #fcz =- 2,1`% 1,2%¸ 12,2`% 2,12%¸ 0,12`% 12,%-",											"Neo",			1415473619,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(53,"#evz",				"hoppus123","EV Zug",							982007912,		1,3,1,		"ertn-k",	"12% 0,12%¸ 2,12`% 12,2%¸ 1,2% 2,1% 0,1 -= #evz =- 2,1`% 1,2%¸ 12,2`% 2,12%¸ 0,12`% 12,%-",											"Neo",			1415474819,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(54,"#zsc",				"hoppus123","ZSC Lions",						982007912,		1,3,1,		"ertn-k",	"9,0æ 0,9æ 3,9æ 9,3æ 1,3æ 3,1æ 9,1 #zsc3,1æ 1,3æ 9,3æ 3,9æ 0,9æ 9,0æ",																	"Neo",			1415474819,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(55,"#flyers",			"hoppus123","Kloten Flyers",					982007912,		1,3,1,		"ertn-k",	"12% 0,12%¸ 2,12`% 12,2%¸ 1,2% 2,1% 0,1 -= #flyers =- 2,1`% 1,2%¸ 12,2`% 2,12%¸ 0,12`% 12,%-",											"Fish-Guts",	1414474819,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(56,"#hcap",			"hoppus123","Ambri-Piotta",						982007912,		1,3,1,		"ertn-k",	"9,0æ 0,9æ 3,9æ 9,3æ 1,3æ 3,1æ 9,1 #hcap3,1æ 1,3æ 9,3æ 3,9æ 0,9æ 9,0æ",																"Neo",			1415474819,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(57,"#hcl",				"hoppus123","HC Lugano",						982007912,		1,3,1,		"ertn-k",	"9,0æ 0,9æ 3,9æ 9,3æ 1,3æ 3,1æ 9,1 #hcl3,1æ 1,3æ 9,3æ 3,9æ 0,9æ 9,0æ",																	"Fish-Guts",	1415444819,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(58,"#hcd",				"hoppus123","HC Davos",							982007912,		1,3,1,		"ertn-k",	"7,4% 0,4% 4,4 5,4% 4,5% 5,5 1,5% 5,1% 1,1 15,1 #hcd 5,1% 1,5% 5,5 4,5% 5,4% 4,4 1,4% 7,4%",								"Fish-Guts",	1415464819,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(59,"#scl-tigers",		"hoppus123","Langnau",							982007912,		1,3,1,		"ertn-k",	"7,4% 0,4% 4,4 5,4% 4,5% 5,5 1,5% 5,1% 1,1 15,1 #scl-tiger 5,1% 1,5% 5,5 4,5% 5,4% 4,4 1,4% 7,4%",							"Neo",			1415424819,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(60,"#lakers",			"hoppus123","Rapperswil-Jona Lakers",			982007912,		1,3,1,		"ertn-k",	"7,4% 0,4% 4,4 5,4% 4,5% 5,5 1,5% 5,1% 1,1 15,1 #lkaers 5,1% 1,5% 5,5 4,5% 5,4% 4,4 1,4% 7,4%",								"Neo",			1415474819,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(61,"#tservice",		"hoppus123","Teentalk Operator Service",		982007912,		1,1,3,		"ertn-k",	"9,0æ 0,9æ 3,9æ 9,3æ 1,3æ 3,1æ 9,1 #tservice,1æ 1,3æ 9,3æ 3,9æ 0,9æ 9,0æ",																"Fish-Guts",	1382007912,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(62,"#mservice",		"hoppus123","Music Operator Service",			982007912,		1,1,3,		"ertn-k",	"9,0æ 0,9æ 3,9æ 9,3æ 1,3æ 3,1æ 9,1 #mservice,1æ 1,3æ 9,3æ 3,9æ 0,9æ 9,0æ",																"Fish-Guts",	1382007912,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(63,"#help",			"hoppus123","Chat Help Channel",				982007912,		1,1,3,		"ertn-k",	"9,0æ 0,9æ 3,9æ 9,3æ 1,3æ 3,1æ 9,1 #help,1æ 1,3æ 9,3æ 3,9æ 0,9æ 9,0æ",																	"Fish-Guts",	1382007912,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(64,"#ladiesonly",		"hoppus123","Ladies only",						982007912,		1,1,3,		"ertn-k",	"9,0æ 0,9æ 3,9æ 9,3æ 1,3æ 3,1æ 9,1 #ladiesonly,1æ 1,3æ 9,3æ 3,9æ 0,9æ 9,0æ",																"Fish-Guts",	1382007912,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(65,"#fcsion",			"hoppus123","FC Sion",							982007912,		1,1,3,		"ertn-k",	"9,0æ 0,9æ 3,9æ 9,3æ 1,3æ 3,1æ 9,1 #fcsion,1æ 1,3æ 9,3æ 3,9æ 0,9æ 9,0æ",																	"Fish-Guts",	1382007912,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(66,"#mIRC-Info",		"hoppus123","Mirc Info",						982007912,		1,1,3,		"ertn-k",	"9,0æ 0,9æ 3,9æ 9,3æ 1,3æ 3,1æ 9,1 #mirc-info,1æ 1,3æ 9,3æ 3,9æ 0,9æ 9,0æ",																"Fish-Guts",	1382007912,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(67,"#kurdchat",		"hoppus123","Kurd Chat",						982007912,		1,1,3,		"ertn-k",	"9,0æ 0,9æ 3,9æ 9,3æ 1,3æ 3,1æ 9,1 #kurdchat,1æ 1,3æ 9,3æ 3,9æ 0,9æ 9,0æ",																"Fish-Guts",	1382007912,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(68,"#albachat",		"hoppus123","Albanien-Chat",					982007912,		1,1,3,		"ertn-k",	"9,0æ 0,9æ 3,9æ 9,3æ 1,3æ 3,1æ 9,1 #albachat,1æ 1,3æ 9,3æ 3,9æ 0,9æ 9,0æ",																"Fish-Guts",	1382007912,0,1,0,4,1,1,"www.reefmaster.ch",5);
INSERT INTO CHANS VALUES(69,"#winterthur",		"hoppus123","Winterthur",						982007912,		1,1,3,		"ertn-k",	"9,0æ 0,9æ 3,9æ 9,3æ 1,3æ 3,1æ 9,1 #winterthur,1æ 1,3æ 9,3æ 3,9æ 0,9æ 9,0æ",																"Fish-Guts",	1382007912,0,1,0,4,1,1,"www.reefmaster.ch",5);

-- Level 1 Uop 2 Vop 3 Hop 4 Aop 5 Sop 6 Cop 7 Qop 8 Successor 9 Founder
-- Added additionally 10 Full Founder, 11 ServiceRootAdmin
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
-- #ircops
-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,1,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,1,"Fish-Guts",11,1415474819);
-- Qop
-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,10,1,"Fish-Guts",11,1415174819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,11,1,"Fish-Guts",11,1415374819);
-- Sop
-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,1,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,1,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,1,"Snox",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,1,"FG",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,1,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,57,1,"Fish-Guts",11,1466718240);

-- #cservice
-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,2,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,2,"Fish-Guts",11,1415474819);
-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,10,2,"Fish-Guts",11,1415174819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,11,2,"Fish-Guts",11,1415374819);
-- Sop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (5,15,2,"Jamc",6,1415474819);
-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,2,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,2,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,2,"waterlily",5,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,2,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,2,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,57,2,"Fish-Guts",11,1466718240);

-- #schaffhausen
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
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
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,3,"Fish-Guts",11,1415429819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,3,"Fish-Guts",11,1415415819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,3,"Fish-Guts",11,1415424819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,3,"Fish-Guts",11,14154344819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,29,3,"moebius",5,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,52,3,"moebius",5,1415474819);

-- #zurich
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
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
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,24,4,"Fish-Guts",11,1285474819);

-- #basel
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
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
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,57,5,"Fish-Guts",11,1466718240);

-- #zug
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
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
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,57,6,"Fish-Guts",11,1466718240);

-- #thurgau
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
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
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,57,7,"Fish-Guts",11,1466718240);

-- #stgallen
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
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
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,57,8,"Fish-Guts",11,1466718240);

-- #aargau
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
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
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,57,9,"Fish-Guts",11,1466718240);

-- #bern
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
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
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,57,10,"Fish-Guts",11,1466718240);

-- #wallis
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
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
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,57,11,"Fish-Guts",11,1466718240);

-- #vaud
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
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
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,57,12,"Fish-Guts",11,1466718240);

-- #glarus
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
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
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,57,13,"Fish-Guts",11,1466718240);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,57,13,"Fish-Guts",11,1466718240);

-- #schwyz
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
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
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,57,14,"Fish-Guts",11,1466718240);
-- #graubuenden
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
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
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,57,15,"Fish-Guts",11,1466718240);

-- #ticino
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
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
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,57,16,"Fish-Guts",11,1466718240);

-- #uri
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
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
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,57,17,"Fish-Guts",11,1466718240);

-- #obwalden
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
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
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,57,18,"Fish-Guts",11,1466718240);

-- #nidwalden
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
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
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,57,19,"Fish-Guts",11,1466718240);

-- #genf
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
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
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,57,20,"Fish-Guts",11,1466718240);

-- #fribourg
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
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
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,57,21,"Fish-Guts",11,1466718240);

-- #luzern
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
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
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,57,22,"Fish-Guts",11,1466718240);

-- #jura
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
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
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,57,23,"Fish-Guts",11,1466718240);

-- #solothurn
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
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
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,57,24,"Fish-Guts",11,1466718240);

-- #neuchatel
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
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
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,57,25,"Fish-Guts",11,1466718240);

-- #appenzell
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
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
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
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
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,57,27,"Fish-Guts",11,1466718240);

-- #kidstalk
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
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
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,57,28,"Fish-Guts",11,1466718240);

-- #reefmaster
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
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
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
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
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
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
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
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
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
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
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
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
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
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
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
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
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
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
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,57,37,"Fish-Guts",11,1466718240);

-- #menonly
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
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
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,57,38,"Fish-Guts",11,1466718240);

-- #punk
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,39,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,39,"Fish-Guts",11,1415474819);
-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,15,39,"Fish-Guts",11,1415474819);
-- Sop
-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,39,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,39,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,39,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,39,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,39,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,39,"Fish-Guts",11,1415174819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,39,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,57,39,"Fish-Guts",11,1466718240);

-- #rock
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,40,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,40,"Fish-Guts",11,1415474819);
-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,15,40,"Fish-Guts",11,1415474819);
-- Sop
-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,40,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,40,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,40,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,40,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,40,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,40,"Fish-Guts",11,1415174819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,40,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,57,40,"Fish-Guts",11,1466718240);

-- #gabber
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,41,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,41,"Fish-Guts",11,1415474819);
-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,15,41,"Fish-Guts",11,1415474819);
-- Sop
-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,41,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,41,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,41,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,41,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,41,"FG",7,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,41,"Fish-Guts",11,1415174819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,41,"Fish-Guts",11,1415474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,57,41,"Fish-Guts",11,1466718240);

-- #trance
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,42,"Fish-Guts",11,1425474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,42,"Fish-Guts",11,1425474819);
-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,15,42,"Fish-Guts",11,1425474819);
-- Sop
-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,42,"Fish-Guts",11,1425474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,42,"Fish-Guts",11,1425474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,42,"Fish-Guts",11,1425474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,42,"Fish-Guts",11,1425474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,42,"FG",7,1425474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,42,"Fish-Guts",11,1425174819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,42,"Fish-Guts",11,1425474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,57,42,"Fish-Guts",11,1466718240);

-- #pop
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,43,"Fish-Guts",11,1435474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,43,"Fish-Guts",11,1435474819);
-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,15,43,"Fish-Guts",11,1435474819);
-- Sop
-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,43,"Fish-Guts",11,1435474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,43,"Fish-Guts",11,1435474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,43,"Fish-Guts",11,1435474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,43,"Fish-Guts",11,1435474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,43,"FG",7,1435474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,43,"Fish-Guts",11,1435174819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,43,"Fish-Guts",11,1435474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,57,43,"Fish-Guts",11,1466718240);

-- #indie
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,44,"Fish-Guts",11,1445474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,44,"Fish-Guts",11,1445474819);
-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,15,44,"Fish-Guts",11,1445474819);
-- Sop
-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,44,"Fish-Guts",11,1445474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,44,"Fish-Guts",11,1445474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,44,"Fish-Guts",11,1445474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,44,"Fish-Guts",11,1445474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,44,"FG",7,1445474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,44,"Fish-Guts",11,1445174819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,44,"Fish-Guts",11,1445474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,57,44,"Fish-Guts",11,1466718240);

-- #hip-hop
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,45,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,45,"Fish-Guts",11,1455474819);
-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,15,45,"Fish-Guts",11,1455474819);
-- Sop
-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,45,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,45,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,45,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,45,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,45,"FG",7,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,45,"Fish-Guts",11,1455174819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,45,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,57,45,"Fish-Guts",11,1466718240);

-- #dnb
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,46,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,46,"Fish-Guts",11,1455474819);
-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,15,46,"Fish-Guts",11,1455474819);
-- Sop
-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,46,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,46,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,46,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,46,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,46,"FG",7,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,46,"Fish-Guts",11,1455174819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,46,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,57,46,"Fish-Guts",11,1466718240);

-- #fcb
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,47,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,47,"Fish-Guts",11,1455474819);
-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,57,47,"Fish-Guts",11,1466718240);
-- Sop
-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,47,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,47,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,47,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,47,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,47,"FG",7,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,47,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,47,"Fish-Guts",11,1455174819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,47,"Fish-Guts",11,1455474819);

-- #fca
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,48,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,48,"Fish-Guts",11,1455474819);
-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,57,48,"Fish-Guts",11,1466718240);
-- Sop
-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,48,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,48,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,48,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,48,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,48,"FG",7,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,48,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,48,"Fish-Guts",11,1455174819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,48,"Fish-Guts",11,1455474819);

-- #yb
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,49,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,49,"Fish-Guts",11,1455474819);
-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,57,49,"Fish-Guts",11,1466718240);
-- Sop
-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,49,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,49,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,49,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,49,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,49,"FG",7,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,49,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,49,"Fish-Guts",11,1455174819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,49,"Fish-Guts",11,1455474819);

-- #gc
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,50,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,50,"Fish-Guts",11,1455474819);
-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,57,50,"Fish-Guts",11,1466718240);
-- Sop
-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,50,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,50,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,50,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,50,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,50,"FG",7,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,50,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,50,"Fish-Guts",11,1455174819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,50,"Fish-Guts",11,1455474819);

-- #fcl
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,51,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,51,"Fish-Guts",11,1455474819);
-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,57,51,"Fish-Guts",11,1466718240);
-- Sop
-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,51,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,51,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,51,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,51,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,51,"FG",7,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,51,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,51,"Fish-Guts",11,1455174819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,51,"Fish-Guts",11,1455474819);

-- #fcz
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,52,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,52,"Fish-Guts",11,1455474819);
-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,57,52,"Fish-Guts",11,1466718240);
-- Sop
-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,52,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,52,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,52,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,52,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,52,"FG",7,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,52,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,52,"Fish-Guts",11,1455174819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,52,"Fish-Guts",11,1455474819);

-- #evz
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,53,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,53,"Fish-Guts",11,1455474819);
-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,57,53,"Fish-Guts",11,1466718240);
-- Sop
-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,53,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,53,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,53,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,53,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,53,"FG",7,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,53,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,53,"Fish-Guts",11,1455174819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,53,"Fish-Guts",11,1455474819);

-- #zsc
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,54,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,54,"Fish-Guts",11,1455474819);
-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,57,54,"Fish-Guts",11,1466718240);
-- Sop

-- Ao
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,54,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,54,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,54,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,54,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,54,"FG",7,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,54,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,54,"Fish-Guts",11,1455174819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,54,"Fish-Guts",11,1455474819);

-- #flyers
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,55,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,55,"Fish-Guts",11,1455474819);
-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,57,55,"Fish-Guts",11,1466718240);
-- Sop
-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,55,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,55,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,55,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,55,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,55,"FG",7,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,55,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,55,"Fish-Guts",11,1455174819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,55,"Fish-Guts",11,1455474819);

-- #hcap
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,56,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,56,"Fish-Guts",11,1455474819);
-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,57,56,"Fish-Guts",11,1466718240);
-- Sop
-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,56,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,56,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,56,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,56,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,56,"FG",7,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,56,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,56,"Fish-Guts",11,1455174819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,56,"Fish-Guts",11,1455474819);

-- #hcap
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,57,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,57,"Fish-Guts",11,1455474819);
-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,57,57,"Fish-Guts",11,1466718240);
-- Sop
-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,57,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,57,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,57,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,57,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,57,"FG",7,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,57,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,57,"Fish-Guts",11,1455174819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,57,"Fish-Guts",11,1455474819);

-- #hcd
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,58,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,58,"Fish-Guts",11,1455474819);
-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,57,58,"Fish-Guts",11,1466718240);
-- Sop
-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,58,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,58,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,58,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,58,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,58,"FG",7,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,58,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,58,"Fish-Guts",11,1455174819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,58,"Fish-Guts",11,1455474819);

-- #scl-tigers
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,59,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,59,"Fish-Guts",11,1455474819);
-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,57,59,"Fish-Guts",11,1466718240);
-- Sop
-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,59,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,59,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,59,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,59,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,59,"FG",7,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,59,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,59,"Fish-Guts",11,1455174819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,59,"Fish-Guts",11,1455474819);

-- #lakers
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,60,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,60,"Fish-Guts",11,1455474819);
-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,57,60,"Fish-Guts",11,1466718240);
-- Sop
-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,60,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,60,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,60,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,60,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,60,"FG",7,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,60,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,60,"Fish-Guts",11,1455174819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,60,"Fish-Guts",11,1455474819);

-- #tservice
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,61,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,61,"Fish-Guts",11,1455474819);
-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,11,61,"Fish-Guts",11,1455474819);
-- Sop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (5,57,61,"Fish-Guts",11,1466718240);
-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,61,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,61,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,61,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,61,"FG",7,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,61,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,61,"Fish-Guts",11,1455174819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,61,"Fish-Guts",11,1455474819);

-- #mservice
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,62,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,62,"Fish-Guts",11,1455474819);
-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,11,62,"Fish-Guts",11,1455474819);
-- Sop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (5,57,62,"Fish-Guts",11,1466718240);
-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,62,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,62,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,62,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,62,"FG",7,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,62,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,62,"Fish-Guts",11,1455174819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,62,"Fish-Guts",11,1455474819);

-- #mservice
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,63,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,63,"Fish-Guts",11,1455474819);
-- Qop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (7,57,63,"Fish-Guts",11,1466718240);
-- Cop
-- Sop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (5,11,63,"Fish-Guts",11,1455474819);
-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,63,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,63,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,63,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,63,"FG",7,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,63,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,63,"Fish-Guts",11,1455174819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,63,"Fish-Guts",11,1455474819);

-- #ladiesonly
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,64,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,64,"Fish-Guts",11,1455474819);
-- Qop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (7,57,64,"Fish-Guts",11,1466718240);
-- Cop
-- Sop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (5,11,64,"Fish-Guts",11,1455474819);
-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,64,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,64,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,64,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,64,"FG",7,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,64,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,64,"Fish-Guts",11,1455174819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,64,"Fish-Guts",11,1455474819);

-- #hcd
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,65,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,65,"Fish-Guts",11,1455474819);
-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,57,65,"Fish-Guts",11,1466718240);
-- Sop
-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,65,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,65,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,65,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,65,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,65,"FG",7,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,65,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,65,"Fish-Guts",11,1455174819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,65,"Fish-Guts",11,1455474819);

-- #mIRC-Info
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,66,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,66,"Fish-Guts",11,1455474819);
-- Cop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (6,57,66,"Fish-Guts",11,1466718240);
-- Sop
-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,66,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,66,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,66,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,66,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,66,"FG",7,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,66,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,66,"Fish-Guts",11,1455174819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,66,"Fish-Guts",11,1455474819);

-- #kurdchat
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,67,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,67,"Fish-Guts",11,1455474819);
-- Cop
-- Sop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (5,57,67,"Fish-Guts",11,1466718240);
-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,67,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,67,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,67,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,67,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,67,"FG",7,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,67,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,67,"Fish-Guts",11,1455174819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,67,"Fish-Guts",11,1455474819);

-- #albachat
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,68,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,68,"Fish-Guts",11,1455474819);
-- Cop
-- Sop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (5,57,68,"Fish-Guts",11,1466718240);
-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,68,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,68,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,68,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,68,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,68,"FG",7,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,68,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,68,"Fish-Guts",11,1455174819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,68,"Fish-Guts",11,1455474819);

-- #winterthur
-- ircops are: jamc(10), cgiman(11), red-dog(12), V(13), delfin(14), waterlily(15), yj(16), neo(17), moebius(57)
-- Founder / Successor
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (9,1,69,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (8,2,69,"Fish-Guts",11,1455474819);
-- Cop
-- Sop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (5,57,69,"Fish-Guts",11,1466718240);
-- Aop
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,10,69,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,11,69,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,12,69,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,13,69,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,14,69,"FG",7,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,15,69,"Fish-Guts",11,1455474819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,16,69,"Fish-Guts",11,1455174819);
INSERT INTO OP_LIST (TYPE,NICK,CHAN,ADDED_BY,ADDED_BY_ACC,ADDED_ON) VALUES (4,17,69,"Fish-Guts",11,1455474819);


INSERT INTO NS_ACCESS(NICK_ID,MASK) VALUES (1,"fish-guts@*");
INSERT INTO NS_ACCESS(NICK_ID,MASK) VALUES (1,"FG@*");
INSERT INTO NS_ACCESS(NICK_ID,MASK) VALUES (1,"pennywise@*");
INSERT INTO NS_ACCESS(NICK_ID,MASK) VALUES (2,"FG@*");
INSERT INTO NS_ACCESS(NICK_ID,MASK) VALUES (4,"test1@*");
INSERT INTO NS_ACCESS(NICK_ID,MASK) VALUES (5,"test2@*");
INSERT INTO NS_ACCESS(NICK_ID,MASK) VALUES (6,"test3@*");
INSERT INTO NS_ACCESS(NICK_ID,MASK) VALUES (7,"test4@*");
INSERT INTO NS_ACCESS(NICK_ID,MASK) VALUES (8,"test4@*");
INSERT INTO NS_ACCESS(NICK_ID,MASK) VALUES (9,"test4@*");
INSERT INTO NS_ACCESS(NICK_ID,MASK) VALUES (10,"test4@*");

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

INSERT INTO AKILL (HOST,EXPIRY,ADDED_BY,REASON) VALUES('bill@gates',1414674819,'Fish-Guts','No bouncers. FG');
