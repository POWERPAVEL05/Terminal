#include <cstddef>
#include <cstdio>
#include <vector>
#include <sys/ioctl.h>/*ioctl TIOGETWINSZ*/
#include <string>
#include "sequence.hpp"
#include "display.hpp"

using namespace std;
using namespace dply; 

void 
dply::screen_get_dim
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
            lines.push_back(temp_vec);
            temp_vec.clear();
            continue;
        }
        temp_vec.emplace_back(buffer.at(idx),F_WHT,B_BLK);
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
    const int wid, const int hei,const int pos_x,const int pos_y,int &count ,const int start_at_line)
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
    else 
    {
        wid_max-=pos_x;
    }

    if(hei+pos_y<hei_max)
    {
        hei_max = hei;
    }
    for(int lines = 0,lineoffset = 0; lines < fbuffer.size(); lines++)
    {
        if((lines + lineoffset) == hei)
        {

        }
        if(fbuffer[lines].empty()){
            temp.emplace_back('~',F_RED,B_BLK);
        }
        for(int sign = 0;sign < fbuffer[lines].size();sign++)
        {
            if(((sign) % (wid_max)) == 0 && sign != 0)
            {
                map.push_back(temp);
                temp.clear();
                lineoffset++;
            }
            temp.push_back(fbuffer[lines][sign]);
        }
        map.push_back(temp);
        temp.clear();
    }
    /*out of bounds*/
    return map;
}
// TODO adjust to actually refresh
void 
dply::draw_screen
(const vector<vector<Char_cell>>& Buf_map,int pos_x, int pos_y)
 {
    for(int row = 0;row < Buf_map.size();row++)
    {
        for(int column = 0;column < Buf_map[row].size();column++)
        {
            print_char_at(Buf_map[row][column],column+pos_x,row+pos_y);
        }
    }
}

void
dply::Window::map_textbox
(const vector<vector<Char_cell>>& fbuffer,int &count,int start_at_line)
{
    this->map = dply::map_textbox(fbuffer, this->wid, this->hei, this->pos_x, this->pos_y,count,start_at_line);
}

void 
dply::Window::draw_screen
()
{
    dply::draw_screen(this->map,this->pos_x,this->pos_y);
}