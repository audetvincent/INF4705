# Adapted from : http://rosettacode.org/wiki/Sorting_algorithms/Quicksort#Python

import sys
import datetime

file = open(str(sys.argv[1]), "r")

data = file.readlines()
data = map(int, [x.strip() for x in data]) 

time_init = datetime.datetime.now()

def insertion_sort(l):
    for i in xrange(1, len(l)):
        j = i-1 
        key = l[i]
        while (l[j] > key) and (j >= 0):
           l[j+1] = l[j]
           j -= 1
        l[j+1] = key

def quickSort(arr):
    less = []
    pivotList = []
    more = []
    if len(arr) <= 10:
        return insertion_sort(arr)
    else:
        pivot = arr[0]
        for i in arr:
            if i < pivot:
                less.append(i)
            elif i > pivot:
                more.append(i)
            else:
                pivotList.append(i)
        less = quickSort(less)
        more = quickSort(more)
    return less + pivotList + more

time_end = datetime.datetime.now()
time_delta = time_end - time_init
print time_delta.total_seconds()

file.close()

#quickSort(data) == sorted(data)
