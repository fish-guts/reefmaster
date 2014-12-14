#ifndef DATABASE_H_
#define DATABASE_H_

int dbase_query(sqlite3 *db,char *qry);
void db_remove(const char *file,const char *entry);
int ns_reset(void);
void db_save_nicks(void);
void db_save_chans(void);
void db_save_ops(void);
void load_database(void);
void install_db(void);

#endif /*DATABASE_H_*/
