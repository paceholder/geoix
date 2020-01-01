import random

f = open("points.txt", "w")

for i in range(0, 40):
	x = random.randint(0, 200)
	y = random.randint(0, 200)
	z = float(random.randint(0, 40))/100.0
	f.write("%d %d %f\n" % (x, y, z))

f.close()		
