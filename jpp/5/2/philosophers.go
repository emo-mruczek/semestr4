package main

import (
    "fmt"
    "sync"
    "math/rand"
    "time"
)

const Number_Of_Philosophers = 5
const Number_Of_Meals = 3

const Min_Time = 400
const Max_Time = 1000

type State int
const (
    THINKING State = iota
    HUNGRY
    EATING
)
var Status [Number_Of_Philosophers]State

// By default an array is zero-valued, which for ints means 0s. ~https://gobyexample.com/arrays
var meal_eaten [Number_Of_Philosophers]int

var print_mu sync.Mutex
var forks_mu sync.Mutex
//var meal_mu sync.Mutex

// semaphore https://www.codingexplorations.com/blog/understanding-and-implementing-the-semaphore-pattern-in-go
var fork_semaphores [Number_Of_Philosophers]chan struct{}

func random_time() int {
    rand.Seed(time.Now().UnixNano())
    return rand.Intn(Max_Time - Min_Time) + Min_Time
}

func think(n int) {
    print_mu.Lock()
    fmt.Printf("The %d philosopher is thinking\n", n)
    print_mu.Unlock()
    time.Sleep(time.Duration(random_time()) * time.Millisecond)
}

func test(n int) {
    var left int = (n - 1 + Number_Of_Philosophers) % Number_Of_Philosophers
    var right int = (n + 1) % Number_Of_Philosophers
    if Status[n] == HUNGRY && Status[left] != EATING && Status[right] != EATING {
        Status[n] = EATING
        fork_semaphores[n] <- struct{}{}
    }
}

func take_forks(n int) {
    forks_mu.Lock()
    Status[n] = HUNGRY
    print_mu.Lock()
    fmt.Printf("The %d philosopher is hungry\n", n)
    print_mu.Unlock()
    test(n)
    forks_mu.Unlock()
    <-fork_semaphores[n]
}

func eat(n int) {
    print_mu.Lock()
    fmt.Printf("The %d philosopher is eating\n", n)
    print_mu.Unlock()
    time.Sleep(time.Duration(random_time()) * time.Millisecond)
}

func put_forks(n int) {
    var left int = (n - 1 + Number_Of_Philosophers) % Number_Of_Philosophers
    var right int = (n + 1) % Number_Of_Philosophers
    forks_mu.Lock()
    Status[n] = THINKING
    test(left)
    test(right)
    forks_mu.Unlock()
}

func test_all() {
    for i := 0; i < Number_Of_Philosophers; i++ {
        test(i)
    }
}

func philosopher(n int, wg *sync.WaitGroup) {
    defer wg.Done()
    for {
        think(n)
        take_forks(n)
        eat(n)
        put_forks(n)

      //  meal_mu.Lock()
        meal_eaten[n] = meal_eaten[n] + 1
        if meal_eaten[n] == Number_Of_Meals {
            print_mu.Lock()
            fmt.Printf("Finished eating! %d\n", n)
            print_mu.Unlock()
            test_all()
         //   meal_mu.Unlock()
            return
        }
       // meal_mu.Unlock()
    }
}

func main() {
    // wait goup
    var wg sync.WaitGroup
    wg.Add(Number_Of_Philosophers)
    for i:= 0; i < Number_Of_Philosophers; i++ {
       fork_semaphores[i] = make(chan struct{}, 1)
    }
    fmt.Println("Starting...")
    // goroutines
    for i := 0; i < Number_Of_Philosophers; i++ {
        go philosopher(i, &wg)
    }

    wg.Wait()
}
