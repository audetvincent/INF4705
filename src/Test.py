#!/usr/bin/env python

import os
import csv
import math

dir = os.path.dirname('mean.py')
means_path = '../results/means/'
optimal_path = '../results/quicksort_optimal/'
worst_path = '../results/quicksort_worst/'

const_opt = '../results/test_constance_optimal/'
const_worst = '../results/test_constance_worst/'

for filename in os.listdir(means_path):
	opt_output = open(optimal_path+filename, 'w+')
	worst_output = open(worst_path+filename, 'w+')
	
	co_out = open(const_opt+filename, 'w+')
	cw_out = open(const_worst+filename, 'w+')
	
	with open(means_path+filename, 'rb') as csvfile:
		reader = csv.reader(csvfile, delimiter=' ', quotechar='|')
		print(csvfile.name)
		for row in reader:
			x = float(row[0])
			y = float(row[1])
			f_opt = (x*math.log(x))
			f_worst = (math.pow(x,2))
			y_opt = y / f_opt
			y_worst = y / f_worst
			
			#Test de rapport
			opt_writer = csv.writer(opt_output)
			opt_writer.writerow([x, y_opt])
			
			worst_writer = csv.writer(worst_output)
			worst_writer.writerow([x, y_worst])
			
			#Test de constante
			co_writer = csv.writer(co_out)
			co_writer.writerow([y, f_opt])
			
			cw_writer = csv.writer(cw_out)
			cw_writer.writerow([y, f_worst])			
			
			print(str(x) + " " + str(y_opt) + " " + str(y_worst))
