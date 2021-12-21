#include <gtest/gtest.h>

#define EMPTY_CELL '_'

extern void init_game();
extern void end_game();
extern int make_move(unsigned int, unsigned int);;
extern char **_game_field;

TEST(KernelTest, init_game)
{
    EXPECT_NO_THROW(init_game());
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
            if(!_game_field) init_game();

            EXPECT_EQ(0, make_move(i, j));
            EXPECT_NE(EMPTY_CELL, _game_field[i][j]);
        }
    }

    end_game();
    make_move(0, 0);
    EXPECT_EQ(2, make_move(0, 0));
}