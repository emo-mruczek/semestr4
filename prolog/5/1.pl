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
int([H|T]) :- char_type(H,digit), int(T).
int([]) :- !.

% nazwa zmiennej
id([H|T]) :-
	char_type(H,upper), id(T).
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

czytaj(Char1,Char2,L,Output) :-
		bialy(Char2),
		get_char(Char3),czytaj(Char2,Char3,T,Output2),
		prawo(T,Output2,Output),L=[Char1].

czytaj(Char1,Char2,L,[OutputH|OutputT]) :-
		sep(Char2),
		get_char(Char3),czytaj(Char2,Char3,T,Output2),
		(	
			(atom_chars(S,[Char1,Char2]),sep(S),prawo(T,Output2,OutputT),OutputH=sep(S),L=[]);
			(prawo(T,Output2,OutputT),OutputH=sep(Char2),L=[Char1])
		).

czytaj(Char1,Char2,[Char1|T],Output) :-
		get_char(Char3),czytaj(Char2,Char3,T,Output).

prawo([_|[]],X,X).
prawo([_|T],IN,Output) :- 
		atom_token(T,TOKEN),Output=[TOKEN|IN].	

atom_token(L,Tokeny) :-
			(id(L),atom_chars(T,L),Tokeny=id(T));
			(int(L),atom_chars(T,L),Tokeny=int(T));
			(atom_chars(T,L),key(T),Tokeny=key(T)).

scanner(Strumień,Tokeny) :-
		set_input(Strumień),
		get_char(Char),
		czytaj(' ',Char,L,P),!,
		prawo(L,P,Tokeny),!.
 
