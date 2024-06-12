mergesort([], []). 
mergesort([A], [A]).

mergesort([A, B | Rest], S) :-
  divide([A, B | Rest], L1, L2),
  mergesort(L1, S1),
  mergesort(L2, S2),
  my_merge(S1, S2, S).

divide([], [], []).
divide([A], [A], []).

divide([A, B | R], [A | Ra], [B | Rb]) 
    :-  divide(R, Ra, Rb).

my_merge(A, [], A).
my_merge([], B, B).

my_merge([A | Ra], [B | Rb], [A | M]) :-
  A =< B,
  my_merge(Ra, [B | Rb], M).
my_merge([A | Ra], [B | Rb], [B | M]) :-
  A > B,
  my_merge([A | Ra], Rb, M).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

egcd(A, 0, 1, 0, A).
egcd(A, B, X, Y, G) :-
    B \= 0,
    Q is A // B,
    R is A mod B,
    egcd(B, R, X1, Y1, G),
    X is Y1,
    Y is X1 - Q * Y1.
    
de(A, B, X, Y, Z) :-
    egcd(A, B, X, Y, G),
    Z is G.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

prime_factors(N, X) :-
    N > 1,
    prime_factors(N, 2, X).

prime_factors(1, _, []).
prime_factors(N, D, [D|X]) :-
    N > 1,
    N mod D =:= 0,
    N1 is N // D,
    prime_factors(N1, D, X).
prime_factors(N, D, X) :-
    N > 1,
    (D = 2 -> D1 is 3 ; D1 is D + 2),
    prime_factors(N, D1, X).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

distinct_factors(L, D) :-
    sort(L, D).

totient(N, T) :-
    N > 0,
    prime_factors(N, Factors),
    distinct_factors(Factors, DistinctFactors),
    compute_totient(N, DistinctFactors, T).

compute_totient(N, [], N).
compute_totient(N, [P|Ps], T) :-
    N1 is N * (P - 1) // P,
    compute_totient(N1, Ps, T).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

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

primes(N, Xs) :-
    findall(X, prime(2, N, X), Xs).
