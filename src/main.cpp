#include "keyhandler.hpp"
#include "screen.hpp"
#include "sequence.hpp"
#include "terminal_utility.hpp"
#include "screen1.hpp"

#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <csignal>

using namespace std;
using namespace scr;
using namespace seq;
using namespace trm;

state_data data0;

nscr::windowman_t winman;

void new_refresh(int signal)
{
    winman.update_align();
    winman.draw();
}

int main(int argc,char** argv)
{
    nscr::window_t win (0,0,0,0,nscr::behave_rect);
    winman.add(win);
    winman.add(win);
    winman.add(win);
    winman.update_align();
    
    flag_options f_opts;
    init_flags(&f_opts,argv,argc);

    terminal_init(true);

    /*programm loop*/
    screen_enter_altbuff();
   
    signal(SIGWINCH, new_refresh);

    while(1)
    {
        winman.update_align();
        winman.draw();
        while(1)
        {
            if(key::do_key(&winman) > 0) break;
        }
    }

    screen_exit_altbuff(); 
    terminal_deinit(); 
    return 0;
}