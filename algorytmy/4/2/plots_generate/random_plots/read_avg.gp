set title "AVG READS by N for RANDOM data"
set style data lines
set xlabel "n"
set ylabel "Average reads of pointers divided by n"
set title font "Helvetica,14"

plot "average.txt" using 1:3 t "BST"
set terminal png size 400,300
set output "read_avg.png"
replot
