using Base.Threads
using Random

const Number_Of_Philosophers = 5
const Number_Of_Meals = 3

const Min_Time = 400
const Max_Time = 1000

@enum State begin
    THINKING
    HUNGRY
    EATING
end
status = fill(THINKING, Number_Of_Philosophers)

#meal_eaten = fill(0, Number_Of_Philosophers)

print_mu = ReentrantLock()
forks_mu = ReentrantLock()

# Atomivc objects prevents race condition https://docs.julialang.org/en/v1/base/multi-threading/#Base.Threads.Atomic
forks = [Base.Threads.Atomic{Bool}(true) for _ in 1:Number_Of_Philosophers]

function random_time()
    return rand(Min_Time:Max_Time)/1000
end

function think(n)
    lock(print_mu)
    println("The $n philosopher is thinking")
    unlock(print_mu)
    time = random_time()
    sleep(time)
end

function test(n)
    left = (n - 1 + Number_Of_Philosophers) % Number_Of_Philosophers + 1
    right = (n % Number_Of_Philosophers) + 1
    if status[n] == HUNGRY && status[left] != EATING && status[right] != EATING
        status[n] = EATING
        #fork semaphore
        forks[n][] = false
    end
end

function take_forks(n)
    lock(forks_mu)
    status[n] = HUNGRY
    lock(print_mu)
    println("The $n philosopher is hungry")
    unlock(print_mu)
    test(n)
    unlock(forks_mu)
    #semaphore
    while forks[n][]
        Base.Threads.yield()
    end
end

function eat(n)
    lock(print_mu)
    println("The $n philosopher is eating")
    unlock(print_mu)
    time = random_time()
    sleep(time)
end

function put_forks(n)
    left = (n - 1 + Number_Of_Philosophers) % Number_Of_Philosophers + 1
    right = (n % Number_Of_Philosophers) + 1
    lock(forks_mu)
    status[n] = THINKING
    test(left)
    test(right)
    unlock(forks_mu)
end

function test_all()
    for i in 1:Number_Of_Philosophers
        test(i)
    end
end

function philosopher(n)
    meals_eaten = 0
    while true
        think(n)
        take_forks(n)
        eat(n)
        put_forks(n)

        meals_eaten += 1
        if meals_eaten == Number_Of_Meals
            lock(print_mu)
            println("Finished eating! $n")
            unlock(print_mu)
            test_all()
            return
        end
    end
end

philosophers = [Threads.@spawn philosopher(i) for i in 1:Number_Of_Philosophers]

for phil in philosophers
    fetch(phil)
end










