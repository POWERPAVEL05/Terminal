#include <sys/ioctl.h>
#include "sequence.hpp"

//gets the dimensions of the terminal through syscall ioctl and winsize both defined in <sys/ioctl>
void seq::screen_get_dim(int* cols, int* rows){
    struct winsize size;
    ioctl(0, TIOCGWINSZ, &size);
    *cols = size.ws_col;
    *rows = size.ws_row;
}
