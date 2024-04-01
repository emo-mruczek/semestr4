set title "AVG SWAPS by N for random data, k = 100"
set style data lines
set xlabel "n"
set ylabel "Average swaps divided by n"
set title font "Helvetica,14"

plot "average_100_small.txt" using 1:9 t "QuickSort", \
"" using 1:11 t "DualPivot QuickSort"
