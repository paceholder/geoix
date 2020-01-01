#!/usr/bin/python
import math
import random

""" Script generates two sets of points: for top and bottom of some horisont """


def save_in_file(list, name):
	file = open("points_"+name, "w+")
	for line in list:
		file.write("%f %f %f\n" % line)

	file.close()


def generate_well(name):
	random.seed()
    
	list = []
	for i in range(0, 20):
		x = random.randint(-200, 200)
		y = random.randint(-200, 200)
		z = random.randint(100, 200)

		list.append((x, y, z))

	save_in_file(list, name)



if __name__ == "__main__":
	generate_well("kriging")
