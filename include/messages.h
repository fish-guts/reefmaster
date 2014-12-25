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

#define KNRM  "\x1B[0m;"
#define KRED  "\x1b[31;1m"
#define KGRN  "\x1b[32;1m"
#define KYEL  "\x1b[33;1m"
#define KBLU  "\x1b[34;1m"
#define KMAG  "\x1b[35;1m"
#define KCYN  "\x1b[36;1m"
#define KWHT  "\x1b[37;1m"
#define KDEF  "\x1b[0m"
#define FAIL  "\x1b[32;1mfailed\x1b[0m \n"
#define OK	  "\x1b[32;2mok\x1b[0m \n"

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
#define CONF_LOG_ERR_MISSINGOPT		"[CONFIG] %s:%i: Option '%s' is missing.\n"
#define CONF_LOG_ERR_NEGVALUEFOUND	"[CONFIG] %s:%i: Option '%s' must not have a negative value.\n"
#define CONF_LOG_ERR_PORTOUTOFRANGE	"[CONFIG] %s:%i: Port out of range in option '%s'."
#define CONF_LOG_ERR_TOOMANYCHARS	"[CONFIG] %s:%i: Option '%s' must not need exceed %i characters.\n"
#define CONF_LOG_ERR_MUSTBEBOOL		"[CONFIG] %s:%i: Value in option '%s' must be 0 or 1.\n"
#define CONF_LOG_ERR_INT			"[CONFIG] %s:%i: Value in option '%s' must be between %i and %i.\n"
#define CONG_MSG_SOP_SECTION		"the 'Sop' section\n\n"
#define CONG_MSG_AOP_SECTION		"the 'Aop' section\n\n"
#define CONG_MSG_HOP_SECTION		"the 'Hop' section\n\n"
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
#define NS_RPL_HLP					"For more help, type /msg %s \2HELP %s %s\2."
#define NS_ERR_HLP_USAGE			"/msg %s \2HELP\2 <Command> <Subcommand>"
#define NS_RPL_HLP_SHORT			"For more help, type /msg %s \2HELP %s\2."
#define NS_RPL_HLP_MAIN				"For help on commands, type /msg %s \2HELP\2."
#define NS_RPL_LISTFOUND1			"Listing Complete - \2%i\2 entry found."
#define NS_RPL_LISTFOUND2			"Listing Complete - \2%i\2 entries found."
#define NS_RPL_NEEDIDENTIFY			"Please identify for the nickname \2%s\2 to use this function."
#define NS_ERR_NEEDMOREPRIVS		"Permission denied - You don't have the required privileges."
#define NS_ERR_NOSUCHCMD			"Unknown command: \2%s\2."
#define NS_ERR_NOSUCHUSER			"No such user online: \"%s\"."
#define NS_ERR_NOTREG				"The nickname \2%s\2 is not registered."
#define NS_RPL_PLZ_IDENTIFY0		"This nickname belongs to someone else"
#define NS_RPL_PLZ_IDENTIFY1		"If this is your nickname, please identify using /%s IDENTIFY <password>"
#define NS_RPL_PLZ_IDENTIFY2		"You have\2 60 Seconds\2 to identify before your nickname is changed"
#define NS_RPL_PLZ_IDENTIFY3		"This nickname has the 'aggressive proction' enabled."
#define NS_RPL_PLZ_IDENTIFY4		"You won't be able to use the nickname unless you identify using /%s IDENTIFY <password>"
#define NS_RPL_PLZ_30SECSLEFT		"You have\2 30 Seconds\2 left to identify before your nickname is changed"
#define NS_RPL_PLZ_NOTIMELEFT		"Time's up. Your nickname is now being changed. If this is your nickname, please identify."
#define NS_ERR_TOOMANYPASS			"Too many wrong passwords. Please try again later."

/* Access
 ******************************************************************************************************************************************
 */

#define NS_RPL_ACC_1ENTRYREMOVED	"1 entry removed."
#define NS_RPL_ACC_ADDSUCCESS		"The mask \2%s\2 has been added to your access list."
#define NS_RPL_ACC_ADDSUCCESS2		"The mask \2%s\2 has been added to the access list of \2%s\2."
#define NS_RPL_ACC_DELSUCCESS		"The mask \2%s\2 has been deleted from your access list."
#define NS_RPL_ACC_DELSUCCESS2		"The mask \2%s\2 has been deleted from the access list of \2%s\2."
#define NS_ERR_ACC_USAGE			"Usage: \2ACCESS\2 <command> [arguments]"
#define NS_ERR_ACC_MASKEXISTS		"The mask \2%s\2 already is in your access list."
#define NS_ERR_ACC_MASKEXISTS2		"The mask \2%s\2 already is in the access list of \2%s\2."
#define NS_ERR_ACC_MASKFORMAT		"Mask must be in format <user@host>"
#define NS_ERR_ACC_MASKFORMAT2		"Please use a more secure mask. \2%s\2 matches all users"
#define NS_ERR_ACC_MASKNOTFOUND		"The mask \2%s\2 was not found in your access list"
#define NS_ERR_ACC_MASKNOTFOUND2	"The mask \2%s\2 was not found in the access list of \2%s\2"
#define NS_RPL_ACC_LEVEL0			"%s - 0 - No Access."
#define NS_RPL_ACC_LEVEL1			"%s - 1 - Matches an entry in the nickname's access list."
#define NS_RPL_ACC_LEVEL2			"%s - 2 - User has identified for this nickname."  
#define NS_RPL_ACC_LIST				"The nickname \2%s\2 has the following access entries:"
#define NS_RPL_ACC_LISTFOUND1		"Listing Complete - \2%i\2 entry found"
#define NS_RPL_ACC_LISTFOUND2		"Listing Complete - \2%i\2 entries found"
#define NS_RPL_ACC_LISTENTRIES		"\2%i\2 - \2%s\2"
#define NS_ERR_ATH_LISTUSAGE		"Usage: \2AUTH LIST\2."
#define NS_RPL_ACC_WIPESUCCESS		"Your access list has been wiped."
#define NS_RPL_ACC_WIPESUCCESS2		"The access list of \2%s\2 has been wiped."
#define NS_RPL_ACC_NENTRIESREMOVED	"%i entries removed."
#define NS_RPL_ACC_NOENTRIES		"You don't have any access list entries."
#define NS_RPL_ACC_NOENTRIES2		"The nickname \2%s\2 doesn't have any access list entries."

