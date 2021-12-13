#include <stdio.h>

#include "headers/kernel.h"
#include "headers/USB.h"

#define PACKAGE_SIZE 11
#define BOARD_SIZE 3

int _parse_package(char *_package)
{   
    switch(_package[0]){
        case SUCCESS:
            ++_package;
            printf("X  ");
            for(int i = 0; i < BOARD_SIZE; i++) printf("%d ", i);
            puts(" ");
            puts("Y|——————");

            for (int i = 0; i < BOARD_SIZE; i++)
            {   
                printf("%d| ", i);
                for (int j = 0; j < BOARD_SIZE; j++)
                {
                    printf("%c ", _package[ i*BOARD_SIZE + j ]);
                }
                puts("");
            }
            puts("");
            break;
        case OUT_OF_BOUNDS:
            puts("Error: the index is out of bounds!");
            break;
        case CELL_IS_OCCUPIED:
            puts("Error: the cell is already occupied!");
            break;
    }

    fflush(stdout);

    return _package[ 9 ];
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
    char package =  ( Y << 2 ) | X;

    usb_write(&package, 1);
}

void receive_response()
{
    char *package = malloc(PACKAGE_SIZE);

    //wait until some bytes are read
    while(!usb_read(package, PACKAGE_SIZE));

    const game_status = _parse_package(package);
    if( game_status == WINNER_FOUND )
    {
        printf("Winner found!!!");
    }
}
