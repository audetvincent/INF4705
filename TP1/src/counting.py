# from : http://rosettacode.org/wiki/Sorting_algorithms/Counting_sort#Python

from collections import defaultdict
import sys
import datetime

# Ouverture du fichier de donnees
file = open(str(sys.argv[1]), "r")
data = file.readlines()
data = map(int, [x.strip() for x in data])

# On va chercher le min et le max pour les fournir à l'algorithme
mini = min(data)
maxi = max(data)

def countingSort(array, mn, mx):
    count = defaultdict(int)
    for i in array:
        count[i] += 1
    result = []
    for j in range(mn,mx+1):
        result += [j]* count[j]
    return result

# Execution du tri et mesure du temps
time_init = datetime.datetime.now() 
result = countingSort(data, mini, maxi)
time_end = datetime.datetime.now()
time_delta = time_end - time_init

# Verification des parametres fournis
if "-p" in sys.argv or "--print" in sys.argv:
    for i in result:
        print i

if "-t" in sys.argv or "--time" in sys.argv:
    print time_delta.total_seconds()
