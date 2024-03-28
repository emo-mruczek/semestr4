
with Interfaces.C; use Interfaces.C;

package librec is

type solutionRec is record
    x : Integer;
    y : Integer;
    comment : Integer;
end record
with Convention => C;

--pointers
type A_Integer is access Integer;

function factorialRec (n : Integer) return Long_Integer
 with
       Export        => True,
       Convention    => C,
       External_Name => "factorialRec";

function gcdRec (a : Integer; b : Integer) return Integer
with
       Export        => True,
       Convention    => C,
       External_Name => "gcdRec";

function diofRec (a : Integer; b : Integer; c : Integer) return solutionRec 
 with
       Export        => True,
       Convention    => C,
       External_Name => "diofRec";

function gcdExtendedRec (a : Integer; b : Integer; x : A_Integer; y : A_Integer) return Integer
 with
       Export        => True,
       Convention    => C,
       External_Name => "gcdExtendedRec";


end librec;