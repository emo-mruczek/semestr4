%    Norweg zamieszkuje pierwszy dom
%    Anglik mieszka w czerwonym domu.
%    Zielony dom znajduje się bezpośrednio po lewej stronie domu białego.
%    Duńczyk pija herbatkę.
%    Palacz papierosów light mieszka obok hodowcy kotów.
%    Mieszkaniec żółtego domu pali cygara.
%    Niemiec pali fajkę.
%    Mieszkaniec środkowego domu pija mleko.
%    Palacz papierosów light ma sąsiada, który pija wodę.
%    Palacz papierosów bez filtra hoduje ptaki.
%    Szwed hoduje psy.
%    Norweg mieszka obok niebieskiego domu.
%    Hodowca koni mieszka obok żółtego domu.
%    Palacz mentolowych pija piwo.
%    W zielonym domu pija się kawę.





% nr, kto, kolor, co hoduje, co pije, co pali
rybki(Kto) :-
	Domy = [[1, _, _, _, _, _],[2, _, _, _, _, _],[3, _, _, _, _, _],[4, _, _, _, _, _],[5, _, _, _, _, _]],
	member([1, norweg, _, _, _, _], Domy),
	member([_, anglik, czerwony, _, _, _], Domy),
	po_lewej([_, _, zielony, _, _, _], [_, _, biały, _, _, _], Domy),
	member([_, duńczyk, _, _, herbata, _], Domy),
	obok([_, _, _, _, _, light], [_, _, _, koty, _, _], Domy),
	member([_, _, żółty, _, _, cygara], Domy),
	member([_, niemiec, _, _, _, fajka], Domy),
	member([3, _, _, _, mleko, _], Domy),
	obok([_, _, _, _, _, light], [_, _, _, _, woda, _], Domy),
	member([_, _, _, ptaki, _, bez_filtra], Domy),
	member([_, szwed, _, psy, _, _], Domy),
	obok([_, norweg, _, _, _, _], [_, _, niebieski, _, _, _], Domy),
	obok([_, _, _, konie, _, _], [_, _, żółty, _, _, _], Domy),
	member([_, _, _, _, piwo, mentole], Domy),
	member([_, _, zielony, _, kawa, _], Domy),
	member([_, Kto, _, rybki, _, _], Domy).

po_lewej(X, Y, [X, Y |_]).
po_lewej(X, Y, [_|R]) :-
	po_lewej(X, Y, R).

obok(X, Y, Domy) :-
	po_lewej(X, Y, Domy).

obok(X, Y, Domy) :-
	po_lewej(Y, X, Domy).
