#ifndef MESSAGES_H_
#define MESSAGES_H_


/* These are the default program messages
 * 
 * Format:
 * 
 * SECTION_<RPL|ERR|DBG>_MSG
 * 
 * Example:
 * 
 * NS_RPL_TESTMSG 
 * CS_ERR_NOSUCHROOM
 * LOG_DBG_LOGMSG
 */

/* General messages
 ******************************************************************************************************************************************
 */


#define FAIL  "\x1b[32;1mfailed\x1b[0m \n"
#define OK	  "\x1b[32;2mok\x1b[0m \n"

/* color definition */
#define KNRM  "\x1B[0m;"
#define KRED  "\x1b[31;1m"
#define KGRN  "\x1b[32;1m"
#define KYEL  "\x1b[33;1m"
#define KBLU  "\x1b[34;1m"
#define KMAG  "\x1b[35;1m"
#define KCYN  "\x1b[36;1m"
#define KWHT  "\x1b[37;1m"
#define KDEF  "\x1b[0m"

/* time format for regular expressions */
#define TIME_FORMAT_H "[[:digit:]]+h"
#define TIME_FORMAT_M "[[:digit:]]+m"
#define TIME_FORMAT_W "[[:digit:]]+w"
#define TIME_FORMAT_D "[[:digit:]]+d"
#define TIME_FORMAT_Y "[[:digit:]]+y"

/* minutes for date calculation */
#define MINUTES_PER_HOUR 60
#define MINUTES_PER_DAY 1440
#define MINUTES_PER_WEEK 10080
#define MINUTES_PER_MONTH 43200
#define MINUTES_PER_YEAR 525948

/* Adminserv messages
 ******************************************************************************************************************************************
 */

#define AS_ERR_CHAN_USAGE "Usage: \2CHANNEL [ADD|DEL|LIST|SET] <Channel>"


/* Main messages
 ******************************************************************************************************************************************
 */

#define APP_DBG_CONNECTINGCLIENT	"*** Connecting \x1b[35;1m%s\x1b[0m..."
#define APP_DBG_CONNECTINGTOSERVER	"*** Connecting to \x1b[35;1m%s\x1b[0m..."
#define APP_ERR_CONNECTIONERROR		"*** Error: Could not connect to %s\n"
#define APP_DBG_REGISTERINGSRV		"*** Registering services with \x1b[35;1m%s\x1b[0m..."
#define APP_ERR_REGISTERINGERROR	"*** Error: could not register services with %s\n"
#define APP_DBG_STARTED				"Services successfully started"
#define APP_DBG_UNKNOWN_CMD			"Valid commands are ./services [start|stop|restart].\n"
#define APP_ERR_SOCKET				"*** Error: Socket error. Please restart services\n"
#define APP_ERR_UNKNOWNMSG			"Unknown message from server: %s\n"
#define APP_ERR_OUTOFMEMORY 		"*** Error: Out of memory! Please restart the application.\n"
#define APP_ERR_LOADINGFAILED 		"*** Error: Loading Application failed (%i)\n" 
#define APP_DBG_WAITINGFORSRV		"*** Waiting for server response...\n"

#define S_QUIT						"Service are shutting down.... See you soon"

/* Configuration messages
 ******************************************************************************************************************************************
 */

#define CONF_ERR_INT				"*** Error %s:%i: Value in option '%s' must be between %i and %i.\n"
#define CONF_ERR_FILENOTFOUND 		"*** Error: Configuration file not found\n"
#define CONF_ERR_MISSINGOPT			"*** Error %s:%i: Option '%s' is missing.\n"
#define CONF_ERR_MUSTBEBOOL			"*** Error %s:%i: Value in option '%s' must be 0 or 1.\n"
#define CONF_ERR_NEGVALUEFOUND		"*** Error %s:%i: Option '%s' must not have a negative value.\n"
#define CONF_ERR_PORTOUTOFRANGE		"*** Error %s:%i: Port out of range in option '%s'."
#define CONF_ERR_TOOMANYCHARS		"*** Error %s:%i: Option '%s' must not need exceed %i characters.\n"
#define CONF_ERR_XOP_TOO_HIGH		"*** ERROR %s:%i: Value in option '%s' cannot be higher than the value of %s"
#define CONF_LOG_ERR_FILENOT		"[CONFIG] Configuration file not found\n"
#define CONF_LOG_ERR_INT			"[CONFIG] %s:%i: Value in option '%s' must be between %i and %i.\n"
#define CONF_LOG_ERR_MISSINGOPT		"[CONFIG] %s:%i: Option '%s' is missing.\n"
#define CONF_LOG_ERR_NEGVALUEFOUND	"[CONFIG] %s:%i: Option '%s' must not have a negative value.\n"
#define CONF_LOG_ERR_PORTOUTOFRANGE	"[CONFIG] %s:%i: Port out of range in option '%s'."
#define CONF_LOG_ERR_MUSTBEBOOL		"[CONFIG] %s:%i: Value in option '%s' must be 0 or 1.\n"
#define CONF_LOG_ERR_TOOMANYCHARS	"[CONFIG] %s:%i: Option '%s' must not need exceed %i characters.\n"
#define CONG_MSG_QOP_SECTION		"the 'Qop' section\n\n"
#define CONG_MSG_COP_SECTION		"the 'Cop' section\n\n"
#define CONG_MSG_AOP_SECTION		"the 'Aop' section\n\n"
#define CONG_MSG_HOP_SECTION		"the 'Hop' section\n\n"
#define CONG_MSG_SOP_SECTION		"the 'Sop' section\n\n"
#define CONG_MSG_VOP_SECTION		"the 'Vop' section\n\n"

/*
 * Adminserv messages
 ******************************************************************************************************************************************
 */

#define AS_ERR_ACCESS_DENIED		"Access denied to that function of \2%s\2. You need \2%s\2 or higher access"
/*
 * Nickserv messages
 ******************************************************************************************************************************************
 */

/* General
 ******************************************************************************************************************************************
 */

#define NS_ERR_ACCESSDENIED			"Access denied for this function for the nickname \2%s\2."
#define NS_ERR_HLP_USAGE			"/msg %s \2HELP\2 <Command> <Subcommand>"
#define NS_ERR_NEEDMOREPRIVS		"Permission denied - You don't have the required privileges."
#define NS_ERR_NOSUCHCMD			"Unknown command: \2%s\2."
#define NS_ERR_NOSUCHUSER			"No such user online: \"%s\"."
#define NS_ERR_NOTREG				"The nickname \2%s\2 is not registered."
#define NS_ERR_TOOMANYPASS			"Too many wrong passwords. Please try again later."
#define NS_RPL_HLP					"For more help, type /msg %s \2HELP %s %s\2."
#define NS_RPL_HLP_SHORT			"For more help, type /msg %s \2HELP %s\2."
#define NS_RPL_HLP_MAIN				"For help on commands, type /msg %s \2HELP\2."
#define NS_RPL_LISTFOUND1			"Listing Complete - \2%i\2 entry found."
#define NS_RPL_LISTFOUND2			"Listing Complete - \2%i\2 entries found."
#define NS_RPL_NEEDIDENTIFY			"Please identify for the nickname \2%s\2 to use this function."
#define NS_RPL_PLZ_IDENTIFY0		"This nickname belongs to someone else"
#define NS_RPL_PLZ_IDENTIFY1		"If this is your nickname, please identify using /%s IDENTIFY <password>"
#define NS_RPL_PLZ_IDENTIFY2		"You have\2 60 Seconds\2 to identify before your nickname is changed"
#define NS_RPL_PLZ_IDENTIFY3		"This nickname has the 'aggressive proction' enabled."
#define NS_RPL_PLZ_IDENTIFY4		"You won't be able to use the nickname unless you identify using /%s IDENTIFY <password>"
#define NS_RPL_PLZ_30SECSLEFT		"You have\2 30 Seconds\2 left to identify before your nickname is changed"
#define NS_RPL_PLZ_NOTIMELEFT		"Time's up. Your nickname is now being changed. If this is your nickname, please identify."
#define NS_LOG_NICK_DROPPED			"Nick %s has expired and is now being dropped"

