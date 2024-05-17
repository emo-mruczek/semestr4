with Ada.Text_IO; use Ada.Text_IO;
with Ada.Numerics.Discrete_Random;
with Ada.Real_Time; use Ada.Real_Time;

-- Dijkstra's solution

package body Philosophers is

Min_Time : constant Integer := 400;
Max_Time : constant Integer := 1000;

-- just for generating random time
function RandomTime return Integer is 
    Loc_Min : Integer := Min_Time;
    Loc_Max : Integer := Max_Time;
    subtype Range_Type is Integer range Loc_Min .. Loc_Max;
    package Random_Numbers is new Ada.Numerics.Discrete_Random(Range_Type);
    use Random_Numbers;
    G : Generator;
    Random_Value : Range_Type;
begin
    Reset(G);
    Random_Value := Random(G);
    return Random_Value;
end RandomTime;

-- the guy's thinkin!
procedure Think (Number: Integer) is 
    Duration_Of_Delay : Integer := RandomTime;
    Delay_Time : Time_Span := Milliseconds(Duration_Of_Delay);
begin
    Put_Line("The " & Integer'Image(Number) & " philosopher is thinking");
    delay until Clock + Delay_Time;
end Think;

-- the guy themselves
task type Philosopher (Number: Integer);
task body Philosopher is
begin
     loop
        Think(Number);
    end loop;
end Philosopher;

procedure Main is
    Phi1 : Philosopher(1);
    Phi2 : Philosopher(2);
    Phi3 : Philosopher(3);
    Phi4 : Philosopher(4);
    Phi5 : Philosopher(5);
begin
    null;
end Main;

end Philosophers;

