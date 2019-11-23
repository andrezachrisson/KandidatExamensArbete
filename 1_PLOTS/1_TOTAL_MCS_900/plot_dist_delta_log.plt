set style line 1 lc rgb '#0060ad' lt 2 lw 3 pt 7 pi -1 ps 1
set style line 2 lc rgb '#0025ad' lt 2 lw 3 pt 7 pi -1 ps 1
set style line 3 lc rgb '#09ad00' lt 2 lw 3 pt 7 pi -1 ps 1
set style line 4 lc rgb 'red' lt 2 lw 3 pt 7 pi -1 ps 1
set style line 5 lc rgb 'yellow' lt 2 lw 3 pt 7 pi -1 ps 1


set title "Cells attatched at 900 MCS"
set xlabel "Kappa"
set ylabel "Cells"

set log

plot '900_KAPPA' title '900 MCS',

set terminal png font arial 20 size 800,600
set output "Cells_900MCS.png"
replot
set term x11


