#include <stdio.h>
#include <cs50.h>

int checksum (long cardnumber);
int credit_card_lenght(long cardnumber);
void print_brand (int digirs, int counter);
int starting_digits (long cardnumber);


//main
int main(void)
{

    long cardnumber;
    
    //prompt for user
    do
    {
    cardnumber = get_long("Number?:   ");
    }
    while (cardnumber < 0);
    int tuvieja = checksum(cardnumber);
    printf ("%i\n", tuvieja);
  

}



int checksum (long cardnumber)
    {

    int remainder1;
    int remainder2;
    int check1;
    int check2;
    check1 = 0;
    check2 = 0;
    int checksum;
    
        do
        {
        remainder1 = cardnumber %10;
        check1 = check1 + remainder1;
        cardnumber = (cardnumber - remainder1) /10;
        remainder2 = cardnumber %10;
        int digit = remainder2 *2;
        check2 = check2 + digit /10 + digit % 10;
        cardnumber = (cardnumber - remainder2) /10;
        }
        while (cardnumber > 0);
        checksum = (check1 + check2) %10;
        return checksum;
        
    }
    
    
  