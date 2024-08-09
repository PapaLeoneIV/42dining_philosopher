# Philosophers

In this project, you will learn the basics of threading a process. You will see how to create threads and you will discover mutexes.

## Table of Contents

1. [About](#about)
2. [Installation](#installation)
3. [Usage](#usage)

## About

Philosophers is a simulation of philosophers sitting at a round table, alternately thinking, eating, or sleeping. This simulation is a classic problem in concurrent programming and synchronization.

## Installation

1. Clone the repository:
```bash
git clone https://github.com/lpincoli/Philosophers42.git
```

2. Move to the project's directory:
```bash
cd Philosophers42
```
3. Compile the project:
```bash
make
```
## Usage

The program takes 4 or 5 arguments:
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
Where:
- **number_of_philosophers**: The number of philosophers and also the number of forks.
- **time_to_die** (in milliseconds): If a philosopher doesn’t start eating 'time_to_die' milliseconds after starting their last meal or the simulation, they die.
- **time_to_eat** (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
- **time_to_sleep** (in milliseconds): The time a philosopher will spend sleeping.
- **number_of_times_each_philosopher_must_eat** (optional): If all philosophers eat at least 'number_of_times_each_philosopher_must_eat' times, the simulation stops. If not specified, the simulation stops when a philosopher dies.
