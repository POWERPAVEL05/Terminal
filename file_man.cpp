#include "file_man.hpp"
#include "sequence.hpp"
#include <cstddef>
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
        return 0;
    }else{
        buffer.resize(size);
        std::size_t bytes_read = std::fread(buffer.data(),sizeof(std::uint8_t),size,t_file);
        //buffer.resize(bytes_read);
        return bytes_read;
    }
}

vector<vector<uint8_t>> format_buffer(vector<uint8_t>buffer){
    vector< vector<uint8_t> > lines;
    vector<uint8_t> append;
    for(std::size_t i = 0,line = 0,column = 0; i < buffer.size();i++){
        if(buffer.at(i) == 10){
            line++;
            lines.push_back(append);
            append.clear();
            continue;
        }
        append.push_back(buffer.at(i));
    }
    return lines;
}

//draw lines --> formated buffer needed
void draw_call_fbuffer(vector<vector<uint8_t>> buffer, size_t width,size_t height,size_t n, size_t start = 0){
    if(width == 0) width = 1;
    if(height == 0) height = 1;
    size_t temp_height = 0;
    //print lines
    for(size_t i = start; i < buffer.size();i++){
        if (temp_height == height) {
            break;
        }
        if((i-start) == n)break;//max ammount n of lines have been printed
        printf("%s%lu %s",CL_YEL,i,CL_RES);
        //line is empty
        if(buffer[i].empty()){ 
            printf("%s~%s",CL_RED,CL_RES);
            printf("\n");
            temp_height++;
            continue;
        }
        //print single line
        for(size_t lttr = 0;lttr < buffer[i].size();lttr++){
            //goto next line if width is reached
            if((lttr % width) == 0 && lttr != 0){
               printf("\n  "); 
               temp_height++;
            }
            printf("%c",buffer[i][lttr]);
        }
        printf("\n");
        temp_height++;
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
