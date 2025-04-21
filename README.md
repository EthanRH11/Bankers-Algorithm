# Banker's Algorithm Implementation

This program implements the Banker's Algorithm for deadlock avoidance in resource allocation systems.

## Description

The Banker's Algorithm is a deadlock avoidance algorithm that tests for safety by simulating the allocation of predetermined maximum possible amounts of all resources, and then checks if resource requests can be satisfied safely or not.

This implementation:
- Reads system state from an input file
- Determines if the system is in a safe state
- Finds a safe sequence if one exists

## Input File Format

The input file (`banker_input.txt`) should be formatted as follows:

```
[num_processes] [num_resources]
[available_resources]
[allocation_matrix]
[max_need_matrix]
```

For example:
```
5 3
3 3 2
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
```

Where:
- First line: 5 processes, 3 resource types
- Second line: Available resources (3 of type A, 3 of type B, 2 of type C)
- Next 5 lines: Allocation matrix (what each process currently has)
- Last 5 lines: Max need matrix (maximum resources each process may need)

## Compilation

To compile the program:

```
g++ main.cpp -o bankers_algorithm
```

## Usage

1. Create the input file `banker_input.txt` with the system state
2. Run the compiled program:

```
./bankers_algorithm
```

3. The program will output:
   - The current system state
   - Whether the system is in a safe state
   - If safe, the safe sequence of processes

## Example

For the example system with 5 processes and 3 resource types (A, B, C) where:
- Resource type A has 10 instances
- Resource type B has 5 instances
- Resource type C has 7 instances

The program will determine if the system is in a safe state and find a safe sequence if one exists.
