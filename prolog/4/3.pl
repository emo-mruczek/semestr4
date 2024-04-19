% zabierz K zapalek tak, aby pozostałe tworzyły D dużych, S średnich, M małych
zapalki(K, D, S, M) :-
    mały(M, List1),
    średni(S, List1,  List2),
    duży(D, List2,  List3),
    length(List3, Len),
    K is 24 - Len, % ile zabrało zapałek
    narysuj(List3).

mały(Ile, List) :-
    ((List1 = [1, 4, 5, 8], Ile1 = 1) ; (List1 = [], Ile1 = 0)),
    ((union(List1, [2, 5, 6, 9], List2), Ile2 is Ile1 + 1) ; (List2 = List1, Ile2 = Ile1)),
    ((union(List2, [3, 6, 7, 10], List3), Ile3 is Ile2 + 1) ; (List3 = List2, Ile3 = Ile2)),
    ((union(List3, [8, 11, 12, 15], List4), Ile4 is Ile3 + 1) ; (List4 = List3, Ile4 = Ile3)),
    ((union(List4, [9, 12, 13, 16], List5), Ile5 is Ile4 + 1) ; (List5 = List4, Ile5 = Ile4)),
    ((union(List5, [10, 13, 14, 17], List6), Ile6 is Ile5 + 1) ; (List6 = List5, Ile6 = Ile5)),
    ((union(List6, [15, 18, 19, 22], List7), Ile7 is Ile6 + 1) ; (List7 = List6, Ile7 = Ile6)),
    ((union(List7, [16, 19, 20, 23], List8), Ile8 is Ile7 + 1) ; (List8 = List7, Ile8 = Ile7)),
    ((union(List8, [17, 20, 21, 24], List), Ile is Ile8 + 1) ; (List = List8, Ile = Ile8)).

średni(Ile, Obecnie,  List) :-
    Kwadrat1 = [1, 2, 4, 6, 11, 13, 15, 16],
    Kwadrat2 = [2, 3, 5, 7, 12, 14, 16, 17],
    Kwadrat3 = [8, 9, 11, 13, 18, 20, 22, 23],
    Kwadrat4 = [9, 10, 12, 14, 19, 21, 23, 24],
    ((union(Obecnie, Kwadrat1, List1), Ile1 = 1) ; (List1 = Obecnie, Ile1 = 0)),
    ((union(List1, Kwadrat2, List2), Ile2 is Ile1 + 1) ; (List2 = List1, Ile2 = Ile1)),
    ((union(List2, Kwadrat3, List3), Ile3 is Ile2 + 1) ; (List3 = List2, Ile3 = Ile2)),
    ((union(List3, Kwadrat4, List), Ile is Ile3 + 1) ; (List = List3, Ile = Ile3)).

duży(Ile, Obecnie,  List) :-
    Kwadrat = [1, 2, 3, 4, 7, 11, 14, 18, 21, 22, 23, 24],
    ((union(Obecnie, Kwadrat, List), Ile = 1) ; (List = Obecnie, Ile = 0)).

% rysuje zapalke tylko gdy numer zapalki jest w liscie zapalki
narysuj(Zapalki) :-
	(member(1, Zapalki) -> write("+---+") ; write("+   +")),
	(member(2, Zapalki) -> write("---+") ; write("   +")),
	(member(3, Zapalki) -> write("---+\n") ; write("   +\n")),
	(member(4, Zapalki) -> write("|   ") ; write("    ")),
	(member(5, Zapalki) -> write("|   ") ; write("    ")),
	(member(6, Zapalki) -> write("|   ") ; write("    ")),
	(member(7, Zapalki) -> write("|\n") ; write(" \n")),
	(member(8, Zapalki) -> write("+---+") ; write("+   +")),
	(member(9, Zapalki) -> write("---+") ; write("   +")),
	(member(10, Zapalki) -> write("---+\n") ; write("   +\n")),
	(member(11, Zapalki) -> write("|   ") ; write("    ")),
	(member(12, Zapalki) -> write("|   ") ; write("    ")),
	(member(13, Zapalki) -> write("|   ") ; write("    ")),
	(member(14, Zapalki) -> write("|\n") ; write(" \n")),
	(member(15, Zapalki) -> write("+---+") ; write("+   +")),
	(member(16, Zapalki) -> write("---+") ; write("   +")),
	(member(17, Zapalki) -> write("---+\n") ; write("   +\n")),
	(member(18, Zapalki) -> write("|   ") ; write("    ")),
	(member(19, Zapalki) -> write("|   ") ; write("    ")),
	(member(20, Zapalki) -> write("|   ") ; write("    ")),
	(member(21, Zapalki) -> write("|\n") ; write(" \n")),
	(member(22, Zapalki) -> write("+---+") ; write("+   +")),
	(member(23, Zapalki) -> write("---+") ; write("   +")),
	(member(24, Zapalki) -> write("---+\n") ; write("   +\n")).







