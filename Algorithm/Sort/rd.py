import random as rd

len = 30000
mx_int = 10000

f1 = open("input1.txt", "w")
f2 = open("input2.txt", "w")
f3 = open("input3.txt", "w")

f1.write(str(len)+'\n')
f2.write(str(len)+'\n')
f3.write(str(len)+'\n')
for i in range(len) :
	f1.write(str(rd.randint(1, mx_int))+'\n')
	f2.write(str(i+1)+'\n');
	f3.write(str(len-i)+'\n');
f1.close()
f2.close()
f3.close()