/* Access
 ******************************************************************************************************************************************
 */

#define NS_ACCESS_ERR_MASKEXISTS		"The mask \2%s\2 already is in your access list."
#define NS_ACCESS_ERR_MASKEXISTS2		"The mask \2%s\2 already is in the access list of \2%s\2."
#define NS_ACCESS_ERR_MASKFORMAT		"Mask must be in format <user@host>"
#define NS_ACCESS_ERR_MASKFORMAT2		"Please use a more secure mask. \2%s\2 matches all users"
#define NS_ACCESS_ERR_MASKNOTFOUND		"The mask \2%s\2 was not found in your access list"
#define NS_ACCESS_ERR_MASKNOTFOUND2		"The mask \2%s\2 was not found in the access list of \2%s\2"
#define NS_ACCESS_ERR_USAGE				"Usage: \2ACCESS\2 <command> [arguments]"
#define NS_ACCESS_RPL_1ENTRYREMOVED		"1 entry removed."
#define NS_ACCESS_RPL_ADDSUCCESS		"The mask \2%s\2 has been added to your access list."
#define NS_ACCESS_RPL_ADDSUCCESS2		"The mask \2%s\2 has been added to the access list of \2%s\2."
#define NS_ACCESS_RPL_DELSUCCESS		"The mask \2%s\2 has been deleted from your access list."
#define NS_ACCESS_RPL_DELSUCCESS2		"The mask \2%s\2 has been deleted from the access list of \2%s\2."
#define NS_ACCESS_RPL_LEVEL0			"%s - 0 - No Access."
#define NS_ACCESS_RPL_LEVEL1			"%s - 1 - Matches an entry in the nickname's access list."
#define NS_ACCESS_RPL_LEVEL2			"%s - 2 - User has identified for this nickname."  
#define NS_ACCESS_RPL_LIST				"The nickname \2%s\2 has the following access entries:"
#define NS_ACCESS_RPL_LISTFOUND1		"Listing Complete - \2%i\2 entry found"
#define NS_ACCESS_RPL_LISTFOUND2		"Listing Complete - \2%i\2 entries found"
#define NS_ACCESS_RPL_NENTRIESREMOVED	"%i entries removed."
#define NS_ACCESS_RPL_NOENTRIES			"You don't have any access list entries."
#define NS_ACCESS_RPL_NOENTRIES2		"The nickname \2%s\2 doesn't have any access list entries."
#define NS_ACCESS_RPL_LISTENTRIES		"\2%i\2 - \2%s\2"
#define NS_ACCESS_RPL_WIPESUCCESS		"Your access list has been wiped."
#define NS_ACCESS_RPL_WIPESUCCESS2		"The access list of \2%s\2 has been wiped."

/* AUTH
 ******************************************************************************************************************************************
 */

#define NS_AUTH_ERR_LISTUSAGE		"Usage: \2AUTH LIST\2."
#define NS_AUTH_ERR_ISNONUM			"The supplied value is not a number."
#define NS_AUTH_ERR_NUMTOOBIG		"No authorization request with number %i found."
#define NS_AUTH_ERR_ACCEPTUSAGE		"Usage: \2AUTH ACCEPT\2 <number>."
#define NS_AUTH_ERR_DECLINEUSAGE	"Usage: \2AUTH DECLINE\2 <number>."
#define NS_AUTH_ERR_READUSAGE		"Usage: \2AUTH READ\2 <number>."
#define NS_AUTH_ERR_LISTCOMPLETE1	"Listing complete -\2 1 \2match found"
#define NS_AUTH_ERR_LISTCOMPLETE2	"Listing complete - \2%i\2 matches found"
#define NS_AUTH_ERR_USAGE			"Usage: \2AUTH <ACCEPT|DECLINE|READ|LIST> [#]."
#define NS_AUTH_RPL_ACCEPTED		"You have accepted the authorization request No \2%i\2."
#define NS_AUTH_RPL_ALREADYINLIST	"You already sent such a request to \2%s\2."
#define NS_AUTH_RPL_DECLINED		"You have declined the authorization request No \2%i\2."
#define NS_AUTH_RPL_HASACCEPTED_NFY	"\2%s\2 has accepted your request to add them to your notify list"
#define NS_AUTH_RPL_HASACCEPTED_CHN	"\2%s\2 has accepted your request to add them to the \2%s\2 list of \2%s\2"
#define NS_AUTH_RPL_PENDING			"You have the following pending requests:"
#define NS_AUTH_RPL_NOENTRIES		"You have no pending requests."
#define NS_AUTH_RPL_OPEN			"You have pending authorization requests"
#define NS_AUTH_RPL_READCHAN		"Authorization Request No. \2%i %s  \2%s\2"
#define NS_AUTH_RPL_READNOTIFY		"Authorization Request No. \2%i\2 - \2%s\2"
#define NS_AUTH_RPL_TEXT_NOTIFY		"\2%s\2 wants to add you to his/her notify list."
#define NS_AUTH_RPL_TEXT_CHAN		"\2%s\2 wants to add you to the \2%s\2 list of \2%s\2"
#define NS_AUTH_RPL_XOP_READ		"Authorization request no \2%s\2 - \2%s\2 wants to add you to the \2%s\2 list of \2%s\2"
#define NS_AUTH_RPL_TEXT7			"\2%s\2 wants you to be the \2Successor\2 of %s"
#define NS_AUTH_RPL_TEXT8			"\2%s\2 wants you to be the \2Founder\2 of %s"
#define NS_AUTH_RPL_REQUESTLIST		"\2%i\2 - Request from \2%s\2"

/* ACC
 ******************************************************************************************************************************************
 */
#define NS_ACC_USAGE			"Usage: \2ACC\2 <Nickname>"

/* DROP
 ******************************************************************************************************************************************
 */
#define NS_DROP_RPL_SUCCESS			"The nickname \2%s\2 has been dropped."
#define NS_DROP_ERR_USAGE			"Usage: \2DROP\2 <nickname>"

/* GETPASS
 ******************************************************************************************************************************************
 */

#define NS_GETPASS_USED_LOG			"%s: GETPASS command used by: %s for the nickname %s"
#define NS_GETPASS_USED_GLOBAL		"GETPASS command used by: \2%s\2 for the nickname \2%s\2"
#define NS_GETPASS_MSG_LOGGED		"This command has been logged."
#define NS_GETPASS_RPL_SUCCESS		"The Password for the Nickname \2%s\2 is: %s."
#define NS_GETPASS_ERR_USAGE		"Usage: \2GETPASS\2 <nickname>."

/* GHOST
 ******************************************************************************************************************************************
 */
#define NS_GHOST_RPL_GHOSTDISCONNECT 	"You ghost has been disconnected."
#define NS_GHOST_RPL_NEEDRELEASE	 	"To release this nickname, please use /msg %s \2RELEASE\2."
#define NS_GHOST_RPL_NICKISHELD		 	"The nickname \2%s\2 is currently being held by services."
#define NS_GHOST_ERR_USAGE				"Usage: \2GHOST\2 <Nickname> [Password]"

/* HELP
 ******************************************************************************************************************************************
 */

#define NS_HELP_PATH				 	"docs/help/en/nickserv"


/* IDENTIFY
 ******************************************************************************************************************************************
 */
#define NS_IDENTIFY_RPL_ALREADYIDF		"You have already identified for the nickname \2%s\2."
#define NS_IDENTIFY_RPL_PASSACCEPTED	"Password accepted - You are now identified"
#define NS_IDENTIFY_RPL_USAGE 			"Usage: \2IDENTIFY\2 <Password>"
#define NS_IDENTIFY_RPL_WRONGPASS		"Incorrect password for the Nickname \2%s\2"
/* INFO
 ******************************************************************************************************************************************
 */
