set title "Average COMPARISONS DualPivot vs DualPivotSelect"
set style data lines
set xlabel "n"
set ylabel "Average comp"
set title font "Helvetica,14"

plot "average.txt" using 1:2 t "DualPivot", \
"" using 1:4 "DualPivotSelect"

