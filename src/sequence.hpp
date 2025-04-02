#include <asm-generic/ioctls.h>
#include <cstdio>
#include <sys/ioctl.h>

//===ANSI-ESCSequences===

#ifndef H_SEQ
#define H_SEQ

namespace seq {

//===Screen===

//clear screen
#define screen_clear() puts("\e[2J")

//get screen dimensions
//void screen_get_dim(int* cols, int* rows);

//alternate buffer
#define screen_enter_altbuff() puts("\e[?1049h")
#define screen_exit_altbuff() puts("\e[?1049l")

void screen_change(int sig);//todo?
//===Cursor===

//move cursor to
//in ansi: rows by cols instead of cols by rows
#define cursor_move(X,Y) std::printf("\e[%d;%dH",(Y+1),(X+1)) 

//===Color===

//Reset Color
#define CL_RES "\e[0;0m"

//Forground
#define F_RED "\e[0;31m"
#define F_GRE "\e[0;32m"
#define F_YEL "\e[0;33m"
#define F_BLU "\e[0;34m"
#define F_MAG "\e[0;35m"
#define F_CYA "\e[0;36m"
#define F_BLK "\e[0;30m"
#define F_WHT "\e[0;37m"

//Background
#define B_RED "\e[41m"
#define B_GRE "\e[42m"
#define B_YEL "\e[43m"
#define B_BLU "\e[44m"
#define B_MAG "\e[45m"
#define B_CYA "\e[46m"
#define B_WHT "\e[47m"
#define B_BLK "\e[40m"

/*private Sequence*/

#define hide_cursor() puts("\e[?25l");

#define show_cursor() puts("\e[?25h");

}//seq
#endif