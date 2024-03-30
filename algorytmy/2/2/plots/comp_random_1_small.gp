set title "Average COMPARISONS for random data, k = 1"
set style data lines
set xlabel "n"
set ylabel "Average comparisons"
set title font "Helvetica,14"

plot "average_1_small.txt" using 1:2 t "QuickSort", \
"" using 1:4 t "HybridSort", \
"" using 1:6 t "InsertionSort"

