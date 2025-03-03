#include <cstddef>
#include <vector>
#include <sys/ioctl.h>/*ioctl TIOGETWINSZ*/
#include <string>
#include "sequence.hpp"
#include "display.hpp"

using namespace std;
using namespace dply; 

void 
screen_get_dim
(int* cols, int* rows)
{
    struct winsize size;
    ioctl(0, TIOCGWINSZ, &size);
    *cols = size.ws_col;
    *rows = size.ws_row;
}

vector<vector<Char_cell>>
dply::format_buffer
(const vector<uint8_t>& buffer)
{
    vector<vector<Char_cell>> lines;
    vector<Char_cell> temp_vec;
    for(std::size_t idx = 0; idx < buffer.size();idx++){
        if(buffer.at(idx)==10){
            if(buffer.empty()){temp_vec.emplace_back('X',F_RED,B_GRE);}
            lines.push_back(temp_vec);
            temp_vec.clear();
            continue;
        }
        temp_vec.emplace_back(buffer.at(idx),F_RED,B_BLU);
    }
    return lines;
}

void
dply::print_char_at
(Char_cell letter,int pos_x,int pos_y)
{
    cursor_move(pos_x,pos_y);
    printf("%s%s%c%s",(letter.f_color).c_str(),(letter.b_color).c_str(),letter.letter,CL_RES);
    cursor_move(0,0);
}

void 
dply::set_buffer
(vector<vector<Char_cell>>& Buf_screen,Char_cell letter,int col,int row)
{
    Buf_screen[row][col] = letter;
}

void
dply::flush_map
(vector<vector<Char_cell>>& buffer)
{
    int* cols;
    int* rows;
    screen_get_dim(cols,rows);
    buffer.clear();
    buffer.reserve(*rows);
    for(int n = 0; n < *rows ;n++)
    {
        buffer[n].reserve(*cols);
    }
}

vector<vector<Char_cell>> 
dply::map_textbox
(const vector<vector<Char_cell>>& fbuffer,
    const int wid, const int hei,const int pos_x,const int pos_y,const int start_at_line)
{
    vector<vector<Char_cell>> map;
    vector<Char_cell> temp; 
    /*assume map is wid by hei big*/
    int wid_max;
    int hei_max;
    screen_get_dim(&wid_max,&hei_max);
    
    if(wid+pos_x<wid_max)
    {
        wid_max = wid;
    }

    if(hei+pos_y<hei_max)
    {
        hei_max = hei;
    }
    for(int lines = 0 ; lines < fbuffer.size(); lines++){
        for(Char_cell sign : fbuffer[lines]){
            temp.emplace_back('X',F_RED,B_GRE);
        }
        map.push_back(temp);
        temp.clear();
    }
    /*out of bounds*/
    return map;
}

void 
dply::draw_screen
(const vector<vector<Char_cell>>& Buf_map)
{
    for(int row = 0;row < Buf_map.size();row++)
    {
        for(int column = 0;column < Buf_map[row].size();column++)
        {
            print_char_at(Buf_map[row][column],column,row);
        }
    }
}