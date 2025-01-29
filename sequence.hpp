#include <asm-generic/ioctls.h>
#include <cstdio>
#include <sys/ioctl.h>

//===ANSI-ESCSequences===

#ifndef SEQ_H
#define SEQ_H

namespace seq {

//===Screen===

//clear screen
#define screen_clear() puts("\e[2J")

//get screen dimensions
void screen_get_dim(int* cols, int* rows);

//alternate buffer
#define screen_enter_altbuff() puts("\e[?1049h")
#define screen_exit_altbuff() puts("\e[?1049l")

void screen_change(int sig);//todo?
//===Cursor===

//move cursor to
//in ansi: rows by cols instead of cols by rows
#define cursor_move(X,Y) std::printf("\e[%d;%dH",Y,X) 

//===Color===

//Reset Color
#define CL_RES "\e[0;0m"

//Forground
#define CL_RED "\e[0;31m"
#define CL_GRE "\e[0;32m"
#define CL_YEL "\e[0;33m"
#define CL_BLU "\e[0;34m"
#define CL_MAG "\e[0;35m"
#define CL_CYA "\e[0;36m"
#define CL_BLK "\e[0;30m"
#define CL_WHT "\e[0;37m"

//Background
#define CL_B_RED "\e[41m"
#define CL_B_GRE "\e[42m"
#define CL_B_YEL "\e[43m"
#define CL_B_BLU "\e[44m"
#define CL_B_MAG "\e[45m"
#define CL_B_CYA "\e[46m"
#define CL_B_WHT "\e[47m"
#define CL_B_BLK "\e[40m"

}//pav
#endif