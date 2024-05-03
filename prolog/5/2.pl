
board(X):-
    length(X,L),
    rysuj(X,1,L).

% z poprzedniej listy
hetmany(N, P):-
    between(1, 100, N),
    numlist(1, N, L),
    permutation(L,P),

    dobra(P).

dobra(P) :-
    \+ zla(P).

zla(P) :-
    append(_, [Wi | L1], P),
    append(L2, [Wj | _ ], L1),
    length(L2, K),
    abs(Wi - Wj) =:= K + 1.
    
rysuj(_, Nk, Rozmiar):-
    Nk > Rozmiar,
    przerywana(Rozmiar),
    nl,
    !.

rysuj(Tab, Nk, Rozmiar):-
    przerywana(Rozmiar),
    Y is Rozmiar - Nk +1,
    prosta(1, Y, Tab, Rozmiar),
    prosta(1, Y, Tab, Rozmiar),
    Nk1 is Nk +1,
    rysuj(Tab, Nk1, Rozmiar),
    !.

prosta(Nw, _, _, Rozmiar):-
    Rozmiar + 1 =:= Nw,
    write('|'),
    nl,
    !.

prosta(Nw, Nk, Tab, Rozmiar):-
    nth1(Nw, Tab, Nk),
    (   ((Nw mod 2 =:= 0, Nk mod 2 =:= 1)
        ;(Nw mod 2 =:= 1, Nk mod 2 =:= 0)
        ) -> write('|:###:') ; write('| ### ')
    ),
    Nw1 is Nw + 1,
    prosta(Nw1, Nk, Tab, Rozmiar),
    !.

prosta(Nw, Nk, Tab, Rozmiar):-
    (   ((Nw mod 2 =:= 0, Nk mod 2 =:= 1)
        ;(Nw mod 2 =:= 1, Nk mod 2 =:= 0)
        ) -> write('|:::::') ; write('|     ')
    ),
    Nw1 is Nw + 1,
    prosta(Nw1, Nk, Tab, Rozmiar),
    !.

przerywana(0):-
    write('+'),
    nl,
    !.

przerywana(Rozmiarmiar):-
    write('+-----'),
    R is Rozmiarmiar -1,
    przerywana(R).


