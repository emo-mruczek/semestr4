--with ada.strings.unbounded;
--with ada.strings.unbounded_text_io;
with Ada.Strings; use Ada.Strings;
with Ada.Strings.Unbounded; use  Ada.Strings.Unbounded;
package libloop is


type solutionLoop is record
    x : Integer;
    y : Integer;
    comment : Unbounded_String;
end record;

--pointers
--type A_Float is access all Float;
type A_Integer is access Integer;

function factorialLoop (n : Integer) return Long_Integer;

function gcdLoop (a : Integer; b : Integer) return Integer;

function diofLoop (a : Integer; b : Integer; c : Integer) return solutionLoop;

function gcdExtendedLoop(a : Integer; b : Integer; x : A_Integer; y : A_Integer) return Integer;

end libloop;