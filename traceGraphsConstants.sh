#!/bin/bash

for data in $(ls results/test_constance_optimal/)
do
	sed -i 's/,/ /g' results/test_constance_optimal/$data
	gnuplot -e "set xrange [500:600000]; set yrange[0.0001:00.1]; set term png; set output \"graphs/${data%.csv}_constant_opt.png\"; f(x)=a*x+b; fit f(x) \"results/test_constance_optimal/$data\" via a, b; plot \"results/test_constance_optimal/$data\" with points, f(x) with lines title sprintf('f(x) = %.8f·x+{%.8f}', a, b)"
done

for data in $(ls results/test_constance_worst/)
do
	sed -i 's/,/ /g' results/test_constance_worst/$data
	gnuplot -e "set xrange [500:600000]; set yrange[0.0001:00.1]; set term png; set output \"graphs/${data%.csv}_constant_worst.png\"; f(x)=a*x+b; fit f(x) \"results/test_constance_worst/$data\" via a, b; plot \"results/test_constance_worst/$data\" with points, f(x) with lines title sprintf('f(x) = %.8f·x+{%.8f}', a, b)"
done
