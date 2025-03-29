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
        letter(' '),f_color(F_WHT),b_color(B_BLK){};
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
int get_size(const vector<vector<Char_Cell>> &main_screen);
int resize_screen(vector<vector<Char_Cell>> &main_screen,int cols,int rows);
}//scr
#endif //H_SCREEN