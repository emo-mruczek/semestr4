set title "MAX HEIGHT for INSERTION by N for ASCENDING data"
set style data lines
set xlabel "n"
set ylabel "Maximum height for insertion"
set title font "Helvetica,14"

plot "maximum.txt" using 1:2 t "BST"
set terminal png size 400,300
set output "h_ins_max.png"
replot
