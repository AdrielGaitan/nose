from cs50 import get_float

# como no hay ciclo do-while el while siempre sera verdadero
while True:
    # se escribe la solicitud
    cash = get_float("Change owed: ")
    # se aplica la condición
    if (cash) >= 0:
        # se usa el break
        break

centts = round(cash * 100)
coint = 0

while centts >= 25:
    centts -= 25
    coint += 1

while centts >= 10:
    centts -= 10
    coint += 1

while centts >= 5:
    centts -= 5
    coint += 1

while centts >= 1:
    centts -= 1
    coint += 1

print(coint)
