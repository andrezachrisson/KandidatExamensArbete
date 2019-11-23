set style line 1 lt 2 lc rgb '#0060ad' pt 6 lw 3
set style line 2 lt 2 lc rgb '#09ad00' pt 6 lw 3
set style line 3 lt 2 lc rgb 'red' pt 6 lw 3
set style line 4 lt 2 lc rgb 'orange' pt 6 lw 3
set style line 5 lt 2 lc rgb 'yellow' pt 6 lw 3


set title "Average cells attached for all delta"
set xlabel "Time"
set ylabel "Cells"
set key left
set log


plot 'distribution_total_KAPPA0P1' with linespoints ls 1 title 'Kappa = 0.1', \
'distribution_total_KAPPA0P3' with linespoints ls 2 title 'Kappa = 0.3', \
'distribution_total_KAPPA0P5' with linespoints ls 3 title 'Kappa = 0.5', \
'distribution_total_KAPPA0P8' with linespoints ls 4 title 'Kappa = 0.8', \
'distribution_total_KAPPA1' with linespoints ls 5 title 'Kappa = 1',


set terminal png font arial 20 size 1200,800
set output "4_AVERAGE_DELTA_DIFFERENT_KAPPA_LOG.png"
replot
set term x11
