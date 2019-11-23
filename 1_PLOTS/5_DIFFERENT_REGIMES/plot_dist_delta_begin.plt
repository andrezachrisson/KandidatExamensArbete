set style line 1 lt 2 lc rgb '#0060ad' pt 6 lw 2
set style line 2 lt 2 lc rgb '#09ad00' pt 6 lw 2
set style line 3 lt 2 lc rgb 'red' pt 6 lw 2
set style line 4 lt 2 lc rgb 'orange' pt 6 lw 2
set style line 5 lt 2 lc rgb 'yellow' pt 6 lw 2


set title "Average cells for all delta"
set xlabel "Time"
set ylabel "Cells"
set key left


f(x) = a*x + c
g(x) = b*x + d
h(x) = k*x + m



fit f(x) 'distribution_DELTA4_KAPPA0P1_begin' using (log($1)):(log($2)) via a, c 
fit g(x) 'distribution_DELTA4_KAPPA0P5_begin' using (log($1)):(log($2)) via b, d
fit h(x) 'distribution_DELTA4_KAPPA1_begin' using (log($1)):(log($2)) via k, m

plot f(x) ls 1 notitle,\
'distribution_DELTA4_KAPPA0P1' using (log($1)):(log($2)) ls 1 pt 6 title 'data kappa = 0.1',\
g(x) ls 2 notitle,\
'distribution_DELTA4_KAPPA0P5' using (log($1)):(log($2)) ls 2 pt 6 title 'data kappa = 0.5',\
h(x) ls 3 notitle,\
'distribution_DELTA4_KAPPA1' using (log($1)):(log($2)) ls 3 pt 6 title 'data kappa = 1'

set terminal png font arial 20 size 1200,800
set output "5_FITTING_FIRST_REGIM.png"
replot
set term x11
