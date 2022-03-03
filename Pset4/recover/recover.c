#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define buffer_size 512

//validador de imagen
bool validateImage(unsigned char buffer [])


{
    if (buffer [0] == 0xff && buffer [1] == 0xd8 && buffer [2] == 0xff && (buffer [3] == 0xe1 || buffer [3] == 0xe0))
    {
        return true;
    }
    else
    {
        return false;
    }

}
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover card.raw\n");
        return 1;
    }
    //se abre la memoria
    FILE *inFile = fopen(argv[1], "r");

    if (inFile == NULL)
    {
        printf("Could not open file");
        return 2;
    }
    //se crea el buffer
    unsigned char buffer [buffer_size];

    //archivo de counter
    int filecount = 0;

    FILE *outFile = NULL;

    //char * filename = malloc (8 * sizeof (char));
    char filename [8];

    //contador
    int cont = 0;

    //lectura de la confirmacion de los 512 bytes
    while (fread(& buffer, buffer_size, 1, inFile) == 1)
    {
        if (validateImage(buffer))
        {

            if (cont == 1)
            {
                fclose(outFile);
            }
            else if (cont == 0)
            {
                cont++;
            }
            //comprobacion de la imagen
            sprintf(filename, "%03i.jpg", filecount);
            outFile = fopen(filename, "w");
            filecount++;
        }
        if (cont == 1)
        {
            //se reescribe archivo de salida
            fwrite(&buffer, buffer_size, 1, outFile);
        }


    }
    //se cierra entrada

    fclose(inFile);
    return 0;
}