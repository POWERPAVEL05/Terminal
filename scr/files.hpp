#include <cstddef>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdint>
#include "display.hpp"
#ifndef FILE_MAN 
#define FILE_MAN

using namespace std;

#define no_mode ""

namespace file{

struct file_man{

    enum Mode{read,write,append,close};

    FILE* t_file;
    Mode t_mode;
    std::string t_namef;

    
    //Modes
    const char* get_mode(Mode mode);

    bool is_readable(Mode mode);

    bool change_modef(Mode mode);

    //file access
    FILE* open_file(std::string namef, Mode mode);

    bool writef_byte();

    std::size_t readf_bytes(std::size_t size,std::vector<uint8_t> &buffer);

    std::size_t get_sizef();

    explicit file_man(std::string namef, Mode mode);

    ~ file_man();
};

vector<vector<dply::Char_cell>> format_buffer(vector<uint8_t> buffer);

void draw_call_fbuffer(vector<vector<uint8_t>> buffer,size_t width,size_t height,size_t n,size_t start );
}//file
#endif //FILE_MAN