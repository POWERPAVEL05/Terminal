#include "keyhandler.hpp"
#include <cstdint>
#include <unistd.h>
#include "terminal.hpp"
using namespace key;


/* returns pressed key */
uint64_t key::get_key()
{
    /*bad tty*/
    if(trm::descriptor_terminal == -1)
    {
        return -1;
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

int do_key(uint64_t key_code,usage_mode mode)
{
    switch (mode)
    {
        case normal:
            //do smth
            break;
        case insert:
            //do smth
            break;
        default:
            return -1;
    }
    return 0;
}