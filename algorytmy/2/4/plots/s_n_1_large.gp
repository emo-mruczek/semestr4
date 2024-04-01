set title "AVG SWAPS by N for large random data, k = 1"
set style data lines
set xlabel "n"
set ylabel "Average swaps divided by n"
set title font "Helvetica,14"

plot "average_1_large.txt" using 1:7 t "QuickSort", \
"" using 1:9 t "DualPivot QuickSort"
