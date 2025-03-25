#include "display.hpp"
#include "files.hpp"
#include "sequence.hpp"
#include <cstdio>
#include <vector>
#include <cassert>
#include <csignal>

using namespace std;

dply::Window w1(50,50,3,0);
dply::Window w2(50,25,26,0);
vector<vector<dply::Char_cell>> fbuffer;

void
draw_call(int signal)
{
    screen_clear();
    int cols;
    int rows;
    int count;
    int count1;
    dply::screen_get_dim(&cols,&rows);
    cursor_move(0, rows-1);
    printf("c:%i c1:%i",count,count1);
    w1.map_textbox(fbuffer,count);
    //w1.draw_screen();
    for(int row = 0;row < w1.map.size();row++)
    {
        for(int column = 0;column < w1.map[row].size();column++)
        {
            print_char_at(w1.map[row][column],column+w1.pos_x,row+w1.pos_y);
        }
        count = w1.map.size();
    }
    for(int row = 0;row < w1.map.size();row++)
    {
        for(int column = 0;column < w1.map[row].size();column++)
        {
            print_char_at(w1.map[row][column],column+w1.pos_x,row+w1.pos_y);
        }
        count1 = w1.map.size();
    }
    //dply::draw_screen(w1.map, 3, 0);
    
}

void
analyze_file
(vector<vector<dply::Char_cell>> map)
{
    for(vector<dply::Char_cell> list : map){
        if(list.empty()) printf("fizz");
        for(dply::Char_cell sign : list){
            printf("%u ",sign.number);
        }
        printf("\t%lu\n",list.size());
    }
    printf("%lu\n",map.size());
}

int main(int argc,char** argv){
    if(argc<2)
    {
        return 1;
    }
    
    std::vector<uint8_t> m_buf;
    file::file_man f1(argv[1],file::file_man::read);
    f1.readf_bytes(f1.get_sizef(), m_buf);
    fbuffer = dply::format_buffer(m_buf);
    
    std::signal(SIGWINCH,draw_call);

    screen_enter_altbuff();
    //draw_call(SIGWINCH);
    int count = 0;
   
    char c = getchar();

    screen_exit_altbuff();
    //w1.draw_screen();
    //analyze_file(w1.map);
    return 0;
}