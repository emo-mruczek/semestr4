awk '{
    sumCQ[$1] += $2
    sumSQ[$1] += $3
    sumCH[$1] += $4
    sumSH[$1] += $5
    sumCI[$1] += $6
    sumSI[$1] += $7
    count[$1]++
}
END {
    for (key in sumSQ) {
        print key, sumCQ[key] / count[key], sumSQ[key] / count[key], sumCH[key] / count[key], sumSH[key] / count[key], sumCI[key] / count[key], sumSI[key] / count[key]
    }
}' random_1_small.txt > average_1_small.txt


awk '{
    sumSQ[$1] += $2
    sumCQ[$1] += $3
    sumSH[$1] += $4
    sumCH[$1] += $5
    sumSI[$1] += $6
    sumSI[$1] += $7
    count[$1]++
}
END {
    for (key in sumSQ) {
        print key, sumSQ[key] / count[key], sumCQ[key] / count[key], sumSH[key] / count[key], sumCH[key] / count[key], sumSI[key] / count[key], sumSI[key] / count[key]
    }
}' random_10_small.txt > average_10_small.txt

awk '{
    sumSQ[$1] += $2
    sumCQ[$1] += $3
    sumSH[$1] += $4
    sumCH[$1] += $5
    sumSI[$1] += $6
    sumSI[$1] += $7
    count[$1]++
}
END {
    for (key in sumSQ) {
        print key, sumSQ[key] / count[key], sumCQ[key] / count[key], sumSH[key] / count[key], sumCH[key] / count[key], sumSI[key] / count[key], sumSI[key] / count[key]
    }
}' random_100_small.txt > average_100_small.txt
