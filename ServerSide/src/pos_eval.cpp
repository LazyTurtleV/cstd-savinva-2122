#include <float.h>

#include "../headers/kernel.h"

double evaluate_position(char **_b, char _p)
{
    char winner = resolve_winner_player();
    if(winner)
    {
        return _p == winner ? DBL_MAX: DBL_MIN;
    }

    return (double)_eval_rows(_b, _p) + (double)_eval_columns(_b, _p);
}

double _eval_rows(char **_b, char _p)
{   
    double score = 0.0;

    for (int i = 0; i < 3; i++)
    {
        int count = 0;
        bool row_clean = true;

        for (int j = 0; j < 3; j++)
        {
            char cell = _b[i][j];

            if (cell == _p) score++;
            else if (cell != EMPTY_CELL)
            {
                row_clean = false;
                break;
            }
        }

        if (row_clean && count)
            score += count;
    }

    return score;
}

double _eval_columns(char **_b, char _p)
{   
    double score = 0.0;

    for (int i = 0; i < 3; i++)
    {
        int count = 0;
        bool row_clean = true;

        for (int j = 0; j < 3; j++)
        {
            char cell = _b[j][i];

            if (cell == _p) score++;
            else if (cell != EMPTY_CELL)
            {
                row_clean = false;
                break;
            }
        }

        if (row_clean && count)
            score += count;
    }

    return score;
}