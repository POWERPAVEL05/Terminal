#include <csignal>
#include <cstdio>
#include "sequence.hpp"
#include "fileIO.hpp"
using namespace pav;
//todo, resize window will has to show filecontents still
//make fileio separate file etc
void run(){
    int cols = 0;
    int rows = 0;
    screen_get_dim(&cols,&rows);
    screen_clear();
    //fp.print_buffer();
    cursor_move((cols-10)/2,rows-1);//12 is offset by string
    std::printf("%s%sX:%d,Y:%d\n%s",CL_BLK,CL_B_WHT,cols,rows,CL_RES);
    //std::printf("%s%s test %s\n",CL_RED,CL_B_BLU,CL_RES);
}

//void reformat(int sig){
//    run();
//}

int main(int argc,char** argv){
    FileIO f1(argv[1]);
    //signal(SIGWINCH, &reformat);
    screen_enter_altbuff();
    cursor_move(0, 0);
    //run();
    printf("hit1\n");
    f1.file_read();
    f1.print_buffer();
    printf("hit2\n");
    char c = std::getchar();
    screen_exit_altbuff();
    return 0;
}
