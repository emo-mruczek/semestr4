#!/run/current-system/sw/bin/bash
awk '{
    if ($2 > maxCT[$1]) maxCT[$1] = $2
    if ($3 > maxST[$1]) maxST[$1] = $3
    if ($4 > maxTT[$1]) maxTT[$1] = $4
    if ($5 > maxCF[$1]) maxCF[$1] = $5
    if ($6 > maxH[$1]) maxH[$1] = $6
    count[$1]++
}
END {
    for (key in maxCT) {
        print key, maxCT[key], maxST[key], maxTT[key],  maxCF[key], maxH[key]
    }
}' random.txt | sort -n > maximum.txt

