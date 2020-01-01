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
	for line in list:
		file.write("%f %f %f\n" % line)

	file.close()


def generate_well(wellindex):
	random.seed()

	angle = wellindex / 10.0 * math.pi * 2
	rad = 200
	alt = random.randint(0, 100)

	scale = 350
	originscale = 100

	origin = (originscale * math.cos(angle), originscale * math.sin(angle), alt)

	step = 50 #between poinst

	list = []
	#50 points in each well
	pointnum = 50
	for i in range(0, pointnum + 1):
		depth = float(i)/float(pointnum)
		val = sigmoid(depth)  * scale
		list.append((val * math.cos(angle), val * math.sin(angle), i * step))

	# list is complete

	save_in_file(wellindex, origin, list)



if __name__ == "__main__":
	for i in range(1,11):
		generate_well(i)
