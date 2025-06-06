#include "terminal_utility.hpp"
#include "sequence.hpp"
#include <cstddef>
#include <cstdio>
#include <termios.h>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <errno.h>
#include <vector>
#include <string>

using namespace std;

/* important global vars*/
int trm::descriptor_terminal = -1;
termios trm::restore_terminal;
termios trm::settings_terminal;

/*call when critical error occurs, app has to close*/
void trm::terminal_kill(const char* error_message, const int error_code)
{
    screen_exit_altbuff();
    fprintf(stderr,"[%i] %s\n",error_code,error_message);
    exit(error_code);
}

/*set terminal back to state before program execution perform on exit or error*/
void trm::terminal_deinit()
{
    if(descriptor_terminal == -1)
    {
        return;
    }
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
        settings_terminal.c_cc[VTIME] = 1; /*100ms timeout*/
        settings_terminal.c_cc[VMIN] = 0;
    }

    if(tcsetattr(descriptor_terminal,TCSAFLUSH,&settings_terminal) == -1)
    {
        return 1;
    }

    return 0;
}

int trm::bstrcmp(const string str1,const string str2)
{
    if(!str1.compare(str2))
    {
        return 1;
    }else 
    {
        return 0;
    }
}

int trm::cmpflg(const string arg,const vector<string>& flags)
{
    for(string flag : flags)
    {
        if(bstrcmp(arg,flag))
        {
            return 1;
        }
    }
    return 0;
}
void trm::init_flags(trm::flag_options* flag_op,char** args, size_t count)
{
    enum
    {
        await_any = 0,await_arg = 1,await_file = 2
    }t_state = await_any;

    for(int idx = 1; idx < count;idx++)
    {
        char* arg = args[idx];

        if(arg[0] != '-')
        {
            t_state = await_file;
        }

        switch (t_state)
        {
            case(await_any):
            {
                if(cmpflg(arg,{"-h","--help"}))
                {
                    printf("Usage\n");
                    return;
                }
                if(cmpflg(arg,{"-v","--version"}))
                {
                    printf("Version\n");
                    return;
                }
                else if(cmpflg(arg,{"-1"}) && (flag_op->s_flag & 1) == 0)
                {
                    flag_op->s_flag += 1;
                }
                else if(cmpflg(arg,{"-2"})&& (flag_op->s_flag & 2) == 0)
                {
                    flag_op->s_flag += 2;
                }
                else if(cmpflg(arg,{"-3"})&& (flag_op->s_flag & 4) == 0)
                {
                    flag_op->s_flag += 4;
                }
                else if(cmpflg(arg,{"-4"}) && (flag_op->s_flag & 8) == 0)
                {
                    flag_op->s_flag += 8;
                }
                break;
            }
            case(await_arg):
            {
                printf("ding!\n");
                break;
            }
            case(await_file):
            {
                flag_op->filename = arg;
                printf("[FILE] %s\n",flag_op->filename);
                break;
            }
        }
    }
}