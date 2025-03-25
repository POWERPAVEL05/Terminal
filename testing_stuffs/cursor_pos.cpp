#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <termios.h>
#include <unistd.h>

using namespace std;

int main()
{
    int filedes = 2;
    termios old;
    termios settings;

    //is stream connected to tty?
    // if(isatty(STDERR_FILENO)) filedes = STDERR_FILENO;
    // else
    //     if(isatty(STDIN_FILENO)) filedes = STDIN_FILENO;
    //     else
    //     if(isatty(STDOUT_FILENO)) filedes = STDOUT_FILENO;
    //     else 
    //         return 1;

    tcgetattr(filedes,&old);
    tcgetattr(filedes,&settings);
    settings.c_lflag &= ~(ICANON|ECHO);
    tcsetattr(filedes,TCSANOW,&settings);
    //freopen("test.log","w",stdout);
    write(filedes,"\e[6n",4);

    char buf[24] = {' '};
    for(int i = 0;i<(sizeof(buf)/sizeof(buf[0]));i++){
        char temp[1];
        int size = read(filedes,temp,1);//fd ist egal solang er mit tty verbunden ist
        buf[i] = temp[0];

        printf("%i\n",i);
        if(temp[0] == 'R')
        {
            printf("hit\n");
            break;
        }

        if(size == 0){ 
            printf("no read\n"); 
            break;
        }
        //printf("%c",temp[0]); 
    }
    char buffbuff[6]= "hallo";
    write(2,&buffbuff,6);
    char another_buffer[20];
    read(1,&another_buffer,6);
    tcsetattr(filedes,TCSANOW,&old);
    for(int i = 1;i<strlen(buf);i++)
    {
        // printf("%i",i);
        printf("%c",buf[i]);
    }
    for(int i = 1;i<strlen(another_buffer);i++)
    {
        // printf("%i",i);
        printf("%c",another_buffer[i]);
    }
    printf("\n");
    printf("size:%lu\n",strlen(buf));
    if(strlen(buf) < 2)
    {
        printf("no data");
    }
    printf("\n");
    return 0;
}
int mdain()
{
    const char* dev;
    dev = ttyname(STDIN_FILENO);
    for(int i = 0;i<strlen(dev);i++)
    {
        printf("%c",dev[i]);
    }
    printf("\n");
    return 0;
}