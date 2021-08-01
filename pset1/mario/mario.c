#include <stdio.h>
#include <cs50.h>

//main
int main(void)
{
    //question for the user
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);


    // each floor loop
    for (int i = 0; i < n; i++)
    {
        //spaces
        for (int j = n - 1; j > i; j--)
        {
            printf(" ");
        }
        //hashes
        for (int k = 0; k < i + 1; k++)
        {

            printf("#");
        }
        //space between pyramids
        printf("  ");
        for (int l = 0; l < i + 1; l++)
        {
            printf("#");
        }
        printf("\n");
    }
}
