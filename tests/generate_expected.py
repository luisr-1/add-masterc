def factorial_big(n: int):
    if n < 0:
        # mesmo texto do seu programa:
        return "undefined"
    r = 1
    for i in range(1, n + 1):
        r *= i
    return str(r)


def calculate(op, a, b=None):
    A = int(a)
    if b is not None:
        B = int(b)

    if op == "+":
        return str(A + B)

    if op == "-":
        return str(A - B)

    if op == "*":
        return str(A * B)

    if op == "/":
        # divisão inteira truncada como no C
        if B == 0:
            return "undefined"
        return str(A // B)

    if op == "%":
        # seu C: módulo só permitido se ambos são >= 0
        if A < 0 or B < 0:
            return "Pela definição dada, a operação módulo só é permitida para números positivos"
        if B == 0:
            return "undefined"
        return str(A % B)

    if op == "!":
        return factorial_big(A)

    return "undefined"


scenarios = open("tests/scenarios.txt").read().strip().splitlines()

out = open("tests/expected.txt", "w")

i = 0
while i < len(scenarios):
    line = scenarios[i].strip()
    if not line:
        i += 1
        continue

    op = line[0]

    # caso fatorial
    if op == "!":
        n = scenarios[i + 1].strip()
        result = calculate("!", n)
        if result == "undefined":
            out.write("Fatorial para números reais negativos não é definido\n")
        else:
            out.write(f"!{n} = {result}\n")
        i += 2
        continue

    # operações binárias
    num1 = scenarios[i + 1].strip()
    num2 = scenarios[i + 2].strip()

    result = calculate(op, num1, num2)

    if op == "%" and result.startswith("Pela definição"):
        out.write(result + "\n")
    else:
        out.write(f"{num1} {op} {num2} = {result}\n")

    i += 3

out.close()

print("expected.txt atualizado.")