/* AUTH
 ******************************************************************************************************************************************
 */

#define NS_RPL_ATH_ACCEPTED			"You have accepted the authorization request No \2%i\2."
#define NS_ERR_ATH_ACCEPTUSAGE		"Usage: \2AUTH ACCEPT\2 <number>."
#define NS_RPL_ATH_ALREADYINLIST	"You already sent such a request to \2%s\2."
#define NS_RPL_ATH_DECLINED			"You have declined the authorization request No \2%i\2."
#define NS_ERR_ATH_DECLINEUSAGE		"Usage: \2AUTH DECLINE\2 <number>."
#define NS_ERR_ATH_ISNONUM			"The supplied value is not a number."
#define NS_ERR_ATH_NUMTOOBIG		"No authorization request with number %i found."
#define NS_RPL_ATH_HASACCEPTED_NFY	"\2%s\2 has accepted your request to add them to your notify list"
#define NS_RPL_ATH_HASACCEPTED_CHN	"\2%s\2 has accepted your request to add them to the \2%s\2 list of \2%s\2"
#define NS_RPL_ATH_PENDING			"You have the following pending requests:"
#define NS_RPL_ATH_NOENTRIES		"You have no pending requests."
#define NS_RPL_ATH_OPEN				"You have pending authorization requests"
#define NS_RPL_ATH_READCHAN			"Authorization Request No. \2%i %s  \2%s\2"
#define NS_RPL_ATH_READNOTIFY		"Authorization Request No. \2%i\2 - \2%s\2"
#define NS_ERR_ATH_READUSAGE		"Usage: \2AUTH READ\2 <number>."
#define NS_ERR_ATH_LISTCOMPLETE1	"Listing complete -\2 1 \2match found"
#define NS_ERR_ATH_LISTCOMPLETE2	"Listing complete - \2%i\2 matches found"
#define NS_ERR_ATH_USAGE			"Usage: \2AUTH <ACCEPT|DECLINE|READ|LIST> [#]."
#define NS_RPL_ATH_TEXT_NOTIFY		"\2%s\2 wants to add you to his/her notify list."
#define NS_RPL_ATH_TEXT_CHAN		"\2%s\2 wants to add you to the \2%S\2 list of \2%s\2"
#define NS_RPL_ATH_XOP_READ			"Authorization request no \2%s\2 - \2%s\2 wants to add you to the \2%s\2 list of \2%s\2"
#define NS_RPL_ATH_TEXT7			"\2%s\2 wants you to be the \2Successor\2 of %s"
#define NS_RPL_ATH_TEXT8			"\2%s\2 wants you to be the \2Founder\2 of %s"
#define NS_RPL_ATH_REQUESTLIST		"\2%i\2 - Request from \2%s\2"

/* ACC
 ******************************************************************************************************************************************
 */
#define NS_ERR_CACC_USAGE			"Usage: \2ACC\2 <Nickname>"

/* DROP
 ******************************************************************************************************************************************
 */
#define NS_RPL_DRP_SUCCESS			"The nickname \2%s\2 has been dropped."
#define NS_ERR_DRP_USAGE			"Usage: \2DROP\2 <nickname>"

/* GETPASS
 ******************************************************************************************************************************************
 */

#define NS_LOG_GETPASS_USED			"%s: GETPASS command used by: %s for the nickname %s"
#define NS_CTP_GETPASS_USED			"GETPASS command used by: \2%s\2 for the nickname \2%s\2"
#define NS_RPL_GPASS_LOGGED			"This command has been logged."
#define NS_RPL_GPASS_SUCCESS		"The Password for the Nickname \2%s\2 is: %s."
#define NS_ERR_GPASS_USAGE			"Usage: \2GETPASS\2 <nickname>."

/* GHOST
 ******************************************************************************************************************************************
 */
#define NS_RPL_GHT_GHOSTDISCONN		"You ghost has been disconnected."
#define NS_RPL_GHT_NEEDRELEASE		"To release this nickname, please use /msg %s \2RELEASE\2."
#define NS_ERR_GHT_NICKISHELD		"The nickname \2%s\2 is currently being held by services."
#define NS_ERR_GHT_USAGE			"Usage: \2GHOST\2 <Nickname> [Password]"

/* HELP
 ******************************************************************************************************************************************
 */

#define NS_HELP_PATH			"docs/help/en/nickserv"



/* IDENTIFY
 ******************************************************************************************************************************************
 */
#define NS_RPL_IDF_ALREADYIDF		"You have already identified for the nickname \2%s\2."
#define NS_RPL_IDF_PASSACCEPTED		"Password accepted - You are now identified"
#define NS_RPL_IDF_USAGE 			"Usage: \2IDENTIFY\2 <Password>"
#define NS_ERR_IDF_WRONGPASS		"Incorrect password for the Nickname \2%s\2"
/* INFO
 ******************************************************************************************************************************************
 */
