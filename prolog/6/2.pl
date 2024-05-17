% zad 2

wykonaj(NazwaPliku):-
    open(NazwaPliku, read, X),
    scanner(X, Y),
    close(X),
    phrase(program(Z), Y),
    interpreter(Z).

%%%%%%%%%%%%%%%%%%


% podstaw(+Stare, +ID, +Wartosc, -Nowe)
podstaw([], ID, N, [ID = N]).
podstaw([ID=_ | AS], ID, N, [ID=N | AS]) :-
    !.
podstaw([ID1=W1 | AS1], ID, N, [ID1=W1 | AS2]) :-
    podstaw(AS1, ID, N, AS2).

% pobierz(+Asocjacje, +ID, -Wartosc)
pobierz([ID=N | _], ID, N) :-
    !.
pobierz([_ | AS], ID, N) :-
    pobierz(AS, ID, N).

% wartosc(+Wyrazenie, +Asocjacje, -Wartosc)
wartosc(int(N), _,N).
wartosc(id(ID), AS, N) :-
    pobierz(AS, ID, N).
wartosc(W1 + W2, AS, N) :-
    wartosc(W1, AS, N1),
    wartosc(W2, AS, N2),
    N is N1 + N2.
wartosc(W1 -W2, AS, N) :-
    wartosc(W1, AS, N1),
    wartosc(W2, AS, N2),
    N is N1 - N2.
wartosc(W1 * W2, AS, N) :-
    wartosc(W1, AS, N1),
    wartosc(W2, AS, N2),
    N is N1 * N2.
wartosc(W1 / W2, AS, N) :-
    wartosc(W1, AS, N1),
    wartosc(W2, AS, N2),N2 =\= 0,
    N is N1 div N2.
wartosc(W1 mod W2, AS, N) :-
    wartosc(W1, AS, N1),
    wartosc(W2, AS, N2),
    N2 =\= 0,
    N is N1 mod N2.

% prawda(+Warunek, +Asocjacje)
prawda(W1 =:= W2, AS) :-
    wartosc(W1, AS, N1),
    wartosc(W2, AS, N2),
    N1 =:= N2.
prawda(W1 =\= W2, AS) :-
    wartosc(W1, AS, N1),
    wartosc(W2, AS, N2),
    N1 =\= N2.
prawda(W1 < W2, AS) :-
    wartosc(W1, AS, N1),
    wartosc(W2, AS, N2),
    N1 < N2.
prawda(W1 > W2, AS) :-
    wartosc(W1, AS, N1),
    wartosc(W2, AS, N2),
    N1 > N2.
prawda(W1 >= W2, AS) :-
    wartosc(W1, AS, N1),
    wartosc(W2, AS, N2),
    N1 >= N2.
prawda(W1 =< W2, AS) :-
    wartosc(W1, AS, N1),
    wartosc(W2, AS, N2),
    N1 =< N2.
prawda((W1, W2), AS) :-
    prawda(W1, AS),
    prawda(W2, AS).
prawda((W1; W2), AS) :-
    (   prawda(W1, AS),
    !
    ;   prawda(W2, AS)).

% interpreter(+Program, +Asocjacje)
interpreter([], _).
interpreter([read(ID) | PGM], ASSOC) :-
    !,
    read(N),
    integer(N),
    podstaw(ASSOC, ID, N, ASSOC1),
    interpreter(PGM, ASSOC1).
interpreter([write(W) | PGM], ASSOC) :-
    !,
    wartosc(W, ASSOC, WART),
    write(WART),
    nl,
    interpreter(PGM, ASSOC).
interpreter([assign(ID, W) | PGM], ASSOC) :-
    !,
    wartosc(W, ASSOC, WAR),
    podstaw(ASSOC, ID, WAR, ASSOC1),
    interpreter(PGM, ASSOC1).
interpreter([if(C, P) | PGM], ASSOC) :- !,
    interpreter([if(C, P, []) | PGM], ASSOC).
interpreter([if(C, P1, P2) | PGM], ASSOC) :-
    !,
    (   prawda(C, ASSOC)->  append(P1, PGM, DALEJ)
    ;   append(P2, PGM, DALEJ)
    ),
    interpreter(DALEJ, ASSOC).
interpreter([while(C, P) | PGM], ASSOC) :-
    !,
    append(P, [while(C, P)], DALEJ),
    interpreter([if(C, DALEJ) | PGM], ASSOC).

% interpreter(+Program)
    interpreter(PROGRAM) :-interpreter(PROGRAM, []).




%%%%%%%%%%%%%%%%%%%%%%


program([H|R]) -->
    instrukcja(H),
    [sep(;)],
    !,
    program(R).

 program([]) -->
    [].


instrukcja(assign(X, Y)) -->
    [id(X)],
    [sep(:=)],
    wyrazenie(Y).

instrukcja(read(X)) -->
    [key(read)],
    [id(X)].

instrukcja(write(Y)) -->
    [key(write)],
    wyrazenie(Y).

instrukcja(if(X, Y)) -->
    [key(if)],
    warunek(X),
    [key(then)],
    program(Y),
    [key(fi)].

instrukcja(if(X, Y, Z)) -->
    [key(if)],
    warunek(X),
    [key(then)],
    program(Y),
    [key(else)],
    program(Z),
    [key(fi)].

