set title "Average TIME for QuickSort vs QuickSortSelect"
set style data lines
set xlabel "n"
set ylabel "Average time"

plot "average.txt" using 1:3 t "QuickSort", \
"" using 1:5 t "QuickSortSelect"