#define NS_RPL_INF_AUTHCHAN			"Authorization is required before adding this user to channel access lists."
#define NS_RPL_INF_AUTHNOTIFY		"Authorization is required before adding this user to notify lists."
#define NS_RPL_INF_EMAIL			"E-Mail Address		: %s."
#define NS_RPL_INF_HEAD1			"\2%s\2 (currently online) is \2%s\2."
#define NS_RPL_INF_HEAD2			"\2%s\2 is \2%s\2."
#define NS_RPL_INF_LASTADDR			"Last seen address	: %s"
#define NS_RPL_INF_LASTSEEN			"Last seen time		: %s"
#define NS_RPL_INF_MFORWARD			"Memos to this user are forwarded to \2%s\2."
#define NS_RPL_INF_NOMEMO			"This user is not accepting memos."
#define NS_RPL_INF_NOOP				"This user will not automatically opped by %s."
#define NS_RPL_INF_PROTECT1			"This user has 'normal' protection enabled."
#define NS_RPL_INF_PROTECT2			"This user has 'agressive' protection enabled."
#define NS_RPL_INF_TIMEREG			"Time registered	: %s."
#define NS_RPL_INF_TIMENOW			"Time now			: %s."
#define NS_ERR_INF_USAGE			"USAGE: \2INFO\2 <Nickname>"

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
#define NS_RPL_NFY_1ENTRYREMOVED	"1 entry removed."
#define NS_RPL_NFY_ALREADYINLIST	"The nickname \2%s\2 is already in your notify list."
#define NS_RPL_NFY_ISNOWOFFLINE		"\2%s\2 has gone offline."
#define NS_RPL_NFY_ISNOWONLINE		"\2%s\2 is now online!"
#define NS_RPL_NFY_LIST				"Notify list of \2%s\2:"
#define NS_RPL_NFY_LISTENTRIES		"\2%i\2 - \2%s\2"
#define NS_RPL_NFY_LIST_COMPLETE_1	"Listing complete - \21\2 entry found"
#define NS_RPL_NFY_LIST_COMPLETE	"Listing complete - \2%i\2 entries found"
#define NS_ERR_NFY_MUSTBEREG		"You need to have a registered nickname to add someone to your notify list."
#define NS_ERR_NFY_MUSTBEREG2		"You can only add registered nicknames to your notify list."
#define NS_RPL_NFY_NENTRIESREMOVED	"%i entries removed."
#define NS_RPL_NFY_NICKADDED		"The nickname \2%s\2 has been added to your notify list."
#define NS_RPL_NFY_NICKDELETED		"The nickname \2%s\2 has been deleted from your notify list."
#define NS_ERR_NFY_NICKNOTFOUND		"The nickname \2%s\2 was not found in your notify list."
#define NS_RPL_NFY_NOENTRIES		"You don't have any notify entries"
#define NS_RPL_NFY_NOENTRIES2		"The nickname \2%s\2 does not have any notify entries."
#define NS_RPL_NFY_REQUESTSENT1		"The nickname \2%s\2 has authorization for notify lists enabled."
#define NS_RPL_NFY_REQUESTSENT2		"Your request to add \2%s\2 has been sent."
#define NS_RPL_NFY_REQUESTSENT3		"Once \2%s\2 approved your request, they will be on your notify list."
#define NS_ERR_NFY_SAMEASSRC		"You cannot add yourself to the notify list."
#define NS_ERR_NFY_USAGE			"Usage: \2NOTIFY ADD\2 <add|del|list|wipe> [nickname]."
#define NS_RPL_NFY_WIPESUCCESS		"Your notify list has been wiped."

/* REGISTER
 ******************************************************************************************************************************************
 */
#define NS_ERR_REG_ALREADYREG		"The nickname \2%s\2 is already registered"
#define NS_ERR_REG_DELAY			"Please wait another %i seconds before registering another nickname."
#define NS_ERR_REG_GENERALERROR		"Sorry, an unknown error occured. Please try again later."
#define NS_ERR_REG_INVALDEMAIL		"Invalid E-Mail Address"
#define NS_ERR_REG_PASSSAMEASNICK	"The password must not be the same as your nickname. Please use a more obscure password"
#define NS_ERR_REG_PASSTOOSHORT		"Password too short. Your password should be at least 5 characters long"
#define NS_ERR_REG_PRIVS			"Permission denied. You need to be \2%s\2 to register a Nickname" 
#define NS_RPL_REG_SUCCESS1			"Your nickname \2%s\2 has been successfully registered to you."
#define NS_RPL_REG_SUCCESS2			"Your password is \2%s\2. Remember it for further use."
#define NS_RPL_REG_SUCCESS3			"The mask \2%s\2 has automatically been added to your access list."
#define NS_RPL_REG_USAGE 			"Usage: \2REGISTER\2 <Password> <E-Mail Address>"
#define NS_RPL_REL_NICKRELEASED		"The nickname \2%s\2 has been released from custody."
#define NS_ERR_REL_USAGE			"Usage: \2RELEASE\2 <Nickname> [Password]."
#define NS_ERR_REL_NICKNOTHELD		"The Nickname \2%s\2 is not being held by services"

/* SET
 ******************************************************************************************************************************************
 */
