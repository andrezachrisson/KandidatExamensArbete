set style line 1 lc rgb '#0060ad' lt 2 lw 3 pt 7 pi -1 ps 1
set style line 2 lc rgb '#0025ad' lt 2 lw 3 pt 7 pi -1 ps 1
set style line 3 lc rgb '#09ad00' lt 2 lw 3 pt 7 pi -1 ps 1
set style line 4 lc rgb 'red' lt 2 lw 3 pt 7 pi -1 ps 1
set style line 5 lc rgb 'yellow' lt 2 lw 3 pt 7 pi -1 ps 1


set title "Some Sample Plots"
set xlabel "Number of oriented sites"
set ylabel ""

plot 'distribution_DELTA4' with linespoints ls 1 title 'Delta = 4', \
'distribution_DELTA5' with linespoints ls 2 title 'Delta = 5',\
'distribution_DELTA6' with linespoints ls 3 title 'Delta = 6',



set terminal png font arial 20 size 800,600
set output "nr_cells_DELTA.png"
replot
set term x11
