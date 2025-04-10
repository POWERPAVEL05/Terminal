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

int bstrcmp(const char* str1,const char* str2);
int cmpflg(const char* arg,const char** flags, size_t count);
struct flag_options
{
    const char* filename;
    uint8_t s_flag = 0;//startup-flags
}
;

void init_flags(flag_options* flag_op,char** args,size_t count);

}//trm

#endif //UTIL