#!/usr/bin/python
import math
import random

def save_in_file(list, name):
	file = open("points_"+name, "w+")
	for line in list:
		file.write("%f %f %f\n" % line)

	file.close()


def generate_well(name):
	random.seed()
    
	list = []
	for i in range(0, 20):
		x = random.randint(-500, 500)
		y = random.randint(-500, 500)
		z = random.randint(1800, 1900)

		if name == "bottom": z -= 250;

		list.append((x, y, z))

	save_in_file(list, name)



if __name__ == "__main__":
		generate_well("up")
		generate_well("bottom")
