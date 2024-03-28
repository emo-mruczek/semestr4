with Ada.text_IO; use Ada.Text_IO;
with Ada.Strings; use Ada.Strings;
with Ada.Strings.Unbounded; use  Ada.Strings.Unbounded;
with libloop;
with librec;

procedure Main is
    use libloop;
    use librec;
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
    Put_Line ("(" & Ada.Strings.Unbounded.To_String(diofL.comment) & ")");

    Put_Line ("For recursive implementation: ");
    Put_Line ("a) " & Long_Integer'Image (facRec));
    Put_Line ("b) " & Integer'Image (gcdR));
    Put_Line ("c) " & Integer'Image (diofR.x));
    Put_Line ("c) " & Integer'Image (diofR.y));
    Put_Line ("(" & Ada.Strings.Unbounded.To_String(diofR.comment) & ")");

   --Put_Line ("c) " & Unbounded_String (diofL.comment));
    
end Main;
