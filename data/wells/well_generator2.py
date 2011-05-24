#!/usr/bin/python
import math
import random

# x in (0;1) range
# result in (0;1)


def sigmoid(x):
	x = x * 12.0
	return (math.atan(x-6) + math.pi/2.0)/ math.pi

def save_in_file(wellindex, origin, list):
	file = open(str(wellindex), "w+")
	file.write("origin : %f %f %f\n" % origin)
	file.write("curves : %s %s %s %s\n" % ('X', 'Y', 'Z', 'Data'))
	for line in list:
		file.write("%f %f %f %f\n" % line)

	file.close()


def generate_well(wellindex):
	random.seed()
	
	c1 = float(random.randint(0,10))
	c2 = float(random.randint(0,10))
	c3 = float(random.randint(0,10))

	angle = wellindex / 10.0 * math.pi * 2
	rad = 200
	alt = random.randint(0, 100)

	scale = 350
	originscale = 100

	origin = (originscale * math.cos(angle), originscale * math.sin(angle), alt)

	step = 5 #between poinst

	list = []
	#50 points in each well
	pointnum = 500
	for i in range(0, pointnum + 1):
		depth = float(i)/float(pointnum)
		val = sigmoid(depth)  * scale
		data = math.sin(c1 * i / math.pi) * math.sin(c2 * i / math.pi) * math.sin(c3 * i / math.pi)
		list.append((val * math.cos(angle), val * math.sin(angle), i * step, data))

	# list is complete

	save_in_file(wellindex, origin, list)



if __name__ == "__main__":
	for i in range(1,11):
		generate_well(i)
