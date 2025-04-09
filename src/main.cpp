#include "key_codes.hpp"
#include "keyhandler.hpp"
#include "screen.hpp"
#include "sequence.hpp"
#include "terminal_utility.hpp"

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
        
    //draw_screen(g_main);
}

int bstrcmp(const char* str1,const char* str2)
{
    if(strlen(str1) != strlen(str2))
    {
        return 0;
    }
    for(int idx = 0; idx < strlen(str1);idx++)
    {
        if(str1[idx] != str2[idx])
        {
            //printf("s1:%c s2:%c\n",str1[idx],str2[idx]);
            return 0;
        }
    }
    return 1;
}

int main(int argc,char** argv)
{

    enum{
        await_any = 0,await_option = 1,await_file = 2
    }state_flag;

    state_flag= await_any;
    char lastflag = ' ';
    for(int nflag = 1; nflag < argc; nflag++)
    {
        char* inputf = argv[nflag];
        option_change:
        switch (state_flag) 
        {
            case(await_any):
            {
                if(inputf[0] != '-')
                {
                    if(lastflag == ' ')
                    {
                        state_flag = await_file;
                    }
                    else 
                    {
                        state_flag = await_option;
                    }
                    goto option_change;
                }
                if(bstrcmp(inputf,"-h")||bstrcmp(inputf,"--help"))
                {
                    printf("Usage: %s [options] -filename\n",argv[0]);
                    return 0;
                }
                else if (bstrcmp(inputf,"-g")) 
                {
                    printf("[%s]flag set\n",inputf);
                }
                else if (bstrcmp(inputf,"-f")) 
                {
                    printf("[%s]flag set, awating option\n",inputf);
                    lastflag = 'f';
                    state_flag = await_option;
                }
                else 
                {
                    printf("bad flag %s\n",inputf);
                }
                break;
            }
            case(await_option):
            {
                if(lastflag == 'f' && ((bstrcmp(inputf,"TRUE"))||(bstrcmp(inputf,"FALSE"))))
                {
                    printf("good option after -%c !\n",lastflag);
                    lastflag = ' ';
                    state_flag = await_any;
                }
                else 
                {
                    printf("bad option after -%c !\n",lastflag);
                    return 1;
                }
                break;
            }
            case(await_file):
            {
                printf("[FILE] %s\n",inputf);
                state_flag = await_any;
            }
        }
    }

    return 0;
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
    int refresh_count = 0;

    while(1)
    {
        key::do_key(key::normal);
        refresh_count++;
    }

    //char c = getchar();

    screen_exit_altbuff(); 
    terminal_deinit(); 
    return 0;
}