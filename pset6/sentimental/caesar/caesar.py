from cs50 import get_string
import sys

def main():
    if len(sys.argv) != 2:
        print("Usando ./caesar")
        sys.exit(1)
    llave = int(sys.argv[1])
    if llave < 0:
        print("Error")
        sys.exit(1)
    plaintext = get_string("Plaintext: ")
    print("ciphertext: ", end="")
    for chr_txt in plaintext:
        if chr_txt.islower():
            print(chr(((ord(chr_txt) - 97) + llave)% 26 + 97) ,end="")
        elif chr_txt.isupper():
            print(chr(((ord(chr_txt)- 65) + llave) % 26 + 65) ,end="")
        else:
            print(chr_txt, end="")
    print()
if __name__ == "__main__":
    main()

# sys.argv, ord, chr, str -> int, leng, islower, isupper
