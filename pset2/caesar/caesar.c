//Inicio del programa: Implementa un programa que cifre mensajes usando el cifrado Caesar,
//en el cual una letra de un texto original es reemplazada por otra letra que se encuentra en
//un número fijo de posiciones más adelante en el alfabeto.
#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(int argc, string argv[]) //declaramos la funcion main, un argumento de tipo entero y un arreglo de cadenas
{
    if (argc != 2)
    {
        printf("usando ./caesar \n");
        return 1;
    }

    int llave = atoi(argv[1]);
    if (llave < 0)
    {
        printf("Error\n");
        return 1;
    }

    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (islower(plaintext[i]))
        {
            printf("%c", ((plaintext[i] - 97) + llave) % 26 + 97);
        }
        else if (isupper(plaintext[i]))
        {
            printf("%c", (plaintext[i] - 65 + llave) % 26 + 65);
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
    return 0;
}