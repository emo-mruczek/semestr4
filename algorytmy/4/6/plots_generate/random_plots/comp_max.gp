set title "MAX COMPARISONS by N for RANDOM data"
set style data lines
set xlabel "n"
set ylabel "Maximum comparisons"
set title font "Helvetica,14"

plot "maximum.txt" using 1:2 t "SPLAY"
