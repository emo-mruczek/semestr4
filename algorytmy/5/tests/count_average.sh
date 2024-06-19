#!/run/current-system/sw/bin/bash
awk '{
    sumCT[$1] += $2
    sumST[$1] += $3
   count[$1]++
}
END {
    for (key in sumCT) {
        print key, sumCT[key] / count[key], sumST[key] / count[key] }
}' results.txt | sort -n > average.txt
