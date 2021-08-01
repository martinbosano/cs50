#include <stdio.h>
#include <cs50.h>
#include <math.h>

//main
int main(void)
{
    float dolars;
    do 
    {
        dolars = get_float("Cash?:   ");
    }
    while (dolars < 0);
    
    int cents = round(dolars * 100);
    int a = 25;
    int b = 10;
    int c = 5;
    int d = 1;
    int monedas = 0;
    
    while (cents >= a)
    {
    cents = cents - a;
    monedas++;
    }
    
    while (cents >= b)
    {
    cents = cents - b;
    monedas++;
    }
    while (cents >= c)
    {
    cents = cents - c;
    monedas++;
    }
    while (cents >= d)
    {
    cents = cents - d;
    monedas++;
    }
    printf("%i\n", monedas);
}