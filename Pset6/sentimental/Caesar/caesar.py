import sys
from cs50 import get_string

# sys = La lista de argumentos de
# la línea de comandos pasados a un script de Python.


def main():
    # si la condicion no se cumple
    # el programa debera imprimir el mensaje y retornar al inicio

    if len(sys.argv) != 2:
        print("Usage: ./caesar k")
        sys.exit(1)

    k = int(sys.argv[1])
    plaintext = get_string("Plaintext: ")

    print("ciphertext: ", end="")

    for ch in plaintext:
        if not ch.isalpha():
            print(ch, end="")
            continue
        # formula
        ascc = 65 if ch.isupper() else 97

        pi = ord(ch) - ascc
        ci = (pi + k) % 26

        print(chr(ci + ascc),  end="")

    print()


if __name__ == "__main__":
    main()