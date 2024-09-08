import matplotlib.pyplot as plt
import numpy as np

# Updated data including execution times (parallel and sequential)
fib_numbers = [10, 15, 20, 25, 30, 35, 40, 45]
threads = [1, 2, 4, 8]

# Times including sequential execution time (as the first element in each list)
times = {
    10: [0.000001, 0.000001, 0.000001, 0.000001, 0.000001],  # Last value is sequential time
    15: [0.000009, 0.000006, 0.000005, 0.000006, 0.000004],
    20: [0.000046, 0.000046, 0.000048, 0.000048, 0.000044],
    25: [0.000485, 0.000421, 0.000423, 0.000492, 0.000462],
    30: [0.006583, 0.003669, 0.003855, 0.004221, 0.005947],
    35: [0.062769, 0.038736, 0.050651, 0.050598, 0.055054],
    40: [0.693290, 0.430440, 0.444401, 0.444354, 0.606598],
    45: [8.071788, 4.878401, 4.755520, 4.787391, 6.739155]
}

# Convert times to numpy arrays for easier manipulation
times_np = {n: np.array(times[n]) for n in fib_numbers}

# Plot 1: Execution Time vs. Number of Threads for different Fibonacci numbers including sequential
plt.figure(figsize=(12, 6))

for n in fib_numbers:
    plt.plot(threads + ['Sequential'], times_np[n], marker='o', label=f'Fibonacci({n})')

plt.xlabel('Number of Threads')
plt.ylabel('Time Taken (seconds)')
plt.title('Execution Time vs. Number of Threads for Fibonacci Computation (Including Sequential)')
plt.legend(title='Fibonacci Number')
plt.grid(True, linestyle='--', alpha=0.7)
plt.savefig('execution_time_vs_threads_and_sequential.png')
plt.close()

# Compute Speedup relative to the sequential time
speedups = {}
for n in fib_numbers:
    time_sequential = times_np[n][-1]
    speedups[n] = [time_sequential / t for t in times_np[n][:-1]]  # Exclude the sequential time itself

# Plot 2: Speedup vs. Number of Threads for different Fibonacci numbers
plt.figure(figsize=(12, 6))

for n in fib_numbers:
    plt.plot(threads, speedups[n], marker='o', label=f'Fibonacci({n})')

plt.xlabel('Number of Threads')
plt.ylabel('Speedup')
plt.title('Speedup vs. Number of Threads for Fibonacci Computation (Relative to Sequential)')
plt.legend(title='Fibonacci Number')
plt.grid(True, linestyle='--', alpha=0.7)
plt.savefig('speedup_vs_threads_relative_to_sequential.png')
plt.close()

