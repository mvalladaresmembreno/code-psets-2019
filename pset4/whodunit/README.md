# Questions

## What's `stdint.h`?

Declara conjuntos de tipos enteros para declarar anchos especificos y define conjuntos de macros correspondientes

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

Son tipos enteros usados para medir la longitud en bits de una funcion.
uint8_t es un tipo de entero sin signo con longitud de 8 bits,
uint32_t es un tipo entero sin signo con longitud de 32 bits
int32_t es un tipo de entero con una longitud de 32 bits,
y uint16_t es un tipo de entero sin signo cuya longitud es de 16 bits.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

BYTE tiene 1 byte, DWORD tiene 4 bytes, LONG tiene 4 bytes y WORD tiene 2 bytes.

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

El primero es la firma, lo que identifica al archivo como un BMP con dos caracteres,
la segunda muestra el tamaño total del archivo en bytes.

## What's the difference between `bfSize` and `biSize`?

bfSize es el tamaño del archivo BMP completo, que incluye los archivos de encabezado,
mientras que biSize es el tamaño del archivo de encabezado BITMAPINFOHEADER.

## What does it mean if `biHeight` is negative?

Significa que el mapa de bits es un DIB de arriba a abajo y empieza en la esquina
superior izquierda.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

Lo especifica biClrUsed.

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

Returna en un NULL si el archivo al cual apunta esta vacio, e indica que el archivo no puede
abrirse o crearse.

## Why is the third argument to `fread` always `1` in our code?

Porque el fread especifica que solamente lee 1 vez el archivo.

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

Asigna a padding el valor de 3.

## What does `fseek` do?

Mueve la posicion del puntero a una direccion especifica.

## What is `SEEK_CUR`?

SEEK_CUR es una funcion que mueve la posicion del puntero del archivo a una posicion especifica..
