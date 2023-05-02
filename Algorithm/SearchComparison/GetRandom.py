import random as rd

n = 274000
lst = rd.sample(range(1, 1000000000), n)

f = open('input.txt', 'w')
f.write(f'{n} {rd.choice(lst)}\n')
for i in lst :
    f.write(str(i)+'\n')
f.close()
