
ojciec(X, Y).
matka(X, Y).
mężczyzna(X).
kobieta(X).
rodzic(X, Y).


jest_matką(X) :- kobieta(X), matka(X, Y), X \= Y.
jest_ojcem(X) :- mężczyzna(X), ojciec(X, Y), X \= Y.
jest_synem(X) :- mężczyzna(X), rodzic(Y, X), x \= Y.
siostra(X, Y) :- kobieta(X), rodzic(Z, X), rodzic(Z,Y), X \= Y, Z \= Y, Z \= X.
dziadek(X, Y) :- mężczyzna(X), rodzic(Z, Y), rodzic(X, Z), Z \= Y, Z \= X, X \= Y.
rodzeństwo(X, Y) :- rodzic(Z, X), rodzic(Z, Y), X \= Y, X \= Z, Y \= Z.
