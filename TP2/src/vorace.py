#!/usr/bin/env python

# Algorithme vorace permettant de calculer le nombre d'extensions lineaires dans un graphe oriente sans cycle

from __future__ import division
import sys
import datetime
from DAG import DAG
from collections import deque
import math

# Ouverture du fichier de donnees
file = open(str(sys.argv[1]), "r")

# Creation du graphie
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

def entropy(chains):
    entropy = 0
    for c in chains:
        x = len(c) / nbVertices
        entropy += -x * math.log(x, 2)

    return entropy

# Denombrement des solutions
nbOrderings = 0
time_start = datetime.datetime.now()
nbOrderings = int(math.ceil(2**(0.5*nbVertices*entropy(decomp(dag)))))
time_end = datetime.datetime.now()

# Verification des parametres fournis
if "-p" in sys.argv or "--print" in sys.argv:
    print nbOrderings

if "-t" in sys.argv or "--time" in sys.argv:
    print (time_end - time_start).total_seconds()
