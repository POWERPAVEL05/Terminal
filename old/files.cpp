#include "files.hpp"
#include "sequence.hpp"
#include <cstdint>
#include <cstdio>
#include <string>
#include <sys/types.h>
#include <vector>
#include <cstring>

using namespace std;
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

FILE* file_man::open_file(string namef,Mode mode){
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

size_t file_man::readf_bytes(size_t size,vector<uint8_t>&buffer){
    if(!t_file || !is_readable(t_mode)){
        return 69;
    }else{
        buffer.resize(size);
        std::size_t bytes_read = std::fread(buffer.data(),sizeof(std::uint8_t),size,t_file);
        //buffer.resize(bytes_read);
        return bytes_read;
    }
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
	if(t_file){
	    fclose(t_file);
	}
}

}//file
