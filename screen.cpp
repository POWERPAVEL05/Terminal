#include "screen.hpp"
#include "sequence.hpp"
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>

using namespace std;
namespace scre {

//why does not work mens
void Screen::display_text(vector<uint8_t> buffer){
    cursor_move(t_pos_x,t_pos_y);
    int counter_w = 0;
    int cur_line = 0;
    for(uint8_t data : buffer){
        if(counter_w == t_width){
            if(strcmp(data, "\n"))//do something with info
                counter_w = 0;
                cur_line++;
                cursor_move(t_pos_x, t_pos_y+cur_line);
        }   
        printf("%c",data);
        counter_w++;
    }
}

}