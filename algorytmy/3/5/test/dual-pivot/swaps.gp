set title "Average TIME DualPivot vs DualPivotSelect"
set style data lines
set xlabel "n"
set ylabel "Average time"
set title font "Helvetica,14"

plot "average.txt" using 1:3 t "DualPivot", \
"" using 1:5 "DualPivotSelect"

