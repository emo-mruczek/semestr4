set title "Average COMPARISONS for finding MIDDLE statistics"
set style data lines
set xlabel "n"
set ylabel "Average comparisons"

plot "average.txt" using 1:2 t "SelectThree", \
"" using 1:5 t "SelectFive", \
"" using 1:8 t "SelectSeven", \
"" using 1:11 t "SelectNine"
