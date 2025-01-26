#include <csignal>
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <vector>
#include <cstdio>
#include <cstdint>
#include "sequence.hpp"
//#include "fileIO.hpp"
#include "file_man.hpp"
using namespace pav;
using namespace file;
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

int main(int argc,char** argv){
    //signal(SIGWINCH, &reformat);
    if(argc < 2){
        std::printf("%s [FILENAME]\n",argv[0]);
        return 1;
    }

    std::vector<uint8_t> buffer;
    file_man filer(argv[1],file::file_man::read);
    size_t bytes = filer.get_sizef();
    printf("Read bytes:%lu\n",filer.readf_bytes(bytes,buffer));
    
    screen_enter_altbuff();
    cursor_move(0, 0);
    printf("hit1\nsize of file:%lu",bytes);
    for_each(buffer.begin(),buffer.end(),[](uint8_t n){
        printf("%c",n);
        });
    printf("\n%lu\n",buffer.size());
    printf("\n");
    printf("hit2\n");
    char c = std::getchar();
    screen_exit_altbuff();
    return 0;
}
