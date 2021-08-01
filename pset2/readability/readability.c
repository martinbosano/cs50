///libraries included
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/// functions declaration
int count_words(string text);
int count_letters(string text);
int count_sentences(string text);
int coleman_liau_index(int words, int letters, int sentences);

/// main function
int main(void)
{
    /// get user input
    string text = get_string("Text?:     ");
    ///integers used in the function
    int words = count_words(text);
    int letters = count_letters(text);
    int sentences = count_sentences(text);
    int grade = coleman_liau_index(words, letters, sentences);
    ///grade clasification
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 1 && grade < 16)
    {
        printf("Grade %i\n", grade);
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    printf("G %i", grade);
    printf("L %i", letters);
    printf("W %i", words);
    printf("S %i", sentences);
}


//// contar letras
int count_letters(string text)
{
    int characters = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            characters++;
        }
    }
    return characters;
}


/// count sentences
int count_sentences(string text)
{
    int sentences = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            sentences++;
        }
    }
    return sentences;

}


/// count words
int count_words(string text)
{
    int words = 1;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isblank(text[i]))
        {
            words++;
        }
    }
    return words;
}


/// coleman liau algorythm

int coleman_liau_index(int words, int letters, int sentences)
{
    float S = (100.0 * sentences) / words;
    printf("%f\n", S);
    float L = (100.0 * letters) / words;
    printf("%f\n", L);
    float index = 0.0588 * L - 0.296 * S - 15.8;
    printf("%f\n", index);
    int grade = round(index);
    return grade;
}


