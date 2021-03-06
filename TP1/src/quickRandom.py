# Adapted from : http://rosettacode.org/wiki/Sorting_algorithms/Quicksort#Python

import sys
import random
import datetime
import sys
sys.setrecursionlimit(5000000)


# Ouverture du fichier de donnees
file = open(str(sys.argv[1]), "r")
data = file.readlines()
data = map(int, [x.strip() for x in data]) 


def quickSort(arr):
    less = []
    pivotList = []
    more = []
    if len(arr) <= 1:
        return arr
    else:
        pivot = arr[int(random.uniform(0, len(arr)))]
        for i in arr:
            if i < pivot:
                less.append(i)
            elif i > pivot:
                more.append(i)
            else:
                pivotList.append(i)
		if (len(less) < len(more)):
			less = quickSort(less)
			more = quickSort(more)
		else:
			more = quickSort(more)
			less = quickSort(less)
    return less + pivotList + more

# Execution du tri et mesure du temps
time_init = datetime.datetime.now()
result = quickSort(data)
time_end = datetime.datetime.now()
time_delta = time_end - time_init

file.close()

# Verification des parametres fournis
if "-p" in sys.argv or "--print" in sys.argv:
    for i in result:
        print i

if "-t" in sys.argv or "--time" in sys.argv:
    print time_delta.total_seconds()
