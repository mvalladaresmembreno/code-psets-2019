from cs50 import get_float


def main():

    cambio = 0
    contador = 0
    while (cambio <= 0):
        cambio = get_float("Cambio: ")

    centavos = int(cambio * 100)

    while (centavos >= 25):
        contador += 1
        centavos -= 25

    while (centavos >= 10):
        contador += 1
        centavos -= 10

    while (centavos >= 5):
        contador += 1
        centavos -= 5

    while (centavos >= 1):
        contador += 1
        centavos -= 1

    print(contador)


if __name__ == "__main__":
    main()
