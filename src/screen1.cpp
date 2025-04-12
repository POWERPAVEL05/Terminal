#include "screen1.hpp"
#include "sequence.hpp"
#include "terminal_utility.hpp"
#include <cmath>
#include <cstdio>
#include <sys/ioctl.h>

using namespace nscr;

void nscr::screen_get_dim (int* cols, int* rows)
{
    struct winsize size;
    ioctl(0, TIOCGWINSZ, &size);
    *cols = size.ws_col;
    *rows = size.ws_row;
}

void nscr::map_screen(vector<vector<cell>>& p_screen,cell p_cell,int pos_x,int pos_y)
{
    if(p_screen.size() <= pos_y || p_screen.at(0).size() <= pos_x)
    {
        printf("x:%i,y:%i",pos_x,pos_y);
        return;
    }
    p_screen[pos_y][pos_x] = p_cell;
}

int nscr::resize_screen(vector<vector<cell>> &main_screen)
{  
    int cols,rows;
    nscr::screen_get_dim(&cols,&rows);
    main_screen.clear();
    main_screen.resize(rows);

    for(int line = 0;line<main_screen.size();line++)
    {
        main_screen[line].resize(cols);
    }
    return main_screen.size();
}

nscr::windowman_t::windowman_t()
{

    int cols,rows;
    nscr::screen_get_dim(&cols,&rows);
    state.screen.reserve(rows);
    vector<cell>tempv(cols,cell(0x20,F_WHT,B_BLK));
    for(int line = 0; line < rows;line++)
    {
        state.screen.push_back(tempv);
    }
}
void nscr::windowman_t::add(window_t p_win)
{
    windows.insert(windows.begin(),p_win);
}

void nscr::windowman_t::remove()
{
    windows.erase(windows.begin()+state.select_window);
}

void nscr::windowman_t::update()
{
    for(window_t window : windows)
    {
        void(*update)(const window_t*,state_t*) = window.update_behaviour;
        update(&window,&state);
    }
}

void nscr::windowman_t::update_align()
{
    nscr::resize_screen(state.screen);
    if(windows.size() == 0)
    {
        trm::terminal_kill("No windows", 69);
    }

    int term_cols,term_rows;
    screen_get_dim(&term_cols,&term_rows);

    int padding = windows.size()-1;
    float tmp_wid = ((float)(term_cols-padding))/windows.size();
	int leftover = term_cols-padding-(ceil(tmp_wid)+((windows.size()-1)*floor(tmp_wid)));

    windows[0].wid = std::ceil(tmp_wid);
    windows[0].hei = term_rows-1; 
    windows[0].pos_x = 0;
    windows[0].pos_y = 0;
	size_t compound_wid = windows[0].wid+1;
    for(size_t idx = 1; idx < windows.size();++idx)
    {
        if(leftover > 0)
        {
            windows[idx].wid = std::floor(tmp_wid)+1;
        }
        else 
        {
            windows[idx].wid = std::floor(tmp_wid);
        }
        windows[idx].hei = term_rows-1; 
        windows[idx].pos_x = compound_wid;
        windows[idx].pos_y = 0;
	    compound_wid += windows[idx].wid+1;
    }

    for(window_t win : windows)
    {
        printf("wid:%i hei:%i pos_x:%i pos_y:%i\n",win.wid,win.hei,win.pos_x,win.pos_y);
    }
    printf("size:%lu,len:%lu",state.screen.size(),state.screen[0].size());
    update();
}

void nscr::windowman_t::draw()
{
    int cell_count;
    cursor_move(0,0);
    hide_cursor();
    for(int line = 0;line < state.screen.size();line++)
    {
        for(int cell = 0;cell < state.screen[line].size();cell++)
        {
            cursor_move(0,0);
            fprintf(stdout,"%s%s",state.screen[line][cell].f_color.c_str(),state.screen[line][cell].b_color.c_str());
            cursor_move(cell,line);
            fprintf(stdout,"%c",state.screen[line][cell].letter);
            cursor_move(0,0);
            fprintf(stdout,"%s",CL_RES);
        }
    }
    show_cursor();
    fflush(stdout);
}


void nscr::behave_rect(const window_t* p_win,state_t* p_state)
{
    cell c0('X',F_CYA,B_BLU);
    for(int l_hei = 0;l_hei < p_win->hei;l_hei++)
    {
        for(int l_wid = 0; l_wid < p_win->wid;l_wid++)
        {
            //printf("nums:%i\n",l_wid+(1));
            // map_screen(p_state->screen,c0,l_wid+(2),l_hei+(3));
            map_screen(p_state->screen,c0,l_wid+(p_win->pos_x),l_hei+(p_win->pos_y));
        }
    }
}