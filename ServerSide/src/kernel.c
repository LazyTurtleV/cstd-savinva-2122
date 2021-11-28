#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "math.h"

#include "../headers/kernel.h"

#define FIELD_SIZE 3
#define EMPTY_CELL '_'

char **_game_field;
const size_t g_FIELD_SIZE = FIELD_SIZE;

size_t step = 0;


enum role
{
    X = 'X',
    O = 'O'
};

void _render_board();
int _detect_winner();
void _announce_winner(char _winner);
void _announce_draw();

void init_game()
{
    _game_field = malloc(FIELD_SIZE * sizeof(char*));
    for(int i = 0; i < FIELD_SIZE; i++)
    { 
        _game_field[i] = malloc(FIELD_SIZE);
        memset(_game_field[i], EMPTY_CELL, FIELD_SIZE);
    }
}

void end_game()
{
    for(int i = 0; i < FIELD_SIZE; i++)
        memset(_game_field[i], EMPTY_CELL, FIELD_SIZE);
}

int make_move(unsigned int _i, unsigned int _j)
{   
    if (_i >= FIELD_SIZE || _j >= FIELD_SIZE) 
        return OUT_OF_BOUNDS;
    if(_game_field[_i][_j] != EMPTY_CELL) 
        return CELL_IS_OCCUPIED;

    _game_field[_i][_j] = step % 2 ? O : X;

    ++step;

    _render_board();

    return SUCCESS;
}

int game_status()
{
    int winner = _detect_winner();
    if(winner)
    {
        _announce_winner(winner);
        return WINNER_FOUND;
    }

    if (step == pow(FIELD_SIZE, 2))
    {
        _announce_draw();
        return DRAW;
    }

    return GAME_CONTINUES;
}

int _detect_winner()
{
    for(int i = 0; i < FIELD_SIZE; i++)
    {   
        int isLineComplete = 1;
        char prev_el = _game_field[i][0];
        for(int j = 0; j < FIELD_SIZE; j++)
        {
            isLineComplete &= prev_el == _game_field[i][j] && _game_field[i][j] != EMPTY_CELL;
            prev_el = _game_field[i][j];
        }
        
        if(isLineComplete) return  prev_el;
    }

    for(int i = 0; i < FIELD_SIZE; i++)
    {   
        int isColumnComplete = 1; 
        char prev_el = _game_field[0][i];
        for(int j = 0; j < FIELD_SIZE; j++)
        {
            isColumnComplete &= prev_el == _game_field[j][i] && _game_field[j][i] != EMPTY_CELL;
            prev_el = _game_field[j][i];
        }
        
        if(isColumnComplete) return prev_el;
    }

    return 0;
}

void _announce_winner(char _winner)
{
    printf("%c wins!\n", _winner);
}

void _announce_draw()
{
    puts("DRAW!\n");
}

void _render_board()
{
    for (int i = 0; i < FIELD_SIZE; i++)
    {
        for (int j = 0; j < FIELD_SIZE; j++)
        {
            printf( "%c ", _game_field[i][j]);
        }
        puts("\n");
    }

    fflush(stdout);
}
