import random

file = open("points", "w")

for i in range(0, 30):
	x = random.randint(-100, 100)
	y = random.randint(-100, 100)
	z = random.randint(0, 20)
	file.write("%d %d %d\n" % (x, y, z))

file.close()		