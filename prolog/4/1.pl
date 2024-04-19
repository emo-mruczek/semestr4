wyrażenie([X], X, X).

wyrażenie(L, RET, A + B) :-
    działanie(L, Ret1, Ret2, A, B),
    RET is Ret1 + Ret2.

wyrażenie(L, RET, A - B) :-
    działanie(L, Ret1, Ret2, A, B),
    RET is Ret1 - Ret2.

wyrażenie(L, RET, A * B) :-
    działanie(L, Ret1, Ret2, A, B),
    RET is Ret1 * Ret2.

wyrażenie(L, RET, A / B) :-
    działanie(L, Ret1, Ret2, A, B),
    Ret2 =\= 0,  % nie mozna dzielic przez zero
    RET is Ret1 / Ret2.

działanie(Lista, Ret1, Ret2, A, B):-
    append([H1|T1], [H2|T2], Lista), % podziel liste
    wyrażenie([H1|T1], Ret1, A),  % wywolaj rekursywnie
    wyrażenie([H2|T2], Ret2, B).



