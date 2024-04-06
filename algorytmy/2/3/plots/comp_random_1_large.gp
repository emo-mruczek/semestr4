 
set title "Average COMPARISONS for large random data, k = 1"
set style data lines
set xlabel "n"
set ylabel "Average comparisons"
set title font "Helvetica,14"

plot "average_1_large.txt" using 1:2 t "MergeSort", \
"" using 1:4 t "MySort"

