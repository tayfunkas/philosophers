# philosophers

**Philosophers** is a simulation of the classic Dining Philosophers problem, developed as part of the 42 programming school curriculum. This project demonstrates multithreading and synchronization by managing multiple philosophers who alternately think and eat while sharing resources (forks) and avoiding deadlocks.

## Key Learnings

- **Synchronization mechanisms:** Using mutexes and condition variables.
- **Concurrency issues:** Understanding and solving concurrency problems.
- **Resource management:** Efficient management of shared resources.
- **Deadlock prevention:** Techniques for avoiding deadlock and starvation.
- **Algorithmic problem-solving:** Optimization and implementation of algorithms.

## Learning Objectives

- **Basics of multithreading:** Process synchronization in C.
- **Pthreads library:** Working with the `pthreads` (POSIX threads) library.
- **Resource management:** Efficient communication between threads.
- **Deadlock prevention:** Techniques for ensuring thread safety.
- **Dining Philosophers problem:** Implementing the classic synchronization problem.

## Usage

1. **Compile the project** with the `make` command:
   
   `make`

2. **Run the simulation** with the following command:
   
   `./philosophers <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]`
   - `<number_of_philosophers>`: Number of philosophers (threads) to simulate.
   - `<time_to_die>`: Time in milliseconds until a philosopher dies from starvation.
   - `<time_to_eat>`: Time in milliseconds that a philosopher spends eating.
   - `<time_to_sleep>`: Time in milliseconds that a philosopher spends sleeping.
   - `[number_of_times_each_philosopher_must_eat]` (optional): Number of times each philosopher must eat before the simulation ends.

3. **Observe the simulation** in the terminal. Philosophers will alternate between thinking and eating, and the program will handle synchronization to avoid conflicts.

4. **Terminate the simulation** by pressing `Ctrl+C` or letting the program run until completion.

## Example

To start a simulation with 5 philosophers, where each philosopher will die if they do not eat within 800 milliseconds, spend 200 milliseconds eating, and 200 milliseconds sleeping, run:

`./philosophers 5 800 200 200`

## Notes

- Ensure that the `pthread` library is available on your system as it is required for running the simulation.
- Adjust the parameters according to the desired simulation scenario and performance.
