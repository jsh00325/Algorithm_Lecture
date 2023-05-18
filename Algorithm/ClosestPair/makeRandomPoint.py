import random as rd

minX, maxX = -500, 500
minY, maxY = -500, 500
pointCount = 200

with open("input.txt", "w") as f :
    f.write(f'{pointCount}\n')
    for point in [(rd.randint(minX, maxX), rd.randint(minY, maxY)) for _ in range(pointCount)] :
        f.write(f'{point[0]} {point[1]}\n')