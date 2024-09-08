import matplotlib.pyplot as plt

# Updated performance data
performance_data = {
    1: [
        (1000000, 0.002106),
        (10000000, 0.024735),
        (100000000, 0.214021)
    ],
    2: [
        (1000000, 0.001163),
        (10000000, 0.010998),
        (100000000, 0.106708)
    ],
    4: [
        (1000000, 0.001134),
        (10000000, 0.010459),
        (100000000, 0.072817)
    ],
    8: [
        (1000000, 0.000655),
        (10000000, 0.005973),
        (100000000, 0.058721)
    ]
}

# Extracting the unique vector sizes
vector_sizes = sorted({size for results in performance_data.values() for size, _ in results})

# Plot 1: Performance vs. Vector Size for each thread count
plt.figure(figsize=(10, 6))

for num_threads, results in performance_data.items():
    sizes, times = zip(*results)
    plt.plot(sizes, times, marker='o', label=f'{num_threads} threads')

plt.title('Performance of Pi Calculation with OpenMP')
plt.xlabel('Number of Steps')
plt.ylabel('Time Taken (seconds)')
plt.xscale('log')  # Use logarithmic scale for vector size
plt.yscale('log')  # Use logarithmic scale for time taken
plt.legend()
plt.grid(True, ls="--")
plt.savefig('performance_vs_steps.png')  # Save the plot as an image
plt.close()

# Plot 2: Thread-Wise Performance for each vector size
plt.figure(figsize=(10, 6))

for size in vector_sizes:
    thread_counts = []
    times = []
    for num_threads, results in performance_data.items():
        for vector_size, time_taken in results:
            if vector_size == size:
                thread_counts.append(num_threads)
                times.append(time_taken)
                break
    plt.plot(thread_counts, times, marker='o', label=f'Steps {size}')

plt.title('Thread-Wise Performance of Pi Calculation')
plt.xlabel('Number of Threads')
plt.ylabel('Time Taken (seconds)')
plt.yscale('log')  # Use logarithmic scale for time taken
plt.xticks(thread_counts)  # Ensure the thread counts are correctly labeled
plt.legend()
plt.grid(True, ls="--")
plt.savefig('thread_wise_performance.png')  # Save the plot as an image
plt.close()
