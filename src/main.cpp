#include "screen.hpp"
#include "sequence.hpp"
#include "terminal.hpp"
#include "key_codes.hpp"
#include "keyhandler.hpp"

#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <csignal>

using namespace std;
using namespace scr;
using namespace seq;
using namespace trm;
using namespace key;


Char_Cell grob(' ',F_WHT,B_GRE);
Char_Cell blob('X',F_WHT,B_RED);
Char_Cell bob('Y',F_WHT,B_YEL);

vector<vector<Char_Cell>>g_main;
usage_mode g_mode = normal; 

Screen s1(10,20,10,15,&g_main);
Screen s2(5,11,10,100,&g_main);
bool running;
void resize_refresh(int signal)
{
    int cols,rows;
    screen_get_dim(&cols,&rows);
    resize_screen(g_main,cols,rows);
    s1.map_rect(blob);
    s2.map_rect(bob);
    draw_screen(g_main);
}

void draw_screen()
{
    //map_windows
    draw_screen(g_main);
}

int main()
{
    /*init segment todo: will be replaced by dedicated method*/
    int cols,rows;
    screen_get_dim(&cols,&rows);

    g_main.reserve(rows);
    vector<Char_Cell>tempv(cols,Char_Cell(0x20,F_WHT,B_BLK));
    for(int line = 0; line < rows;line++)
    {
        g_main.push_back(tempv);
    }

    s1.map_rect(blob);
    s2.map_rect(bob);

    terminal_init(true);

    screen_enter_altbuff();
   
    cursor_move(0,0);
    draw_screen(g_main);
    signal(SIGWINCH,resize_refresh);

    /*programm loop*/
    while(running)
    {
        if(1)//todo check if refresh is needed
        {
            draw_screen(g_main);
        }
        key::do_key(g_mode);
    }

    //char c = getchar();

    screen_exit_altbuff(); 
    terminal_deinit(); 
    return 0;
}