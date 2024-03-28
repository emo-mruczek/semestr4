arc(a, b).
arc(b, a).
arc(b, c).
arc(c, d).

osiągalny(X, Y, Odwiedzone) :-
    arc(X, Y), % bezposrednio
    \+ member(X, Odwiedzone). % czy byl odwiedzony

osiągalny(X, Y, Odwiedzone) :-
    arc(X, Z), 
    \+ member(X, Odwiedzone), % czy odwiedzony
    osiągalny(Z, Y, [X|Odwiedzone]). %  Z jest osiągalny z Y, to Y jest osiągalny z X.

osiągalny(X, X, Odwiedzone) :-
	\+ member(X, Odwiedzone). % dla samego siebie jest sie osiagalnym

% poczatkowo
osiągalny(X, Y) :-
    osiągalny(X, Y, []).


