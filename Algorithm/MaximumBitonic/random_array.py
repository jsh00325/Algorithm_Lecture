import random as rd

f = open("input.txt", "w")

t, n = 10, 10

f.write(f'{t} {n}\n')
for _ in range(t) :
    left = sorted(rd.sample(list(range(1, n)), rd.randint(1, n-2)))
    right = sorted([x for x in range(1, n) if left.count(x) == 0], reverse=True)
    f.write(' '.join([str(x) for x in left + [n] + right])+'\n')
f.close()