#define NS_INFO_RPL_AUTHCHAN			"Authorization is required before adding this user to channel access lists."
#define NS_INFO_RPL_AUTHNOTIFY		"Authorization is required before adding this user to notify lists."
#define NS_INFO_RPL_EMAIL			"E-Mail Address		: %s."
#define NS_INFO_RPL_HEAD1			"\2%s\2 (currently online) is \2%s\2."
#define NS_INFO_RPL_HEAD2			"\2%s\2 is \2%s\2."
#define NS_INFO_RPL_LASTADDR			"Last seen address	: %s"
#define NS_INFO_RPL_LASTSEEN			"Last seen time		: %s"
#define NS_INFO_RPL_MFORWARD			"Memos to this user are forwarded to \2%s\2."
#define NS_INFO_RPL_NOMEMO			"This user is not accepting memos."
#define NS_INFO_RPL_NOOP				"This user will not automatically opped by %s."
#define NS_INFO_RPL_PROTECT1			"This user has 'normal' protection enabled."
#define NS_INFO_RPL_PROTECT2			"This user has 'agressive' protection enabled."
#define NS_INFO_RPL_TIMEREG			"Time registered	: %s."
#define NS_INFO_RPL_TIMENOW			"Time now			: %s."
#define NS_INFO_RPL_USAGE			"USAGE: \2INFO\2 <Nickname>"

/* LIST
 ******************************************************************************************************************************************
 */
#define NS_RPL_LIST_BEGIN			"Listing all nickname matching the pattern  \2\"%s\"\2"
#define NS_RPL_LIST_ENTRY			"\2%i\2 - \2%s\2 (%s)"
#define NS_RPL_LIST_END1			"Listing complete - %i matches found"
#define NS_RPL_LIST_END2			"Listing complete - 1 match found"
#define NS_ERR_LIST_USAGE			"Usage: \2LIST\2 [Pattern]>."

/* LISTCHANS
 ******************************************************************************************************************************************
 */
#define NS_RPL_LISTCHANS_BEGIN		"Listing channel with access for \2%s\2"
#define NS_RPL_LISTCHANS_END1		"Listing complete - 1 match found"
#define NS_RPL_LISTCHANS_END2		"Listing complete - %i matches found"
#define NS_RPL_LISTCHANS_ENTRY		"\2%i\2 - \2%s\2 in \2%s\2 (Added by %s:%s on %s)"
#define NS_RPL_LISTCHANS_ENTRY2		"\2%i\2 - \2%s\2 of \2%s\2"

/* NOTIFY
 ******************************************************************************************************************************************
 */
#define NS_NOTIFY_RPL_1ENTRYREMOVED	"1 entry removed."
#define NS_NOTIFY_RPL_ALREADYINLIST	"The nickname \2%s\2 is already in your notify list."
#define NS_NOTIFY_RPL_ISNOWOFFLINE		"\2%s\2 has gone offline."
#define NS_NOTIFY_RPL_ISNOWONLINE		"\2%s\2 is now online!"
#define NS_NOTIFY_RPL_LIST				"Notify list of \2%s\2:"
#define NS_NOTIFY_RPL_LISTENTRIES		"\2%i\2 - \2%s\2"
#define NS_NOTIFY_RPL_LIST_COMPLETE_1	"Listing complete - \21\2 entry found"
#define NS_NOTIFY_RPL_LIST_COMPLETE	"Listing complete - \2%i\2 entries found"
#define NS_NOTIFY_ERR_MUSTBEREG		"You need to have a registered nickname to add someone to your notify list."
#define NS_NOTIFY_ERR_MUSTBEREG2		"You can only add registered nicknames to your notify list."
#define NS_NOTIFY_RPL_NENTRIESREMOVED	"%i entries removed."
#define NS_NOTIFY_RPL_NICKADDED		"The nickname \2%s\2 has been added to your notify list."
#define NS_NOTIFY_RPL_NICKDELETED		"The nickname \2%s\2 has been deleted from your notify list."
#define NS_NOTIFY_ERR_NICKNOTFOUND		"The nickname \2%s\2 was not found in your notify list."
#define NS_NOTIFY_RPL_NOENTRIES		"You don't have any notify entries"
#define NS_NOTIFY_RPL_NOENTRIES2		"The nickname \2%s\2 does not have any notify entries."
#define NS_NOTIFY_RPL_REQUESTSENT1		"The nickname \2%s\2 has authorization for notify lists enabled."
#define NS_NOTIFY_RPL_REQUESTSENT2		"Your request to add \2%s\2 has been sent."
#define NS_NOTIFY_RPL_REQUESTSENT3		"Once \2%s\2 approved your request, they will be on your notify list."
#define NS_NOTIFY_ERR_SAMEASSRC		"You cannot add yourself to the notify list."
#define NS_NOTIFY_ERR_USAGE			"Usage: \2NOTIFY ADD\2 <add|del|list|wipe> [nickname]."
#define NS_NOTIFY_RPL_WIPESUCCESS		"Your notify list has been wiped."

/* REGISTER
 ******************************************************************************************************************************************
 */
#define NS_REGISTER_ERR_ALREADYREG		"The nickname \2%s\2 is already registered"
#define NS_REGISTER_ERR_DELAY			"Please wait another %i seconds before registering another nickname."
#define NS_REGISTER_ERR_GENERALERROR	"Sorry, an unknown error occured. Please try again later."
#define NS_REGISTER_ERR_INVALDEMAIL		"Invalid E-Mail Address"
#define NS_REGISTER_ERR_PASSSAMEASNICK	"The password must not be the same as your nickname. Please use a more obscure password"
#define NS_REGISTER_ERR_PASSTOOSHORT	"Password too short. Your password should be at least 5 characters long"
#define NS_REGISTER_ERR_PRIVS			"Permission denied. You need to be \2%s\2 to register a Nickname"
#define NS_REGISTER_RPL_SUCCESS1		"Your nickname \2%s\2 has been successfully registered to you."
#define NS_REGISTER_RPL_SUCCESS2		"Your password is \2%s\2. Remember it for further use."
#define NS_REGISTER_RPL_SUCCESS3		"The mask \2%s\2 has automatically been added to your access list."
#define NS_REGISTER_RPL_USAGE 			"Usage: \2REGISTER\2 <Password> <E-Mail Address>"


/* RELEASE
 ******************************************************************************************************************************************
 */

#define NS_RELEASE_RPL_NICKRELEASED	"The nickname \2%s\2 has been released from custody."
#define NS_RELEASE_RPL_USAGE		"Usage: \2RELEASE\2 <Nickname> [Password]."
#define NS_RELEASE_RPL_NICKNOTHELD	"The Nickname \2%s\2 is not being held by services"

/* SET
 ******************************************************************************************************************************************
 */
