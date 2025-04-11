#ifndef H_SCREEN_1
#define H_SCREEN_1

#include <vector>
#include <cstdint>
#include <string>
#include "sequence.hpp"

using namespace seq;
using namespace std;

namespace nscr{
struct cell
{
    union
    {
        char letter;
        uint8_t number;
    };
    string f_color;
    string b_color;
    cell(char letter,string f_color,string b_color):
        letter(letter),f_color(f_color),b_color(b_color){};
    cell():
        letter(0x20),f_color(F_WHT),b_color(B_BLK){};
};

struct state_t
{
    vector<vector<cell>> screen;
    size_t col = 0,row = 0;
    size_t select_window = 0;
};

struct window_t
{
    int pos_x;
    int pos_y;
    int wid;
    int hei;
    void(*update_behaviour)(const window_t*,const state_t*);
    void* buffer = nullptr;
};

struct windowman_t
{
    vector<window_t> windows;
    state_t state;

    void add(window_t p_win);
    void remove();
    void update();
    void update_align();
    void draw();
};

} //nscr

#endif //H_SCREEN_1