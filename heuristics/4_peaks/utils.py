from random import randint

def fitness(bits : list[int], T : int) -> int:
    
    MAX = len(bits)

    def z(bits : list[int]):
        qtd = 0

        while qtd < MAX and bits[qtd] == 1:
            qtd += 1

        return qtd

    def o(bits : list[int]):
        qtd = MAX -1

        while 0 <= qtd and bits[qtd] == 0:
            qtd -= 1

        return MAX - (qtd + 1)

    

    p1 = z(bits)
    p2 = o(bits)

    return p1 + p2 + (100 if p1 > T and p2 > T else 0)

def gen_element(MAX : int, continuous : bool = True) -> list[int]:
    ret = []

    if continuous:
        dif = randint(0, MAX)
        for _ in range(dif):
            ret.append(1)
        while len(ret) < MAX:
            ret.append(0)
    else:
        while len(ret) < MAX:
            ret.append(randint(0, 1))

    return ret
