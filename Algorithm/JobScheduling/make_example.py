import random as rd

n, range1, range2 = 10, 1, 30

with open("input.txt", "w") as f :
    f.write(f'{n}\n')
    for _ in range(n) :
        st = rd.randint(range1, range2 - 1)
        en = rd.randint(st+1, range2)
        f.write(f'{st} {en}\n')