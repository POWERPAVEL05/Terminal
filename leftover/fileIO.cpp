#include <cstddef>
#include <cstdint>
#include <cstdio>
#include "fileIO.hpp"

using namespace pav;

//get size of file in bytes
std::size_t pav::FileIO::get_file_size(FILE* fp){
    std::fseek(fp,0,SEEK_END);
    size_t file_size = (size_t)ftell(fp);
    std::fseek(fp,0,SEEK_SET);//reset position
    return(file_size);
}

//read file into buffer of FILEIO
int pav::FileIO::file_read(){
    FILE* fp = fopen(this->file_name,"r");
    if(!fp){
        return 1;
    }
    this->buffer = new uint8_t[get_file_size(fp)];
    size_t actually_read = fread(this->buffer,sizeof(uint8_t),get_file_size(fp),fp);
    printf("filesize:%lu\t read:%lu",get_file_size(fp),actually_read);
    fclose(fp);
    return 0;
}

//print contents of buffer
void pav::FileIO::print_buffer(){
    FILE* fp = fopen(this->file_name,"r");
    for(int i = 0;i<(int)get_file_size(fp);i++){
        printf("%c",this->buffer[i]);
    }
    printf("\n");
}

void open_file(){
    
}