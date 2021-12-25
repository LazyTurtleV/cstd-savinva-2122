#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>

MYSQL* _db_connection;

#define SAVE_PCKG_SIZE 9

void init_db()
{
    _db_connection = mysql_init(NULL);
    if (!_db_connection)
    {   
        printf("FAILED TO ESTABLISH MYSQL SERVER CONNECTION: %s", mysql_error(_db_connection));
        return;
    }

    puts("Successfully established mysql server connection");

    if (
        !mysql_real_connect(
            _db_connection, 
            "localhost", 
            "table_daemon", 
            "123GHhTy_F", 
            NULL, 
            0, 
            NULL, 
            0
        )
    )
    {
        printf("FAILED TO ESTABLISH DB CONNECTION: %s", mysql_error(_db_connection));
        return;
    }

    puts("Successfully established db connection");
}

void close_db_conn()
{
    if (_db_connection)
    {
        mysql_close(_db_connection);
    }
}

void save_data(char *_data, size_t _n)
{
    puts("SAVE DATA");

    char msg[512];
    snprintf(msg, 512, "INSERT INTO save () VALUES()");

    if (mysql_query(_db_connection, msg))
    {
        printf("Failed to execute query: %s\n", mysql_error(_db_connection));
    }
}

char** get_data()
{

    char msg[512];
    snprintf(msg, 512, "SELECT * FROM game_saves.saves");

    if (mysql_query(_db_connection, msg))
    {
        printf("Failed to select data: %s\n", mysql_error(_db_connection));
        return NULL;
    }

    MYSQL_RES *result = mysql_store_result(_db_connection);
    if(!result)
    {
        printf("Error: none value, %s", mysql_error(_db_connection));
        return NULL;
    }

    MYSQL_ROW row;
    while((row = mysql_fetch_row(result)))
    {
        printf("it %s\n", row[2]);
    }

    fflush(stdout);
}

