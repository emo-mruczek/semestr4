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

dodaj([_|[]],X,X).
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
 
