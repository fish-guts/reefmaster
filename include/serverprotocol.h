/*
 * serverprotocol.h
 *
 *  Created on: Dec 15, 2014
 *      Author: severin
 */

#ifndef SERVERPROTOCOL_H_
#define SERVERPROTOCOL_H_



#endif /* SERVERPROTOCOL_H_ */

#define CHANMODE	":%s MODE %s %s %s %ld\r\n"
#define CHATOPS		":%s CHATOPS : %s\r\n"
#define JOIN		":%s JOIN %s\r\n"
#define KILL		":%s KILL %s :%s!%s %s\r\n"
#define SNICK		"& %s 1 0 %s %s %s 0 +qdS * :%s\r\n"
#define NOTICE		":%s NOTICE %s :%s\r\n"
#define PRIVMSG		":%s PRIVMSG %s :%s\r\n"
#define PART		":%s PART %s :%s\r\n"
#define PONG		"PONG %s :%s\r\n"
#define QUIT		":%s QUIT :Quit: Leaving\r\n"
#define SVS2MODE	":%s SVS2MODE %s %s %s\r\n"
#define SVS2UMODE	":%s SVS2MODE %s %s\r\n"
#define SVSNICK		"SVSNICK %s %s :%lu\r\n"
#define SVSMODE		":%s SVSMODE %s %s %s\r\n"
#define SVSUMODE	":%s SVSMODE %s %s\r\n"
#define TOPIC		":%s ) %s %s %ld :%s\r\n"
#define USERMODE	":%s MODE %s %s\r\n"
#define WALLOPS		":%s WALLOPS :%s\r\n"
#define XLINE		"BD + %c %s %s %s %ld %ld :%s\r\n"
#define RXLINE		"BD - %c %s %s %s\r\n"
#define ZLINE		"BD + Z %s %s %ld %ld :%s\r\n"

