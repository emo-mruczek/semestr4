% definiujemy, ze 2 i 3 są pierwsze, ! odcina
isPrime(2) :- !.
isPrime(3) :- !.
% czy n jest pierwsza
isPrime(N) :- 
	integer(N), N > 3, N mod 2 =\= 0, \+ factor(N, 3).

% czy n ma dzielnik f
factor(N, F) :-
	N mod F =:= 0.
% rekurencja
factor(N, F) :-
	F * F < N, F2 is F + 2, factor(N, F2).

% glowny predykat
prime(LO, HI, N) :-
	between(LO, HI, N), isPrime(N).

