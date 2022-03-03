from cs50 import get_int

height = -1
while True:
    altura = get_int("Heinght: ")
    if altura >= 0 and altura < 24:
        break

for fila in range(1, altura+1, 1):
    for columna in range(1, (altura - fila + 1), 1):
        print(" ", end="")
    for columna in range(0, fila + 1, 1):
        print("#", end="")
    print()