#include "screen.hpp"
#include "sequence.hpp"
#include <cstring>
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

/*window_t section*/

void scr::map_screen(vector<vector<Char_Cell>> *win_main,Char_Cell cell,int pos_x,int pos_y)
{
    if(win_main->size() <= pos_y || win_main->at(0).size() <= pos_x)
    {
        return;
    }
    (*win_main)[pos_y][pos_x] = cell;
}

void scr::behave_box(const window_t *win)
{
    Char_Cell cell(' ',F_WHT,B_BLU);
    for(int hei = 0;hei < win->hei;hei++)
    {
        for(int wid = 0;wid < win->wid;wid++)
        {
            map_screen(win->win_main,cell,((win->pos_x)+wid),((win->pos_y)+hei));
        }
    }
}

void scr::behave_text(const window_t *win)
{
    if(!win->buffer)
    {
        fprintf(stderr,"Text-Window does not have access to valid buffer\n");
        return;
    }
    vector<const char*> *t_buffer = (vector<const char*>*) win->buffer;
}

void scr::behave_status(const window_t *win)
{
    if(!win->buffer)
    {
        fprintf(stderr,"Status-Window does not have access to valid buffer\n");
        return;
    }
    state_data *t_buffer = (state_data*)win->buffer;
    const char * mode;
    if(t_buffer->mode == 0)
    {
        mode = "NORMAL";
    }
    else 
    {
        mode = "INSERT";
    }
    char data[256];
    sprintf(data,"MODE:%s [%lu,%lu]",mode,t_buffer->line,t_buffer->row);
    int cols,rows;
    screen_get_dim(&cols,&rows);
    for(int i = 0; i < strlen(data);i++)
    {
        Char_Cell cell(data[i],F_BLK,B_WHT);
        map_screen(win->win_main,cell,i,win->pos_y);
    }
    for(int i = strlen(data);i<cols;i++)
    {
        Char_Cell cell(' ',F_BLK,B_WHT);
        map_screen(win->win_main,cell,i,win->pos_y);
    }
}

void scr::update_win(const window_t *win)
{
    void(*update)(const window_t*) = win->update_behaviour;
    update(win);
}