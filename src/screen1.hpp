#ifndef H_SCREEN_1
#define H_SCREEN_1

#include <cstddef>
#include <vector>
#include <cstdint>
#include <string>
#include <sys/ioctl.h>
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

enum mode{
    normal  = 0,
    insert  = 1,
    command = 2,
    any     = 3    
};

struct state_t
{
    mode win_mode;
    vector<vector<cell>> screen;
    size_t col = 0,row = 0;
    size_t select_window = 0;
    size_t count_window = 3;
};

struct window_t
{
    int pos_x = 0,pos_y = 0;
    int wid = 0,hei = 0;
    void(*update_behaviour)(const window_t*,state_t*);
    void* buffer = nullptr;
    window_t(int p_x,int p_y,int p_wid,int p_hei,void(*p_update_behaviour)(const window_t*,state_t*)):
        pos_x(p_x),
        pos_y(p_y),
        wid(p_wid),
        hei(p_hei),
        update_behaviour(p_update_behaviour)
    {}
};

struct windowman_t
{
    vector<window_t>windows;
    state_t state;

    windowman_t();
    void add(window_t p_win);
    void remove();
    void update();
    void update_align();
    void draw();
};

void screen_get_dim (int* cols, int* rows);
int resize_screen(vector<vector<cell>> &main_screen);
void map_screen(vector<vector<cell>>& p_screen,cell p_cell,int pos_x,int pos_y);

void behave_rect(const window_t* p_win,state_t* p_state);
} //nscr

#endif //H_SCREEN_1