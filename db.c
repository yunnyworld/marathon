#include <stdio.h>

#include "db.h"

static MYSQL *connect = NULL;

int db_init()
{
	if( (connect = mysql_init(connect))== NULL) {
		printf("Failed to initiate DB\n");
		return -1;
	}
	
	if( !mysql_real_connect(connect, "localhost", "root", "YourRootPassword", 
								"esports", 0, NULL, 0)) {
 		printf( "Failed to connect to DB (Error: %s)\n",
		mysql_error(connect)); 
		return -1;
	}

	printf("Connected to DB successfuly!\n");

	return 0;
}

void db_select(int stmt_id)
{
	char qbuf[160];
	MYSQL_ROW row;
	MYSQL_RES *res;

	printf("db_select::stmt_id : %d\n", stmt_id);

	// Prepare a DB statement
	switch(stmt_id) {
		case QUERY_SELECT_AREA_TBL:
			sprintf(qbuf, "select * from Area_tbl");
			break;
		default:
			break;
	}

	// MySQL Query
	mysql_query(connect, qbuf);
	res = mysql_store_result(connect);

	// Display Query results
	switch(stmt_id) {
		case QUERY_SELECT_AREA_TBL:
			while( (row=mysql_fetch_row(res)) !=NULL ) {
				printf(":: DB Select %s, %s\n", row[0], row[1]);
			}
			break;
		default:
			break;
	}

	mysql_free_result(res);

	return;
}

void db_insert(int stmt_id)
{
	printf("db_insert::stmt_id : %d\n", stmt_id);

	return;
}

void db_delete(int stmt_id)
{
	printf("db_delete::stmt_id : %d\n", stmt_id);

	return;
}

void db_update(int stmt_id)
{
	printf("db_update::stmt_id : %d\n", stmt_id);

	return;
}

void db_close()
{
	mysql_close(connect);

	return;
}
