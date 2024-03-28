with Ada.Strings; use Ada.Strings;
with Ada.Strings.Unbounded; use  Ada.Strings.Unbounded;
package body librec is

function factorialRec (n : Integer) return Long_Integer is
    i : Long_Integer := 1;
    locN : Integer := n;
begin
    if ( locN  = 0 or locN  = 1 ) then
        return 1;
    else 
        return (Long_Integer(locN) * factorialRec(locN - 1));
    end if;
end factorialRec;

function gcdRec(a : Integer; b : Integer) return Integer is
    locA : Integer := a;
    locB : Integer := b;
begin
    if locA < 0 then
        locA := -locA;
    end if;
    if locB < 0 then
        locB := -locB;
    end if;

    if (locA = locB) then
        return locA;
    elsif (locA > locB) then
        return gcdRec (locA - locB, locB);
    else 
        return gcdRec (locA, locB - locA);
    end if;
end gcdRec;

function diofRec (a : Integer; b : Integer; c : Integer) return solutionRec is
    result : solutionRec;
    d : Integer := gcdRec(a, b);
    gcda, gcdb, gcdc: Integer;
    gcd : Integer;
    x, y : Integer;
     x_ptr, y_ptr : A_Integer := new Integer'(0);
begin

    if (c rem d) /= 0 then    
        result.x := 0;
        result.y := 0;
        result.comment := To_Unbounded_String("Soulution does not exist");
        return result;
    end if;

    gcda := a / d;
    gcdb := b / d;
    gcdc := c / d;

    gcd := gcdExtendedRec(gcda, gcdb, x_ptr, y_ptr);
    x := x_ptr.all;
    y := y_ptr.all;

    result.x := x * gcdc;
    result.y := y * gcdc;
    result.comment := To_Unbounded_String("Solution exist");

    return result;
end diofRec;

function gcdExtendedRec(a : Integer; b : Integer; x : A_Integer; y : A_Integer) return Integer is
    x1 : Integer := 0;
    y1 : Integer := 1;
    currX : Integer := 1;
    currY : Integer := 0; 
    quotient, tempX, tempY, temp : Integer;
    locA : Integer := a;
    locB : Integer := b;
    gcd : Integer;
    x1ptr: A_Integer := x;
    x2ptr: A_Integer := y;
begin
    if (locA = 0) then
        x.all := 0;
        y.all := 1;
        return locB;
    end if;
    
    gcd := gcdExtendedRec( (locB rem locA), locA, x1ptr, x2ptr);

   -- x'Access := currX;
   -- y'Access := currY;
    x.all := y1 - (locB / locA) * x1;
    y.all := x1;

    return gcd;
end gcdExtendedRec;

end librec;