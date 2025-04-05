#ifndef BEHAVE_H
#define BEHAVE_H
#include <cstdlib>

struct window_t{int pos_x,pos_y,wid,hei;};

void update_scr(const void *win,void(*func)(const void*,const void*),const void* buffer);

void behave_0(const void *win,const void* buffer);

void behave_1(const void *win,const void* buffer);

void behave_2(const void *win,const void* buffer);
#endif //BEHAVE_H