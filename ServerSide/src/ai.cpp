#include <string.h>
#include <stdlib.h>
#include <limits.h>

#ifdef ARDUINO_MOCK
#   include "../../Tests/headers/Arduino.h"
#else 
#   include <Arduino.h>
#endif


#include "../headers/kernel.h"
#include "../headers/input.h"
#include "../headers/ai.h"

bool is_strategy = true;

unsigned int _recursion_depth = 0;
#define RECURSION_LIMIT 3

int _minimux(char **_b, char _p)
{
    char winner = resolve_winner_player();
    if(winner)
    {
        return winner == _p 
            ? INT_MAX
            : INT_MIN;
    }

    int eval = -2;
    bool isSomeEval = false;
    for( int i = 0; i < 3; i++)
    {   
        for(int j = 0; j < 3; j++)
        {
            if (_b[i][j] != EMPTY_CELL) continue;
            
            _b[i][j] = _p;

            int curr_move_score = 0;
            if (_recursion_depth < RECURSION_LIMIT)
            {   
                _recursion_depth++;

                curr_move_score = _minimux(
                    _b, 
                    resolve_opponent_player(_p)
                );

                _recursion_depth--;
            }

            if (curr_move_score > eval)
            {
                eval = curr_move_score;
                isSomeEval = true;
            }

            _b[i][j] = EMPTY_CELL;
        }
    }
    if(!isSomeEval) return 0;
    return eval;
}

void set_complexity(bool _lvl)
{
    is_strategy = _lvl;
}

int comp_move(char **_b)
{
    if (!is_strategy)
    {
        return make_move( rand() % 3, rand() % 3);
    }

    int move[] = { -1, -1};
    int eval = -2;
    
    for (int i = 0; i < 3; i++)
    {   
        for(int j = 0; j < 3; j++)
        {
            if (_b[i][j] != EMPTY_CELL) continue;

            char player = 'O';
            _b[i][j] = player;
            int curr_move_score = _minimux(
                _b, 
                resolve_opponent_player(player)
            );

            if (curr_move_score > eval)
            {
                eval = curr_move_score;
                move[0] = i;
                move[1] = j;
            }

            _b[i][j] = EMPTY_CELL;
        }
    }

    return make_move(move[0], move[1]);
}