#define NS_RPL_SET_AUTH_SUCCESS1	"Success - Authorization is now required before anyone can add you to channel access lists."
#define NS_RPL_SET_AUTH_SUCCESS2	"Success - Authorization was already required before anyone can add you to channel access lists."
#define NS_RPL_SET_AUTH_SUCCESS3	"Success - Authorization is no longer required before anyone can add you to channel access lists."
#define NS_RPL_SET_AUTH_SUCCESS4	"Success - Channel Authorization was already turned off."
#define NS_RPL_SET_AUTH_SUCCESS5	"Success - Authorization is now required before anyone can add you to notify lists."
#define NS_RPL_SET_AUTH_SUCCESS6	"Success - Authorization was already required before anyone can add you to notify lists."
#define NS_RPL_SET_AUTH_SUCCESS7	"Success - Authorization is no longer required before anyone can add you to notify lists."
#define NS_RPL_SET_AUTH_SUCCESS8	"Success - Notify Authorization was already turned off."
#define NS_ERR_SET_AUTH_USAGE		"Usage: \2SET AUTHORIZE\2 <chan|notify> <on|off>"
#define NS_ERR_SET_USAGE			"Usage: \2SET\2 <Command> <Parameters>."
#define NS_ERR_SET_EMAIL_USAGE		"Usage: \2SET EMAIL\2 <E-Mail Address>."
#define NS_RPL_SET_EMAILSUCCESS		"Success - \2%s\2 has been set as your e-mail address."
#define NS_ERR_SET_HIDEEMAIL_USAGE	"Usage: \2SET HIDEEMAIL <on|off>\2"
#define NS_RPL_SET_HMAIL_SUCCESS1 	"Success - Your e-mail address will be hidden."
#define NS_RPL_SET_HMAIL_SUCCESS2 	"Success - Your e-mail address will now be unhidden." 
#define NS_RPL_SET_MFWD_ON			"Success - All your memos will be forwarded to the nickname \2%s\2."
#define NS_RPL_SET_MFWD_OFF			"Success - Memos are not  being forwarded anymore." 
#define NS_ERR_SET_MFWD_USAGE		"Usage: \2SET MFORWARD\2 <[Nickname]|OFF>."
#define NS_ERR_SET_MFWD_SELF		"Error - You cannot set memo forwarding to yourself."
#define NS_RPL_SET_MFY_SUCCESS		"Success - You will no longer be notified about new memos on logon."
#define NS_RPL_SET_MFY_SUCCESS2		"Success - You will be notified about new memos on logon." 
#define NS_ERR_SET_MFY_USAGE		"Usage: \2SET MNOTIFY\2 <on|off>."
#define NS_RPL_SET_MLOCKSUCCESS		"Success - Modes are locked to \2%s\2."
#define NS_ERR_SET_MLOCK_USAGE		"Usage: \2SET MLOCK\2 <+|-> [modes]."
#define NS_RPL_SET_NOMEMO_SUCCESS	"Success - Your memos will be delivered to you."
#define NS_RPL_SET_NOMEMO_SUCCESS2	"Success - You will no longer receive memos."
#define NS_ERR_SET_NOMEMO_USAGE		"Usage: \2SET NOMEMO\2 <on|off>."
#define NS_RPL_SET_NOMEMO_HLP		"For more help, type /msg %s \2HELP SET NOMEMO\2." 
#define NS_RPL_SET_NOOP_SUCCESS		"Success - Automatic opping has been disabled." 
#define NS_RPL_SET_NOOP_SUCCESS2	"Success - Automatic opping was already disabled."
#define NS_RPL_SET_NOOP_SUCCESS3	"Success - Automatic opping has been enabled."
#define NS_RPL_SET_NOOP_SUCCESS4	"Success - Automatic opping was already enabled."	
#define NS_ERR_SET_NOOP_USAGE		"Usage: \2SET NOOP\2 <on|off>"
#define NS_ERR_SET_PASS_USAGE		"Usage: \2SET PASSWORD\2 <New Password>."
#define NS_RPL_SET_PASS_SUCCESS		"Success - Your new password is \2%s\2 - remember it for further use."
#define NS_RPL_SET_PROTECT_SUCCESS	"Success - Nickname Protection disabled" 
#define NS_RPL_SET_PROTECT_SUCCESS2	"Success - Nickname Protection was already disabled."
#define NS_RPL_SET_PROTECT_SUCCESS3	"Success - Normal Nickname Protection enabled."
#define NS_RPL_SET_PROTECT_SUCCESS4	"Success - Normal Nickname Protection was already enabled."
#define NS_RPL_SET_PROTECT_SUCCESS5	"Success - Agressive Nickname Protection enabled."
#define NS_RPL_SET_PROTECT_SUCCESS6	"Success - Agressive Nickname Protection was already enabled."
#define NS_ERR_SET_PROTECT_USAGE	"Usage: \2SET PROTECT\2 <OFF|NORMAL|HIGH>"
#define NS_RPL_SET_URL_SUCCESS		"Success - Your URL has been set to \2%s\2."
#define NS_ERR_SET_URL_USAGE		"Usage: \2SET URL\2 <url>."

/* SETPASS
 ******************************************************************************************************************************************
 */
#define NS_LOG_SETPASS_USED			"%s: SETPASS command used by: %s for the nickname %s"
#define NS_CTP_SETPASS_USED			"SETPASS command used by: \2%s\2 for the nickname \2%s\2"
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

/* ACC
 ******************************************************************************************************************************************
 */
