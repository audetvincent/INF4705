#!/usr/bin/env python

import os
import csv

dir = os.path.dirname('mean.py')
raw_path = '../results/raw/'
means_path = '../results/means/'
for filename in os.listdir(raw_path):
    output_list = []
    list_1000 = 0
    list_10000 = 0
    list_100000 = 0
    list_5000 = 0
    list_50000 = 0
    list_500000 = 0
    with open(raw_path+filename, 'rb') as csvfile:
        print csvfile.name
        csv_f = csv.reader(csvfile)
        for row in csv_f:
            #print row[0]
            if "1000" in row:
                list_1000 += float(row[1])
            elif "10000" in row:
                list_10000 += float(row[1])
            elif "100000" in row:
                list_100000 += float(row[1])
            elif "5000" in row:
                list_5000 += float(row[1])
            elif "50000" in row:
                list_50000 += float(row[1])
            elif "500000" in row:
                list_500000 += float(row[1])

        print ("before mean : "+ str(list_1000))
        list_1000 = list_1000 / 10

        print ("after mean : " + str(list_1000))

        print ("before mean : " + str(list_5000))
        list_5000 = list_5000 / 10
        print ("after mean : " + str(list_5000))

        print ("before mean : " + str(list_10000))
        list_10000 = list_10000 / 10
        print ("after mean : " + str(list_10000))

        print ("before mean : " + str(list_50000))
        list_50000 = list_50000 / 10
        print ("after mean : " + str(list_50000))

        print ("before mean : " + str(list_100000))
        list_100000 = list_100000 / 10
        print ("after mean : " + str(list_100000))

        print ("before mean : " + str(list_500000))
        list_500000 = list_500000 / 10
        print ("after mean : " + str(list_500000))

        # Must finish the writing in csv file
        of = open(means_path+filename, 'w+')
        csvToWrite = csv.writer(of)
        csvToWrite.writerow(["1000", list_1000])    
        csvToWrite.writerow(["5000", list_5000])
        csvToWrite.writerow(["10000", list_10000])
        csvToWrite.writerow(["50000", list_50000])
        csvToWrite.writerow(["100000", list_100000])
        csvToWrite.writerow(["500000", list_500000])


