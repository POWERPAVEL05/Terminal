#include "terminal.hpp"
#include <cstdio>
#include <termios.h>
#include <cstdlib>
#include <unistd.h>
#include <errno.h>

using namespace std;

/* important global vars*/
int trm::descriptor_terminal = -1;
termios trm::restore_terminal;
termios trm::settings_terminal;

/*call when critical error occurs, app has to close*/
void trm::terminal_kill(const char* error_message, const int error_code)
{
    fprintf(stderr,"[%i]%s\n",error_code,error_message);
    exit(error_code);
}

/*set terminal back to state before program execution perform on exit or error*/
void trm::terminal_deinit()
{
    tcsetattr(descriptor_terminal,TCSANOW,&restore_terminal);
}

/*assure requirements are met then set terminal settings*/
int trm::terminal_init(bool raw = false)
{

    /*terminal has already been initialised*/
    if (descriptor_terminal != -1)
    {
        return 0;
    }

    /*check if any stream is connected to tty*/
    if(isatty(STDERR_FILENO)) descriptor_terminal = STDERR_FILENO;
    else
        if(isatty(STDIN_FILENO)) descriptor_terminal = STDIN_FILENO;
        else
            if(isatty(STDOUT_FILENO)) descriptor_terminal = STDOUT_FILENO;
            else 
                return errno = ENOTTY; 

    /*set exit-function*/
    int register_fail = atexit(terminal_deinit);
    if(register_fail)
    {
        return 1;
    }

    /*get current terminal settings*/
    if(tcgetattr(descriptor_terminal, &restore_terminal) == -1)
    {
        return 1;
    }

    if(tcgetattr(descriptor_terminal, &settings_terminal) == -1)
    {
        return 1;
    }

    /*set attributes to raw mode*/
    if(raw){
        settings_terminal.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP| INLCR | IGNCR | ICRNL | IXON);
        settings_terminal.c_oflag &= ~OPOST;
        settings_terminal.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
        settings_terminal.c_cflag &= ~(CSIZE | PARENB);
        settings_terminal.c_cflag |= CS8;
    }

    if(tcsetattr(descriptor_terminal,TCSAFLUSH,&settings_terminal) == -1)
    {
        return 1;
    }

    return 0;
}