with Ada.Strings; use Ada.Strings;
with Ada.Strings.Unbounded; use  Ada.Strings.Unbounded;
package librec is
type solutionRec is record
    x : Integer;
    y : Integer;
    comment : Unbounded_String;
end record;

--pointers
--type A_Float is access all Float;
type A_Integer is access Integer;

function factorialRec (n : Integer) return Long_Integer;

function gcdRec (a : Integer; b : Integer) return Integer;

function diofRec (a : Integer; b : Integer; c : Integer) return solutionRec;

function gcdExtendedRec (a : Integer; b : Integer; x : A_Integer; y : A_Integer) return Integer;

end librec;