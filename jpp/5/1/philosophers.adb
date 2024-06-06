with Ada.Text_IO; use Ada.Text_IO;
with Ada.Numerics.Discrete_Random;
with Ada.Real_Time; use Ada.Real_Time;

-- Dijkstra's solution

package body Philosophers is

    Number_Of_Meals : constant Integer := 3;
    Number_Of_Philosophers : constant Integer := 5;

    Min_Time : constant Integer := 400;
    Max_Time : constant Integer := 1000;

    type State is (THINKING, HUNGRY, EATING);
    type Status_Array is array (1 .. Number_Of_Philosophers) of State;
    Status : Status_Array := (others => THINKING);

    type Meals_Eaten_Array is array (1 .. Number_Of_Philosophers) Of Integer;
    Meal_Eaten : Meals_Eaten_Array := (others => 0);

    -- semaphore
    protected type Binary_Semaphore (Initially_Available : Boolean) is
        entry Wait;
        procedure Signal;
    private
        Available : Boolean := Initially_Available;
    end Binary_Semaphore;

    protected body Binary_Semaphore is
        entry Wait when Available is
        begin
            Available := False;
        end Wait;

        procedure Signal is
        begin
            Available := True;
        end Signal;
    end Binary_Semaphore;

    type Semaphore_Access is access all Binary_Semaphore;

    Forks : array (1 .. Number_Of_Philosophers) of Semaphore_Access;

    -- just for generating random time
    function Random_Time return Integer is 
        subtype Range_Type is Integer range Min_Time .. Max_Time;
        package Random_Numbers is new Ada.Numerics.Discrete_Random(Range_Type);
        use Random_Numbers;
        G : Generator;
        Random_Value : Range_Type;
    begin
        Reset(G);
        Random_Value := Random(G);
        return Random_Value;
    end Random_Time;

    -- mutex for reliable printing
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

    -- mutex for accessing array of meals 
    protected Meal_Mutex is
        entry Lock;
        procedure Unlock;
    private
        Locked: Boolean := False;
    end Meal_Mutex;

    protected body Meal_Mutex is
        entry Lock when not Locked is
        begin 
            Locked := True;
        end Lock;

        procedure Unlock is
        begin
            Locked := False;
        end Unlock;
    end Meal_Mutex;


    -- mutex for taking forks
    protected Forks_Mutex is
        entry Lock;
        procedure Unlock;
    private
        Locked : Boolean := False;
    end Forks_Mutex;

    protected body Forks_Mutex is
        entry Lock when not Locked is
        begin
            Locked := True;
        end Lock;

        procedure Unlock is
        begin
            Locked := False;
        end Unlock;
    end Forks_Mutex;

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

    -- test state
    procedure Test (Number: Integer) is
        Left : Integer := (Number - 1 + Number_Of_Philosophers) mod Number_Of_Philosophers + 1;
        Right : Integer := (Number mod Number_Of_Philosophers) + 1;
    begin
        if Status(Number) = HUNGRY and then Status(Left) /= EATING and then Status(Right) /= EATING then
            Status(Number) := EATING;
            Forks(Number).Signal;
        end if;
    end Test;

    -- gotten hungry
    procedure Take_Forks (Number: Integer) is
    begin
        Forks_Mutex.Lock;
        Status(Number) := HUNGRY;
        Print_Mutex.Lock;
        Put_Line("The " & Integer'Image(Number) & " philosopher is hungry");
        Print_Mutex.Unlock;
        Test(Number);
        Forks_Mutex.Unlock;
        Forks(Number).Wait;
    end Take_Forks;

    -- put down forks
    procedure Give_Forks (Number: Integer) is
        Left : Integer := (Number - 1 + Number_Of_Philosophers) mod Number_Of_Philosophers + 1;
        Right : Integer := (Number mod Number_Of_Philosophers) + 1;
    begin
        Forks_Mutex.Lock;
        Status(Number) := THINKING;
        Test(Left);
        Test(Right);
        Forks_Mutex.Unlock;
    end Give_Forks;

    -- eating
    procedure Eat (Number: Integer) is
        Duration_Of_Delay : Integer := Random_Time;
        Delay_Time : Time_Span := Milliseconds(Duration_Of_Delay);
    begin
        Print_Mutex.Lock;
        Put_Line("The " & Integer'Image(Number) & " philosopher is eating");
        Print_Mutex.Unlock;
        delay until Clock + Delay_Time;
    end Eat;

    -- 
    procedure Test_All is 
    begin
        for I in 1 .. Number_Of_Philosophers loop
            Test(I);
        end loop;
    end Test_All;

    -- the guy themselves
    task type Philosopher (Number: Integer);
    task body Philosopher is
    begin
        loop
            Think(Number);
            Take_Forks(Number);
            Eat(Number);
            Give_Forks(Number);
            
            --Meal_Mutex.Lock;
            Meal_Eaten(Number) := Meal_Eaten(Number) + 1;
            if Meal_Eaten(Number) = Number_Of_Meals
            then
                Print_Mutex.Lock;
                Put_Line("Finished eating!" & Integer'Image(Number));
                Print_Mutex.Unlock;
                Test_All;
            --    Meal_Mutex.Unlock;
                exit;
            end if;
            --Meal_Mutex.Unlock;
        end loop;
    end Philosopher;

    procedure Main is
        Phi1 : Philosopher(1);
        Phi2 : Philosopher(2);
        Phi3 : Philosopher(3);
        Phi4 : Philosopher(4);
        Phi5 : Philosopher(5);
    begin
        for I in Forks'Range loop
            Forks(I) := new Binary_Semaphore(True);
        end loop;

        null;
    end Main;

end Philosophers;

