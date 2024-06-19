
set terminal png size 500,400
set output "time_avg.png"

set title "Average TIME of mst algorithms"
set style data lines
set xlabel "n"
set ylabel "Average time"

plot "average.txt" using 1:2 t "Prim", \
"" using 1:3 t "Kruskal"

unset output
