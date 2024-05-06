set title "Average TIME for QuickSort vs QuickSortSelect - worst case"
set style data lines
set xlabel "n"
set ylabel "Average time"

plot "results.txt" using 1:3 t "QuickSort", \
"" using 1:5 t "QuickSortSelect"
