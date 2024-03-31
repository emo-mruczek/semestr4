set title "AVG COMPARISONS by N for large random data, k = 100"
set style data lines
set xlabel "n"
set ylabel "Average comparisons divided by n"
set title font "Helvetica,14"

plot "average_100_large.txt" using 1:6 t "HybridSort", \
"" using 1:8 t "QuickSort"
