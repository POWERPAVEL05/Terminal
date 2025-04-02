#ifndef H_KEYS
#define H_KEYS
#include <cstdint>
using namespace std;

/*defines methods for key input handling*/

namespace key 
{
    enum usage_mode {normal = 0, insert = 1};

    void normal_key(uint64_t key_code);

    void insert_key(uint64_t key_code);

    uint64_t get_key();

    int do_key(usage_mode mode);
}
#endif