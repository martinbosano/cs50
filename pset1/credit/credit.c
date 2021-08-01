#include <stdio.h>
#include <cs50.h>

//checksum math
int checksum(long cardnumber);
// how many numbers has the credit card
int credit_card_lenght(long cardnumber);
// card brand printing function
void print_brand(int digirs, int counter);
//get the starting digits function
int starting_digits(long cardnumber);


//main function
int main(void)
{

    long cardnumber;

    //prompt for user
    do
    {
        cardnumber = get_long("Number?:   ");
    }
    while (cardnumber < 0);

    //card check
    if (checksum(cardnumber) == 0)
    {
        int digits = starting_digits(cardnumber);
        int counter = credit_card_lenght(cardnumber);
        print_brand(digits, counter);
        
    }

    else
    {
        printf("INVALID\n");
    }
    int check = checksum(cardnumber);
    printf("%i\n", check);
}


//secondary functions


// print card function
void print_brand(int digits, int counter)
{
    if ((digits == 34 && counter == 15) || (digits == 37 && counter == 15))
    {
        printf("AMEX\n");
    }
    else if (digits >= 51 && digits <= 55 && counter == 16)
    {
        printf("MASTERCARD\n");
    }
    else if ((digits >= 40 && digits <= 49 && counter == 13) || (digits >= 40 && digits <= 49 && counter == 16))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}


//checksum function
int checksum(long cardnumber)
{

    int remainder1, remainder2, check1, check2, checksum;
    check1 = 0;
    check2 = 0;


    do
    {
        remainder1 = cardnumber % 10;
        check1 = check1 + remainder1;
        cardnumber = (cardnumber - remainder1) / 10;
        remainder2 = cardnumber % 10;
        int digit = remainder2 * 2;
        check2 = check2 + digit / 10 + digit % 10;
        cardnumber = (cardnumber - remainder2) / 10;

    }
    while (cardnumber > 0);
    checksum = (check1 + check2) % 10;
    return checksum;

}



//calculate card lenght
int credit_card_lenght(long cardnumber)
{
    int counter = 0;


    while (cardnumber > 0)
    {
        cardnumber = cardnumber / 10;
        counter++;
    }

    return counter;
}



// getting starting digits
int starting_digits(long cardnumber)
{
    int digits;
    do
    {
        digits = (cardnumber - cardnumber % 10) / 10;
        cardnumber = (cardnumber - cardnumber % 10) / 10;
    }
    while (cardnumber > 100);
    return digits;
}




