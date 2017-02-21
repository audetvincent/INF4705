#!/bin/bash

for data in $(ls results/quicksort_optimal/)
do
	sed -i 's/,/ /g' results/quicksort_optimal/$data
	gnuplot -e "set autoscale xy; set term png; set output \"graphs/${data%.csv}_rapport_opt.png\"; plot \"results/quicksort_optimal/$data\" with linespoints"
done

for data in $(ls results/quicksort_worst/)
do
	sed -i 's/,/ /g' results/quicksort_worst/$data
	gnuplot -e "set autoscale xy; set term png; set output \"graphs/${data%.csv}_rapport_worst.png\"; plot \"results/quicksort_worst/$data\" with linespoints"
done
