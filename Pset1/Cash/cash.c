#include <stdio.h>
#include <cs50.h>
#include <math.h>
int main(void)
{
    float cash;
    int v = 25, d = 10, c = 5, i = 1, contador;
    int conttotal = 0;

    do
    {
        cash1 = get_float("change owed $ ");

    }


    while (cash1 < 0);

    cash = round(cash1 * 100);
    while (v <= cash)
    {
        cash = cash - v;
        conttotal++;
    }
    while (d <= cash)
    {
        cash = cash - d;
        conttotal++;
    }

    while (c <= cash)
    {
        cash = cash - c;
        conttotal++;

    }
    while (i <= cash)
    {
        cash = cash - i;
        conttotal++;

    }


    printf("%d\n", conttotal);




}