#define NS_SET_AUTH_RPL_SUCCESS1	"Success - Authorization is now required before anyone can add you to channel access lists."
#define NS_SET_AUTH_RPL_SUCCESS2	"Success - Authorization was already required before anyone can add you to channel access lists."
#define NS_SET_AUTH_RPL_SUCCESS3	"Success - Authorization is no longer required before anyone can add you to channel access lists."
#define NS_SET_AUTH_RPL_SUCCESS4	"Success - Channel Authorization was already turned off."
#define NS_SET_AUTH_RPL_SUCCESS5	"Success - Authorization is now required before anyone can add you to notify lists."
#define NS_SET_AUTH_RPL_SUCCESS6	"Success - Authorization was already required before anyone can add you to notify lists."
#define NS_SET_AUTH_RPL_SUCCESS7	"Success - Authorization is no longer required before anyone can add you to notify lists."
#define NS_SET_AUTH_RPL_SUCCESS8	"Success - Notify Authorization was already turned off."
#define NS_SET_AUTH_RPL_USAGE		"Usage: \2SET AUTHORIZE\2 <chan|notify> <on|off>"
#define NS_SET_RPL_USAGE			"Usage: \2SET\2 <Command> <Parameters>."
#define NS_SET_EMAIL_RPL_USAGE		"Usage: \2SET EMAIL\2 <E-Mail Address>."
#define NS_SET_EMAIL_RPL_SUCCESS	"Success - \2%s\2 has been set as your e-mail address."
#define NS_SET_HIDEEMAIL_RPL_USAGE	"Usage: \2SET HIDEEMAIL <on|off>\2"
#define NS_SET_HIDEEMAIL_RPL_SUCC1 	"Success - Your e-mail address will be hidden."
#define NS_SET_HIDEEMAIL_RPL_SUCC2 	"Success - Your e-mail address will now be unhidden."
#define NS_SET_MFORWARD_RPL_ON		"Success - All your memos will be forwarded to the nickname \2%s\2."
#define NS_SET_MFORWARD_RPL_OFF		"Success - Memos are not  being forwarded anymore."
#define NS_SET_MFORWARD_ERR_USAGE	"Usage: \2SET MFORWARD\2 <[Nickname]|OFF>."
#define NS_SET_MFORWARD_ERR_SELF	"Error - You cannot set memo forwarding to yourself."
#define NS_SET_MNOTIFY_RPL_SUCCESS	"Success - You will no longer be notified about new memos on logon."
#define NS_SET_MNOTIFY_RPL_SUCCESS2	"Success - You will be notified about new memos on logon."
#define NS_SET_MNOTIFY_RPL_USAGE	"Usage: \2SET MNOTIFY\2 <on|off>."
#define NS_SET_MLOCK_RPL_SUCCESS	"Success - Modes are locked to \2%s\2."
#define NS_SET_MLOCK_RPL_USAGE		"Usage: \2SET MLOCK\2 <+|-> [modes]."
#define NS_SET_NOMEMO_RPL_SUCCESS	"Success - Your memos will be delivered to you."
#define NS_SET_NOMEMO_RPL_SUCCESS2	"Success - You will no longer receive memos."
#define NS_SET_NOMEMO_RPL_USAGE		"Usage: \2SET NOMEMO\2 <on|off>."
#define NS_SET_NOMEMO_RPL_HLP		"For more help, type /msg %s \2HELP SET NOMEMO\2."
#define NS_SET_NOOP_RPL_SUCCESS		"Success - Automatic opping has been disabled."
#define NS_SET_NOOP_RPL_SUCCESS2	"Success - Automatic opping was already disabled."
#define NS_SET_NOOP_RPL_SUCCESS3	"Success - Automatic opping has been enabled."
#define NS_SET_NOOP_RPL_SUCCESS4	"Success - Automatic opping was already enabled."
#define NS_SET_NOOP_RPL_USAGE		"Usage: \2SET NOOP\2 <on|off>"
#define NS_SET_PASS_RPL_USAGE		"Usage: \2SET PASSWORD\2 <New Password>."
#define NS_SET_PASS_RPL_SUCCESS		"Success - Your new password is \2%s\2 - remember it for further use."
#define NS_SET_PROTECT_RPL_SUCCESS	"Success - Nickname Protection disabled"
#define NS_SET_PROTECT_RPL_SUCCESS2	"Success - Nickname Protection was already disabled."
#define NS_SET_PROTECT_RPL_SUCCESS3	"Success - Normal Nickname Protection enabled."
#define NS_SET_PROTECT_RPL_SUCCESS4	"Success - Normal Nickname Protection was already enabled."
#define NS_SET_PROTECT_RPL_SUCCESS5	"Success - Agressive Nickname Protection enabled."
#define NS_SET_PROTECT_RPL_SUCCESS6	"Success - Agressive Nickname Protection was already enabled."
#define NS_SET_PROTECT_ERR_USAGE	"Usage: \2SET PROTECT\2 <OFF|NORMAL|HIGH>"
#define NS_SET_URL_RPL_SUCCESS		"Success - Your URL has been set to \2%s\2."
#define NS_SET_URL_RPL_USAGE		"Usage: \2SET URL\2 <url>."

/* SETPASS
 ******************************************************************************************************************************************
 */
#define NS_LOG_SETPASS_USED			"%s: SETPASS command used by: %s for the nickname %s"
#define NS_GLOBAL_SETPASS_USED		"SETPASS command used by: \2%s\2 for the nickname \2%s\2"
#define NS_RPL_SPASS_SUCCESS		"Success - The Password for the nickname \2%s\2 has been changed to \2%s\2."
#define NS_ERR_SPASS_USAGE			"Usage: \2SETPASS\2 <nickname> <password>"

/* Chanserv messages
 ******************************************************************************************************************************************
 */

/* General
 ******************************************************************************************************************************************
 */
#define CS_ERR_ACCESSDENIED			"Access denied for this function for the channel \2%s\2."
#define CS_RPL_NEEDIDENTIFY			"Please identify for the channel \2%s\2"
#define CS_ERR_NOSUCHCHAN			"No such channel: \2%s\2"
#define CS_ERR_NOSUCHCMD			"Unknown Command: \2%s\2"
#define CS_ERR_NEEDREG				"You need a registered nickname to register a channel."
#define CS_ERR_NOSUCHCHANNEL		"No such channel: %s."
#define CS_ERR_NOTREG				"The Channel \2%s\2 is not registered."
#define CS_RPL_HLP					"For more help, type /msg %s \2HELP %s %s\2."
/* ACC
 ******************************************************************************************************************************************
 */
#define CS_ACC_RPL_USAGE			"Usage: \2ACC\2 <#channel> <nickname>"
#define CS_ACC_RPL_HLP				"For more help, type /msg %s \2HELP ACC\2"
#define CS_ACC_RPL_NOACC			"The user \2%s\2 has no access to channel \2%s\2"
#define CS_ACC_RPL_IRCOP			"%s: This is an \2%s\2 and thus has full access to the channel \2%s\2"
#define CS_ACC_RPL_XOP				"%s: has identified or matches an access entry for the nickname \2%s\2 who has \2%s\2 access to \2%s\2"
#define CS_ACC_RPL_IDENTIFIED		"%s: has full founder access because they identified for the channel \2%s\2"
#define CS_ACC_RPL_SUCCFND_ACC		"%s: has restricted founder access because they match an entry in the access list of \2%s\2 who is the \2%s\2 of \2%s\2"
#define CS_ACC_RPL_SUCCFND			"%s: has identified for the nickname \2%s\2 who is the \2%s\2 of \2%s\2"
#define CS_ACC_RPL_NOACCESS			"\2%s\2 has no access to \2%s\2."

/* AKICK
 ******************************************************************************************************************************************
 */
#define CS_AKICK_ERR_ALREADYONLIST	"The mask \2%s\2 already is on the \2Akick\2 list of \2%s\2"
#define CS_AKICK_ERR_USAGE			"Usage: \2AKICK\2 [#channel] \2<add|del|list|wipe> [reason]\2"
#define CS_AKICK_RPL_KICKREASON		"Your mask has been added to the AKICK list (%s)"
#define CS_AKICK_ERR_ADD_NOSENSE	"The mask \2%s\2 doesn't make any sense."
#define CS_AKICK_ERR_ADD_USAGE		"Usage: \2AKICK\2 [#channel] \2ADD [mask] [reason]\2"
#define CS_AKICK_ERR_DEL_USAGE		"Usage: \2AKICK\2 [#channel] \2DEL [mask]\2"
#define CS_AKICK_RPL_LIST			"\2%i\2 - \2%s\2 (Added by %s:%s on %s) (%s)"
#define CS_AKICK_RPL_LIST2			"\2%i\2 - \2%s\2 (Added by %s:%s on %s)"

/* DROP
 ******************************************************************************************************************************************
 */
#define CS_DROP_RPL_SUCCESS			"The Channel \2%s\2 has been dropped"
#define CS_DROP_RPL_USAGE			"Usage: \2DROP\2 <channel>"

/* GETPASS
 ******************************************************************************************************************************************
 */
#define CS_LOG_GETPASS_USED			"%s: GETPASS command used by: %s for the channel %s"
#define CS_GLOBOPS_GETPASS_USED		"GETPASS command used by: \2%s\2 for the channel \2%s\2"
#define CS_GETPASS_RPL_SUCCESS		"The Password for the channel \2%s\2 is: %s."
#define CS_GETPASS_RPL_USAGE		"Usage: \2GETPASS\2 <channel>."


