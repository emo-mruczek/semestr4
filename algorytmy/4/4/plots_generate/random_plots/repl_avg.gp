set title "AVG REPLACEMENTS by N for RANDOM data"
set style data lines
set xlabel "n"
set ylabel "Average replacements of pointers"
set title font "Helvetica,14"

plot "average.txt" using 1:4 t "RB"
set terminal png size 400,300
set output "repl_avg.png"
replot
