#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "headers/kernel.h"
#include "headers/USB.h"

#define PACKAGE_SIZE 13
#define BOARD_SIZE 3

#define HANDSHAKE_CONST 0xFE

char player = 1;

char* _parse_package(char *_package)
{   
    puts("\n");
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
            player = !_package[10];
            break;
        case OUT_OF_BOUNDS:
            puts("Error: the index is out of bounds!");
            break;
        case CELL_IS_OCCUPIED:
            puts("Error: the cell is already occupied!");
            break;
    }

    fflush(stdout);

    return _package + 11;
}

char _resolve_player(char bit)
{
    return bit ? 'X': 'O';
}

void input_coords()
{
    char *X_str = malloc(1);
    char *Y_str = malloc(1);

    printf("%c turn to move!\n", _resolve_player(player));

    printf("Enter X coord:");
    gets(X_str);

    printf("Enter Y coord:");
    gets(Y_str);

    char X = atoi(X_str), Y = atoi(Y_str);
    char package =  ( Y << 2 ) | X;

    usb_write(&package, 1);
}

int select_mode()
{   
    puts("Select game mode");
    puts("Man vs Man - 0");

    char mode = getc(stdin) - '0';
    usb_write(&mode, 1);

    getc(stdin); //dummy read in order to delete \n from in stream

    char response;
    //wait until some bytes are read
    while(!usb_read(&response, 1));

    return response;
}

int receive_response()
{
    char *package = malloc(PACKAGE_SIZE);

    //wait until some bytes are read
    while(!usb_read(package, PACKAGE_SIZE));

    char *game_status = _parse_package(package);

    #if DEBUG
        puts("package received");
        ___print_mem___(package, PACKAGE_SIZE);
        puts("game status");
        ___print_mem___(game_status, 3);
    #endif
    
    if(game_status[1] != GAME_CONTINUES)
    {   
        char *str = game_status[1] == WINNER_FOUND
            ? "%c won!\n"
            : "Draft\n";

        printf(str, _resolve_player(!player));

        puts("\n\n");

        return 1;
    }

    fflush(stdout);
}

void handshake(){
    char *res = malloc(1);
    do
    {
        char HNDHK_CONST = HANDSHAKE_CONST;
        usb_write(&HNDHK_CONST, 1);

        usb_read(res, 1);
        
        #if DEBUG
            printf("The response was gotten: %2X\n", *res);
        #endif

        usb_write(res, 1);

        usb_read(res, 1);
    } while ( ((*res) & 0xFF ) != HANDSHAKE_CONST);

    #if DEBUG
        puts("Stable communication channel was established!");
    #endif
    
    free(res);
}