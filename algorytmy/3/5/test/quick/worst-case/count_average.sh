awk '{
     sumCH[$1] += $2
    sumSH[$1] += $3
    sumCQ[$1] += $4
    sumSQ[$1] += $5
    count[$1]++
}
END {
    for (key in sumSQ) {
        print key, sumCH[key] / count[key], sumSH[key] / count[key], sumCQ[key] / count[key], sumSQ[key] / count[key]
    }
}' random.txt | sort -n > average.txt


