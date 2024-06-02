set title "AVG COMPARISONS by N for RANDOM data"
set style data lines
set xlabel "n"
set ylabel "Average comparisons"
set title font "Helvetica,14"

plot "average.txt" using 1:2 t "BST"
