% predykat jednokrotnie
% zabieram X z listy i sprawdzam, czy nieprawdą jest, że X należy do Reszty
jednokrotnie(X, List) :-
    select(X, List, Reszta),
    \+ member(X, Reszta).

% predykat dwukrotnie
dwukrotnie(X, List) :-
	select(X, List, Reszta),
	select(X, Reszta, KolejnaReszta),
	\+ member(X, KolejnaReszta).


