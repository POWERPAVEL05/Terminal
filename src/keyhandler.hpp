#ifndef H_KEYS
#define H_KEYS
#include "screen1.hpp"
#include <cstdint>
using namespace std;

/*defines methods for key input handling*/

namespace key 
{
    void normal_key(uint64_t key_code,nscr::windowman_t* program_state);

    void insert_key(uint64_t key_code,nscr::windowman_t* program_state);

    uint64_t get_key();

    uint64_t do_key(nscr::windowman_t* program_state);
}
#endif