#include <stdio.h>
#include <cs50.h>

//main
int main(void)
{

    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    for (int i = 0; i < n; i++)
    {
        for (int j = n -1; j > i; j--)
            {
                printf(" ");
            }
        for (int k = 0; k < i+1; k++)
        {

         printf("#");
        }
        printf("  ");
        for (int l = 0; l < i +1; l++)
        {
            printf("#");
        }


    printf("\n");
    }
}
