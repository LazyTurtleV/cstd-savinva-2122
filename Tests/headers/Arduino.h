//mock Arduino lib
#include <stdio.h>
#include <stdint.h>

class SerialClass 
{
public:
    static void begin(int _n)
    {
        puts("Begin...");
    }

    static int read()
    {
        puts("Reading");
        return 100;
    }

    static int print(char *_m)
    {
        puts("Printing");
        return 100;
    }

    static int print(char _m)
    {
        puts("Printing");
        return 100;
    }

    static int println(char *_m)
    {
        puts("Printing in a new line");
        return 100;
    }

    static int write(char *_b, size_t _n)
    {
        puts("Writing");
        return 100;
    }

    static int write(const uint8_t *_b, size_t _n)
    {
        puts("Writing");
        return 100;
    }

    static int write(char *_b)
    {
        puts("Writing");
        return 100;
    }

    static int write(char _b)
    {
        puts("Writing");
        return 100;
    }

    static bool available()
    {
        return true;
    }

    bool operator ! (){
        return true;
    }
};

SerialClass Serial;