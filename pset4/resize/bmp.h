// BMP-related data types based on Microsoft's own

#include <stdint.h>

// aliases for C/C++ primitive data types
// https://msdn.microsoft.com/en-us/library/cc230309.aspx
typedef uint8_t  BYTE;
typedef uint32_t DWORD;
typedef int32_t  LONG;
typedef uint16_t WORD;

// information about the type, size, and layout of a file
// https://msdn.microsoft.com/en-us/library/dd183374(v=vs.85).aspx
typedef struct
{
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
    
} __attribute__((__packed__))
BITMAPFILEHEADER;

// information about the dimensions and color format
// https://msdn.microsoft.com/en-us/library/dd183376(v=vs.85).aspx
typedef struct
{
    DWORD biSize;//tamaño de la estructura
    LONG biWidth;//ancho de la estructura
    LONG biHeight;//altura de la estructura
    WORD biPlanes;//lee los bits segun su componente
    WORD biBitCount;//determina el numero de bits de cada pixel
    DWORD biCompression;//tipo de compresion de un mapa de bits comprimido ascendentemente
    DWORD biSizeImage;//determina el tamaño de la imagen
    LONG biXPelsPerMeter;//especifica la impresion horizontal de los pixeles
    LONG biYPelsPerMeter;//especifica la impresion vertical de los pixeles
    DWORD biClrUsed;//especifica el numero de color
    DWORD biClrImportant;//Especifica el número de índices de color necesarios para mostrar el mapa de bits
} __attribute__((__packed__))
BITMAPINFOHEADER;

// relative intensities of red, green, and blue
// https://msdn.microsoft.com/en-us/library/dd162939(v=vs.85).aspx
typedef struct
{
    BYTE rgbtBlue;//cantidad de azul
    BYTE rgbtGreen;//cantidad de verde
    BYTE rgbtRed;//cantidad de rojo
} __attribute__((__packed__))
RGBTRIPLE;
