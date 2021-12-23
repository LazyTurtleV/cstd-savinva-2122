#include <gtest/gtest.h>

#include "../../ServerSide/headers/kernel.h"

#define EMPTY_CELL '_'

extern char **_game_field;
extern size_t step;
extern void init_game(char *_m);
extern void end_game();
extern int make_move(unsigned int, unsigned int);;
extern int game_status();
extern void announce_player();
extern int _detect_winner();


void make_win_situation(bool is1stPlayer)
{
    init_game(0);

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            _game_field[i][j] = '_';
        }
    }

    for(int i = 0; i < 3; i++)
        _game_field[0][i] = is1stPlayer ? 'X': 'O';
}

void make_draw()
{
    init_game(0);

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            make_move(i, j);
        }
    }
}


TEST(KernelTest, init_game)
{
    EXPECT_NO_THROW(init_game(0));
    ASSERT_NE(0, reinterpret_cast<std::uintptr_t>(_game_field) );
    
    for(int i = 0; i < 3; i++)
    {   
        for(int j = 0; j < 3; j++)
        {
            ASSERT_NO_THROW(_game_field[i][j]) << "i = " << i << ", j = " << j;
            EXPECT_EQ(EMPTY_CELL, _game_field[i][j] ) << "i = " << i << ", j = " << j;
        }
    }
}

TEST(KernelTest, end_game)
{
    EXPECT_NO_THROW(end_game());
    ASSERT_NE(0, reinterpret_cast<std::uintptr_t>(_game_field) );
    
    for(int i = 0; i < 3; i++)
    {   
        for(int j = 0; j < 3; j++)
        {
            ASSERT_NO_THROW(_game_field[i][j]) << "i = " << i << ", j = " << j;
            EXPECT_EQ(EMPTY_CELL, _game_field[i][j] ) << "i = " << i << ", j = " << j;
        }
    }

}

TEST(KernelTest, make_move)
{   
    EXPECT_EQ(
        1,
        make_move(-1, -1)
    ) << "Expected to throw an error when i or j are invalid";

    EXPECT_EQ(
        1,
        make_move(3, 0) 
    ) << "Expected to throw an error when i or j are invalid";

    EXPECT_EQ(
        1,
        make_move(0, 3) 
    ) << "Expected to throw an error when i or j are invalid";

    for (int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {   
            if(!_game_field) init_game(0);

            EXPECT_EQ(0, make_move(i, j));
            EXPECT_NE(EMPTY_CELL, _game_field[i][j]);
        }
    }

    end_game();
    make_move(0, 0);
    EXPECT_EQ(2, make_move(0, 0));
}

TEST(KernelTest, game_status)
{   
    make_win_situation(true);

    EXPECT_EQ( WINNER_FOUND, game_status());

    end_game();

    make_win_situation(false);

    EXPECT_EQ( WINNER_FOUND, game_status());

    end_game();

    make_draw();

    EXPECT_EQ( DRAW, game_status() );

    end_game();
}

TEST(KernelTest, _detect_winner)
{
    make_win_situation(true);
    EXPECT_EQ('X', _detect_winner());
    end_game();

    make_win_situation(false);
    EXPECT_EQ('O', _detect_winner());
    end_game();
}