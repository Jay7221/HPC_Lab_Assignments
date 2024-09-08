import matplotlib.pyplot as plt

# Updated performance data
performance_data = {
    1: [
        (250, 0.000127),
        (500, 0.000689),
        (750, 0.001535),
        (1000, 0.002767),
        (2000, 0.010158)
    ],
    2: [
        (250, 0.000226),
        (500, 0.000295),
        (750, 0.000621),
        (1000, 0.001188),
        (2000, 0.004689)
    ],
    4: [
        (250, 0.000140),
        (500, 0.000329),
        (750, 0.000341),
        (1000, 0.000681),
        (2000, 0.004025)
    ],
    8: [
        (250, 0.000107),
        (500, 0.000216),
        (750, 0.000376),
        (1000, 0.000697),
        (2000, 0.005250)
    ]
}

# Extracting the unique matrix sizes
matrix_sizes = sorted({size for results in performance_data.values() for size, _ in results})

# Plot 1: Performance vs. Matrix Size for each thread count
plt.figure(figsize=(10, 6))

for num_threads, results in performance_data.items():
    sizes = [size for size, _ in results]
    times = [time for _, time in results]
    plt.plot(sizes, times, marker='o', label=f'{num_threads} threads')

plt.title('Performance of 2D Matrix Addition with Different Thread Counts')
plt.xlabel('Matrix Size')
plt.ylabel('Time Taken (seconds)')
plt.xscale('log')  # Use logarithmic scale for matrix size
plt.yscale('log')  # Use logarithmic scale for time taken
plt.legend(title='Number of Threads')
plt.grid(True, linestyle='--', alpha=0.7)
plt.savefig('performance_vs_matrix_size.png')  # Save the plot as an image
plt.close()

# Plot 2: Thread-Wise Performance for each matrix size
plt.figure(figsize=(10, 6))

for size in matrix_sizes:
    thread_counts = []
    times = []
    for num_threads, results in performance_data.items():
        for matrix_size, time_taken in results:
            if matrix_size == size:
                thread_counts.append(num_threads)
                times.append(time_taken)
                break
    plt.plot(thread_counts, times, marker='o', label=f'Matrix Size {size}')

plt.title('Thread-Wise Performance of 2D Matrix Addition')
plt.xlabel('Number of Threads')
plt.ylabel('Time Taken (seconds)')
plt.yscale('log')  # Use logarithmic scale for time taken
plt.xticks(sorted(performance_data.keys()))  # Ensure the thread counts are correctly labeled
plt.legend(title='Matrix Size')
plt.grid(True, linestyle='--', alpha=0.7)
plt.savefig('thread_wise_performance.png')  # Save the plot as an image
plt.close()
