#!/bin/bash

for data in $(ls results/means/)
do
	sed -i 's/,/ /g' results/means/$data	
	gnuplot -e "set xrange [0:600000]; set yrange[0:0.0001]; set term png; set output \"graphs/${data%.csv}.png\"; plot \"results/means/$data\" with linespoints"
done
