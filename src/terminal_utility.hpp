#ifndef H_TERM_UTIL
#define H_TERM_UTIL

#include <termios.h>
#include <cstdint>
#include <cstdlib>

namespace trm
{
extern int descriptor_terminal;
extern termios restore_terminal;
extern termios settings_terminal;

void terminal_kill(const char* error_message,const int error_code);

int terminal_init(bool raw);

void terminal_deinit();

struct flag_options
{
    const char* filename;
    uint8_t s_flag;//startup-flags
}
;

void init_flags(flag_options* flag_op,char** args,size_t count);

}//trm

#endif //UTIL