/* INFO
 ******************************************************************************************************************************************
 */
#define CS_HELP_PATH			"docs/help/en/chanserv"

/* INFO
 ******************************************************************************************************************************************
 */

#define CS_INFO_RPL_USAGE			"Usage: \2INFO\2 <channel>"
#define CS_INFO_RPL_ENTRY1			"\2%s\2 is \2%s\2"
#define CS_INFO_RPL_ENTRY2			"Founder: \2%s\2"
#define CS_INFO_RPL_ENTRY3			"Successor: \2%s\2"
#define CS_INFO_RPL_ENTRY4			"Last Topic is: %s"
#define CS_INFO_RPL_ENTRY5			"Time registered: %s"
#define CS_INFO_RPL_ENTRY6			"Time now		: %s"
#define CS_INFO_RPL_ENTRY7			"ModeLock: %s"
#define CS_INFO_RPL_ENTRY8			"Options: %s"
#define CS_INFO_RPL_ENTRY9			"MemoLevel: %s"

/* INVITE
 ******************************************************************************************************************************************
 */
#define CS_INVITE_ERR_USAGE			 "Usage: \2INVITE\2 <channel> [Nickname]"
#define CS_INVITE_ERR_ALREADYONCHAN	 "\2%s\2 already is on channel \2%s\2"
#define CS_INVITE_ERR_ALREADYONCHAN2 "You already are on channel \2%s\2"


/* IDENTIFY
 ******************************************************************************************************************************************
 */
#define CS_IDENTIFY_RPL_ALREADYIDF	 "You have already identified for the channel \2%s\2"
#define CS_IDENTIFY_RPL_PASSACCEPTED "Password accepted - You are now identified for channel \2%s\2"
#define CS_IDENTIFY_ERR_USAGE		 "Usage: \2IDENTIFY\2 [#channel] \2[password]\2"
#define CS_IDENTIFY_ERR_WRONGPASS	 "Password incorrect for channel \2%s\2"

/* LIST
 ******************************************************************************************************************************************
 */
#define CS_LIST_RPL_BEGIN			"Listing all registered channels matching the pattern  \2\"%s\"\2"
#define CS_LIST_RPL_ENTRY			"\2%i\2 - \2%s\2 (Founder: %s)"
#define CS_LIST_RPL_END1			"Listing complete - %i matches found"
#define CS_LIST_RPL_END2			"Listing complete - 1 match found"
#define CS_LIST_ERR_USAGE			"Usage: \2LIST\2 [Pattern]>."

/* MDEOP
 ******************************************************************************************************************************************
 */
#define CS_MDEOP_ERR_USAGE			"Usage: \2MDEOP\2 [#channel]"


/* MKICK
 ******************************************************************************************************************************************
 */
#define CS_MKICK_ERR_USAGE			"Usage: \2MKICK\2 [#channel] \2[reason]\2"
#define CS_MKICK_RPL_NOUSERS		"There a no users on channel \2%s\2"
#define CS_MKICK_RPL_USED_BY		"MKICK Command used by %s"

/* OP
 ******************************************************************************************************************************************
 */
#define CS_OP_ERR_USAGE				"Usage: \2OP\2 [#channel] \2[nickname]\2"

/* REGISTER
 ******************************************************************************************************************************************
 */
#define CS_REGISTER_ERR_ALREADYREG	"The Channel \2%s\2 is already registered."

/* SET
 ******************************************************************************************************************************************
 */
#define CS_SET_BOT_ERR_NOBOT		  "There is no bot on channel \2%s\2"
#define CS_SET_BOT_ERR_NOSUCHBOT	  "The bot \2%s\2 was not found"
#define CS_SET_BOT_ERR_USAGE 		  "Usage: \2SET\2 [#channel] \2BOT\2 <Botname>"
#define CS_SET_BOT_RPL_ALREADY		  "Bot \2%s\2 already is on channel \2%s\2"
#define CS_SET_BOT_RPL_BOTADDED		  "The bot \2%s\2 will now join channel \2%s\2"
#define CS_SET_BOT_RPL_BOTREMOVED	  "Success - Bot removed from Channel \2%s\2"
#define CS_SET_BOT_RPL_SUCCESS		  "Bot for \2%s\2 is now set to \2%s\2"
#define CS_SET_ERR_USAGE			  "Usage: \2SET\2 [#channel] <command> <parameters>"
#define CS_SET_FOUNDER_ERR_REG		  "Only a registiered Nickname can be founder of a channel"
#define CS_SET_FOUNDER_ERR_USAGE      "Usage: \2SET\2 [#channel] \2FOUNDER\2 <Nickname>"
#define CS_SET_FOUNDER_RPL_SUCCESS	  "The founder of \2%s\2 was changed to \2%s\2"
#define CS_SET_KEEPTOPIC_ERR_USAGE    "Usage: \2SET\2 [#channel] \2KEEPTOPIC\2 <on|off>"
#define CS_SET_KEEPTOPIC_RPL_DISABLE  "Keeptopic for \2%s\2 is now disabled"
#define CS_SET_KEEPTOPIC_RPL_ENABLE	  "Keeptopic for \2%s\2 is now enabled"
#define CS_SET_LEAVEOPS_ERR_USAGE 	  "Usage: \2SET\2 [#channel] \2LEAVEOPS\2 <on|off>"
#define CS_SET_LEAVEOPS_RPL_DISABLE	  "Leaveops for \2%s\2 is now disabled"
#define CS_SET_LEAVEOPS_RPL_ENABLE	  "Leaveops for \2%s\2 is now enabled"
#define CS_SET_MEMOLEVEL_ERR_USAGE 	  "Usage: \2SET\2 [#channel] \2MEMOLEVEL\2 [Level]"
#define CS_SET_MEMOLEVEL_RPL_SUCCESS  "Memolevel for \2%s\2 was changed to \2%s\2"
#define CS_SET_MLOCK_ERR_USAGE 		  "Usage: \2SET\2 [#channel] \2MLOCK\2 <+|-> [Modes]"
#define CS_SET_MLOCK_RPL_SUCCESS 	  "Modelock for \2%s\2 has been changed to \2%s\2"
#define CS_SET_OPWATCH_ERR_USAGE 	  "Usage: \2SET\2 [#channel] \2OPWATCH\2 <on|off>"
#define CS_SET_OPWATCH_RPL_DISABLE	  "Opwatch for \2%s\2 is now disabled"
#define CS_SET_OPWATCH_RPL_ENABLE	  "Opwatch for \2%s\2 is now enabled"
#define CS_SET_PASSWORD_ERR_USAGE 	  "Usage: \2SET\2 [#channel] \2PASSWORD\2 [Password]"
#define CS_SET_PASSWORD_RPL_SUCCESS	  "The password of \2%s\2 was changed to \2%s\2"
#define CS_SET_RESTRICTED_RPL_ENABLE  "Access to \2%s\2 is now restricted"
#define CS_SET_RESTRICTED_RPL_DISABLE "Access to \2%s\2 is no longer restricted"
#define CS_SET_RESTRICTED_ERR_USAGE   "Usage: \2SET\2 [#channel] \2RESTRICTED\2 <on|off>"
#define CS_SET_SUCCESSOR_ERR_REG	  "Only a registiered Nickname can be successor of a channel"
#define CS_SET_SUCCESSOR_ERR_USAGE 	  "Usage: \2SET\2 [#channel] \2FOUNDER\2 <Nickname>"
#define CS_SET_SUCCESSOR_RPL_SUCCESS  "The successor of \2%s\2 was changed to \2%s\2"
#define CS_SET_TOPICLOCK_RPL_SUCCESS  "Topiclock for \2%s\2 is now set to \2%s\2"
#define CS_SET_TOPICLOCK_RPL_DISABLE  "Topiclock for \2%s\2 is now disabled"
#define CS_SET_TOPICLOCK_ERR_USAGE 	  "Usage: \2SET\2 [#channel] \2TOPICLOCK\2 [Level|Off]"

/* SETPASS
 ******************************************************************************************************************************************
 */
