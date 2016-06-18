#ifndef DB_DATABASE_H_
#define DB_DATABASE_H_

#include "db/chan_mapping.h"
#include "db/nick_mapping.h"
#include "db/op_mapping.h"

int dbase_query(sqlite3 *db,char *qry);
void db_remove(const char *file,const char *entry);
int ns_reset(void);
void load_database(void);
void install_db(void);
void save_database(void);

#endif /*DB_DATABASE_H_*/
