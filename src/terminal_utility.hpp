#ifndef H_TERM_UTIL
#define H_TERM_UTIL

#include <termios.h>
#include <cstdint>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

namespace trm
{
extern int descriptor_terminal;
extern termios restore_terminal;
extern termios settings_terminal;

void terminal_kill(const char* error_message,const int error_code);

int terminal_init(bool raw);

void terminal_deinit();

int bstrcmp(const string str1,const string str2);
int cmpflg(const string,const vector<string>& flags);
struct flag_options
{
    const char* filename = nullptr;
    uint8_t s_flag = 0;//startup-flags
}
;

void init_flags(flag_options* flag_op,char** args,size_t count);

}//trm

#endif //UTIL