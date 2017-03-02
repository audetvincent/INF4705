#!/usr/bin/env python

# Algorithme de tri topologique avec retour arriere permettant de calculer le nombre d'extensions lineaires dans un graphe oriente sans cycle

import sys
import datetime
from DAG import DAG 

# Ouverture du fichier de donnees
file = open(str(sys.argv[1]), "r")

# Creation du graphe
info = file.readline().split()
nbVertices = int(info[0])
nbArcs = int(info[1])
dag = DAG()
for i in range(nbVertices):
    dag.add_node(i)
for i in range(nbArcs):
    arc = file.readline().split()
    dag.add_edge(int(arc[0]), int(arc[1]))
file.close()

# Algorithme
def countOrderings(currentDag, nbVertices):
    #TODO

# Denombrement des solutions
time_start = datetime.datetime.now()
nbOrderings = countOrderings(dag)
time_end = datetime.datetime.now()

# Verification des parametres fournis
if "-p" in sys.argv or "--print" in sys.argv:
    print nbOrderings

if "-t" in sys.argv or "--time" in sys.argv:
    print (time_end - time_start).total_seconds()

