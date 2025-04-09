#include <cstdio>

int get_size(const char** arr)
{
    return(sizeof(arr)/sizeof(arr[0]));
}

int main()
{
    const char * t1[] = {"sd","sdf","sdfj"};
    printf("size: %i\n",get_size(t1));
}