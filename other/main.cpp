#include "display.hpp"
#include "files.hpp"
#include "sequence.hpp"
#include <cstddef>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;
int main(int argc,char** argv){
    if(argc<2)
    {
        return 1;
    }
    
    std::vector<uint8_t> m_buf;
    file::file_man f1(argv[1],file::file_man::read);
    size_t size = f1.get_sizef();
    size_t test = f1.readf_bytes(size, m_buf);
    vector<vector<dply::Char_cell>> fbuffer = dply::format_buffer(m_buf);

    screen_enter_altbuff();

    vector<vector<dply::Char_cell>> map1 = dply::map_textbox(fbuffer, 10, 5, 2, 1,0);
    dply::draw_screen(map1);
    ////dply::print_char_at(fbuffer[1][0],0,0);
    char c = getchar();
    screen_exit_altbuff();
    for(int i = 0;i < map1.size();i++){
        //printf("%lu\n",fbuffer[i].size());
        if(!fbuffer[i].empty())for_each(fbuffer[i].begin(),fbuffer[i].end(),[](dply::Char_cell c1){printf("%u ",c1.number);});
        printf("\n");
        if(fbuffer[i].empty())printf("buzz\n");
       // if(fbuffer[i].back().letter == '\0')printf("ende\n");
    } 
    printf("%lu\n",test);
    return 0;
}