#define CS_LOG_SETPASS_USED			"%s: SETPASS command used by: %s for the channel %s"
#define CS_O_SETPASS_USED			"SETPASS command used by: \2%s\2 for the channel \2%s\2"
#define CS_RPL_SPASS_SUCCESS		"Success - The Password for the Channel \2%s\2 has been changed to \2%s\2."
#define CS_ERR_SPASS_USAGE			"Usage: \2SETPASS\2 <Channel> <password>"


/* UNBAN
 ******************************************************************************************************************************************
 */
#define CS_RPL_UBN_LIFTED			"Success - \2%i\2 ban(s) for in the channel \2%s\2 were lifted."
#define CS_RPL_UBN_NOT_FOUND		"No ban on \2%s\2 found that affects you"
#define CS_RPL_UBN_USAGE			"Usage: \2UNBAN\2 [Channel]"

/* XOP
 ******************************************************************************************************************************************
 */
#define CS_XOP_RPL_AUTH_REQUIRED	"\2%s\2 has authorization enabled for channel access list. "
#define CS_XOP_RPL_AUTH_SENT_XOP	"\2%s\2 will receive a notification about your request to add them to the \2%s\2 list of \2%s\2."
#define CS_XOP_RPL_AUTH_SENT_SF		"\2%s\2 will receive a notification about your request to set them as the \2%s\2 of \2%s\2."
#define CS_XOP_RPL_AUTH_SENT_END	"Once the request has been approved, \2%s\2 will be automatically entered."
#define CS_RPL_ATH_ALREADYSENT		"As request like this has already been sent to \2%s\2"
#define CS_XOP_RPL_ADDED			"\2%s\2 has been added the \2%s\2 List of \2%s\2"
#define CS_XOP_RPL_MOVED			"\2%s\2 has been moved from the \2%s\2 to the \2%s\2 list of \2%s\2."
#define CS_XOP_ERR_ALREADYONLIST	"\2%s\2 is already on the \2%s\2 list of \2%s\2"
#define CS_XOP_ERR_ALREADYONHIGHER	"\2%s\2 already has a higher access to \2%s\2"
#define CS_XOP_ERR_NICKISFOUNDER	"\2%s\2 is already the founder of the channel \2%s\2"
#define CS_XOP_ERR_FOUNDERCANNOTADD "\2%s\2 is the founder of the channel \2%s\2 and cannot be added to its \2%s\2 list"
#define CS_XOP_ERR_SUCCCANNOTADD 	"\2%s\2 is the successor of the channel \2%s\2 and cannot be added to its \2%s\2 list"
#define CS_XOP_ERR_NICKISSUCCESSOR	"\2%s\2 is already the successor of the channel \2%s\2"
#define CS_XOP_RPL_DISABLED			"The \2%s\2 list of \2%s\2 is currently disabled."
#define CS_XOP_RPL_LIST_BEGIN		"This is the \2%s\2 list of \2%s\2"
#define CS_XOP_RPL_LIST				"\2%i\2 - \2%s\2 (Added by %s:%s on %s)"
#define CS_XOP_RPL_LIST_COMPLETE1	"Listing complete - \2%i\2 matches found"
#define CS_XOP_RPL_LIST_COMPLETE2	"Listing complete - 1 match found"
#define CS_XOP_RPL_DELETED			"\2%s\2 has been removed from the \2%s\2 list of \2%s\2"
#define CS_XOP_RPL_WIPED1			"The \2%s\2 list of \2%s\2 has been wiped - 1 entry removed."
#define CS_XOP_RPL_WIPED2			"The \2%s\2 list of \2%s\2 has been wiped - %i entries removed."
#define CS_XOP_ERR_NOTONLIST		"\2%s\2 is not on the \2%s\2 list of \2%s\2"
#define CS_XOP_ERR_USAGE			"Usage: \2%s\2 <Channel> [ADD|DEL|LIST|WIPE|ENABLE|DISABLE]"
#define CS_XOP_ERR_LIMIT			"The Limit of \2%i\2 entries in the \2%s\2 list of \2%s\2 has already been reached."
#define CS_XOP_RPL_USAGE_1			"Usage: \2%s\2 <#channel> \2%s\2 <nickname>"
#define CS_XOP_RPL_USAGE_2			"Usage: \2%s\2 <#channel> \2%s\2"
#define CS_XOP_RPL_USAGE_MAIN		"Usage: \2%s\2 <#channel> \2[ADD|DEL|LIST|WIPE]\2 <nickname>"
#define CS_XOP_ERR_HIGHERACCESS		"Permission denied. You need \2%s\2 Access or higher."
#define CS_XOP_ERR_HIGHERACCESS2	"Sorry, \2%s\2 does not have the required privileges."
#define CS_XOP_RPL_REQUESTSENT1		"The nickname \2%s\2 has authorization for channel lists enabled."
#define CS_XOP_RPL_REQUESTSENT2		"Your request to add \2%s\2 has been sent."
#define CS_XOP_RPL_REQUESTSENT3		"Once \2%s\2 approved your request, they will be added to the \2%s\2 list of \2%s\2."
#define CS_XOP_RPL_REQUESTSENT4		"Once \2%s\2 approved your request, they will be set as the \2%s\2 of \2%s\2."
#define CS_ERR_AOP_GENERALERROR		"Sorry, a general error has occured. Please try again later."
#define OP_AOP						"Aop"
#define OP_COP						"Cop"
#define OP_HOP						"Hop"
#define OP_QOP						"Qop"
#define OP_SOP						"Sop"
#define OP_UOP						"Uop"
#define OP_VOP						"Vop"

/* REGISTER
 ******************************************************************************************************************************************
 */
#define CS_REGISTER_ERR_DELAY			"Please wait another %i seconds before registering another channel."
#define CS_REGISTER_ERR_GENERALERROR	"A general error has occured. Please try again later."
#define CS_REGISTER_RPL_HLP				"For more help, type /msg %s \2HELP REGISTER\2"
#define CS_REGISTER_ERR_NEEDTOBEONCHAN	"You must be on the channel \2%s\2 to register it."
#define CS_REGISTER_ERR_NEEDTOBEOP		"You must be an Operator (+o) on \2%s\2 to register a channel."
#define CS_REGISTER_ERR_PASSSAMEASCHAN	"The password must not be the same as the channel name."
#define CS_REGISTER_ERR_PASSSAMEASFND	"The password must not be the same as the founder's nickname."
#define CS_REGISTER_ERR_PRIVS			"Permission denied. You need to be \2%s\2 to register a Channel"
#define CS_REGISTER_RPL_SUCCESS1		"The channel \2%s\2 has been registered to you."
#define CS_REGISTER_RPL_SUCCESS2		"The password is \2%s\2 - Remember it for further use."
#define CS_REGISTER_RPL_SUCCESS3		"The mask \2%s\2 was automatically added to the channel access list."
#define CS_REGISTER_RPL_USAGE			"Usage: \2REGISTER\2 <# <Password> <Channel Description>"


/* Botserv Messages
 ******************************************************************************************************************************************
 */
#define BS_ERR_ACCESSDENIED			"Access denied for that function of bot \2%s\2. Please identify using /msg %s IDENTIFY <Botname> <Password>"
#define BS_ERR_INVALIDNICKNAME		"%s: Invalid Nickname"
#define BS_ERR_NEEDMOREPRIVS		"Access denied for that command for %s. You don't have the required privileges."
#define BS_ERR_NOSUCHCMD			"Unknown command: SET \2%s\2."
#define BS_ERR_NOTFOUND				"The Bot \2%s\2 does not exist"
#define BS_ERR_PASSSAMEASNICK		"Your bot password must be the same as your bot name - Please use a more obscure password"
#define BS_ERR_PASSTOOSHORT			"Please use at least 5 characters for your password"
#define BS_KILL_NAMECHANGE			"Bot is reconnecting due to changed settings. "
#define BS_PART_RPL_MSG				"Channel management by Bot discontinued"
#define BS_RPL_HLP					"For more help, type /msg %s HELP \2%s\2"

