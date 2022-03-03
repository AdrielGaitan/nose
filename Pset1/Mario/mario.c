#include <stdio.h>
#include <cs50.h>
int main(void)
{
    int height;

    do
    {
        height =  get_int("Height: ");

    }
    while (height > 23 || height < 0);

    for (int cont1 = 1 ; cont1 <= height ; cont1++)
    {
        for (int cont2 = 0 ; cont2 <= height ; cont2++)
        {
            if (cont1 + cont2 <= height - 1)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }

        }
        printf("\n");
    }



}