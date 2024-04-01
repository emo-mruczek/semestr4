set title "Average SWAPS for large random data, k = 1"
set style data lines
set xlabel "n"
set ylabel "Average swaps"
set title font "Helvetica,14"

plot "average_1_large.txt" using 1:3 t "QuickSort", \
"" using 1:5 t "DualPivot QuickSort"
