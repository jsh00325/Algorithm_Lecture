import random as rd

minX, maxX = 0, 2000000000
minY, maxY = 0, 2000000000
pointCount = 3000000

rslt = []
while len(rslt) < pointCount :
    point = (rd.randint(minX, maxX), rd.randint(minY, maxY))
    rslt.append(point)

with open("input.txt", "w") as f :
    f.write(f'{pointCount}\n')
    for point in rslt :
        f.write(f'{point[0]} {point[1]}\n')