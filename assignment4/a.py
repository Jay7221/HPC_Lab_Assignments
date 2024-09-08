import matplotlib.pyplot as plt
import numpy as np

# Data
fib_numbers = [10, 15, 20, 25, 30, 35]
threads = [1, 2, 4, 8]

# Execution times for different Fibonacci numbers and thread counts
times = {
    10: [0.000043, 0.000164, 0.000088, 0.000133],
    15: [0.000401, 0.000232, 0.000238, 0.000310],
    20: [0.004367, 0.002339, 0.002511, 0.003487],
    25: [0.041569, 0.025289, 0.036082, 0.036796],
    30: [0.430148, 0.275798, 0.296802, 0.289904],
    35: [4.744162, 3.134171, 3.117129, 3.079085]
}

# Convert times to numpy arrays for easier manipulation
times_np = {n: np.array(times[n]) for n in fib_numbers}

# Plot 1: Execution Time vs. Number of Threads for different Fibonacci numbers
plt.figure(figsize=(12, 6))

for n in fib_numbers:
    plt.plot(threads, times_np[n], marker='o', label=f'Fibonacci({n})')

plt.xlabel('Number of Threads')
plt.ylabel('Time Taken (seconds)')
plt.title('Execution Time vs. Number of Threads for Fibonacci Computation')
plt.legend(title='Fibonacci Number')
plt.grid(True, linestyle='--', alpha=0.7)
plt.savefig('execution_time_vs_threads.png')
plt.close()

# Compute Speedup
speedups = {}
for n in fib_numbers:
    time_single_thread = times_np[n][0]
    speedups[n] = [time_single_thread / t for t in times_np[n]]

# Plot 2: Speedup vs. Number of Threads for different Fibonacci numbers
plt.figure(figsize=(12, 6))

for n in fib_numbers:
    plt.plot(threads, speedups[n], marker='o', label=f'Fibonacci({n})')

plt.xlabel('Number of Threads')
plt.ylabel('Speedup')
plt.title('Speedup vs. Number of Threads for Fibonacci Computation')
plt.legend(title='Fibonacci Number')
plt.grid(True, linestyle='--', alpha=0.7)
plt.savefig('speedup_vs_threads.png')
plt.close()

