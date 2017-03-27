#!/usr/bin/env python

# Algorithme de programmation dynamique permettant de calculer le nombre d'extensions lineaires dans un graphe oriente sans cycle

import sys
import datetime
from DAG import DAG
from vorace import decomp
import numpy as np
from itertools import product

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

def fermetureTransitive(dag):
    for k in dag.nodes():
        for i in dag.nodes():
            for j in dag.nodes():
                if j in dag.downstream(i):
                    continue
                elif k in dag.downstream(i) and j in dag.downstream(k):
                    dag.add_edge(i, j)

#def remplirTableau(array):

# Denombrement des solutions
nbOrderings = 0
time_start = datetime.datetime.now()
chains = decomp(dag)
fermetureTransitive(dag)
dims = []
for i in range(len(chains)):
    dims.append(len(chains[i]))
array = np.ones(dims)
#TODO
time_end = datetime.datetime.now()

# Verification des parametres fournis
if "-p" in sys.argv or "--print" in sys.argv:
    print nbOrderings

if "-t" in sys.argv or "--time" in sys.argv:
    print (time_end - time_start).total_seconds()
