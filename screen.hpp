#ifndef SCREEN_H
#define SCREEN_H
#include <cstddef>
#include <cstdint>
#include <vector>

using namespace std;
namespace scre {

//concept class
struct Screen{
    int t_width,t_height,t_pos_x,t_pos_y;


    Screen(int wid,int hei,int pos_x,int pos_y):
        t_width(wid),
        t_height(hei),
        t_pos_x(pos_x),
        t_pos_y(pos_y)
    {}

    Screen(size_t wid,size_t hei):
        t_width(wid),
        t_height(hei),
        t_pos_x(0),
        t_pos_y(0)
    {}

   // Screen():
   //     t_width(0),
   //     t_height(0)
   // {}

    ~Screen(){

    }

    void display_text(std::vector<uint8_t> buffer); 

    };
}//scre

#endif