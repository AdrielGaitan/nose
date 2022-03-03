// Implementa un corrector ortográfico

#include <ctype.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>

#include "dictionary.h"

// No defina las definiciones
#undef calculate
#undef getrusage

// Diccionario predeterminado
#define DICTIONARY "dictionaries/large"

// el prototipo
double calculate(const struct rusage *b, const struct rusage *a);

int main(int argc, char *argv[])
{
    // Verifique el número correcto de argumentos
    if (argc != 2 && argc != 3)
    {
        printf("Usage: speller [dictionary] text\n");
        return 1;
    }

    // Estructuras para datos de cronometraje
    struct rusage before, after;

    // Benchmarks
    double time_load = 0.0, time_check = 0.0, time_size = 0.0, time_unload = 0.0;

    // Determinar el diccionario para usar
    char *dictionary = (argc == 3) ? argv[1] : DICTIONARY;

    // Lectura del diccionario
    getrusage(RUSAGE_SELF, &before);
    bool loaded = load(dictionary);
    getrusage(RUSAGE_SELF, &after);

    // Salir del diccionario si no logro cargar
    if (!loaded)
    {
        printf("Could not load %s.\n", dictionary);
        return 1;
    }

    // Calcular el tiempo para cargar el diccionario
    time_load = calculate(&before, &after);

    // Intenta abrir el texto
    char *text = (argc == 3) ? argv[2] : argv[1];
    FILE *file = fopen(text, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", text);
        unload();
        return 1;
    }

    // Prepárese para informar errores ortográficos
    printf("\nMISSPELLED WORDS\n\n");

    //Prepárese para revisar la ortografía
    int index = 0, misspellings = 0, words = 0;
    char word[LENGTH + 1];

    // Revise la ortografía de cada palabra en el texto
    for (int c = fgetc(file); c != EOF; c = fgetc(file))
    {
        // Permitir solo caracteres alfabéticos y apóstrofos
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            // Agregar carácter a la palabra
            word[index] = c;
            index++;

            // Ignore las cadenas alfabéticas demasiado largas para ser palabras
            if (index > LENGTH)
            {
                // Consumir el resto de la cadena alfabética
                while ((c = fgetc(file)) != EOF && isalpha(c));

                // Prepárate para una nueva palabra
                index = 0;
            }
        }

        // Ignore las palabras con números (como puede hacerlo MS Word)
        else if (isdigit(c))
        {
            // Consume remainder of alphanumeric string
            while ((c = fgetc(file)) != EOF && isalnum(c));

            // Prepárate para una nueva palabra
            index = 0;
        }

        // Debemos haber encontrado una palabra completa
        else if (index > 0)
        {
            // Terminar palabra actual
            word[index] = '\0';

            // Contador de palabras
            words++;

            // Revisar la ortografía de la palabra
            getrusage(RUSAGE_SELF, &before);
            bool misspelled = !check(word);
            getrusage(RUSAGE_SELF, &after);

            // Actualizar el punto de referencia
            time_check += calculate(&before, &after);

            // Imprimir palabra si está mal escrita
            if (misspelled)
            {
                printf("%s\n", word);
                misspellings++;
            }

            // Prepárate para la próxima palabra
            index = 0;
        }
    }

    //Verifique si hubo un error
    if (ferror(file))
    {
        fclose(file);
        printf("Error reading %s.\n", text);
        unload();
        return 1;
    }

    // Cerrar texto
    fclose(file);

    //Determinar el tamaño del diccionario
    getrusage(RUSAGE_SELF, &before);
    unsigned int n = size();
    getrusage(RUSAGE_SELF, &after);

    // Calcule el tiempo para determinar el tamaño del diccionario
    time_size = calculate(&before, &after);

    //Descargar diccionario
    getrusage(RUSAGE_SELF, &before);
    bool unloaded = unload();
    getrusage(RUSAGE_SELF, &after);

    // Abortar si el diccionario no está descargado
    if (!unloaded)
    {
        printf("Could not unload %s.\n", dictionary);
        return 1;
    }

    // Calcular el tiempo para descargar el diccionario
    time_unload = calculate(&before, &after);

    // Report benchmarks
    printf("\nWORDS MISSPELLED:     %d\n", misspellings);
    printf("WORDS IN DICTIONARY:  %d\n", n);
    printf("WORDS IN TEXT:        %d\n", words);
    printf("TIME IN load:         %.2f\n", time_load);
    printf("TIME IN check:        %.2f\n", time_check);
    printf("TIME IN size:         %.2f\n", time_size);
    printf("TIME IN unload:       %.2f\n", time_unload);
    printf("TIME IN TOTAL:        %.2f\n\n",
           time_load + time_check + time_size + time_unload);

    // exito
    return 0;
}

// Devuelve el número de segundos entre b y a
double calculate(const struct rusage *b, const struct rusage *a)
{
    if (b == NULL || a == NULL)
    {
        return 0.0;
    }
    else
    {
        return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) -
                  (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
                 ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec) -
                  (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec)))
                / 1000000.0);
    }
}
