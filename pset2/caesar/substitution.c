#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//other functions
bool validity(int argc, char argv[]);


/// main function
int main(int argc, string argv[])
{

    if (validity(argc, argv[1]) == 1)
    {
        return 1;
    }

//list of variables and storage data types used in the program.
    string plainText = get_string("plaintext: ");
    int plain_length = strlen(plainText);
    int key_length = strlen(argv[1]);
    char alphabet[key_length];
    char cipherText[plain_length];
   
///transform all the alphabet to lowercase
    for (int i = 0; i < key_length; i++)
    {
        alphabet[i] = tolower(argv[1][i]);
    }
   
    printf("ciphertext: ");
   
/// ciphertext printing function
    for (int j = 0; j < plain_length; j++)
    {
//if plaintext character is in lowercase, function will print.
        if (islower(plainText[j]))
        {
            int key1 = plainText[j] - 'a';
            cipherText[j] = alphabet[key1];
            printf("%c", cipherText[j]);
        }
/// if plaintext is upper, converts cipher to upper and prints
        else if (isupper(plainText[j]))
        {
            int key2 = plainText[j] - 'A';
            cipherText[j] = toupper(alphabet[key2]);
            printf("%c", cipherText[j]);
        }
/// prints non alpha characters
        else
        {
            cipherText[j] = plainText[j];
            printf("%c", cipherText[j]);
        }
    }
    printf("\n");
    return 0;
}




//implementation of the validity function.
bool validity(int argc, char argv[])
{
///checks amount of command line arguments
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
/// checks amount of characters
    if (strlen(argv) != 26)
    {
        printf("key must contain 26 characters\n");
        return 1;
    }
/// checks for non alphanumeric characters
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
///checks for repeated characters
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