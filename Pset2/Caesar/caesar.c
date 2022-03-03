#include<stdio.h>
#include<cs50.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


int main(int argc, string argv [])
{
//si la condicion no s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e cumple el programa debera imprimir el mensaje y retornar al inicio
    if (argc != 2)
    {
        return 1;
    }
    string p = get_string("Plaintext: ");
    //atoi es una de las funciones de la libreria stdlib la cual permite convertir un numero en int
    int key = atoi(argv[1]);

    printf("ciphertext: ");
    for (int i = 0; i < strlen(p) ; i++)
    {
        //Comprobar si es de caracter alfabetico
        if (!isalpha(p[i]))
        {
            printf("%c", p[i]);
        }
        else

            //usa formula c i = (p i+ k ) mod 26
            if (p[i] > 'Z')
            {
                printf("%c", (p[i] - 'a' + key) % 26 + 'a');
            }
            else
            {
                printf("%c", (p[i] - 'A' + key) % 26 + 'A');
            }

    }



    printf("\n");


}