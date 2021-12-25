#include <string.h>
#include <stdlib.h>

#include "../headers/kernel.h"
#include "../headers/ai.h"

bool is_strategy = true;

int _minimux(char **_b, char _p)
{
    char winner = resolve_winner_player();
    if(!winner) return 0;

    bool is_there_any = false;
    int eval = -1;
    for( int i = 0; i < 3; i++)
    {   
        for(int j = 0; j < 3; j++)
        {
            if (_b[i][j] != EMPTY_CELL) continue;
            
            _b[i][j] = _p;
            int curr_move_score = -_minimux(
                _b, 
                resolve_opponent_player(_p)
            );

            if (curr_move_score > eval)
            {
                eval = curr_move_score;
                is_there_any = false;
            }

            _b[i][j] = EMPTY_CELL;
        }
    }

    if (!is_there_any) return 0;

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
    int eval = -1;
    
    for (int i = 0; i < 3; i++)
    {   
        for(int j = 0; j < 3; j++)
        {
            if (_b[i][j] != EMPTY_CELL) continue;

            char player = resolve_current_player();
            _b[i][j] = player;
            int curr_move_score = -_minimux(
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