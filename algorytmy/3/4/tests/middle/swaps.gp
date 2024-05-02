set title "Average TIME for finding element NEAR MIDDLE"
set style data lines
set xlabel "n"
set ylabel "Average time"

plot "results.txt" using 1:3 t "BinarySearch"
