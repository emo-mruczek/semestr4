set title "MAX REPLACEMENTS by N for ASCENDING data"
set style data lines
set xlabel "n"
set ylabel "Maximum replacements of pointers"
set title font "Helvetica,14"

plot "maximum.txt" using 1:4 t "BST"
