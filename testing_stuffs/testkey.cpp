#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstdint>
#include <unistd.h>
#include <cstring>
#include "terminal.hpp"

using namespace std;
#define tab 9
#define f1 0x1b4f50
#define ZIGINT 3 

void keyman(uint64_t goober)
{
    switch(goober)
    {
        case tab:
            printf("oi you pressed tab man\r\n");
            break;
        case f1:
            printf("oi you pressed f1 man\r\n");
            break;
        case ZIGINT:
            exit(1);
        default:
            break;
    }
}


int main()
{
    trm::terminal_init();
    char c = 0;
    int ret_val = -1;
    clock_t previous_time = clock();
    uint8_t buffer[5];
    while(1)
    {
        //if(c == '\e') c = '#';
        //if(buffer[0] == '\e') buffer[0] = '#';

        uint64_t goober = 0;

        if(ret_val == 0)
        {
            //printf("timed out \r\n");
            goto end;
        }

        // if(ret_val < 2 && buffer[0] == 'x')
        // {
        //     exit(0);
        // }

        // printf("char is:%s\r\n",buffer);
        for(int i = 0; i < ret_val;i++)
        {
            printf("%x",buffer[i]);
        }

        goober = buffer[0];
        for(int i = 1; i < ret_val;i++)
        {
            goober = goober << 8;
            goober += buffer[i];
        }
        printf(" goober: %lx",goober);
        printf("\r\n");
        // printf("c is:%x\r\n",c);
        printf("time since press:%.3f\r\n",(((double)(clock()-previous_time)/CLOCKS_PER_SEC))*1000);
        printf("ret_val:%i\r\n",ret_val);
        keyman(goober);
        previous_time = clock();
        for(int i = 0;i < sizeof(buffer);i++)
        {
            buffer[i] = 0;
        }
        end:
        ret_val = read(2,&buffer,5);
    }
    return 0;
}