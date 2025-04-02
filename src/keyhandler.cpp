#include "keyhandler.hpp"
#include "terminal.hpp"
#include "key_codes.hpp"

#include <cstdint>
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
void key::normal_key(uint64_t key_code)
{
    switch(key_code)
    {
        case INTRPT_KEY:
            trm::terminal_kill("forced exit",3);
            break;
        case 'i':
            //change mode
            break;
        default:
            //display key at bottom
            break;
    }
}

/*key interpreatation and functions in insert mode*/
void key::insert_key(uint64_t key_code)
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
int key::do_key(usage_mode mode)
{
    uint64_t current_key = get_key();
    switch (mode)
    {
        case normal:
            normal_key(current_key);
            return 0;
        case insert:
            insert_key(current_key);
            return 0;
        default:
            return -1;
    }
    return 0;
}