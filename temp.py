def add(a, b):
    x = 10
    result = 0
    while x > 0:
        result = result + a
        result = result * b
        x = x - 1
    return result


print(add(2, 3))