instrukcja(while(X, Y)) -->
    [key(while)],
    warunek(X),
    [key(do)],
    program(Y),
    [key(od)].


wyrazenie(X + Y) -->
    skladnik(X),
    [sep(+)],
    wyrazenie(Y).

wyrazenie(X - Y) -->
    skladnik(X),
    [sep(-)],
    wyrazenie(Y).

wyrazenie(X) -->
    skladnik(X).


skladnik(X * Y) -->
    czynnik(X),
    [sep(*)],
    skladnik(Y).

skladnik(X / Y) -->
    czynnik(X),
    [sep(/)],
    skladnik(Y).

skladnik(X mod Y) -->
    czynnik(X),
    [key(mod)],
    skladnik(Y).

skladnik(X) -->
    czynnik(X).


czynnik(id(X)) -->
    [id(X)].

czynnik(int(X)) -->
    [int(X)].

czynnik(( X )) -->
    [sep('(')],
    wyrazenie(X),
    [sep(')')].


warunek((X ; Y)) -->
    koniunkcja(X),
    [key(or)],
    warunek(Y).

warunek(X) -->
    koniunkcja(X).


koniunkcja((X , Y)) -->
    prosty(X),
    [key(and)],
    koniunkcja(Y).

koniunkcja(X) -->
    prosty(X).


prosty(X =:= Y) -->
    wyrazenie(X),
    [sep(=)],
    wyrazenie(Y).

prosty(X =\= Y) -->
    wyrazenie(X),
    [sep(/=)],
    wyrazenie(Y).

prosty(X < Y) -->
    wyrazenie(X),
    [sep(<)],
    wyrazenie(Y).

prosty(X > Y) -->
    wyrazenie(X),
    [sep(>)],
    wyrazenie(Y).

prosty(X >= Y) -->
    wyrazenie(X),
    [sep(>=)],
    wyrazenie(Y).

prosty(X =< Y) -->
    wyrazenie(X),
    [sep(=<)],
    wyrazenie(Y).

prosty(( X )) -->
    [sep('(')],
    warunek(X),
    [sep(')')].

%%%%%%%%%%%%%%%%%%%

% słowa kluczowe
key(read).
key(write).
key(if).
key(then).
key(else).
key(fi).
key(while).
key(do).
key(od).
key(and).
key(or).
key(mod).

% separatory
sep(';').
sep('+').
sep('-').
sep('*').
sep('/').
sep('(').
sep(')').
sep('<').
sep('>').
sep('=').
sep('/=').
sep('=<').
sep('>=').
sep(':=').

% biale znaki
koniec(' ').
koniec('\n').
koniec('\r').
koniec('\t').

scanner(X,Y):-
    czytaj(X,R),
    oddziel(R,Y).

oddziel([],[]).
oddziel([H|R],W):-
    oddziel(R,W1),
    rozdzielacz(H,W2),
    append(W2,W1,W).

pomocniczy(X,[key(X)]):-
    key(X),
    !.

pomocniczy(X,[sep(X)]):-
    sep(X),
    !.

pomocniczy(X,[int(R)]):-
    atom_number(X,R),
    !.

pomocniczy(X,[Z]):-
    \+ (sub_atom(X,_,1,_,C),
       \+ char_type(C,upper)),
    Z =.. [id,X],
    !.

rozdzielacz(S,R):-
    atom_chars(S,Sl),
    rozdzielacz(Sl,'',0,[],R).

jaki_znak(H,T1):-
    (   (char_type(H,digit),T1=4)
        ;(char_type(H,lower),T1=2)
        ;(char_type(H,upper),T1=1)
        ;(char_type(H,prolog_symbol),T1=3)
        ;(H = ';',T1=3)),
        !.

rozdzielacz([],B,_,L,W):-
    (   B = '' -> L = W;
    (pomocniczy(B,R),append(L,R,W))),
    !.

rozdzielacz([H|R],_,0,L,W):-
    jaki_znak(H,T1),
    rozdzielacz(R,H,T1,L,W),
    !.

rozdzielacz([H|R],B,T,L,W):-
    jaki_znak(H,T1),
    T1 = T,
    atom_concat(B,H,B1),
    rozdzielacz(R,B1,T,L,W),
    !.

rozdzielacz([H|R],B,_,L,W):-
    jaki_znak(H,T1),
    pomocniczy(B,B1),
    append(L,B1,L1),
    rozdzielacz(R,H,T1,L1,W).

czytaj(Str,R):-
    get_char(Str, C),
    czytaj(Str, C, R).

czytaj(_, end_of_file, []):-!.

czytaj(Str, C, R):-
    koniec(C),
    get_char(Str, C1),
    czytaj(Str, C1, R),
    !.

czytaj(Str, C, R):-
    czytaj_slowo(Str, C, '', X),
    czytaj(Str, R1),
    append(X, R1, R),
    !.

czytaj_slowo(end_of_file, _, S, [S]):-!.


czytaj_slowo(_, C, Slowo, [Slowo]):-
    koniec(C),
    !.

czytaj_slowo(Str,C,Slowo,Res):-
    atom_concat(Slowo, C, Sl),
    get_char(Str, C1),
    czytaj_slowo(Str, C1, Sl, Res),
    !.




