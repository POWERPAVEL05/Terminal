#ifndef FILEIO_H
#define FILEIO_H
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <new>
namespace pav {

struct FileIO{
    //FILE* t_fp;
    std::size_t file_size;
    char* file_name;
    uint8_t* buffer = new uint8_t[0];

    FileIO(char* t_file_name):
        file_name(t_file_name),
        //t_fp(open_file()),
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
};

}

#endif