import random as rd

f = open("input.txt", "w")

n = int(input("n : "))
f.write(f'{n}\n')
for _ in range(n) :
	f.write(' '.join([str(rd.randint(0, 1)) for _ in range(n)]) + '\n')