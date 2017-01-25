#!/bin/bash

# Exemple de script qui exécute tous les algos pour chaque exemplaire et qui
# imprime la taille de l'exemplaire et le temps d'exécution. On peut piper
# la sortie de ce script vers un fichier csv et l'ouvrir avec R ou encore
# python (avec matplotlib) pour faire les graphiques.

for algo in counting quick quickRandom quickSeuil quickRandomSeuil; do
  # creer un fichier par algo pour contenir les resultats

  # Fichier ou se trouves les exemplaires
  for ex in `ls ./INF4705_H17_TP1_donnees/0-9/`; do
    t=""
    t=`timeout 180 ./tp.sh -a $algo -e ./INF4705_H17_TP1_donnees/0-9/$ex -t`
    if [ "${t}" != "" ]; then
      # Si on a des noms d'exemplaires de la forme testset_n_ne.txt, on peut 
      # extraire la taille avec sed (par exemple...)
      taille_ex=`echo $ex | sed 's/^testset_\([0-9]*\)_[0-9]*.txt/\1/'`
      echo $taille_ex,$t >> $algo.txt
    fi
  done
done

