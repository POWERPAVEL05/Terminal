#ifndef FILEIO_H
#define FILEIO_H
#include <cstddef>
#include <cstdint>
#include <cstdio>
namespace pav {

struct FileIO{
    //FILE* t_fp;
    std::size_t file_size;
    char* file_name;
    uint8_t* buffer;

    FileIO(char* t_file_name):
        file_name(t_file_name),
        buffer(nullptr),
        file_size(0)
    {}

    FileIO():
        file_name(nullptr),
        buffer(nullptr),
        file_size(0)
    {}
    ~FileIO(){
        delete[](buffer);
    }

    FILE* open_file();

    size_t get_file_size(FILE* fp);    

    int file_read();

    void print_buffer();

    int file_write();

    void rm_buff();

    bool has_file();
};

}

#endif