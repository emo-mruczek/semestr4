set title "Average TIME of mst algorithms"
set style data lines
set xlabel "n"
set ylabel "Average time"
set title font "Helvetica,14"

plot "average.txt" using 1:2 t "Prime", \
"" using 1:3 t "Kruskal"


set terminal png size 500,400
set output "time_avg.png"
replot
