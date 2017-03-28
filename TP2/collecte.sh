#!/usr/bin/env zsh

for algo in {"vorace","retourArriere","dynamique"}; do
    # Pour chaque fichier de serie.
    for ex in $(ls tp2-donnees); do
        echo "$ex, $algo"
	# On receuille le temps d'execution dans t et le nombre d'extensions lineaires dans l
        t=$(timeout 180 ./tp.sh -a $algo -e tp2-donnees/$ex -t -p)
	l=$(echo $t | cut -d$'\n' -f 2)
	t=$(echo $t | cut -d$'\n' -f 1)
        # On evalue le nombre de sommets, la largeur et le nombre d'arcs de l'exemplaire
        n=$(head -1 tp2-donnees/$ex | awk '{print $1;}')
	w=$(echo $ex | cut -d '-' -f 2)
	e=$(cat tp2-donnees/$ex | wc -l)
	e=$((e-1))
        
	# Si jamais on mesure un temps, on l'insere dans le fichier.
        if [ t != "" ]; then
            echo $n,$w,$e,$t,$l >> ./resultats/${algo}.csv
        fi
    done
done
