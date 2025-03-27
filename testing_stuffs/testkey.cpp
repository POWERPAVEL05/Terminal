#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <cstring>
#include "terminal.hpp"

using namespace std;

int main()
{
    trm::terminal_init();
    char c = 0;
    clock_t previous_time = clock();
    char buffer[5];
    int ret_val = -1;
    while(1)
    {
        //if(c == '\e') c = '#';
        if(buffer[0] == '\e') buffer[0] = '#';

        if(ret_val == 0)
        {
            printf("timed out \r\n");
            goto end;
        }

        if(strlen(buffer) == 1 && buffer[0] == 'x')
        {
            exit(0);
        }

        printf("char is:%s\r\n",buffer);
        // printf("c is:%x\r\n",c);
        printf("time since press:%.3f\r\n",(((double)(clock()-previous_time)/CLOCKS_PER_SEC))*1000);
        previous_time = clock();
        for(int i = 0;i < sizeof(buffer);i++)
        {
            buffer[i] = 0;
        }
        end:
        ret_val = read(0,&buffer,5);
    }
    return 0;
}