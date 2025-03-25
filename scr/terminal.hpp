#ifndef H_TERM
#define H_TERM

#include <termios.h>

namespace trm
{
extern int descriptor_terminal;
extern termios restore_terminal;
extern termios settings_terminal;

void terminal_kill(const char* error_message,const int error_code);

int terminal_init(bool raw);

void terminal_deinit();
}//trm

#endif