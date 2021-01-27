#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int altura;
    int fila;
    int columna;

    do
    {
        altura = get_int("ingrese la altura de la piramide:(un numero entero del 1 al 23)\n");
    }
    while (altura < 0 || altura > 23);

    for (fila = 1; fila <= altura; fila++)
    {
        for (columna = 1; columna <= (altura - fila); columna++)
        {
            printf(" ");
        }
        for (columna = 0; columna <= fila; columna++)
        {
            printf("#");
        }
        printf("\n");
    }
}