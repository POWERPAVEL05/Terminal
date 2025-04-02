#include "screen.hpp"
#include "sequence.hpp"
#include <vector>
#include <cstdio>
#include <sys/ioctl.h>

using namespace std;
using namespace scr;

void scr::screen_get_dim (int* cols, int* rows)
{
    struct winsize size;
    ioctl(0, TIOCGWINSZ, &size);
    *cols = size.ws_col;
    *rows = size.ws_row;
}

int scr::Screen::map_to_screen(const Char_Cell& character,int pos_x,int pos_y)
{
    if(main_screen->size()<=pos_y+position_y)//max_height reached
    {
        return 1;
    }
    if(main_screen->at(pos_y).size()<=pos_x+position_x)//max width reached
    {
        return 2;
    }
    (*main_screen)[pos_y+position_y][pos_x+position_x] = character;
    return 0;
}

int scr::draw_screen(const vector<vector<Char_Cell>>& main_screen)
{
    int cell_count;
    cursor_move(0,0);
    hide_cursor();
    for(int line = 0;line < main_screen.size();line++)
    {
        for(int cell = 0;cell < main_screen[line].size();cell++)
        {
            cursor_move(0,0);
            fprintf(stdout,"%s%s",main_screen[line][cell].f_color.c_str(),main_screen[line][cell].b_color.c_str());
            cursor_move(cell,line);
            fprintf(stdout,"%c",main_screen[line][cell].letter);
            cursor_move(0,0);
            fprintf(stdout,"%s",CL_RES);
        }
    }
    show_cursor();
    fflush(stdout);
    return cell_count;
}

int scr::get_size(const vector<vector<Char_Cell>> &main_screen)
{
    return main_screen.size();
}

int scr::resize_screen(vector<vector<Char_Cell>> &main_screen,int cols,int rows)
{  
    main_screen.resize(rows);

    for(int line = 0;line<main_screen.size();line++)
    {
        main_screen[line].resize(cols);
    }
    return main_screen.size();
}

/*draw rectangle with height and width of screen*/
void scr::Screen::map_rect(Char_Cell background_cell)
{
    for(int line = 0;line < height;line++)
    {
        for(int cell = 0;cell < width;cell++)
        {
            map_to_screen(background_cell,cell,line);
        }
    }
}