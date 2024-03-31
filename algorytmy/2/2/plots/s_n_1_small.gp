set title "AVG SWAPS by N for random data, k = 1"
set style data lines
set xlabel "n"
set ylabel "Average swaps divided by n"
set title font "Helvetica,14"

plot "average_1_small.txt" using 1:9 t "HybridSort", \
"" using 1:11 t "QuickSort", \
"" using 1:13 t "InsertionSort"
