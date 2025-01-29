#include <cstddef>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdint>
#ifndef FILE_MAN 
#define FILE_MAN

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

    std::vector<uint8_t*> format_buffer(std::vector<uint8_t> buffer);

    //std::size_t readf_lines(std::size_t size,std::vector<uint8_t*> &buffer);
    //file utility
    std::size_t get_sizef();

    explicit file_man(std::string namef, Mode mode);

    ~ file_man();
};

}//file
#endif //FILE_MAN