#define CS_ERR_ACC_USAGE			"Usage: \2ACC\2 <#channel> <nickname>"
#define CS_RPL_ACC_HLP				"For more help, type /msg %s \2HELP ACC\2"
#define CS_RPL_ACC_NOACC			"The user \2%s\2 has no access to channel \2%s\2"
#define CS_RPL_ACC_IRCOP			"%s: This is an \2%s\2 and thus has full access to the channel \2%s\2"
#define CS_RPL_ACC_XOP				"%s: has identified or matches an access entry for the nickname \2%s\2 who has \2%s\2 access to \2%s\2"
#define CS_RPL_ACC_IDENTIFIED		"%s: has full founder access because they identified for the channel \2%s\2"
#define CS_RPL_ACC_SUCCFND_ACC		"%s: has restricted founder access because they match an entry in the access list of \2%s\2 who is the \2%s\2 of \2%s\2"
#define CS_RPL_ACC_SUCCFND			"%s: has identified for the nickname \2%s\2 who is the \2%s\2 of \2%s\2"
#define CS_RPL_ACC_NOACCESS			"\2%s\2 has no access to \2%s\2."
#define CS_ERR_ACCCMD_USAGE			"Usage: \2%s\2 ACC [#channel] \2[nickname]\2"
#define CS_ERR_ALREADYREG			"The Channel \2%s\2 is already registered."

/* AKICK
 ******************************************************************************************************************************************
 */
#define CS_ERR_AKICK_ALREADYONLIST	"The mask \2%s\2 already is on the \2Akick\2 list of \2%s\2"
#define CS_ERR_AKICK_USAGE			"Usage: \2AKICK\2 [#channel] \2<add|del|list|wipe> [reason]\2"
#define CS_RPL_AKICK_KICKREASON		"Your mask has been added to the AKICK list (%s)"
#define CS_ERR_AKICK_ADD_NOSENSE	"The mask \2%s\2 doesn't make any sense."
#define CS_ERR_AKICK_ADD_USAGE		"Usage: \2AKICK\2 [#channel] \2ADD [mask] [reason]\2"
#define CS_ERR_AKICK_DEL_USAGE		"Usage: \2AKICK\2 [#channel] \2DEL [mask]\2"
#define CS_RPL_AKICK_LIST			"\2%i\2 - \2%s\2 (Added by %s:%s on %s) (%s)"
#define CS_RPL_AKICK_LIST2			"\2%i\2 - \2%s\2 (Added by %s:%s on %s)"

/* DROP
 ******************************************************************************************************************************************
 */
#define CS_RPL_DRP_SUCCESS			"The Channel \2%s\2 has been dropped"

/* GETPASS
 ******************************************************************************************************************************************
 */
#define CS_LOG_GETPASS_USED			"%s: GETPASS command used by: %s for the channel %s"
#define CS_CTP_GETPASS_USED			"GETPASS command used by: \2%s\2 for the channel \2%s\2"
#define CS_RPL_GPASS_SUCCESS		"The Password for the channel \2%s\2 is: %s."
#define CS_ERR_GPASS_USAGE			"Usage: \2GETPASS\2 <channel>."


/* INFO
 ******************************************************************************************************************************************
 */
#define CS_HELP_PATH			"docs/help/en/chanserv"

/* INFO
 ******************************************************************************************************************************************
 */

#define CS_ERR_INF_USAGE			"Usage: \2INFO\2 <channel>"
#define CS_RPL_INF_ENTRY1			"\2%s\2 is \2%s\2"
#define CS_RPL_INF_ENTRY2			"Founder: \2%s\2"
#define CS_RPL_INF_ENTRY3			"Successor: \2%s\2"
#define CS_RPL_INF_ENTRY4			"Last Topic is: %s"
#define CS_RPL_INF_ENTRY5			"Time registered: %s"
#define CS_RPL_INF_ENTRY6			"Time now		: %s"
#define CS_RPL_INF_ENTRY7			"ModeLock: %s"
#define CS_RPL_INF_ENTRY8			"Options: %s"
#define CS_RPL_INF_ENTRY9			"MemoLevel: %s"

/* INVITE
 ******************************************************************************************************************************************
 */
#define CS_ERR_INV_USAGE			"Usage: \2INVITE\2 <channel> [Nickname]"
#define CS_ERR_INV_ALREADYONCHAN	"\2%s\2 already is on channel \2%s\2"
#define CS_ERR_INV_ALREADYONCHAN2	"You already are on channel \2%s\2"
#define CS_RPL_HLP					"For more help, type /msg %s \2HELP %s\2"

/* IDENTIFY
 ******************************************************************************************************************************************
 */
#define CS_RPL_IDF_ALREADYIDF		"You have already identified for the channel \2%s\2"
#define CS_RPL_IDF_PASSACCEPTED		"Password accepted - You are now identified for channel \2%s\2"
#define CS_ERR_IDF_USAGE			"Usage: \2IDENTIFY\2 [#channel] \2[password]\2"
#define CS_ERR_IDF_WRONGPASS		"Password incorrect for channel \2%s\2"

/* LIST
 ******************************************************************************************************************************************
 */
#define CS_RPL_LIST_BEGIN			"Listing all registered channels matching the pattern  \2\"%s\"\2"
#define CS_RPL_LIST_ENTRY			"\2%i\2 - \2%s\2 (Founder: %s)"
#define CS_RPL_LIST_END1			"Listing complete - %i matches found"
#define CS_RPL_LIST_END2			"Listing complete - 1 match found"
#define CS_ERR_LIST_USAGE			"Usage: \2LIST\2 [Pattern]>."

/* MDEOP
 ******************************************************************************************************************************************
 */
