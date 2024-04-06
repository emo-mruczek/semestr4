set title "Average SWAPS for large random data, k = 100"
set style data lines
set xlabel "n"
set ylabel "Average swaps"
set title font "Helvetica,14"

plot "average_100_large.txt" using 1:3 t "MergeSort", \
"" using 1:5 t "MySort"
