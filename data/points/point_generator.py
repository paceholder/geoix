#!/usr/bin/python
import math
import random


""" Script generates file with point data named points_numpoints. """

def save_in_file(list, num):
	file = open("points_" + str(num), "w+")
	for line in list:
		file.write("%f %f %f\n" % line)

	file.close()


def generate_well(num):
	random.seed()
    
	list = []
	for i in range(0, num):
		x = random.randint(0, 10000)
		y = random.randint(0, 10000)
		z = random.randint(0, 10)
		list.append((x, y, z))

	save_in_file(list, num)



if __name__ == "__main__":
        for i in range(5, 18):
                generate_well(2 ** i)
