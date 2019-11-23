set style line 1 lt 2 lc rgb '#0060ad' pt 6 lw 3
set style line 2 lt 2 lc rgb '#09ad00' pt 6 lw 3
set style line 3 lt 2 lc rgb 'red' pt 6 lw 3



set title "Cells attached for all delta"
set xlabel "Log(Time)"
set ylabel "Log(Cells)"

set key left
set log

plot 'distribution_DELTA4_KAPPA0P5' with linespoints ls 1 title  'Kappa = 0.5', \
'distribution_DELTA5_KAPPA0P5' with linespoints ls 1 notitle, \
'distribution_DELTA6_KAPPA0P5' with linespoints ls 1 notitle, \
'distribution_DELTA7_KAPPA0P5' with linespoints ls 1 notitle, \
'distribution_DELTA4_KAPPA1' with linespoints ls 2 title 'Kappa = 1', \
'distribution_DELTA5_KAPPA1' with linespoints ls 2 notitle, \
'distribution_DELTA6_KAPPA1' with linespoints ls 2 notitle, \
'distribution_DELTA7_KAPPA1' with linespoints ls 2 notitle,


set terminal png font arial 20 size 1200,800
set output "3_ALL_DELTA_DIFFERENT_KAPPA_LOG.png"
replot
set term x11


