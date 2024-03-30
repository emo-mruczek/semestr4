set title "Average SWAPS for random data, k = 100"
set style data lines
set xlabel "n"
set ylabel "Average swaps"
set title font "Helvetica,14"

plot "average_100_small.txt" using 1:3 t "QuickSort", \
"" using 1:5 t "HybridSort", \
"" using 1:7 t "InsertionSort"