#define CS_ERR_MDEOP_USAGE			"Usage: \2MDEOP\2 [#channel]"


/* MKICK
 ******************************************************************************************************************************************
 */
#define CS_ERR_MKICK_USAGE			"Usage: \2MKICK\2 [#channel] \2[reason]\2"
#define CS_RPL_MKICK_NOUSERS		"There a no users on channel \2%s\2"
#define CS_RPL_MKICK_USED_BY		"MKICK Command used by %s"

/* OP
 ******************************************************************************************************************************************
 */
#define CS_ERR_OP_USAGE				"Usage: \2OP\2 [#channel] \2[nickname]\2"

/* SET
 ******************************************************************************************************************************************
 */
#define CS_ERR_SET_FOUNDER_REG		"Only a registiered Nickname can be founder of a channel"
#define CS_ERR_SET_SUCC_REG			"Only a registiered Nickname can be successor of a channel"
#define CS_RPL_SET_FOUNDER_SUCCESS	"The founder of \2%s\2 was changed to \2%s\2"
#define CS_RPL_SET_SUCC_SUCCESS		"The successor of \2%s\2 was changed to \2%s\2"
#define CS_RPL_SET_PASS_SUCCESS		"The password of \2%s\2 was changed to \2%s\2"
#define CS_RPL_SET_TOPICLOCK_SUCCESS "Topiclock for \2%s\2 is now set to \2%s\2"
#define CS_RPL_SET_TOPICLOCK_DISABLE "Topiclock for \2%s\2 is now disabled"
#define CS_RPL_SET_MLOCK_SUCCESS 	"Modelock for \2%s\2 has been changed to \2%s\2"
#define CS_RPL_SET_MEMOLEVEL_SUCCESS "Memolevel for \2%s\2 was changed to \2%s\2"
#define CS_RPL_SET_BOT_SUCCESS		"Bot for \2%s\2 is now set to \2%s\2"
#define CS_RPL_SET_OPWATCH_ENABLE	"Opwatch for \2%s\2 is now enabled"
#define CS_RPL_SET_OPWATCH_DISABLE	"Opwatch for \2%s\2 is now disabled"
#define CS_RPL_SET_LEAVEOPS_ENABLE	"Leaveops for \2%s\2 is now enabled"
#define CS_RPL_SET_LEAVEOPS_DISABLE	"Leaveops for \2%s\2 is now disabled"
#define CS_RPL_SET_KEEPTOPIC_ENABLE	"Keeptopic for \2%s\2 is now enabled"
#define CS_RPL_SET_KEEPTOPIC_DISABLE "Keeptopic for \2%s\2 is now disabled"
#define CS_RPL_SET_RESTRICTED_ENABLE "Access to \2%s\2 is now restricted"
#define CS_RPL_SET_RESTRICTED_DISABLE "Access to \2%s\2 is no longer restricted"
#define CS_ERR_SET_USAGE			"Usage: \2SET\2 [#channel] <command> <parameters>"
#define CS_ERR_SET_RESTRICTED_USAGE "Usage: \2SET\2 [#channel] \2RESTRICTED\2 <on|off>"
#define CS_ERR_SET_BOT_USAGE 		"Usage: \2SET\2 [#channel] \2BOT\2 <Botname>"
#define CS_ERR_SET_OPWATCH_USAGE 	"Usage: \2SET\2 [#channel] \2OPWATCH\2 <on|off>"
#define CS_ERR_SET_LEAVEOPS_USAGE 	"Usage: \2SET\2 [#channel] \2LEAVEOPS\2 <on|off>"
#define CS_ERR_SET_KEEPTOPIC_USAGE 	"Usage: \2SET\2 [#channel] \2KEEPTOPIC\2 <on|off>"
#define CS_ERR_SET_FOUNDER_USAGE 	"Usage: \2SET\2 [#channel] \2FOUNDER\2 <Nickname>"
#define CS_ERR_SET_SUCCESSOR_USAGE 	"Usage: \2SET\2 [#channel] \2FOUNDER\2 <Nickname>"
#define CS_ERR_SET_MLOCK_USAGE 		"Usage: \2SET\2 [#channel] \2MLOCK\2 <+|-> [Modes]"
#define CS_ERR_SET_TOPICLOCK_USAGE 	"Usage: \2SET\2 [#channel] \2TOPICLOCK\2 [Level|Off]"
#define CS_ERR_SET_MEMOLEVEL_USAGE 	"Usage: \2SET\2 [#channel] \2MEMOLEVEL\2 [Level]"
#define CS_ERR_SET_PASSWORD_USAGE 	"Usage: \2SET\2 [#channel] \2PASSWORD\2 [Password]"
#define CS_ERR_SET_BOT_NOSUCHBOT	"The bot \2%s\2 was not found"
#define CS_RPL_SET_BOT_BOTADDED		"The bot \2%s\2 will now join channel \2%s\2"
#define CS_ERR_SET_BOT_NOBOT		"There is no bot on channel \2%s\2"
#define CS_RPL_SET_BOT_BOTREMOVED	"Success - Bot removed from Channel \2%s\2"
#define CS_RPL_SET_BOT_ALREADY		"Bot \2%s\2 already is on channel \2%s\2"

/* SETPASS
 ******************************************************************************************************************************************
 */
