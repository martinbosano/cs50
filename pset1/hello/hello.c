#include <stdio.h>
#include <cs50.h>

// main
int main(void)
{
    string name = get_string("What's your name?\n");
    printf("hello, %s\n", name);
}