/* ADD
 ******************************************************************************************************************************************
 */
#define BS_ADD_ERR_USAGE			"Usage: \2ADD\2 <Botname> [Password]"
#define BS_ADD_ERR_EXISTS			"A bot with the name \2%s\2 already exists"
#define BS_ADD_ERR_INVALIDCHARS		"Invalid characters - Please use Nickname-only characters"
#define BS_ADD_RPL_SUCCESS1			"The bot \2%s\2 has been added."
#define BS_ADD_RPL_SUCCESS2			"The password is \2%s\2 - remember it for further use."
#define BS_ADD_RPL_SUCCESS3			"To customize your bot, please use the command \2SET USERNAME\2 or \2SET REALNAME\2"
#define BS_DEL_RPL_SUCCESS			"The Bot \2%s\2 has been deleted"
#define BS_DEL_ERR_USAGE			"Usage: \2DEL\2 <Botname>"

/* CHAN
 ******************************************************************************************************************************************
 */
#define BS_CHAN_ADD_ERR_USAGE		"Usage: \2CHAN\2 <Botname> \2ADD\2 <Channel>"
#define BS_CHAN_DEL_ERR_USAGE		"Usage: \2CHAN\2 <Botname> \2DEL\2 <Channel>"
#define BS_CHAN_LIST_ERR_USAGE		"Usage: \2CHAN\2 <Botname> \2LIST\2"


/* GETPASS / SETPASS
 ******************************************************************************************************************************************
 */
#define BS_GETPASS_ERR_USAGE		"Usage: \2GETPASS\2 <Bot>."
#define BS_SETPASS_ERR_USAGE		"Usage: \2SETPASS\2 <Bot> <Password>"
#define BS_SETPASS_RPL_SUCCESS		"The Password for the Bot \2%s\2 was changed to \2%s\2."
#define BS_GETPASS_RPL_SUCCESS		"The Password for the Bot \2%s\2 is: %s."
#define BS_GETPASS_RPL_LOGGED		"This command has been logged."

/* IDENTIFY
 ******************************************************************************************************************************************
 */
#define BS_IDENTIFY_ERR_USAGE		"Usage: IDENTIFY <Botname> \2%s\2 <Password>"
#define BS_IDENTIFY_ERR_WRONGPASS	"Password incorrect for Bot \2%s\2"
#define BS_IDENTIFY_ERR_PASSACC		"Password accepted for Bot \2%s\2"

/* INFO
 ******************************************************************************************************************************************
 */
#define BS_INFO_ERR_USAGE			"Usage: \2INFO\2 <Botname>"
#define BS_INFO_RPL_HEAD			"\2%s\2 is \2%s\2."
#define BS_INFO_RPL_CHANS			"\2%s\2 is on the following Channels: %s"
#define BS_INFO_RPL_END				"End of Bot Info"

/* KICK
 ******************************************************************************************************************************************
 */
#define BS_KICK_ERR_BOT				"You cannot kick \2%s\2 because this is a bot."
#define BS_KICK_ERR_USAGE			"Usage: \2KICK\2 <Botname> <Channel> <Nickname> <Reason>"

/* LIST
 ******************************************************************************************************************************************
 */
#define BS_LIST_ERR_USAGE			"Usage: \2LIST\2"
#define BS_LIST_RPL_BEGIN			"The following Bot are registered with Botserv"
#define BS_LIST_RPL_ENTRY			"%i - \2%s\2 (%s@%s) (%s)"
#define BS_LIST_RPL_COMPLETE1		"Listing complete - 1 match found"
#define BS_LIST_RPL_COMPLETE2		"Listing complete - %i matches found"


/* XOP
 ******************************************************************************************************************************************
 */
#define BS_DEHALFOP_ERR_USAGE		"Usage: \2DEHALFOP\2 <Botname> <Channel> <Nickname>"
#define BS_DEOP_ERR_USAGE			"Usage: \2DEOP\2 <Botname> <Channel> <Nickname>"
#define BS_DEVOICE_ERR_USAGE		"Usage: \2DEVOICE\2 <Botname> <Channel> <Nickname>"
#define BS_HALFOP_ERR_USAGE			"Usage: \2HALFOP\2 <Botname> <Channel> <Nickname>"
#define BS_OP_ERR_USAGE				"Usage: \2OP\2 <Botname> <Channel> <Nickname>"
#define BS_OP_ERR_NOT_ON_CHAN		"Bot \2%s\2 is not on channel \2%s\2"
#define BS_VOICE_ERR_USAGE			"Usage: \2VOICE\2 <Botname> <Channel> <Nickname>"


/* RENAME
 ******************************************************************************************************************************************
 */
#define BS_RENAME_ERR_USAGE			"Usage: \2RENAME\2 <Botname> <New Botname>"

/* SET
 ******************************************************************************************************************************************
 */
#define BS_SET_ERR_USAGE			"Usage: \2SET\2 <Botname> \2SET\2 [NAME|USERNAME|REALNAME|PASSWORD] <Argument>"
#define BS_SET_OPT_ERR_USAGE		"Usage: SET <Botname> \2%s\2 <Arguments>"
#define BS_SET_NAME_SUCCESS			"The Name of bot \2%s\2 has been changed to \2%s\2"
#define BS_SET_PASS_SUCCESS			"The Password of bot \2%s\2 has been changed to \2%s\2"
#define BS_SET_USERNAME_SUCCESS		"The Username of bot \2%s\2 has been changed to \2%s\2"
#define BS_SET_REALNAME_SUCCESS		"The Realname of bot \2%s\2 has been changed to \2%s\2"
#define BS_SET_ERR_USERNAME_USAGE	"Usage: \2SET\2 <Botname> \2USERNAME\2 <Username>"
#define BS_SET_REALNAME_ERR_USAGE	"Usage: \2SET\2 <Botname> \2REALNAME\2 <Realname>"
#define BS_SET_PASSWORD_ERR_USAGE	"Usage: \2SET\2 <Botname> \2PASSWORD\2 <Password>"


#define BS_HELP_PATH				"docs/help/en/botserv"

/* Operserv Messages
 ******************************************************************************************************************************************
 */

#define OS_RPL_HELP					"For more help type /msg %s HELP \2%s\2"
#define OS_RPL_ISNOWHELPOP			"\2%s\2 is now a Help Operator\2"
#define OS_RPL_ISNOWIRCOP			"\2%s\2 is now an \2IRC Operator\2"
#define OS_RPL_ISNOWCOADMIN			"\2%s\2 is now a \2Co Administrator\2"
#define OS_RPL_ISNOWSA				"\2%s\2 is now a \2Services Administrator\2"
#define OS_RPL_ISNOWADMIN			"\2%s\2 is now a \2Server Administrator \2"
#define OS_RPL_ISNOWNETADMIN		"\2%s\2 is now a \2Network Administrator\2"
#define OS_ERR_ACCESSDENIED			"Access denied for that function of %s. You need \2%s\2 or higher access"
#define OS_ERR_ACCESSDENIED2		"Access denied for that function of %s. You don't have the required privileges"
#define OS_ERR_NOSUCHCMD			"Unknown command: \2%s\2"
#define OS_ERR_USERNOTFOUND			"User \2%s\2 is not online."

/* AKILL
 ******************************************************************************************************************************************
 */
#define OS_AKILL_RPL_LIST_BEGIN		"The following mask are autokilled"
#define OS_AKILL_ERR_EXISTS			"There is already an AKILL entry for %s"
#define OS_AKILL_LIST_ERR_USAGE		"Usage: OPER AKILL \2LIST\2"
#define OS_AKILL_LIST_RPL_ENTRY		"\2%i\2 - \2%s\2 (Added by: %s (%s) - Expires %s)"
#define OS_AKILL_LIST_RPL_ENTRY2	"\2%i\2 - \2%s\2 (Added by: %s (%s) (Permanent)"
#define OS_AKILL_RPL_ADD_USAGE		"Usage: OPER AKILL \2ADD\2 <Mask> <Duration> <Reason>"
#define OS_AKILL_RPL_ADDED			"%s added a service Autokill for %s (%s) (Expiry: %s)"
#define OS_AKILL_RPL_ADDED2			"%s added a permanent service Autokill for %s (%s)"
#define OS_AKILL_RPL_DEL_USAGE		"Usage: OPER AKILL \2DEL\2 <Mask>"
#define OS_AKILL_RPL_NOTFOUND		"The mask \2%s\2 was not found in the AKILL list."
#define OS_AKILL_RPL_ADD_SUCCESS	"The mask \2%s\2 was added to the AKILL list."
#define OS_AKILL_RPL_DEL_SUCCESS	"The mask \2%s\2 was removed from the AKILL list."
#define OS_AKILL_ERR_NOSUCHCMD		"Unknown command: AKILL \2%s\2."

