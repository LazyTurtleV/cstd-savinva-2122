#include <stddef.h>

int usb_read(char *_in, size_t _n);
int usb_write(char *_in, size_t _n);
void set_up_port(char *_port);