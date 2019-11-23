set style line 1 lc rgb '#0060ad' lt 2 lw 3 pt 7 pi -1 ps 1
set style line 2 lc rgb '#0025ad' lt 2 lw 3 pt 7 pi -1 ps 1
set style line 3 lc rgb '#09ad00' lt 2 lw 3 pt 7 pi -1 ps 1
set style line 4 lc rgb 'red' lt 2 lw 3 pt 7 pi -1 ps 1
set style line 5 lc rgb 'yellow' lt 2 lw 3 pt 7 pi -1 ps 1


set title "Some Sample Plots"
set xlabel "Number of oriented sites"
set ylabel ""

plot 'distribution_KAPPA1' with linespoints ls 4 title 'Kappa = 1', \
'distribution_KAPPA2' with linespoints ls 2 title 'Kappa = 2',\
'distribution_KAPPA10' with linespoints ls 3 title 'Kappa = 10',



