#include <cstdio>
#include <cstring>

using namespace std;

int main()
{
    char readin[10]; 
    FILE* log  = fopen("test.log","w");
    if(!log)
    {
        printf("log not found\n");
        return 1;
    }
    printf("log open\e[6n\n");
    fflush(stdout);
    fgets(readin,sizeof(readin),stdin);
    printf("stdin read\n");
    fwrite(readin,sizeof(char),strlen(readin),log);
    printf("size:%lu\n",strlen(readin));
    printf("done\n");
    return 0;
}