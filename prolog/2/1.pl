
% predykat srodkowy

srodkowy(L, X) :-
	append(Lewa, [X | Prawa], L), % dziele L na dwie czesci
	length(Lewa, N), % N to dlugośc lewej strony
	length(Prawa, N). % Prawa strona ma też długość N, a więc jest taka sama jak lewa

