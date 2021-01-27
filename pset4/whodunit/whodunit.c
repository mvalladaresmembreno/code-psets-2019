//whodunit.c
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 3)
    {
        fprintf(stderr, "Usage: whodunit infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[1];//infile es el nombre del archivo de entrada
    char *outfile = argv[2];//archivo de salida

    // open input file
    FILE *inptr = fopen(infile, "r");//puntero de tipo file que apunta al archivo de entrada, abre los datos del archivo
    if (inptr == NULL)//argumento ingresado por el usuario es invalido
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");//tipo file que apunta hacia el archivo de salida, puede escribir en el archivo xd
    if (outptr == NULL)//si el argumento es invalido
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;//variable tipo estructura
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);//lo que se lee lo guardas en bf, lees el tamaño de fileheader

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);//aspersan para acceder a la memoria de bf, escribis en bf el outptr una vez el tamaño del fileheader

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);//escribis en outptr el tamaño del infoheader

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;//multiplicas el tamaño del rgbtriple por la anchura de la imagen, el resultado debe ser multiplo de 4, por eso las operaciones y lo almacenas en padding pa que rellene la imagen con ceros

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            // printf("%d,%d,%d,\n", triple.rgbtBlue, triple.rgbtGreen, triple.rgbtRed);
            // write RGB triple to outfile
            if (triple.rgbtRed == 255 && triple.rgbtBlue == 255 && triple.rgbtGreen == 255)
            {
                triple.rgbtRed = 255;
                triple.rgbtBlue = 0;
                triple.rgbtGreen = 0;
            }
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