/* CHATOPS
 ******************************************************************************************************************************************
 */
#define OS_CHATOPS_ERR_USAGE		"Usage: \2CHATOPS\2 <Message>"

/* CHGHOST
 ******************************************************************************************************************************************
 */
#define OS_CHGHOST_ERR_USAGE		"Usage: CHGHOST <Nickname> <Host>"
#define OS_CHGHOST_RPL_SUCCESS		"The host of user \2%s\2 was changed to \2%s\2"

/* OPER
 ******************************************************************************************************************************************
 */
#define OS_OPER_LIST_ERR_USAGE		"Usage: OPER \2LIST\2"
#define OS_OPER_ADD_RPL_SUCCESS		"The Nickname \2%s\2 has been granted Oper Access"
#define OS_OPER_DEL_RPL_SUCCESS		"The Nickname \2%s\2 was removed from the Oper list."
#define OS_OPER_ERR_EXISTS			"The Nickname \2%s\2 already has Oper access"
#define OS_OPER_ERR_NOTFOUND		"The Nickname \2%s\2 was not found on the Oper list."
#define OS_OPER_ADD_ERR_USAGE		"Usage: OPER \2ADD\2 <Nickname>"
#define OS_OPER_DEL_ERR_USAGE		"Usage: OPER \2DEL\2 <Nickname>"
#define OS_OPER_LIST_RPL_BEGIN		"The following Nicknames have been granted access to %s:"
#define OS_OPER_LIST_RPL_ENTRY		"\2%i\2 - %s"
#define OS_OPER_SET_ERR_USAGE		"Usage: SET [Command] <Arguments>"
#define OS_OPER_SET_OPT_ERR_USAGE	"Usage: SET \2%s\2 [On|Off]"

/* GLOBAL
 ******************************************************************************************************************************************
 */
#define OS_GLOBAL_ERR_USAGE			"Usage: \2GLOBAL\2 <Message>"
#define OS_GLOBAL_RPL_SENT			"Success - Message sent to opers"



/* KILL
 ******************************************************************************************************************************************
 */
#define OS_KILL_ERR_USAGE			"Usage: \2KILL\2 <Nick> <Reason>"
#define OS_KILL_RPL_SUCCESS			"The user \2%s\2 has been killed"

/* LIST
 ******************************************************************************************************************************************
 */
#define	OS_LIST_RPL_END1			"Listing Complete - 1 entry found"
#define	OS_LIST_RPL_END2			"Listing Complete - %i entries found"

/* LOCAL
 ******************************************************************************************************************************************
 */
#define OS_LOCAL_ERR_USAGE			"Usage: \2LOCAL\2 <Message>"

/* SET
 ******************************************************************************************************************************************
 */
#define OS_SET_RPL_SUCCESS			"Success - Setting for user \2%s\2 was changed."

/* SGLINE
 ******************************************************************************************************************************************
 */
#define OS_SGLINE_ADD_ERR_USAGE		"Usage: SGLINE \2ADD\2 <Mask> <Duration> <Reason>"
#define OS_SGLINE_DEL_ERR_USAGE		"Usage: SGLINE \2DEL\2 <Mask>"
#define OS_SGLINE_RPL_ADDED			"%s added a service G:Line for %s (%s) (Expiry: %s)"
#define OS_SGLINE_RPL_ADDED2		"%s added a permanent service G:Line for %s (%s)"
#define OS_SGLINE_ADD_RPL_SUCCESS	"A G:Line for \2%s\2 was added"
#define OS_SGLINE_DEL_RPL_SUCCESS	"A G:Line for \2%s\2 was removed"

/* SKLINE
 ******************************************************************************************************************************************
 */
#define OS_SKLINE_ADD_ERR_USAGE		"Usage: SKLINE \2ADD\2 <Mask> <Duration> <Reason>"
#define OS_SKLINE_DEL_ERR_USAGE		"Usage: SKLINE \2DEL\2 <Mask>"
#define OS_SKLINE_RPL_ADDED			"%s added a service K:Line for %s (%s) (Expiry: %s)"
#define OS_SKLINE_RPL_ADDED2		"%s added a permanent service K:Line for %s (%s)"
#define OS_SKLINE_ADD_RPL_SUCCESS	"A K:Line for \2%s\2 was added"
#define OS_SKLINE_DEL_RPL_SUCCESS	"A K:Line for \2%s\2 was removed"

/* SQLINE
 ******************************************************************************************************************************************
 */
#define OS_SQLINE_ADD_ERR_USAGE		"Usage: SQLINE \2ADD\2 <Nickname> <Duration> <Reason>"
#define OS_SQLINE_DEL_ERR_USAGE		"Usage: SQLINE \2DEL\2 <Nickname>"
#define OS_SQLINE_RPL_ADDED			"%s added a service Q:Line for %s (%s) (Expiry: %s)"
#define OS_SQLINE_RPL_ADDED2		"%s added a permanent service Q:Line for %s (%s)"
#define OS_SQLINE_ADD_RPL_SUCCESS	"A Q:Line for \2%s\2 was added"
#define OS_SQLINE_DEL_RPL_SUCCESS	"A Q:Line for \2%s\2 was removed"

/* SZLINE
 ******************************************************************************************************************************************
 */
#define OS_SZLINE_ADD_ERR_USAGE		"Usage: SZLINE \2ADD\2 <IP Mask> <Duration> <Reason>"
#define OS_SZLINE_DEL_ERR_USAGE		"Usage: SZLINE \2DEL\2 <IP Mask>"
#define OS_SZLINE_RPL_ADDED			"%s added a service Z:Line for %s (%s) (Expiry: %s)"
#define OS_SZLINE_RPL_ADDED2		"%s added a permanent service Z:Line for %s (%s)"
#define OS_SZLINE_ADD_RPL_SUCCESS	"A Z:Line for \2%s\2 was added"
#define OS_SZLINE_DEL_RPL_SUCCESS	"A Z:Line for \2%s\2 was removed"


#define AS_FUNCTIONDISABLED			"Sorry, This function has been disabled by the Administration."

#define LOG_DBG_ENFORCING			"[%s] Enforcing nickname: %s"
#define LOG_DBG_JOINNONEXIST		"[%s]  JOIN from nonexistent user: %s"
#define LOG_DBG_IRC_KILL			"[%s]  KILL %s (%s@%s): %s"
#define LOG_DBG_IRC_NOTICE			"[%s]  NOTICE %s (%s@%s): %s"
#define LOG_DBG_IRCJOIN				"[%s]  %s JOIN %s" 	
#define LOG_DBG_NS					"[%s]  Command from %s!%s@%s: %s"
#define LOG_DBG_NS_UNKNOWN			"[%s]  Unknown command from %s!%s@%s: %s"
#define LOG_DBG_SERVERMSG			"[%s]  %s"
#define LOG_DBG_SQLQRY				"[SQL QUERY] %s."
#define LOG_ERR_USERNOTFOUND		"User %s not found."
#define LOG_ERR_SQLERROR			"[SQL Error] %s."
#define LOG_DBG_ENTRY				"Entering function %s"
#define LOG_DBG_EXIT				"Exiting function %s"

/* invalid nicks and characters */

#define NICK_PATTERN "^[]a-z0-9|{}^[]{4,36}$"


#endif /*MESSAGES_H_*/
