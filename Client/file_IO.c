#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

const char* _file_name = "save.tmp";

int write_file(char *_out_buf, size_t _n)
{
    int fd = open(_file_name, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);

    if (fd < 0)
    {
        printf("A file opening triggered an error %d: %s\n", errno, strerror(errno));
        return fd;
    }
    int n = write(fd, _out_buf, _n);
    if (n < 0)
    {
        printf("A write to file triggered an error %d: %s\n", errno, strerror(errno));
        return n;
    }

    close(fd);

    return 0;
}

int read_file(char* _in_buf, size_t _n)
{
    int fd = open(_file_name, O_RDONLY);

    if (fd < 0)
    {
        printf("A file opening triggered an error %d: %s\n", errno, strerror(errno));
        return fd;
    }

    int n = read(fd, _in_buf, _n);
    if (n < 0)
    {
        printf("A read from a file triggered an error %d: %s\n", errno, strerror(errno));
        return n;
    }

    close(fd);

    return 0;
}

