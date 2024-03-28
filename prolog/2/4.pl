czyParzysta(_, [], _) :- fail.

czyParzysta(_, [_], _) :- fail.
czyParzysta(N, List, Index1) :-
    znajdzNastepny(N, List, Index1, Index2), % szuka wystapienia
    Total is Index2 - Index1 - 1,
    Total mod 2 =:= 0. % czy jest parzysta liczba pomiedzy wystapieniami?

znajdzNastepny(_, [], _, _) :- fail.
znajdzNastepny(Element, [Element|_], Index, Index).
znajdzNastepny(Element, [_|Tail], Index1, Index) :-
    Index2 is Index1 + 1,
    znajdzNastepny(Element, Tail, Index2, Index).

isOk(0, _).
isOk(N, List) :-
    N > 0, % sprawdza dla kazdej liczby od 1 do N
    czyParzysta(N, List, -1), % od indeksu -1
    N1 is N - 1,
    isOk(N1, List). % rekurencyjnie

lista(N, X) :-
   distinct(( numlist(1, N, Num), % tworze liste z liczbami od 1 do N
    append(Num, Num, Podwojona), % podwajam ją
    permutation(Podwojona, X), % permutuje
    isOk(N, X))). % czy permutacja spełnia zalozenia z zadania?

