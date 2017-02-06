# from : http://rosettacode.org/wiki/Sorting_algorithms/Counting_sort#Python

from collections import defaultdict
import sys
import datetime

file = open(str(sys.argv[1]), "r")

data = file.readlines()
data = map(int, [x.strip() for x in data])

mini = min(data)
maxi = max(data)


time_init = datetime.datetime.now() 
def countingSort(array, mn, mx):
    count = defaultdict(int)
    for i in array:
        count[i] += 1
    result = []
    for j in range(mn,mx+1):
        result += [j]* count[j]
    return result

time_end = datetime.datetime.now()
time_delta = time_end - time_init
print time_delta.total_seconds()
#countingSort(data, mini, maxi) == sorted(data)
