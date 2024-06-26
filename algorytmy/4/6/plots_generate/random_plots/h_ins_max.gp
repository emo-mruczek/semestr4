set title "MAX HEIGHT for INSERTION by N for RANDOM data"
set style data lines
set xlabel "n"
set ylabel "Maximum height for insertion"
set title font "Helvetica,14"

plot "maximum.txt" using 1:6 t "SPLAY"
set terminal png size 400,300
set output "h_ins_max.png"
replot
