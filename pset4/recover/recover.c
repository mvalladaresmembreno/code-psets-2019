//recover.c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE 512

bool validar(unsigned char buffer[SIZE])
{
    if (buffer[0] != 0xff || buffer[1] != 0xd8 || buffer[2] != 0xff)
    {
        return false;
    }
    for (unsigned char i = 0xe0; i <= 0xef; i++)
    {
        if (buffer[3] == i)
        {
            return true;
        }
    }
    return false;
}
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage recover fimage\n");
        return 1;
    }
    char *nombre_archivo = argv[1];
    FILE *archivo = fopen(nombre_archivo, "r");

    if (archivo == NULL)
    {
        fprintf(stderr, "Could not open %s", nombre_archivo);
        return 2;
    }

    unsigned char buffer[SIZE];
    char nombre[8];
    int n = 0;

    fread(&buffer, SIZE, 1, archivo);

    while (fread(&buffer, SIZE, 1, archivo) == 1)
    {
        if (validar(buffer))
        {
            sprintf(nombre, "%03d.jpg", n);
            FILE *img = fopen(nombre, "a");
            n++;
            do
            {
                fwrite(&buffer, SIZE, 1, img);
                fread(&buffer, SIZE, 1, archivo);
            }
            while (!validar(buffer) && feof(archivo) == 0);
            fclose(img);
            fseek(archivo, -1 * SIZE, SEEK_CUR);
        }
    }
    fclose(archivo);
    return 0;

}