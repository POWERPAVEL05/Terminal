#include <csignal>
#include <cstddef>
#include <cstdio>
#include <cstdint>
#include "sequence.hpp"
using namespace pav;

void run(){
    int cols = 0;
    int rows = 0;
    screen_get_dim(&cols,&rows);
    screen_clear();
    cursor_move((cols-10)/2,rows-1);//12 is offset by string
    std::printf("%s%sX:%d,Y:%d\n%s",CL_BLK,CL_B_WHT,cols,rows,CL_RES);
    //std::printf("%s%s test %s\n",CL_RED,CL_B_BLU,CL_RES);
}

void reformat(int sig){
    run();
}

int main(int argc,char** argv){
    const char* FNAME = argv[1]; 
    const size_t SIZE = sizeof(std::uint8_t);
    const size_t BUFF_SIZE = 1024;
    std::uint8_t buffer[BUFF_SIZE];   

    if (argc != 2){
        std::printf("faulty parameters \t[PROGRAMM NAME][FILENAME]\n");
        return 10;
    }

    FILE* fp = std::fopen(FNAME,"r");
    
    if (!fp){
        std::printf("Could not find filename:%s\n",FNAME);   
        return 11; 
    }
    signal(SIGWINCH, &reformat);
    screen_enter_altbuff();
    run();
    cursor_move(0, 0);
    
    size_t actually_read = fread(&buffer, SIZE, 1024, fp);
    
    for(size_t i = 0;i<actually_read;i++){
        std::printf("%c",buffer[i]);
    }
    std::printf("\n");

    while(actually_read!=0){
        actually_read = fread(&buffer, SIZE, 1024, fp);
        
        for(size_t i = 0;i<actually_read;i++){
            std::printf("%c",buffer[i]);
        }
        std::printf("\n");
    }

    //while(actually_read != 0){
    //    actually_read = fread(&buffer, SIZE, 1024, fp);
    //}

    char c = std::getchar();
    screen_exit_altbuff();
    fclose(fp);
    return 0;
}
