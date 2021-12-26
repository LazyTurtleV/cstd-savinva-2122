#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>
#include "headers/kernel.h"

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

    #if DEBUG
        puts("Successfully established mysql server connection");
    #endif

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

    #if DEBUG
        puts("Successfully established db connection");
    #endif
}

void close_db_conn()
{
    if (_db_connection)
    {
        mysql_close(_db_connection);
    }
}

int save_data(char *_data, size_t _n)
{
    char msg[512];
    snprintf(msg, 512, "INSERT INTO game_saves.saves(data) VALUES(\'%s\')", _data);
    
    #if DEBUG
        puts(msg);
    #endif

    if (mysql_query(_db_connection, msg))
    {
        printf("Failed to execute query: %s\n", mysql_error(_db_connection));
        return 1;
    }

    return 0;
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

    char **data = (char**)calloc(100, sizeof(char*));
    MYSQL_ROW row;
    int i = 0;
    while((row = mysql_fetch_row(result)))
    {   
        data[i] = (char*)malloc(1024);
        strcpy(data[i], row[1]);
        i++;
    }

    return data;
}

