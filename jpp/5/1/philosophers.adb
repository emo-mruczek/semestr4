with Ada.Text_IO; use Ada.Text_IO;
with Ada.Numerics.Discrete_Random;
with Ada.Real_Time; use Ada.Real_Time;

-- Dijkstra's solution

package body Philosophers is

Min_Time : constant Integer := 400;
Max_Time : constant Integer := 1000;

-- just for generating random time
function Random_Time return Integer is 
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
end Random_Time;

-- mutex for relieable printing
protected Print_Mutex is 
    entry Lock;
    procedure Unlock;
private
    Locked : Boolean := False;
end Print_Mutex;

protected body Print_Mutex is 
    entry Lock when not Locked is
    begin
        Locked := True;
    end Lock;

    procedure Unlock is
    begin
        Locked := False;
    end Unlock;
end Print_Mutex;

-- the guy's thinkin!
procedure Think (Number: Integer) is 
    Duration_Of_Delay : Integer := Random_Time;
    Delay_Time : Time_Span := Milliseconds(Duration_Of_Delay);
begin
    Print_Mutex.Lock;
    Put_Line("The " & Integer'Image(Number) & " philosopher is thinking");
    Print_Mutex.Unlock;
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

