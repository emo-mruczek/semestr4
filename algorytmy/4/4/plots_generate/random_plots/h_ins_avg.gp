set title "AVG HEIGHT for INSERTION by N for RANDOM data"
set style data lines
set xlabel "n"
set ylabel "Average height for insertion"
set title font "Helvetica,14"

plot "average.txt" using 1:6 t "RB"

set terminal png size 400,300
set output "h_ins_avg.png"
replot
