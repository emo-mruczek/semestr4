#!/run/current-system/sw/bin/bash
awk '{
    sumCT[$1] += $2
   count[$1]++
}
END {
    for (key in sumCT) {
        print key, sumCT[key] / count[key] }
}' results.txt | sort -n > average.txt
