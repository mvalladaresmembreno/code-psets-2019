#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float cambio;
    do
    {
        cambio = get_float("Cambio: ");
    }
    while (cambio < 0);
    int centavos = round(cambio * 100);

    int contador = 0;
    while (centavos >= 25)
    {
        contador++;
        centavos -= 25;
    }
    while (centavos >= 10)
    {
        contador++;
        centavos -= 10;
    }
    while (centavos >= 5)
    {
        contador++;
        centavos -= 5;
    }
    while (centavos >= 1)
    {
        contador++;
        centavos -= 1;
    }
    printf("%d\n", contador);

}
