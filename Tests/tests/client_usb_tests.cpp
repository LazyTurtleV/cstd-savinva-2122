#include <gtest/gtest.h>
#include <termios.h>
#include <stdlib.h>

extern "C"
{   
    extern int _port_fd_;
    void set_up_port(char *_port);
    void _set_blocking (int _fd, int _should_block);
    int _set_interface_attributs(int _fd, int _speed, int _parity);
    int usb_write(char *_in, size_t _n);
    int usb_read(char *_in, size_t _n);
}

TEST(ClientUSB, set_up_port)
{
    char *port = "/dev/ttyUSB0";
    EXPECT_NO_THROW( set_up_port(port) );
    EXPECT_NE(0, _port_fd_);
}

TEST(ClientUSB, _set_blocking)
{
    EXPECT_NO_THROW( _set_blocking(_port_fd_, 0) );
}

TEST(ClientUSB, _set_interface_attributs)
{
    EXPECT_NO_THROW( _set_interface_attributs(_port_fd_, B9600, 0) );
}

TEST(ClientUSB, usb_write)
{
    EXPECT_GE(0, usb_write("a", 1));
}

TEST(ClientUSB, usb_read)
{   
    char *tmp = (char*)malloc(1);
    EXPECT_GE(0, usb_read(tmp, 1));
}

