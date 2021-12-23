//mock Arduino lib
#include <stdio.h>
#include <stdint.h>

class SerialClass 
{
public:
    static void begin(int _n)
    {
    }

    static int read()
    {
        return 1;
    }

    static int readBytes(char *_buf, size_t _n)
    {
        return 1;
    }

    static int print(char *_m)
    {
        puts(_m);
        return 100;
    }

    static int print(char _m)
    {
        printf("%c", _m);
        return 1;
    }

    static int println(char *_m)
    {
        puts(_m);
        return 100;
    }

    static int write(char *_b, size_t _n)
    {
        puts(_b);
        return _n;
    }

    static int write(const uint8_t *_b, size_t _n)
    {
        puts((const char*)_b);
        return 100;
    }

    static int write(char *_b)
    {
        puts(_b);
        return 100;
    }

    static int write(char _b)
    {
        printf("%c", _b);
        return 1;
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