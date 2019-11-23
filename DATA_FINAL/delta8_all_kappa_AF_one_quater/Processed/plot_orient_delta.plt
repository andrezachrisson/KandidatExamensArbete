set style line 1 lc rgb 'yellow' lt 2 lw 3 pt 7 pi -1 ps 1
set style line 2 lc rgb '#0025ad' lt 2 lw 3 pt 7 pi -1 ps 1
set style line 3 lc rgb '#09ad00' lt 2 lw 3 pt 7 pi -1 ps 1
set style line 4 lc rgb 'red' lt 2 lw 3 pt 7 pi -1 ps 1


set title "Some Sample Plots"
set xlabel "Independent Variable (no units)"
set ylabel "Dependent Variable (no units)"

plot 'Orient_DELTA8_KAPPA0P1' with linespoints ls 1 title 'Kappa = 0.1', \
'Orient_DELTA8_KAPPA1' with linespoints ls 2 title 'Kappa = 1',\
'Orient_DELTA8_KAPPA2' with linespoints ls 3 title 'Kappa = 2',\
'Orient_DELTA8_KAPPA10' with linespoints ls 4 title 'Kappa = 10',

set terminal png font arial 20 size 800,600
set output "distribution_orientation_kappa.png"
replot
set term x11
