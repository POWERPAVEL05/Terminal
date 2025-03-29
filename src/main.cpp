#include "screen.hpp"
#include "sequence.hpp"
#include "terminal.hpp"
#include "screen.hpp"
#include "key_codes.hpp"
#include "keyhandler.hpp"

#include <cstdio>
#include <cassert>
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

vector<vector<Char_Cell>>v_main;
usage_mode globla_mode = normal; 
Screen s1(10,20,10,15,&v_main);
Screen s2(5,11,10,100,&v_main);

void resize_refresh(int signal)
{
    int cols,rows;
    screen_get_dim(&cols,&rows);
    resize_screen(v_main,cols,rows);
    s1.map_rect(blob);
    s2.map_rect(bob);
    draw_screen(v_main);
}

int main()
{
    int cols,rows;
    screen_get_dim(&cols,&rows);

    v_main.reserve(rows);

    vector<Char_Cell>tempv;

    for(int cell = 0;cell<cols;cell++)
    {
        tempv.emplace_back(' ',F_WHT,B_BLK);
    }

    for(int line = 0; line < rows;line++)
    {
        v_main.push_back(tempv);
        //tempv.clear();
    }


    s1.map_rect(blob);
    s2.map_rect(bob);

    terminal_init(true);

    screen_enter_altbuff();
   
    cursor_move(0,0);
    draw_screen(v_main);
    signal(SIGWINCH,resize_refresh);
    char c = getchar();

    screen_exit_altbuff(); 
    terminal_deinit(); 
    fprintf(stdout,"char:%c\n",v_main[0][0].letter);
    fprintf(stdout,"size:%lu\n",v_main.size());
    return 0;
}