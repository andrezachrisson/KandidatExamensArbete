set style line 1 lt 2 lc rgb '#0060ad' pt 6 lw 3
set style line 2 lt 2 lc rgb '#09ad00' pt 6 lw 3
set style line 3 lt 2 lc rgb 'red' pt 6 lw 3


set title "Cells attatched at 900 MCS"
set xlabel "Kappa"
set ylabel "Cells"

set xrange [0:1.2]
set yrange[0:75]

plot '900_KAPPA' with linespoints ls 1 title '900 MCS',

set terminal png font arial 20 size 1200,800
set output "1_Cells_900MCS.png"
replot
set term x11
