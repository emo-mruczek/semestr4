awk '{
     sumCH[$1] += $2
    sumSH[$1] += $3
    sumCQ[$1] += $4
    sumSQ[$1] += $5
    sumCI[$1] += $6
    sumSI[$1] += $7
    count[$1]++
}
END {
    for (key in sumSQ) {
        print key, sumCH[key] / count[key], sumSH[key] / count[key], sumCQ[key] / count[key], sumSQ[key] / count[key], sumCI[key] / count[key], sumSI[key] / count[key], (sumCH[key] / count[key])/key, (sumSH[key] / count[key]) / key, (sumCQ[key] / count[key]) / key, (sumSQ[key] / count[key]) / key, (sumCI[key] / count[key]) / key, (sumSI[key] / count[key]) / key
    }
}' random_100_small.txt > average_100_small.txt


