#include <cstdint>
#include <cstdio>
#include <cstring>
#include "screen.hpp"
#include "sequence.hpp"

using namespace std;
using namespace seq;
namespace scrn {

//why does not work mens
//void Screen::display_text(vector<uint8_t> buffer){
//    cursor_move(t_pos_x,t_pos_y);
//    int counter_w = 0;
//    int cur_line = 0;
//    for(uint8_t data : buffer){
//        if(counter_w == t_width){
//            if(strcmp(data, "\n"))//do something with info
//                counter_w = 0;
//                cur_line++;
//                cursor_move(t_pos_x, t_pos_y+cur_line);
//        }   
//        printf("%c",data);
//        counter_w++;
//    }
//}

void scrn::Screen::draw_call_fbuffer(vector<vector<uint8_t>> buffer,dim s_dim, size_t n, size_t start = 0){
    //size_t temp_height = 0;
    int s_wid = t_wid;
    int s_hei = t_hei;
    if(t_wid >= s_dim.t_wid){
        s_wid = s_dim.t_wid;
    }
    if(t_hei >= s_dim.t_hei){
        s_hei = s_dim.t_hei;
    }
    size_t line_offset = 0;
    //print lines
    for(size_t line = start; line < buffer.size();line++){
        cursor_move(t_x,(t_y+(int)(line-start)+(int)(line_offset)));//move to appropriate position with line-offset problem is t_x when screen is bigger than window!! 
        if ((line-start)+line_offset >= s_hei) {
            break;
        }
        //clear line
        // for(int i = 0;i < (s_wid-t_x);i++){
        //     printf(" ");
        // }
        cursor_move(t_x,(t_y+(int)(line-start)+(int)(line_offset)));//move to appropriate position with line-offset problem is t_x when screen is bigger than window!! 
        if((line-start) == n){
            break;//max ammount n of lines have been printed
        }
        //printf("%s%lu %s",CL_YEL,line,CL_RES);
        //line is empty
        if(buffer[line].empty()){ 
            printf("%s~%s",CL_RED,CL_RES);
            //printf("\n");
            //temp_height++;
            //line_offset++;
            continue;
        }
        //print single line
        for(size_t lttr = 0;lttr < buffer[line].size();lttr++){
            //goto next line if width is reached
            if((lttr) % (s_wid-t_x-1) == 0 && lttr != (t_x-1) && lttr != 0){
               //printf("\n"); 
               line_offset++;
               cursor_move(t_x,(t_y+(int)(line-start)+(int)(line_offset)));
            }
            printf("%c",buffer[line][lttr]);
        }
        //line_offset++;
        //printf("\n");//something with t_x
        //temp_height++;
    }
    cursor_move(0, 1);
    printf("%u %u\n",s_wid-t_x-1,s_hei);
}

}//scrn