#ifndef FILEIO_H
#define FILEIO_H
#include <cstddef>
#include <string>
namespace pav {

struct FileIO{
    std::size_t file_size;
    std::string file_name;
    
    FileIO(std::string t_file_name):
        file_name(t_file_name),
        file_size(0)
    {}

    ~FileIO(){

    }

    std::size_t file_get_size();
    
    int file_read();

    int file_write();
};

}

#endif