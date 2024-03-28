
package body libloop is

function factorialLoop (n : Integer) return Long_Integer is
    result : Long_Integer := 1;
    i : Long_Integer := 1;
begin
    while i <= Long_Integer (n) loop  
        result := result * i;
        i := i + 1;
    end loop;
return result;
end factorialLoop;

function gcdLoop(a : Integer; b : Integer) return Integer is
    locA : Integer := a;
    locB : Integer := b;
begin
    if locA < 0 then
        locA := -locA;
    end if;
    if locB < 0 then
        locB := -locB;
    end if;

    while locA /= locB loop
        if locA > locB then
            locA := locA - locB;
        else 
            locB := locB - locA;
        end if;
    end loop;
return LocA;
end gcdLoop;

function diofLoop (a : Integer; b : Integer; c : Integer) return solutionLoop is
    result : solutionLoop;
    d : Integer := gcdLoop(a, b);
    gcda, gcdb, gcdc: Integer;
    gcd : Integer;
    x, y : Integer;
     x_ptr, y_ptr : A_Integer := new Integer'(0);
begin

    if (c rem d) /= 0 then    
        result.x := 0;
        result.y := 0;
        result.comment := -1;
        return result;
    end if;

    gcda := a / d;
    gcdb := b / d;
    gcdc := c / d;

    gcd := gcdExtendedLoop(gcda, gcdb, x_ptr, y_ptr);
    x := x_ptr.all;
    y := y_ptr.all;

    result.x := x * gcdc;
    result.y := y * gcdc;
    result.comment := 1;

    return result;
end diofLoop;

function gcdExtendedLoop(a : Integer; b : Integer; x : A_Integer; y : A_Integer) return Integer is
    x1 : Integer := 0;
    y1 : Integer := 1;
    currX : Integer := 1;
    currY : Integer := 0; 
    quotient, tempX, tempY, temp : Integer;
    locA : Integer := a;
    locB : Integer := b;
begin
    while locA /= 0 loop  
        quotient := locB / locA;
        tempX := currX - quotient * x1;
        tempY := currY - quotient * y1;
        currX := x1;
        currY := y1;
        x1 := tempX;
        y1 := tempY;
 
        temp := locA;
        locA := locB rem locA;
        locB := temp;
    end loop;

   -- x'Access := currX;
   -- y'Access := currY;
    x.all := currX;
    y.all := currY;

    return locB;
end gcdExtendedLoop;
end libloop;