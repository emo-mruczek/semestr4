package main

import (
    "fmt"
    "sync"
    "math/rand"
    "time"
)

const Number_Of_Philosophers = 5
const Number_Of_Meals = 5

const Min_Time = 400
const Max_Time = 1000

// By default an array is zero-valued, which for ints means 0s. ~https://gobyexample.com/arrays
var meal_eaten [Number_Of_Meals]int

var print_mu sync.Mutex
var meal_mu sync.Mutex

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

func philosopher(n int, wg *sync.WaitGroup) {
    defer wg.Done()
    for {
        think(n)

        meal_mu.Lock()
        meal_eaten[n] = meal_eaten[n] + 1
        if meal_eaten[n] == Number_Of_Meals {
            print_mu.Lock()
            fmt.Printf("Finished eating! %d\n", n)
            print_mu.Unlock()
            meal_mu.Unlock()
            return
        }
        meal_mu.Unlock()
    }
}

func main() {
    // wait goup
    var wg sync.WaitGroup
    wg.Add(Number_Of_Philosophers)
    fmt.Println("Starting...")
    // goroutines
    for i := 0; i < Number_Of_Philosophers; i++ {
        go philosopher(i, &wg)
    }

    wg.Wait()
}
