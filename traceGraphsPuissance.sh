#!/bin/bash

for data in $(ls results/means/)
do
	sed -i 's/,/ /g' results/means/$data
	gnuplot -e "set xrange [500:600000]; set yrange[0.0001:00.1]; set logscale xy; set term png; set output \"graphs/${data%.csv}_puissance.png\"; f(x)=a*x**b; fit f(x) \"results/means/$data\" via a, b; plot \"results/means/$data\" with points, f(x) with lines title sprintf('Courbe de puissance f(x) = %.8f·x^{%.8f}', a, b)"
done
