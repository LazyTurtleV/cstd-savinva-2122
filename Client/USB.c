#include <errno.h>
#include <fcntl.h> 
#include <string.h>
#include <stddef.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

int _port_fd_ = 0;

int _set_interface_attributs(int _fd, int _speed, int _parity);
void _set_blocking (int _fd, int _should_block);

int _set_interface_attributs(int _fd, int _speed, int _parity)
{
    struct termios tty;
    if (tcgetattr (_fd, &tty) != 0)
    {
        printf("tcgetattr triggered error %d: %s\n", errno, strerror(errno));
        return -1;
    }

    cfsetospeed (&tty, _speed);
    cfsetispeed (&tty, _speed);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
    // disable IGNBRK for mismatched speed tests; otherwise receive break
    // as \000 chars
    tty.c_iflag &= ~IGNBRK;         // disable break processing
    tty.c_lflag = 0;                // no signaling chars, no echo,
                                    // no canonical processing
    tty.c_oflag = 0;                // no remapping, no delays
    tty.c_cc[VMIN]  = 0;            // read doesn't block
    tty.c_cc[VTIME] = 10;            // 0.5 seconds read timeout

    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

    tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
                                    // enable reading
    tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
    tty.c_cflag |= _parity;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    cfmakeraw(&tty);

    if (tcsetattr (_fd, TCSANOW, &tty) != 0)
    {
        printf("tcgetattr triggered error %d: %s\n", errno ,strerror(errno));
        return -1;
    }
    return 0;
}

void _set_blocking (int _fd, int _should_block)
{
    struct termios tty;
    memset (&tty, 0, sizeof tty);
    if (tcgetattr (_fd, &tty) != 0)
    {
        printf("tcgetattr triggered error %d: %s\n", errno ,strerror(errno));
        return;
    }

    tty.c_cc[VMIN]  = _should_block ? 1 : 0;
    tty.c_cc[VTIME] = 10;            // 0.5 seconds read timeout

    if (tcsetattr (_fd, TCSANOW, &tty) != 0)
        printf("tcgetattr triggered error %d: %s\n", errno ,strerror(errno));
}

void set_up_port(char *_port){
    if(!_port_fd_)
    {
        _port_fd_ = open(_port, O_RDWR | O_NOCTTY | O_SYNC);
    }

    if(_port_fd_ < 0)
    {
        printf("file %s opining triggered error %d: %s\n", _port, errno ,strerror(errno));
        return;
    }

    _set_interface_attributs(_port_fd_, B9600, 0);
    _set_blocking(_port_fd_, 0);
}

void usb_read(char *_in, size_t _n)
{ 
    int n = read(_port_fd_, _in, _n);
    printf("Read %d bytes\n", n);
}

void usb_write(char *_in, size_t _n)
{
    int n = write(_port_fd_, _in, _n);
    printf("Written %d bytes\n", n);
}