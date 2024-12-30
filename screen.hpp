#ifndef SCREEN_H
#define SCREEN_H
#include <cstddef>
#include <cstdint>

namespace pav {

//concept class
struct Screen{
    int x,y;

    Screen()

    {}

    ~Screen(){

    }
    void print_buffer(std::uint8_t buffer,std::size_t filesize);

    void print_frame();

    void draw();
    };

}//pav

#endif