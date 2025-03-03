#ifndef H_DISPLAY
#define H_DISPLAY

#include "sequence.hpp"
#include <vector>
#include <string>
using namespace std;

#define CL_F_DEFAULT "white"
#define CL_B_DEFAULT "black"
#define C_EMPTY 10 
namespace dply{
struct 
Char_cell
{
    union{
        char letter;
        uint8_t number;
    };
    string f_color;
    string b_color;
    Char_cell(char letter,string f_color,string b_color):
        letter(letter),
        f_color(f_color),
        b_color(b_color)
        {};
    /*further attributes*/
};

struct
Window
{
    int wid;
    int hei;
    int x_pos;
    int y_pos;
    vector<vector<Char_cell>> Buf_window;
    Window(int hei, int wid, int x_pos, int y_pos):
        hei(hei),
        wid(wid),
        x_pos(x_pos),
        y_pos(y_pos)
    {};
};

struct
Buf_screen
{
    vector<vector<Char_cell>> lines;
    int max_col;
    int max_row;
    Buf_screen(vector<vector<Char_cell>> lines):
        lines(lines)
        {}; 
    /*further attribs*/
};
vector<vector<Char_cell>> format_buffer(const vector<uint8_t>& buffer);

void print_char_at(Char_cell letter,int pos_x,int pos_y);

void set_buffer(vector<vector<Char_cell>>& Buf_screen,Char_cell letter,int col,int row);

void flush_map(vector<vector<Char_cell>>& buffer);

vector<vector<Char_cell>>map_textbox(const vector<vector<Char_cell>>& fbuffer,
    const int wid, const int hei,const int pos_x,const int pos_y,const int start_at_line = 0);
    
void draw_screen(const vector<vector<Char_cell>>& Buf_map);
}//dply
#endif