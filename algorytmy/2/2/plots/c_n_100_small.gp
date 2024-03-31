set title "AVG COMPARISONS by N for random data, k = 100"
set style data lines
set xlabel "n"
set ylabel "Average comparisons divided by n"
set title font "Helvetica,14"

plot "average_100_small.txt" using 1:8 t "HybridSort", \
"" using 1:10 t "QuickSort", \
"" using 1:12 t "InsertionSort"
