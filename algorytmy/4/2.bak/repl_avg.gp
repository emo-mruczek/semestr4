set title "AVG REPLACEMENTS by N"
set style data lines
set xlabel "n"
set ylabel "Average replacements of pointers"
set title font "Helvetica,14"

plot "average.txt" using 1:4 t "BST"