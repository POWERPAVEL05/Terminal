#include <csignal>
#include <cstdio>
#include "sequence.hpp"
using namespace pav;

void run(){
    int cols = 0;
    int rows = 0;
    screen_get_dim(&cols,&rows);
    screen_clear();
    cursor_move((cols-10)/2,rows/2);//12 is offset by string
    std::printf("X:%d,Y:%d\n",cols,rows);
    //std::printf("%s%s test %s\n",CL_RED,CL_B_BLU,CL_RES);
}

void reformat(int sig){
    run();
}

int main(){
    signal(SIGWINCH, &reformat);
    run();
    char c = std::getchar();
    return 0;
}
