#include <stdio.h>
#include <cs50.h>

int main(void)
{   //declaramos las variables, de tipo long long para almacenar y manipular todo
    long long tarjeta, i, mult;
    int validsum, prod, sum; //valid es para validacion de suma

    do{
        tarjeta = get_long("Ingrese el numero de tarjeta: \n");
        }
    while (tarjeta < 0);

    for(i = tarjeta; validsum = 0, i > 0; i /= 100) //declaramos i y asignamos el valor de tarjeta para no modificar el valor que el usuario ingresa en la variable tarjeta
        validsum += i % 10; //mod 10

    for(mult = tarjeta/10, prod = 0; mult > 0; mult /= 100)//mult toma el valor de i, se divide entre 100, prod de multiplicar se iguala a 0
    {                                                //mult debe ser mayor que cero, se divide entre 100
        if(2 * (mult % 10) > 9)// si el mult es mayor que cero, mod 10
        {
            prod += (2 *(mult % 10)) / 10;
            prod += (2 *(mult % 10)) % 10;
        }
        else
        {
            prod += 2 * (mult % 10);
        }
    }
    sum = validsum + prod; //sum almacena el valor de la validacion sumado al del producto

    if (sum % 10 == 0)//si el mod 10 de sum es igual a cero
    {
        if ((i >= 340000000000000 && i < 350000000000000) || (i >= 370000000000000 && i < 380000000000000))//si la tarjeta esta en estos parametros, recorda que amex tiene 15 digitos)
        {
            printf("AMEX\n");
        }
        else if (i >= 5100000000000000 &&  i < 5600000000000000)//mastercard tiene 16
        {
            printf("Mastercard\n");
        }
        else if ((i >= 4000000000000 && i < 5000000000000) || (i >= 4000000000000000 && i < 5000000000000000))//y visa entre 13 & 16
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALIDO\n"); // si no cumple, es invalida
        }
    }
    else
    {
        printf("INVALID \n"); //si no cumple nada tambien es invalida :p
    }
    return 0;
}