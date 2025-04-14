#include "keyhandler.hpp"
#include "terminal_utility.hpp"
#include "key_codes.hpp"
#include "screen.hpp"
#include "screen1.hpp"

#include <cstddef>
#include <cstdint>
#include <sys/types.h>
#include <unistd.h>

using namespace key;


/* returns pressed key */
uint64_t key::get_key()
{
    /*bad tty*/
    if(trm::descriptor_terminal == -1)
    {
        trm::terminal_kill("bad tty at get_key",-1);
    }

    uint8_t read_buffer[5];
    uint64_t key_code;
    int read_bytes;

    read_bytes = read(trm::descriptor_terminal,&read_buffer,5);

    /*timeout / no key pressed*/
    if(read_bytes == 0)
    {
        return 0;
    }

    key_code = read_buffer[0];
    for(int idx = 1;idx < read_bytes; idx++)
    {
        key_code = key_code << 8;
        key_code += read_buffer[idx];
    }

    return key_code;
}
/*key interpreatation and functions in normal mode*/
void key::normal_key(uint64_t key_code,nscr::windowman_t* program_state)
{
    switch(key_code)
    {
        case INTRPT_KEY:
            trm::terminal_kill("forced exit",3);
            break;
        case 'i':
            //change mode
            break;
        case 'j':
            program_state->state.col += 1;
            break;
        case 'k':
            program_state->state.col -= 1;
            break;
        case 'h':
            if(program_state->state.select_window == 0)
            {
                break;
            }
            program_state->state.select_window-=1;
            program_state->state.col = 0;
            break;
        case 'l':
            if(program_state->state.select_window == 2)
            {
                break;
            }
            program_state->state.select_window+=1;
            program_state->state.col = 0;
            break;
        default:
            //display key at bottom
            break;
    }
}

/*key interpreatation and functions in insert mode*/
void key::insert_key(uint64_t key_code,nscr::windowman_t* program_state)
{
    switch (key_code) 
    {
        case ESC_KEY:
            //change mode
            break;
        default:
            //write key to certain buffer
            break;
    }
}

/*function to pick key action depending on the current mode*/
uint64_t key::do_key(nscr::windowman_t* program_state)
{
    uint64_t current_key = get_key();
    switch (program_state->state.win_mode)
    {
        case nscr::normal:
            normal_key(current_key,program_state);
            break;
        case nscr::insert:
            insert_key(current_key,program_state);
            break;
        default:
            break;
    }
    //printf("%lu",current_key);
    return current_key;
}