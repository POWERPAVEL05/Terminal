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
    int pos_x;
    int pos_y;
    vector<vector<Char_cell>> map;
    Window(int hei, int wid, int pos_x, int pos_y):
        hei(hei),
        wid(wid),
        pos_x(pos_x),
        pos_y(pos_y)
    {};
    void map_textbox(const vector<vector<Char_cell>>& fbuffer,int &count,int start_at_line = 0);
    
    void draw_screen();
};


vector<vector<Char_cell>> format_buffer(const vector<uint8_t>& buffer);

void screen_get_dim (int* cols, int* rows);

void print_char_at(Char_cell letter,int pos_x,int pos_y);

void set_buffer(vector<vector<Char_cell>>& Buf_screen,Char_cell letter,int col,int row);

void flush_map(vector<vector<Char_cell>>& buffer);

vector<vector<Char_cell>>map_textbox(const vector<vector<Char_cell>>& fbuffer,
    const int wid, const int hei,const int pos_x,const int pos_y,int &count,const int start_at_line = 0);
    
void draw_screen(const vector<vector<Char_cell>>& Buf_map,int pos_x,int pos_y);
void draw_screen_x (const vector<vector<Char_cell>>& Buf_map,int pos_x, int pos_y);
}//dply
#endif