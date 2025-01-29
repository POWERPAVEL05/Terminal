#include "file_man.hpp"
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <string>
#include <sys/types.h>
#include <vector>
#include <cstring>

namespace file {

const char* file_man::get_mode(Mode mode){
    switch (mode) {
        case read:
            return "r";
            break;
        case write: 
            return "w";
            break;
        case append:
            return "a";
            break;
        case close:
            return " ";
            break;
    }
    return no_mode;
}

bool file_man::is_readable(Mode mode){
    return mode == read;
}

FILE* file_man::open_file(std::string namef,Mode mode){
    return(fopen(namef.c_str(),get_mode(mode)));
}

bool file_man::change_modef(Mode mode){
    if(strcmp(get_mode(mode), no_mode) != 0){
        return false;
    }
    fclose(t_file);
    t_file = fopen(t_namef.c_str(),get_mode(mode));
    return true;
}

std::size_t file_man::readf_bytes(std::size_t size,std::vector<uint8_t>&buffer){
    if(!t_file || !is_readable(t_mode)){
        return 0;
    }else{
        buffer.resize(size);
        std::size_t bytes_read = std::fread(buffer.data(),sizeof(std::uint8_t),size,t_file);
        //buffer.resize(bytes_read);
        return bytes_read;
    }
}

std::vector<uint8_t*> file_man::format_buffer(std::vector<uint8_t>buffer){
    std::vector<uint8_t*> lines;
    for(std::size_t i = 0,line = 0,column = 0; i < buffer.size();i++){
        if(buffer.at(i) == 10){
            line++;
            column = 0;
        }
        lines[line][column] = buffer.at(i);
        column++;
    }
    return lines;
}

std::size_t file_man::get_sizef(){
    if(!t_file){
        return 0;
    }
    const int temp_inidactor = std::ftell(t_file);
    std::fseek(t_file,0,SEEK_END);
    int result = ftell(t_file);
    std::fseek(t_file,0,temp_inidactor);
    return result;
}
file_man::file_man(std::string namef,Mode mode):
    t_file(open_file(namef,mode)),
    t_mode(mode)
{};

file_man::~file_man(){
    fclose(t_file);
}

}//file