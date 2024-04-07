set multiplot layout 4, 1 title "worst case and best case"
set bmargin 5

set title "Worst case - comparisons"
set style data lines
set xlabel "n"
set ylabel "comparisons"
plot "wb.txt" using 1:6 t "QuickSort", \
"" using 1:8 t "Dual-PivotQuicksort"

set title "Best case - comparisons"
set style data lines
set xlabel "n"
set ylabel "comparisons"
plot "wb.txt" using 1:2 t "QuickSort", \
"" using 1:4 t "Dual-PivotQuicksort"

set title "Worst case - swaps"
set style data lines
set xlabel "n"
set ylabel "swaps"
plot "wb.txt" using 1:7 t "QuickSort", \
"" using 1:9 t "Dual-PivotQuicksort"

set title "Best case - swaps"
set style data lines
set xlabel "n"
set ylabel "swaps"
plot "wb.txt" using 1:3 t "QuickSort", \
"" using 1:5 t "Dual-PivotQuicksort"
