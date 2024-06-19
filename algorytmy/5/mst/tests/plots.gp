
set terminal png size 500,400
set output "rounds.png"

set title "Number of rounds"
set style data lines
set xlabel "n"
set ylabel "rounds"

plot "average.txt" using 1:2 title "average", \
     "maximum.txt" using 1:2 title "maximum", \
     "minimum.txt" using 1:2 title "minimum"

unset output

