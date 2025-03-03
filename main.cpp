#include <cstdint>
#include <vector>
#include <cstdio>
#include <csignal>
#include "sequence.hpp"
#include "file_man.hpp"
#include "screen.hpp"
using namespace std;
using namespace seq;
using namespace scrn;
using namespace file;
//TODO: PAINPAINPAINPAINPAINPAINPAINPAIN convert everything so screen is a big array of arrays to print
//should get rid of flickering
vector<uint8_t> buffer;
vector<vector<uint8_t>> fbuffer;
//Screen s1(20,1,5,5);
Screen s1(100,50,6,2);
dim d1(0,0);

void run(){
    //int cols = 0;
    //int rows = 0;
    //screen_get_dim(&cols,&rows);
    screen_get_dim(&d1.t_wid,&d1.t_hei);
    cursor_move(0,0);

    //screen_clear();
    //s1.draw_call_fbuffer(fbuffer,d1, 50, 0);
    //cursor_move(1, 1);

    cursor_move((d1.t_wid-11)/2,d1.t_hei-2);//12 is offset by string
    std::printf("%s%sX:%d,Y:%d Size:%lu\n%s",CL_BLK,CL_B_WHT,d1.t_wid,d1.t_hei,buffer.size(),CL_RES);
}
void draw_frame(int signal){
    run();
}

int main(int argc,char** argv){
    //signal(SIGWINCH, &reformat);
    if(argc < 2){
        std::printf("%s [FILENAME]\n",argv[0]);
        return 1;
    }

    //setup
    signal(SIGWINCH, &draw_frame);
    file_man filer(argv[1],file_man::read);
    size_t bytes = filer.get_sizef();
    filer.readf_bytes(bytes,buffer);
    fbuffer = format_buffer(buffer);

    screen_enter_altbuff();
    cursor_move(0,0);

    //running test
    run();

    //end
    char c = std::getchar();
    screen_exit_altbuff();
    return 0;
}
