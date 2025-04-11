#include "screen1.hpp"

using namespace nscr;

void windowman_t::add(window_t p_win)
{
    windows.insert(windows.begin(),p_win);
}

void windowman_t::remove()
{
    windows.erase();
}

void windowman_t::update()
{
    for(window_t window : windows)
    {
        void(*update)(const window_t*,const state_t*) = window.update_behaviour;
        update(&window,&state);
    }
}

void windowman_t::update_align()
{
    /*align*/
    update();
}

void windowman_t::draw()
{
    state.screen;
}