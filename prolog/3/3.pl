%  korzystam z faktu, ze permutacja jest parzysta, gdy
% 1. permutacja n-1 elementow jest nieparzysta i element n jest na parzystym indeksie
% 2.permutacja n-1 elementow jest parzysta i element n jest na nieparzystym indeksie

even_permutation([X], [X]).

even_permutation([H|Xs], Ys) :-
    odd_permutation(Xs, NoweYs),
    even_index(H, NoweYs, Ys).

even_permutation([H|Xs], Ys) :-
    even_permutation(Xs, NoweYs),
    odd_index(H, NoweYs, Ys).

%  korzystam z faktu, ze permutacja jest nieparzysta, gdy
% 1. permutacja n-1 elementow jest nieparzysta i element n jest na nieparzystym indeksie
% 2.permutacja n-1 elementow jest parzysta i element n jest na parzystym indeksie


odd_permutation([H|Xs], Ys) :-
    odd_permutation(Xs, NoweYs),
    odd_index(H, NoweYs, Ys).

odd_permutation([H|Xs], Ys) :-
    even_permutation(Xs, NoweYs),
    even_index(H, NoweYs, Ys).


odd_index(X, Xs, [X|Xs]).
odd_index(X, [Y,H|Xs], [Y,H|Ys]) :-
    odd_index(X, Xs, Ys).

even_index(X, [Y|Xs], [Y,X|Xs]).
even_index(X, [Y,H|Xs], [Y,H|Ys]) :-
    even_index(X, Xs, Ys).
