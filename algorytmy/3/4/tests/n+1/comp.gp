set title "Average COMPARISONS for finding the element NOT IN AN ARRAY"
set style data lines
set xlabel "n"
set ylabel "Average comp"
set title font "Helvetica,14"

plot "results.txt" using 1:2 t "BinarySearch", \

