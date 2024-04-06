% predykat max_sum

% suma pustej sekcji to 0
max_sum([], 0).

max_sum(L, S) :-
    max_sum(L, 0, 0, S).

max_sum([], S, _, S).
max_sum([H|T], Max, Obecny, Suma ) :-
    (Obecny < 0 -> Nastepny is H; Nastepny is Obecny + H),
    Naj is max(Max, Nastepny),
    max_sum(T, Naj, Nastepny, Suma).
