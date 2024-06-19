#!/run/current-system/sw/bin/bash
awk '{
    if (!($1 in minCT) || $2 < maxCT[$1]) maxCT[$1] = $2
    count[$1]++
}
END {
    for (key in maxCT) {
        print key, maxCT[key]
    }
}' results.txt | sort -n > minimum.txt
