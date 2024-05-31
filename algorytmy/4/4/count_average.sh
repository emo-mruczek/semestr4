#!/run/current-system/sw/bin/bash
awk '{
    sumCT[$1] += $2
    sumST[$1] += $3
    sumTT[$1] += $4
    sumCF[$1] += $5
   count[$1]++
}
END {
    for (key in sumCT) {
        print key, sumCT[key] / count[key], sumST[key] / count[key], sumTT[key] / count[key],  sumCF[key] / count[key] }
}' random.txt | sort -n > average.txt