#define CS_LOG_SETPASS_USED			"%s: SETPASS command used by: %s for the channel %s"
#define CS_CTP_SETPASS_USED			"SETPASS command used by: \2%s\2 for the channel \2%s\2"
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
#define CS_RPL_XOP_AUTH_REQUIRED	"\2%s\2 has authorization enabled for channel access list. "
#define CS_RPL_XOP_AUTH_SENT_XOP	"\2%s\2 will receive a notification about your request to add them to the \2%s\2 list of \2%s\2."
#define CS_RPL_XOP_AUTH_SENT_SF		"\2%s\2 will receive a notification about your request to set them as the \2%s\2 of \2%s\2."
#define CS_RPL_XOP_AUTH_SENT_END	"Once the request has been approved, \2%s\2 will be automatically entered."
#define CS_RPL_ATH_ALREADYSENT		"As request like this has already been sent to \2%s\2"
#define CS_RPL_XOP_ADDED			"\2%s\2 has been added the \2%s\2 List of \2%s\2"
#define CS_RPL_XOP_MOVED			"\2%s\2 has been moved from the \2%s\2 to the \2%s\2 list of \2%s\2."
#define CS_ERR_XOP_ALREADYONLIST	"\2%s\2 is already on the \2%s\2 list of \2%s\2"
#define CS_ERR_XOP_ALREADYONHIGHER	"\2%s\2 already has a higher access to \2%s\2"
#define CS_ERR_XOP_NICKISFOUNDER	"\2%s\2 is already the founder of the channel \2%s\2"
#define CS_ERR_XOP_FOUNDERCANNOTADD "\2%s\2 is the founder of the channel \2%s\2 and cannot be added to its \2%s\2 list"
#define CS_ERR_XOP_SUCCCANNOTADD 	"\2%s\2 is the successor of the channel \2%s\2 and cannot be added to its \2%s\2 list"
#define CS_ERR_XOP_NICKISSUCCESSOR	"\2%s\2 is already the successor of the channel \2%s\2"
#define CS_RPL_XOP_DISABLED			"The \2%s\2 list of \2%s\2 is currently disabled."
#define CS_RPL_XOP_LIST_BEGIN		"This is the \2%s\2 list of \2%s\2"
#define CS_RPL_XOP_LIST				"\2%i\2 - \2%s\2 (Added by %s:%s on %s)"
#define CS_RPL_XOP_LIST_COMPLETE1	"Listing complete - \2%i\2 matches found"
#define CS_RPL_XOP_LIST_COMPLETE2	"Listing complete - 1 match found"
#define CS_RPL_XOP_DELETED			"\2%s\2 has been removed from the \2%s\2 list of \2%s\2"
#define CS_RPL_XOP_WIPED1			"The \2%s\2 list of \2%s\2 has been wiped - 1 entry removed."
#define CS_RPL_XOP_WIPED2			"The \2%s\2 list of \2%s\2 has been wiped - %i entries removed."
#define CS_ERR_XOP_NOTONLIST		"\2%s\2 is not on the \2%s\2 list of \2%s\2"
#define CS_ERR_XOP_USAGE			"Usage: \2%s\2 <Channel> [ADD|DEL|LIST|WIPE|ENABLE|DISABLE]"

/* REGISTER
 ******************************************************************************************************************************************
 */
#define CS_ERR_REG_DELAY			"Please wait another %i seconds before registering another channel."
#define CS_ERR_AOP_GENERALERROR		"Sorry, a general error has occured. Please try again later."
#define CS_ERR_REG_GENERALERROR		"A general error has occured. Please try again later."
#define CS_RPL_REG_HLP				"For more help, type /msg %s \2HELP REGISTER\2"
#define CS_ERR_XOP_LIMIT			"The Limit of \2%i\2 entries in the \2%s\2 list of \2%s\2 has already been reached."
#define CS_ERR_REG_NEEDTOBEONCHAN	"You must be on the channel \2%s\2 to register it."
#define CS_ERR_REG_NEEDTOBEOP		"You must be an Operator (+o) on \2%s\2 to register a channel."
#define CS_ERR_REG_PASSSAMEASCHAN	"The password must not be the same as the channel name."
#define CS_ERR_REG_PASSSAMEASFND	"The password must not be the same as the founder's nickname."
#define CS_ERR_REG_PRIVS			"Permission denied. You need to be \2%s\2 to register a Channel"
#define CS_RPL_REG_SUCCESS1			"The channel \2%s\2 has been registered to you."
#define CS_RPL_REG_SUCCESS2			"The password is \2%s\2 - Remember it for further use."
#define CS_RPL_REG_SUCCESS3			"The mask \2%s\2 was automatically added to the channel access list."
#define CS_RPL_REG_USAGE			"Usage: \2REGISTER\2 <Password> <Channel Description>"
#define CS_RPL_XOP_USAGE			"Usage: \2%s\2 %s"
#define CS_ERR_XOP_HIGHERACCESS		"Permission denied. You need \2%s\2 Access or higher."
#define CS_ERR_XOP_HIGHERACCESS2	"Sorry, \2%s\2 does not have the required privileges."
#define CS_RPL_XOP_REQUESTSENT1		"The nickname \2%s\2 has authorization for channel lists enabled."
#define CS_RPL_XOP_REQUESTSENT2		"Your request to add \2%s\2 has been sent."
#define CS_RPL_XOP_REQUESTSENT3		"Once \2%s\2 approved your request, they will be added to the \2%s\2 list of \2%s\2."
#define CS_RPL_XOP_REQUESTSENT4		"Once \2%s\2 approved your request, they will be set as the \2%s\2 of \2%s\2."


/* Botserv Messages
 ******************************************************************************************************************************************
 */
