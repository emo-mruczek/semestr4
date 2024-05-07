set title "Average COMPARISONS for QuickSort vs QuickSortSelect - wors case"
set style data lines
set xlabel "n"
set ylabel "Average comparisons"

plot "average.txt" using 1:2 t "QuickSort", \
"" using 1:4 t "QuickSortSelect"
