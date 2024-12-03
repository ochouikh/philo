# Philosophers
The basics of threading and mutexes in C, and a simple simulation of the dining philosophers problem.

## Table of contents
- [Introduction](#introduction)
- [Installation](#installation)
- [How to use](#how-to-use)

## Introduction
This project is a simple simulation of the dining philosophers problem. The problem is a classic example of a concurrency problem and illustrates the importance of proper synchronization when multiple threads are involved. The problem is stated as follows:
* One or more philosophers sit at a round table.
There is a large bowl of spaghetti in the middle of the table.
* The philosophers alternatively eat, think, or sleep.
While they are eating, they are not thinking nor sleeping; while thinking, they are not eating nor sleeping;
and, of course, while sleeping, they are not eating nor thinking.
* There are also forks on the table. There are as many forks as philosophers.
* Because serving and eating spaghetti with only one fork is very inconvenient, a
philosopher takes their right and their left forks to eat, one in each hand.
* When a philosopher has finished eating, they put their forks back on the table and start sleeping. Once awake, they start thinking again. The simulation stops when a philosopher dies of starvation.
* Every philosopher needs to eat and should never starve.
* Philosophers don’t speak with each other.
* Philosophers don’t know if another philosopher is about to die.
* No need to say that philosophers should avoid dying!

## How to use
1. Clone the repository
```bash
git clone git@github.com:ochouikh/philo.git
cd philosophers
```
For the mandatory part:
2. Change directory to the project
```bash
cd philo #for the mandatory part
cd philo_bonus #for the bonus part
```
3. Compile the project
```bash
make
```
4. Run the simulation
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers`: The number of philosophers sitting at the table. Must be greater than 1.
- `time_to_die`: The time in milliseconds after which a philosopher dies if they have not started eating.
- `time_to_eat`: The time in milliseconds it takes for a philosopher to eat.
- `time_to_sleep`: The time in milliseconds it takes for a philosopher to sleep.
- `number_of_times_each_philosopher_must_eat`: Optional. The number of times each philosopher must eat before the simulation stops. If not specified, the simulation stops only when a philosopher dies.