#:!/usr/bin/python
import math
import random

def save_in_file(wellindex, curve_names, list):
	file = open(str(wellindex), "w+")
	s = "curves : " +  " %s" * len(curve_names) + "\n"
	file.write(s % curve_names)
	for line in list:
		file.write(("%f " * len(line) + "\n") % line)

	file.close()


def generate_well(wellindex):
	print "generate well"
	random.seed()

	c1 = float(random.randint(0, 10))
	c2 = float(random.randint(0, 10))	
	c3 = float(random.randint(0, 10))


	step = 2 #between poinst
	top_depth = 2600

	list = []
	#100 points in each well
	pointnum = 100
	for i in range(0, pointnum + 1):
		depth = top_depth + i * step
		val = math.sin(c1 * i / math.pi) * math.sin(c2 * i / math.pi) * math.sin(c3 * i / math.pi)
		list.append((depth, val))

	# list is complete

	save_in_file(wellindex, ("depth", "value"),list)



if __name__ == "__main__":
	for i in range(1,11):
		generate_well(i)
