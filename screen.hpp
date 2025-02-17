#ifndef SCREEN_H
#define SCREEN_H
#include <cstddef>
#include <cstdint>
#include <vector>

using namespace std;
struct dim{
    int t_wid,t_hei;
    explicit dim(int wid, int hei):
        t_wid(wid),
        t_hei(hei)
        {}
};
namespace scrn {

struct Screen{
    int t_wid,t_hei,t_x,t_y;

    //todo accoutn for wid = hei = 0
    Screen(int wid,int hei,int pos_x,int pos_y):
        t_wid(wid),
        t_hei(hei),
        t_x(pos_x),
        t_y(pos_y)
    {}

    Screen(int wid,int hei):
        t_wid(wid),
        t_hei(hei),
        t_x(0),
        t_y(0)
    {}

    ~Screen(){};

    //void display_text(std::vector<uint8_t> buffer); 

    void draw_call_fbuffer(vector<vector<uint8_t>> buffer,dim dim,size_t n,size_t start);

    };



}//scre

#endif