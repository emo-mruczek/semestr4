above(Blocka, Blockb) :- on(Blocka, Blockb).
above(Blocka, Blockb) :- on(Blocka, X), above(X, Blockb).

on(Block1, Block2).
on(Block2, Block3).
on(Block3, Block4).
