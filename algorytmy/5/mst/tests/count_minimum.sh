#!/run/current-system/sw/bin/bash

awk '{
    if (!($1 in minCT) || $2 < minCT[$1]) minCT[$1] = $2
    count[$1]++
}
END {
    for (key in minCT) {
        print key, minCT[key]
    }
}' results.txt | sort -n > minimum.txt

