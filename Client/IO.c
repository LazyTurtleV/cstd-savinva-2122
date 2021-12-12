#include <stdio.h>

#include "headers/USB.h"

#define PACKAGE_SIZE 11

void _parse_package(char *_package)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%c ", _package[ i*3 + j ]);
        }
        puts("\n");
    }

    fflush(stdout);
}

void input_coords()
{
    char *X_str = malloc(1);
    char *Y_str = malloc(1);

    puts("Enter X coord:");
    gets(X_str);

    puts("Enter Y coord:");
    gets(Y_str);

    char X = atoi(X_str), Y = atoi(Y_str);
    char package =  ( X << 2 ) | Y;

    usb_write(&package, 1);
}
void receive_response()
{
    char *package = malloc(PACKAGE_SIZE);

    //wait until some bytes are read
    while(!usb_read(package, PACKAGE_SIZE));

    _parse_package(package);
}
