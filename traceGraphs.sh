#!/bin/bash

for data in $(ls results/means/)
do
	sed -i 's/,/ /g' results/means/$data	
	gnuplot -e "set xrange [500:600000]; set yrange[0.00001:0.0001]; set logscale xy; set term png; set output \"graphs/${data%.csv}_loglog.png\"; plot \"results/means/$data\" with linespoints"
done