#define BS_ERR_INVALIDNICKNAME		"%s: Invalid Nickname"
#define BS_ERR_NEEDMOREPRIVS		"Access denied for that command for %s. You don't have the required privileges."
#define BS_ERR_ADD_USAGE			"Usage: \2ADD\2 <Botname> [Password]"
#define BS_ERR_ADD_EXISTS			"A bot with the name \2%s\2 already exists"
#define BS_ERR_ADD_INVALIDCHARS		"Invalid characters - Please use Nickname-only characters"
#define BS_RPL_ADD_SUCCESS1			"The bot \2%s\2 has been added."
#define BS_RPL_ADD_SUCCESS2			"The password is \2%s\2 - remember it for further use."
#define BS_RPL_ADD_SUCCESS3			"To customize your bot, please use the command \2SET USERNAME\2 or \2SET REALNAME\2"
#define BS_ERR_NOTFOUND				"The Bot \2%s\2 does not exist"
#define BS_RPL_DEL_SUCCESS			"The Bot \2%s\2 has been deleted"
#define BS_ERR_PASSTOOSHORT			"Please use at least 5 characters for your password"
#define BS_ERR_PASSSAMEASNICK		"Your bot password must be the same as your bot name - Please use a more obscure password"
#define BS_ERR_DEL_USAGE			"Usage: \2DEL\2 <Botname>"
#define BS_ERR_INFO_USAGE			"Usage: \2INFO\2 <Botname>"
#define BS_RPL_INF_HEAD				"\2%s\2 is \2%s\2."
#define BS_RPL_INF_CHANS			"\2%s\2 is on the following Channels: %s"
#define BS_RPL_INF_END				"End of Bot Info"

#define BS_ERR_KICK_BOT				"You cannot kick \2%s\2 because this is a bot."
#define BS_ERR_LIST_USAGE			"Usage: \2LIST\2"
#define BS_RPL_LIST_BEGIN			"The following Bot are registered with Botserv"
#define BS_RPL_LIST_ENTRY			"%i - \2%s\2 (%s@%s) (%s)"
#define BS_RPL_LIST_COMPLETE1		"Listing complete - 1 match found"
#define BS_RPL_LIST_COMPLETE2		"Listing complete - %i matches found"
#define BS_ERR_CHAN_ADD_USAGE		"Usage: \2CHAN\2 <Botname> \2ADD\2 <Channel>"
#define BS_ERR_CHAN_DEL_USAGE		"Usage: \2CHAN\2 <Botname> \2DEL\2 <Channel>"
#define BS_ERR_CHAN_LIST_USAGE		"Usage: \2CHAN\2 <Botname> \2LIST\2"
#define BS_ERR_OP_USAGE				"Usage: \2OP\2 <Botname> <Channel> <Nickname>"
#define BS_ERR_OP_NOT_ON_CHAN		"Bot \2%s\2 is not on channel \2%s\2"
#define BS_ERR_ACCESSDENIED			"Access denied for that function of bot \2%s\2. Please identify using /msg %s IDENTIFY <Botname> <Password>"
#define BS_ERR_SET_USAGE			"Usage: \2SET\2 <Botname> \2SET\2 [NAME|USERNAME|REALNAME|PASSWORD] <Argument>"
#define BS_ERR_SET_OPT_USAGE		"Usage: SET <Botname> \2%s\2 <Arguments>"
#define BS_ERR_IDENTIFY_USAGE		"Usage: IDENTIFY <Botname> \2%s\2 <Password>"
#define BS_ERR_IDENTIFY_WRONGPASS	"Password incorrect for Bot \2%s\2"
#define BS_ERR_IDENTIFY_PASSACC		"Password accepted for Bot \2%s\2"

#define BS_SET_NAME_SUCCESS			"The Name of bot \2%s\2 has been changed to \2%s\2"
#define BS_SET_PASS_SUCCESS			"The Password of bot \2%s\2 has been changed to \2%s\2"
#define BS_SET_USERNAME_SUCCESS		"The Username of bot \2%s\2 has been changed to \2%s\2"
#define BS_SET_REALNAME_SUCCESS		"The Realname of bot \2%s\2 has been changed to \2%s\2"
#define BS_KILL_NAMECHANGE			"Bot is reconnecting due to changed settings. "
#define BS_ERR_SET_USERNAME_USAGE	"Usage: \2SET\2 <Botname> \2USERNAME\2 <Username>"
#define BS_ERR_SET_REALNAME_USAGE	"Usage: \2SET\2 <Botname> \2REALNAME\2 <Realname>"
#define BS_ERR_SET_PASSWORD_USAGE	"Usage: \2SET\2 <Botname> \2PASSWORD\2 <Password>"
#define BS_ERR_RENAME_USAGE			"Usage: \2RENAME\2 <Botname> <New Botname>"
#define BS_RPL_HLP					"For more help, type /msg %s HELP \2%s\2"
#define BS_RPL_PART_MSG				"Channel management by Bot discontinued"
#define BS_ERR_NOSUCHCMD			"Unknown command: SET \2%s\2."

#define OS_RPL_ISNOWHELPOP			"\2%s\2 is now a Help Operator\2"
#define OS_RPL_ISNOWIRCOP			"\2%s\2 is now an \2IRC Operator\2"
#define OS_RPL_ISNOWCOADMIN			"\2%s\2 is now a \2Co Administrator\2"
#define OS_RPL_ISNOWSA				"\2%s\2 is now a \2Services Administrator\2"
#define OS_RPL_ISNOWADMIN			"\2%s\2 is now a \2Server Administrator \2"
#define OS_RPL_ISNOWNETADMIN		"\2%s\2 is now a \2Network Administrator\2"


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
