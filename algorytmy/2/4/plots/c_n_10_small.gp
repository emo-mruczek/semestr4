set title "AVG COMPARISONS by N for random data, k = 10"
set style data lines
set xlabel "n"
set ylabel "Average comparisons divided by n"
set title font "Helvetica,14"

plot "average_10_small.txt" using 1:8 t "QuickSort", \
"" using 1:10 t "DualPivot QuickSort"
