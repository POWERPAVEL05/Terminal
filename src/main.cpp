#include "keyhandler.hpp"
#include "screen.hpp"
#include "sequence.hpp"
#include "terminal_utility.hpp"
#include "screen1.hpp"

#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <csignal>

using namespace std;
using namespace scr;
using namespace seq;
using namespace trm;

vector<vector<Char_Cell>>g_main;
vector<window_t> g_window_que;
state_data data0;

void resize_refresh(int signal)
{
    resize_screen(g_main);
    for(window_t window : g_window_que)
    {
        update_win(&window);
    }
        
    draw_screen(g_main);
}

int main(int argc,char** argv)
{
    nscr::windowman_t winman;
    nscr::window_t win (0,0,0,0,nscr::behave_rect);
    winman.add(win);
    winman.add(win);
    winman.add(win);
    winman.update_align();
    char y =getchar(); 
    screen_enter_altbuff();
    winman.draw();

    char c =getchar();

    screen_exit_altbuff();
    printf("%c",winman.state.screen[0][1].letter);
    return 0;
    int cols,rows;
    flag_options f_opts;
    init_flags(&f_opts,argv,argc);

    terminal_init(true);

    screen_get_dim(&cols,&rows);

    g_main.reserve(rows);
    vector<Char_Cell>tempv(cols,Char_Cell(0x20,F_WHT,B_BLK));
    for(int line = 0; line < rows;line++)
    {
        g_main.push_back(tempv);
    }

    state_data data0 = {scr::normal,0,0};
    window_t win0 = {2,2,5,5,&behave_box,&g_main,nullptr};
    window_t win1 = {2,7,90,5,&behave_box,&g_main,nullptr};
    window_t g_status_bar = {0,0,0,0,&behave_status,&g_main,&data0};
    g_window_que = {win0,win1,g_status_bar};

    screen_enter_altbuff();
    for(window_t window : g_window_que)
    {
        update_win(&window);
    }
    draw_screen(g_main);


    screen_enter_altbuff();
   

    /*programm loop*/

    signal(SIGWINCH, resize_refresh);
    draw_screen(g_main);

    while(1)
    {
        for(window_t window : g_window_que)
        {
            update_win(&window);
        }
        draw_screen(g_main);
        while(1)
        {
            if(key::do_key(&data0) > 0) break;
            // printf("%lx\n\r",key::do_key(&data0));
        }
    }

    //char c = getchar();

    screen_exit_altbuff(); 
    terminal_deinit(); 
    return 0;
}