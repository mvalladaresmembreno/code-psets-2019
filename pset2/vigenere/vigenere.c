//Implementa el cifrado Vigenère, el cual mejora considerablemente el cifrado Caesar
#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2) // son 2 pq son 2 argumentos
    {
        printf("usando ./vigenere \n");
        return 1;
    }
    int key = 0;
    string llave = argv[1];

    for (int i = 0; i < strlen(llave); i++)// strlen pa calcular la longitud en enteros del string, el for ta pa recorrer la palabra
    {
        if (!isalpha(llave[i])) // si la llave en la posicion del contador i, se verifica que sea un caracter alfabetico
        {
            printf("Error, ingrese un comando válido.\n");
            return 1; //marca un error si no es alfabetico
        }
    }

    string plaintext = get_string("Ingrese el texto plano: ");// ingresar el texto plano
    printf("ciphertext: ");
    for (int i = 0, j = 0; i < strlen(plaintext); i++)
    {
        if (strlen(llave) == j)
        {
            j = 0;
        }
        if (isalpha(llave[j]))
        {
            if (islower(llave[j]))
            {
                key = llave[j] - 97;
            }

            else if (isupper(llave[j]))
            {
                key = llave[j] - 65;
            }

            if (islower(plaintext[i]))
            {
                printf("%c", (plaintext[i] - 97 + key) % 26 + 97);
                j++;
            }
            else if (isupper(plaintext[i]))
            {
                printf("%c", (plaintext[i] - 65 + key) % 26 + 65);
                j++;
            }

            else
            {
                printf("%c", plaintext[i]);
            }
        }

    }
    printf("\n");
    return 0;
}
