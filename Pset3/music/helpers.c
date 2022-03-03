// Helper functions for music

#include <cs50.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "helpers.h"
#include <stdio.h>



// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int num = atoi(&fraction [0]);
    int denom = atoi(&fraction [2]);
    int frac = (8 / denom) * num;
    return frac;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    char letter;
    char accident = 0;
    float octave = 0.0;

    if (strlen(note) == 3)
    {
        letter = note [0];
        accident = note [1];
        octave = atoi(&note[2]);
    }
    if (strlen(note) == 2)
    {

        letter = note [0];
        octave = atoi(&note [1]);
    }
    int octcont;
    float hz = 0.0;

    // se  calcula la octava es 4 - 440*2  , 2* cada cont -4
    //se saca la letra y la oct , se calcula para obtener  los valores
    if (octave == 4)
    {

        hz = 440.00;
    }

    else if (octave > 4)
    {
        octcont = (octave - 4);
        hz = 440 * pow(2, octcont);
    }
    else if (octave < 4)
    {
        octcont = 4 - octave;
        hz = 440 / pow(2, octcont);
        printf(" %.2f\n", hz);
    }


    float hertz = 0.0;
    float numer = 0.0;
    float mat = pow(2.0, (numer / 12));

    switch (letter)
    {

        case 'C':
        {
            float  power = pow(2, (9.0 / 12));
            hertz = hz / power;
            break;
        }

        case 'D':
        {
            float  power = pow(2, (7.0 / 12));
            hertz = hz / power;
            break;
        }
        case 'E':
        {
            float  power = pow(2, (5.0 / 12));
            hertz = hz / power;
            break;
        }
        case 'F':
        {
            float  power = pow(2, (4.0 / 12));
            hertz = hz / power;
            break;
        }
        case 'G':
        {
            float  power = pow(2, (2.0 / 12));
            hertz = hz / power;
            break;
        }
        case 'A':
        {
            numer = 12.0;
            hertz = hz * mat;
            break;
        }
        case 'B':
        {
            float  power = pow(2, (2.0 / 12));
            hertz = hz * power;
            break;
        }

    }

    switch (accident)
    {
        //expecion
        case '#':
        {
            float power = pow(2, (1.0 / 12));
            hertz = hertz * power;
            break;
        }
        case 'b':
        {
            float power = pow(2, (1.0 / 12));
            hertz = (hertz / power);
            break;
        }
        default:
        {
            break;
        }

    }

    int hertzfinal = round(hertz);
    return hertzfinal;

}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (strcmp(s, "") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}


