
instrukcja(assign(WyrazenieX, WyrazenieY)) -->
    [id(WyrazenieX)],
    [sep(:=)],
    wyrazenie(WyrazenieY).

instrukcja(read(WyrazenieX)) -->
    [key(read)],
    [id(WyrazenieX)].

instrukcja(write(WyrazenieY)) -->
    [key(write)],
    wyrazenie(WyrazenieY).

instrukcja(if(WyrazenieX, WyrazenieY)) -->
    [key(if)],
    warunek(WyrazenieX),
    [key(then)],
    program(WyrazenieY),
    [key(fi)].

instrukcja(if(WyrazenieX, WyrazenieY, Z)) -->
    [key(if)],
    warunek(WyrazenieX),
    [key(then)],
    program(WyrazenieY),
    [key(else)],
    program(Z),
    [key(fi)].

instrukcja(while(WyrazenieX, WyrazenieY)) -->
    [key(while)],
    warunek(WyrazenieX),
    [key(do)],
    program(WyrazenieY),
    [key(od)].


wyrazenie(WyrazenieX + WyrazenieY) -->
    skladnik(WyrazenieX),
    [sep(+)],
    wyrazenie(WyrazenieY).

wyrazenie(WyrazenieX - WyrazenieY) -->
    skladnik(WyrazenieX),
    [sep(-)],
    wyrazenie(WyrazenieY).

wyrazenie(WyrazenieX) -->
    skladnik(WyrazenieX).


skladnik(WyrazenieX * WyrazenieY) -->
    czynnik(WyrazenieX),
    [sep(*)],
    skladnik(WyrazenieY).

skladnik(WyrazenieX / WyrazenieY) -->
    czynnik(WyrazenieX),
    [sep(/)],
    skladnik(WyrazenieY).

skladnik(WyrazenieX mod WyrazenieY) -->
    czynnik(WyrazenieX),
    [key(mod)],
    skladnik(WyrazenieY).

skladnik(WyrazenieX) -->
    czynnik(WyrazenieX).


czynnik(id(WyrazenieX)) -->
    [id(WyrazenieX)].

czynnik(int(WyrazenieX)) -->
    [int(WyrazenieX)].

czynnik(( WyrazenieX )) -->
    [sep('(')],
    wyrazenie(WyrazenieX),
    [sep(')')].


warunek((WyrazenieX ; WyrazenieY)) -->
    koniunkcja(WyrazenieX),
    [key(or)],
    warunek(WyrazenieY).

warunek(WyrazenieX) -->
    koniunkcja(WyrazenieX).


koniunkcja((WyrazenieX , WyrazenieY)) -->
    prosty(WyrazenieX),
    [key(and)],
    koniunkcja(WyrazenieY).

koniunkcja(WyrazenieX) -->
    prosty(WyrazenieX).


prosty(WyrazenieX =:= WyrazenieY) -->
    wyrazenie(WyrazenieX),
    [sep(=)],
    wyrazenie(WyrazenieY).

prosty(WyrazenieX =\= WyrazenieY) -->
    wyrazenie(WyrazenieX),
    [sep(/=)],
    wyrazenie(WyrazenieY).

prosty(WyrazenieX < WyrazenieY) -->
    wyrazenie(WyrazenieX),
    [sep(<)],
    wyrazenie(WyrazenieY).

prosty(WyrazenieX > WyrazenieY) -->
    wyrazenie(WyrazenieX),
    [sep(>)],
    wyrazenie(WyrazenieY).

prosty(WyrazenieX >= WyrazenieY) -->
    wyrazenie(WyrazenieX),
    [sep(>=)],
    wyrazenie(WyrazenieY).

prosty(WyrazenieX =< WyrazenieY) -->
    wyrazenie(WyrazenieX),
    [sep(=<)],
    wyrazenie(WyrazenieY).

prosty(( WyrazenieX )) -->
    [sep('(')],
    warunek(WyrazenieX),
    [sep(')')].

program([H|R]) -->
    instrukcja(H),
    [sep(;)],
    !,
    program(R).

 program([]) -->
    [].

% z poprzedniej listy

% slowo kluczowe
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

% liczba naturalna
int([H|T]) :- 
    char_type(H, digit), int(T).
int([]) :- !.

% nazwa zmiennej
id([H|T]) :-
	char_type(H, upper), id(T).
id([]) :-!.

% separator
sep(';'). 
sep('+'). 
sep('-').
sep('*').
sep('/').
sep('(').
sep(')').
sep('<').
sep('>').
sep('=<').
sep('>=').
sep(':=').
sep('=').
sep('/=').

% biale znaki
bialy(' ').
bialy('\t').
bialy('\n').

czytaj('end_of_file',_,[],[]):-
		!.

czytaj(C1, C2, L, Output) :-
		bialy(C2),
		get_char(C3),
        czytaj(C2, C3, T, Output2),
		dodaj(T, Output2, Output),
        L=[C1].

czytaj(C1, C2, L, [OutputH|OutputT]) :-
		sep(C2),
		get_char(C3), czytaj(C2, C3, T, Output2),
		(	
			(atom_chars(S, [C1,C2]), sep(S), dodaj(T,Output2,OutputT),OutputH=sep(S),L=[]);
			(dodaj(T,Output2,OutputT),OutputH=sep(C2),L=[C1])
		).

czytaj(C1, C2, [C1 | T], Output) :-
		get_char(C3),
        czytaj(C2, C3, T, Output).

dodaj([_|[]],WyrazenieX,WyrazenieX).
dodaj([_|T], Input, Output) :- 
		token(T, TOKEN),
        Output = [TOKEN | Input].	

token(L,Tokeny) :-
			(id(L), atom_chars(T, L), Tokeny=id(T));
			(int(L), atom_chars(T, L), Tokeny=int(T));
			(atom_chars(T, L), key(T), Tokeny=key(T)).

scanner(Strumień, Tokeny) :-
		set_input(Strumień), % do czytania z pliku
		get_char(C), % odczytuje pojedynczy znak ze strumienia
		czytaj(' ',C,L,P),!,
		dodaj(L,P,Tokeny),!.
 
