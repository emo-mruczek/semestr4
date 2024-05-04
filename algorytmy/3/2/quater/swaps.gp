set title "Average SWAPS for finding 1/4th statistics"
set style data lines
set xlabel "n"
set ylabel "Average swaps"

plot "average.txt" using 1:3 t "SelectRandom", \
"" using !;% t "SelectFive"
