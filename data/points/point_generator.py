#!/usr/bin/python
import math
import random

def save_in_file(list):
	file = open("points", "w+")
	for line in list:
		file.write("%f %f %f\n" % line)

	file.close()


def generate_well():
	random.seed()
    
	list = []
	for i in range(0, 100):
		x = random.randint(0, 1000)
		y = random.randint(0, 1000)
		z = random.randint(0, 10)
		list.append((x, y, z))

	save_in_file(list)



if __name__ == "__main__":
		generate_well()
