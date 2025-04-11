#ifndef H_SCREEN
#define H_SCREEN

#include <vector>
#include <cstdint>
#include <string>
#include "sequence.hpp"

using namespace std;
using namespace seq;

namespace scr
{
struct Status
{
    char last_key;
    //do status stuff
};

struct 
Char_Cell
{
    union
    {
        char letter;
        uint8_t number;
    };
    string f_color;
    string b_color;
    Char_Cell(char letter,string f_color,string b_color):
        letter(letter),f_color(f_color),b_color(b_color){};
    Char_Cell():
        letter(0x20),f_color(F_WHT),b_color(B_BLK){};
};

struct
Screen
{
    int position_x;
    int position_y;
    int height;
    int width;
    vector<vector<Char_Cell>>* main_screen;
    Screen(int pos_x,int pos_y,int hei,int wid,vector<vector<Char_Cell>>* m_screen):
        position_x(pos_x),position_y(pos_y),height(hei),width(wid),main_screen(m_screen){};

    int map_to_screen(const Char_Cell& character,int pos_x,int pos_y);
    void set_position();
    void set_dimensions();
    void map_rect(Char_Cell cell);
};

void screen_get_dim (int* cols, int* rows);
int draw_screen(const vector<vector<Char_Cell>> &main_screen);
int resize_screen(vector<vector<Char_Cell>> &main_screen);

enum mode{
    normal  = 0,
    insert  = 1,
    command = 2,
    any     = 3    
};

struct state_data
{
    mode t_mode;
    uint64_t line;
    uint64_t row;
};

struct window_t
{
    int pos_x;
    int pos_y;
    int wid;
    int hei;
    void(*update_behaviour)(const window_t*);
    vector<vector<Char_Cell>> *win_main;
    void* buffer;
};

void map_screen(vector<vector<Char_Cell>> *win_main,Char_Cell cell,int pos_x,int pos_y);
void behave_box(const window_t *win);
void behave_text(const window_t *win);
void behave_status(const window_t *win);

void update_win(const window_t *win);


}//scr
#endif //H_SCREEN