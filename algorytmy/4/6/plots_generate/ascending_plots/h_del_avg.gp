set title "AVG HEIGHT for DELETION by N for ASCENDING data"
set style data lines
set xlabel "n"
set ylabel "Average height for deletion"

set title font "Helvetica,14"

plot "average.txt" using 1:2 t "SPLAY"
set terminal png size 400,300
set output "h_del_avg.png"
replot
