#!/bin/bash

for data in $(ls results/quicksort_optimal/)
do
	sed -i 's/,/ /g' results/means/$data
	gnuplot -e "set xrange [0:600000]; set yrange[0:0.0001]; set term png; set output \"graphs/${data%.csv}_rapport.png\"; plot \"results/quicksort_optimal/$data\" with linespoints"
done

for data in $(ls results/quisort_worst/)
do
	sed -i 's/,/ /g' results/means/$data
	gnuplot -e "set xrange [0:600000]; set yrange[0:0.0001]; set term png; set output \"graphs/${data%.csv}_rapport.png\"; plot \"results/quicksort_worst/$data\" with linespoints"
done
