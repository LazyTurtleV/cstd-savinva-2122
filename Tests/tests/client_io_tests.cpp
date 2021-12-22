#include <gtest/gtest.h>

extern "C"
{   
    extern char player;
    char* _parse_package(char *_package);
    char _resolve_player(char bit);
}

TEST(ClientIO, _parse_package)
{       
    char data_ref[13] = { 0x0, '_', '_', '_', '_', '_', '_', '_', '_', '_', 0x0, 0x0, 0x0 };
    char *pckg = (char*)malloc(13);
    memcpy(pckg, &data_ref, 13);

    EXPECT_EQ( pckg + 11 , _parse_package(pckg));
    EXPECT_EQ( 1, player & 0xFF);
}

TEST(ClientIO, _resolve_player)
{
    EXPECT_EQ('X', _resolve_player(1));
    EXPECT_EQ('O', _resolve_player(0));
}

