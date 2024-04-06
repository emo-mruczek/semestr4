% predykat wariancja
% wzor: (1 / (N)) * \sum_n (x_i - \mu)^2

wariancja(L, D) :-
    length(L, N),
    suma_kwadratow(L, Suma),
    D is (1/N) * Suma.

% oblicza: \sum_n (x_i - \mu)^2 (sume kwadratow)
suma_kwadratow([], 0).
suma_kwadratow([_], 0).
suma_kwadratow(L, W) :-
    srednia(L, M),
    maplist(roznica(M), L, Res),
    sum_list(Res, W).

% oblicza roznice
roznica(Mu, B, A):-
    AB is B - Mu,
    pow(AB, 2, A).

% oblicza srednia
srednia(L, W) :-
    length(L, N),
    sum_list(L, S),
    W is S/N.
