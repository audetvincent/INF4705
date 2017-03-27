#!/usr/bin/env python

# Algorithme de programmation dynamique permettant de calculer le nombre d'extensions lineaires dans un graphe oriente sans cycle

import sys
import datetime
from DAG import DAG
import numpy as np
from itertools import product
import copy

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

# Algorithmes de l'enonce
def longestChain(dag):
    pred = {}
    Q = []
    last = -1

    for v in dag.nodes():
        pred[v] = -1

    for v in dag.ind_nodes():
        Q.append(v)

    while len(Q) != 0:
        u = Q.pop(0)
        last = u
        for a in dag.downstream(u):
            pred[a] = u
            if a in Q:
                Q.pop(Q.index(a))
                Q.append(a)
            else:
                Q.append(a)
    # Si ce n'est pas une valeur frontiere (deja egale a 1)

    c = []
    while last != -1:
        c.insert(0, last)
        last = pred[last]

    return c

def decomp(dag):
    L = []
    c = longestChain(dag)

    while len(c) != 0:
        for v in c:
            dag.delete_node(v)
        L.append(c)
        c = longestChain(dag)

    for v in dag.nodes():
        L.append(v)

    return L

def fermetureTransitive(dag):
    for k in dag.nodes():
        for i in dag.nodes():
            for j in dag.nodes():
                if j in dag.downstream(i):
                    continue
                elif k in dag.downstream(i) and j in dag.downstream(k):
                    dag.add_edge(i, j)

# Denombrement des solutions
nbOrderings = 0
time_start = datetime.datetime.now()
chains = decomp(copy.deepcopy(dag))
print(chains)
fermetureTransitive(dag)
dims = []
# Construction du tableau de calcul
for i in range(len(chains)):
    dims.append(len(chains[i]))
array = np.ones(dims)
# Parcours et remplissage du tableau
for index, item in np.ndenumerate(array):
    # Si ce n'est pas une valeur frontiere (deja egale a 1)
    if index.count(0) < (len(chains) - 1):
        for i in range(len(index)):
            downstream = dag.downstream(chains[i][index[i]])
            chainEnds = []
            for j in range(len(index)):
                if j != i:
                    chainEnds.append(chains[j][index[j]])
            if len(set(downstream).intersection(chainEnds)) == 0:
                temp = list(index)
                temp[i] = 0 if temp[i] <= 0 else (temp[i] - 1)
                array[index] += array[tuple(temp)]
print(array)
nbOrderings = int(array.flat[-1])
time_end = datetime.datetime.now()

# Verification des parametres fournis
if "-p" in sys.argv or "--print" in sys.argv:
    print nbOrderings

if "-t" in sys.argv or "--time" in sys.argv:
    print (time_end - time_start).total_seconds()
