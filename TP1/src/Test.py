#!/usr/bin/env python

import os
import csv
import math

dir = os.path.dirname('mean.py')
means_path = '../results/means/'
count_path = '../results/counting_optimal/'
optimal_path = '../results/quicksort_optimal/'
worst_path = '../results/quicksort_worst/'

const_count = '../results/test_constance_counting/'
const_opt = '../results/test_constance_optimal/'
const_worst = '../results/test_constance_worst/'

for filename in os.listdir(means_path):
	count_output = open(count_path+filename, 'w+')
	opt_output = open(optimal_path+filename, 'w+')
	worst_output = open(worst_path+filename, 'w+')
	
	ct_out = open(const_count+filename, 'w+')
	co_out = open(const_opt+filename, 'w+')
	cw_out = open(const_worst+filename, 'w+')
	
	with open(means_path+filename, 'rb') as csvfile:
		reader = csv.reader(csvfile, delimiter=' ', quotechar='|')
		print(csvfile.name)
		for row in reader:
			x = float(row[0])
			y = float(row[1])
			f_count = x
			f_opt = (x*math.log(x))
			f_worst = (math.pow(x,2))
			y_count = y / f_count
			y_opt = y / f_opt
			y_worst = y / f_worst
			
			#Test de rapport
			if "counting" in csvfile.name:
				count_writer = csv.writer(count_output)
				count_writer.writerow([x, y_count])
			else:
				opt_writer = csv.writer(opt_output)
				opt_writer.writerow([x, y_opt])
			
				worst_writer = csv.writer(worst_output)
				worst_writer.writerow([x, y_worst])
			
			#Test de constante
			if "counting" in csvfile.name:
				ct_writer = csv.writer(ct_out)
				ct_writer.writerow([f_count, y])
			else:
				co_writer = csv.writer(co_out)
				co_writer.writerow([f_opt, y])
			
				cw_writer = csv.writer(cw_out)
				cw_writer.writerow([f_worst, y])			
			
			print(str(x) + " " + str(y_opt) + " " + str(y_worst))
