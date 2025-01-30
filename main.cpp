#include <algorithm>
#include <csignal>
#include <cstddef>
#include <cstdint>
#include <vector>
#include <cstdio>
#include <csignal>
#include "sequence.hpp"
#include "file_man.hpp"
//#include "screen.hpp"
using namespace std;
using namespace seq;
//using namespace scre;
using namespace file;
//todo, resize window will has to show filecontents still
//make fileio separate file etc

vector<uint8_t> buffer;
vector<vector<uint8_t>> fbuffer;
//Screen s1(20,1,5,5);

void run(){
    int cols = 0;
    int rows = 0;
    screen_get_dim(&cols,&rows);
    screen_clear();
    cursor_move(0,0);
   // for_each(buffer.begin(),buffer.end(),[](uint8_t n){
   //     printf("%c",n);
   //     });
   // printf("\n");
    //fp.print_buffer();
    cursor_move((cols-10)/2,rows-1);//12 is offset by string
    std::printf("%s%sX:%d,Y:%d Size:%lu\n%s",CL_BLK,CL_B_WHT,cols,rows,buffer.size(),CL_RES);
   // cursor_move(0, 0);
   // std::printf("%s%sSize:%lu %s\n",CL_BLK,CL_B_WHT,buffer.size(),CL_RES);
    cursor_move(0, 2);
    //for(size_t i = 2; i < fbuffer.size();i++){
    //    printf("%s%lu %s",CL_YEL,i,CL_RES);
    //    if(fbuffer[i].empty()) printf("%s~%s",CL_RED,CL_RES);
    //    for_each(fbuffer[i].begin(),fbuffer[i].end(),[](uint8_t n){
    //        printf("%c",n);
    //    });
    //    printf("\n");
    //}
    draw_call_fbuffer(fbuffer, 1000, 4,0);
    cursor_move(0, 0);
    //s1.display_text(buffer);
    //std::printf("%s%s test %s\n",CL_RED,CL_B_BLU,CL_RES);
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

    signal(SIGWINCH, &draw_frame);
    file_man filer(argv[1],file_man::read);
    size_t bytes = filer.get_sizef();
    filer.readf_bytes(bytes,buffer);
    fbuffer = format_buffer(buffer);
    screen_enter_altbuff();
    cursor_move(0,0);
    run();
    char c = std::getchar();
    screen_exit_altbuff();
    return 0;
}
