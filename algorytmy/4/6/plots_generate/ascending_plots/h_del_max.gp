set title "MAX HEIGHT for DELETION by N for ASCENDING data"
set style data lines
set xlabel "n"
set ylabel "Maximum height for deletion"

set title font "Helvetica,14"

plot "maximum.txt" using 1:5 t "SPLAY"

set terminal png size 400,300
set output "h_del_max.png"
replot
