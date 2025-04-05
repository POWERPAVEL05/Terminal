#include "key_codes.hpp"
#include "keyhandler.hpp"
#include "screen.hpp"
#include "sequence.hpp"
#include "terminal.hpp"

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
window_t win0;
window_t win1;
window_t g_status_bar;

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

    /*init segment todo: will be replaced by dedicated method*/
    terminal_init(true);
    int cols,rows;
    screen_get_dim(&cols,&rows);

    g_main.reserve(rows);
    vector<Char_Cell>tempv(cols,Char_Cell(0x20,F_WHT,B_BLK));
    for(int line = 0; line < rows;line++)
    {
        g_main.push_back(tempv);
    }
    state_data data0 = {1,45,30};
    win0 = {2,2,5,5,&behave_box,&g_main,0,nullptr};
    win1 = {2,7,90,5,&behave_box,&g_main,0,nullptr};
    g_status_bar = {0,0,0,0,&behave_status,&g_main,0,&data0};
    g_window_que = {win0,win1,g_status_bar};

    screen_enter_altbuff();
    for(window_t window : g_window_que)
    {
        update_win(&window);
    }
    draw_screen(g_main);


    screen_enter_altbuff();
   

    /*programm loop*/

    int p_cols,p_rows;
    int c_cols,c_rows;
    screen_get_dim(&p_cols,&p_rows);
    signal(SIGWINCH, resize_refresh);
    draw_screen(g_main);
    while(1)
    {
        if(key::get_key() == INTRPT_KEY)
        {
            terminal_kill("SIGINT\n",2);
        }
        else continue;
    }

    //char c = getchar();

    screen_exit_altbuff(); 
    terminal_deinit(); 
    return 0;
}