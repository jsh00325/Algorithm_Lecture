import random as rd

n, range1, range2 = 12, 100, 200
ans = [[0]*n for _ in range(n)]
for i in range(n) :
    for j in range(i+1, n) :
        ans[i][j] = ans[j][i] = rd.randint(range1, range2)

with open("input.txt", "w") as f :
    f.write("{}\n{}".format(n, '\n'.join([' '.join([str(x) for x in i]) for i in ans])))