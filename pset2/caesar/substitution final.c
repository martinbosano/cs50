#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

bool validity (int argc, char argv[]);

/// main function

int main (int argc, string argv[])
{

    if (validity(argc, argv[1]) == 1)
    {
        return 1;
    }
    string plainText = get_string("plaintext: ");
    char key [strlen(argv[1])];
    char cipherText [strlen(plainText)];
    for (int i = 0; i < strlen(plainText); i++)
    {
       if (isalpha(plainText[i]) && islower(plainText[i]))
       {
           cipherText[i] = (plainText[i] - 97);
       }
       else if(isalpha(plainText[i]) && isupper(plainText[i]))
       {
           cipherText[i] = (plainText[i] - 65);
       }
       else
       {
           cipherText[i] = plainText[i];
       }
       for (int j = 0; j < strlen(key); j++)
       {
           i
       }
    }
    return 0;
}





/// encipher function










/// validity function
bool validity (int argc, char argv[])
{
   if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    if (strlen(argv) != 26)
        {
            printf("key must contain 26 characters\n");
            return 1;
        }
    for (int i = 0; i <= strlen(argv); i++)
    {
        if (isdigit(argv[i]))
        {
            printf("key must only contain alphabetic characters\n");
            return 1;
        }
        else if (ispunct(argv[i]))
        {
            printf("Invalid: Key must not include punctuation signs\n");
            return 1;
        }
        else if (isblank(argv[i]))
        {
            printf("Invalid: Key must not include blank spaces\n");
            return 1;
        }
        for (int j = i + 1; j <= strlen(argv); j++)
        {
            if (argv[i] == argv[j])
            {
                printf("key must not contain repeated character\n");
                return 1;
            }
        }
    }
    return 0;
}
