#!/bin/bash

for data in $(ls result)
do
	sed -i 's/,/ /g' result/$data	
	gnuplot -e "set xrange [0:600000]; set yrange[0:0.0001]; set term png; set output \"graphs/${data%.csv}.png\"; plot \"result/$data\" with linespoints"
done
