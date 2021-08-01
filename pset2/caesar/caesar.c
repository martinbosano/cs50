#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



int main (int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    for (int i = 0; i <= strlen(argv[1]); i++)
    {
        if (isalpha(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    string plainText = get_string("plaintext: ");
    int k = atoi(argv[1]);
    char cipherText [strlen(plainText)];
    for (int i = 0; i < strlen(plainText); i++)
    {
        if (isalpha(plainText[i]) && islower(plainText[i]))
        {
            cipherText[i] = (((plainText[i] - 97 + k) % 26) + 97);
        }
        else if(isalpha(plainText[i]) && isupper(plainText[i]))
        {
            cipherText[i] = (((plainText[i] - 65 + k) % 26) + 65);
        }
        else
        {
            cipherText[i] = plainText[i];
        }
    }
    printf("ciphertext:%s\n",cipherText);
    return 0;
}