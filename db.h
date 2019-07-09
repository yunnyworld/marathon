#include <mysql/mysql.h>

#define QUERY_SELECT_AREA_TBL 100
#define QUERY_INSERT_AREA_TBL 200
#define QUERY_DELETE_AREA_TBL 300
#define QUERY_UPDATE_AREA_TBL 400

int db_init();
void db_select(int stmt_id);
void db_insert(int stmt_id);
void db_delete(int stmt_id);
void db_update(int stmt_id);
void db_close();
