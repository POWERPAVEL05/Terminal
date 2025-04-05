#include <cstdio>
#include "behaviour.hpp"
#include "vector"
using namespace std;
void update_scr(const void* win,void(*func)(const void*,const void*),const void* buffer)
{
   void (*t_func)(const void*,const void*) = func;
   t_func(win,buffer);
}

void behave_0(const void* win,const void* buffer)
{
    window_t t_window = *(window_t*)win;
    const char* t_buffer = (const char*)buffer;
    printf("beh0:\thei:%i wid%i char:%c\n",t_window.hei,t_window.wid,t_buffer[1]);
}

void behave_1(const void* win,const void* buffer)
{
    window_t t_window = *(window_t*)win;
    const int* t_buffer = (const int*)buffer;
    printf("beh1:\thei:%i wid%i char:%i\n",t_window.hei,t_window.wid,t_buffer[0]);
}

void behave_2(const void* win,const void* buffer)
{
    window_t t_window = *(window_t*)win;
    vector<const char*>* t_buffer = (vector<const char*>*)buffer;
    printf("beh2:\tsize:%lu\n",t_buffer->size());
    for(int i = 0; i < t_buffer->size();i++)
    {
        printf("\t%s\n",t_buffer->at(i));
    }
}