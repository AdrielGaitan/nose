#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

//variable usadas a = datos de entrada , i= contador, key= llave

int main(int argc, string argv [])
{
    int keylend;
    //condicion que especifica que si se cumplen mas d 2 funciones imprimira el mensaje y retornara al inicio
    if (argc != 2)
    {
        printf("Error\n ");
        return 1;
    }
    //mensaje de error si no cumple condiciones
    for (int n = 0 ; n < strlen(argv [1]); n++)
    {
        if (!isalpha(argv[1][n]))
        {
            printf("Error\n ");
            return 1;
        }
    }
    string p  = get_string("plaintext: ");

    printf("ciphertext: ");

    //llave, no lleva atoi porque no es necesario.
    string key = (argv[1]);

    //definicion de variables
    int long_p = strlen(p);
    int long_clave = strlen(key);
    char clave_actual;
    char clave;
    //implementacion de la formula
    for (int j = 0, char_novalido = 0 ; j < long_p; j++)
    {
        clave = tolower(key [(j - char_novalido) % long_clave]) - 97;
        if (islower(p[j]))

        {
            printf("%c", (p[j] - 'a' + clave) % 26 + 'a');
        }

        else if (isupper(p[j]))
        {
            printf("%c", (p[j] - 'A' + clave) % 26 + 'A');
        }
        else
        {
            char_novalido++;
            printf("%c", p[j]);
        }

    }
    //Salto de linea

    printf("\n");
}

