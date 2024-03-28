with Interfaces.C; use Interfaces.C;

package libloop is

type solutionLoop is record
    x : Integer;
    y : Integer;
    comment : Integer;
end record
with Convention => C;

type A_Integer is access Integer;

function factorialLoop (n : Integer) return Long_Integer
 with
       Export        => True,
       Convention    => C,
       External_Name => "factorialLoop";

function gcdLoop (a : Integer; b : Integer) return Integer
 with
       Export        => True,
       Convention    => C,
       External_Name => "gcdLoop";

function diofLoop (a : Integer; b : Integer; c : Integer) return solutionLoop
 with
       Export        => True,
       Convention    => C,
       External_Name => "diofLoop";

function gcdExtendedLoop(a : Integer; b : Integer; x : A_Integer; y : A_Integer) return Integer
 with
       Export        => True,
       Convention    => C,
       External_Name => "gcdExtendedLoop";

end libloop;