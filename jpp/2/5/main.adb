with Interfaces.C; use Interfaces.C;
with Ada.text_IO; use Ada.Text_IO;

procedure Main is

type solutionLoop is record
    x : Integer;
    y : Integer;
    comment : Integer;
end record
with Convention => C;

type solutionRec is record
    x : Integer;
    y : Integer;
    comment : Integer;
end record
with Convention => C;

type A_Integer is access Integer;

function factorialLoop (n : Integer) return Long_Integer
 with
       Import       => True,
      Convention    => C,
       External_Name => "factorialLoop";

function gcdLoop (a : Integer; b : Integer) return Integer
 with
       Import       => True,
       Convention    => C,
       External_Name => "gcdLoop";

function diofLoop (a : Integer; b : Integer; c : Integer) return solutionLoop  
with
       Import       => True,
       Convention    => C,
       External_Name => "diofLoop";

function gcdExtendedLoop(a : Integer; b : Integer; x : A_Integer; y : A_Integer) return Integer 
with
       Import       => True,
       Convention    => C,
       External_Name => "gcdExtendedLoop";

function factorialRec (n : Integer) return Long_Integer
 with
       Import       => True,
      Convention    => C,
       External_Name => "factorialRec";

function gcdRec (a : Integer; b : Integer) return Integer
 with
       Import       => True,
       Convention    => C,
       External_Name => "gcdRec";

function diofRec (a : Integer; b : Integer; c : Integer) return solutionRec 
with
       Import       => True,
       Convention    => C,
       External_Name => "diofRec";

function gcdExtendedRec(a : Integer; b : Integer; x : A_Integer; y : A_Integer) return Integer 
with
       Import       => True,
       Convention    => C,
       External_Name => "gcdExtendedRec";

    fac : Long_Integer;
    gcd : Integer;
    diofL : solutionLoop;
    facRec : Long_Integer;
    gcdR : Integer;
    diofR : solutionRec;
begin
    fac := factorialLoop(5);
    gcd := gcdLoop(10, 5);
    diofL := diofLoop(1027, 712, 1);

    facRec := factorialRec(5);
    gcdR := gcdRec(10, 5);
    diofR := diofRec(1027, 712, 1);

    Put_Line ("For loop implementation: ");
    Put_Line ("a) " & Long_Integer'Image (fac));
    Put_Line ("b) " & Integer'Image (gcd));
    Put_Line ("c) " & Integer'Image (diofL.x));
    Put_Line ("c) " & Integer'Image (diofL.y));
    Put_Line ("(" & Integer'Image (diofL.comment) & " )");

     Put_Line ("For recursive implementation: ");
    Put_Line ("a) " & Long_Integer'Image (facRec));
    Put_Line ("b) " & Integer'Image (gcdR));
    Put_Line ("c) " & Integer'Image (diofR.x));
    Put_Line ("c) " & Integer'Image (diofR.y));
    Put_Line ("(" & Integer'Image (diofR.comment) & " )");

end Main;