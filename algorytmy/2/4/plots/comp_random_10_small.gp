set title "Average COMPARISONS for random data, k = 10"
set style data lines
set xlabel "n"
set ylabel "Average comparisons"
set title font "Helvetica,14"

plot "average_10_small.txt" using 1:2 t "QuickSort", \
"" using 1:4 t "DualPivot QuickSort"

