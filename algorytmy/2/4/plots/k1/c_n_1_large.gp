set title "AVG COMPARISONS by N for large random data, k = 1"
set style data lines
set xlabel "n"
set ylabel "Average comparisons divided by n"
set title font "Helvetica,14"

plot "average_1_large.txt" using 1:6 t "QuickSort", \
"" using 1:8 t "DualPivot QuickSort"
