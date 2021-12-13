#include <stdio.h>

#include "headers/kernel.h"
#include "headers/USB.h"

#define PACKAGE_SIZE 13
#define BOARD_SIZE 3

char* _parse_package(char *_package)
{   
    switch(_package[0]){
        case SUCCESS:
            printf("X  ");
            for(int i = 0; i < BOARD_SIZE; i++) printf("%d ", i);
            puts(" ");
            puts("Y|——————");

            for (int i = 0; i < BOARD_SIZE; i++)
            {   
                printf("%d| ", i);
                for (char *p = _package + 1 + i*BOARD_SIZE, j = 0; j < BOARD_SIZE; j++, p++)
                {
                    printf("%c ", *p);
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

    return _package + 10;
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

    char *game_status = _parse_package(package);
    if(game_status[0] != GAME_CONTINUES)
    {
        printf("Step: %d\n", game_status[1]);
        
        char *str = game_status[0] == WINNER_FOUND
            ? "%s won!\n"
            : "Draft\n";

        printf(str, game_status[2] ? "O": "X" ); 
    }
}
