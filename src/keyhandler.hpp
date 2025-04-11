#ifndef H_KEYS
#define H_KEYS
#include "screen.hpp"
#include <cstdint>
using namespace std;

/*defines methods for key input handling*/

namespace key 
{
    void normal_key(uint64_t key_code,scr::state_data* program_state);

    void insert_key(uint64_t key_code,scr::state_data* program_state);

    uint64_t get_key();

    uint64_t do_key(scr::state_data* program_state);
}
#endif