// Helper functions for music
#include <string.h>
#include <cs50.h>
#include <math.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int duracion;
    int num = fraction[0] - '0';
    int den = fraction[2] - '0';
    return num * 8 / den;
}
// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    const string NOTES[] = {"C", "C#", "D", "D#", "E", "F",
                            "F#", "G", "G#", "A", "A#", "B"
                           };
    char notita[2] = {note[0], '\0' };
    int contador = 0;
    while (strcmp(NOTES[contador], notita))
    {
        contador++    ;
    }
    contador = contador - 9;

    if (note[1] == '#')
    {
        contador++;
        int octavas = note[2] - '0';
        contador += (octavas - 4) * 12;
    }
    else if (note[1] == 'b')
    {
        contador--;
        int octavas = note[2] - '0';
        contador += (octavas - 4) * 12;

    }
    else
    {
        int octavas = note[1] - '0';
        contador += (octavas - 4) * 12;
    }
    return round(pow(2.0, (float) contador / 12) * 440);

}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    int descanso = strcmp(s, "");
    if (descanso == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}