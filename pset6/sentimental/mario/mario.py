from cs50 import get_int


def main():
    altura = -1
    while altura < 0 or altura > 23:
        altura = get_int("ingrese la altura de la piramide:(un numero entero del 1 al 23): ")

    for fila in range(1, altura+1, 1):
        for columna in range(1, (altura - fila + 1), 1):
            print(" ", end="")
        for columna in range(0, fila + 1, 1):
            print("#", end="")
        print()


if __name__ == "__main__":
    main()
