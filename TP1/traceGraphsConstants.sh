#!/bin/bash

for data in $(ls results/test_constance_optimal/)
do
	sed -i 's/,/ /g' results/test_constance_optimal/$data
	gnuplot -e "set autoscale xy; set term png; set output \"graphs/${data%.csv}_constant_opt.png\"; f(x)=a*x; fit f(x) \"results/test_constance_optimal/$data\" via a; plot \"results/test_constance_optimal/$data\" with points, f(x) with lines title sprintf('f(x) = %e·x+{%.8f}', a, b)"
done

for data in $(ls results/test_constance_worst/)
do
	sed -i 's/,/ /g' results/test_constance_worst/$data
	gnuplot -e "set autoscale xy; set term png; set output \"graphs/${data%.csv}_constant_worst.png\"; f(x)=a*x; fit f(x) \"results/test_constance_worst/$data\" via a; plot \"results/test_constance_worst/$data\" with points, f(x) with lines title sprintf('f(x) = %e·x+{%.8f}', a, b)"
done

for data in $(ls results/test_constance_counting/)
do
	sed -i 's/,/ /g' results/test_constance_counting/$data
	gnuplot -e "set autoscale xy; set term png; set output \"graphs/${data%.csv}_constant_counting.png\"; f(x)=a*x; fit f(x) \"results/test_constance_counting/$data\" via a; plot \"results/test_constance_counting/$data\" with points, f(x) with lines title sprintf('f(x) = %e·x+{%.8f}', a, b)"
done
