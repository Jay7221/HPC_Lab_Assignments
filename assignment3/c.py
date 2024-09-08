import matplotlib.pyplot as plt

# Updated performance data
performance_data = {
    1: [
        (1000000, 0.002073),
        (10000000, 0.020981),
        (100000000, 0.214750)
    ],
    2: [
        (1000000, 0.001294),
        (10000000, 0.011739),
        (100000000, 0.115240)
    ],
    4: [
        (1000000, 0.000960),
        (10000000, 0.008309),
        (100000000, 0.077307)
    ],
    8: [
        (1000000, 0.002018),
        (10000000, 0.009722),
        (100000000, 0.084853)
    ],
    16: [
        (1000000, 0.001464),
        (10000000, 0.009892),
        (100000000, 0.086645)
    ]
}

# Extracting the unique array sizes
array_sizes = sorted({size for results in performance_data.values() for size, _ in results})

# Plot 1: Performance vs. Array Size for each thread count
plt.figure(figsize=(10, 6))

for num_threads, results in performance_data.items():
    sizes = [size for size, _ in results]
    times = [time for _, time in results]
    plt.plot(sizes, times, marker='o', label=f'{num_threads} threads')

plt.title('Performance of Vector Scalar Addition with Different Thread Counts')
plt.xlabel('Array Size')
plt.ylabel('Time Taken (seconds)')
plt.xscale('log')  # Use logarithmic scale for array size
plt.yscale('log')  # Use logarithmic scale for time taken
plt.legend(title='Number of Threads')
plt.grid(True, linestyle='--', alpha=0.7)
plt.savefig('performance_vs_array_size.png')  # Save the plot as an image
plt.close()

# Plot 2: Thread-Wise Performance for each array size
plt.figure(figsize=(10, 6))

for size in array_sizes:
    thread_counts = []
    times = []
    for num_threads, results in performance_data.items():
        for array_size, time_taken in results:
            if array_size == size:
                thread_counts.append(num_threads)
                times.append(time_taken)
                break
    plt.plot(thread_counts, times, marker='o', label=f'Array Size {size}')

plt.title('Thread-Wise Performance of Vector Scalar Addition')
plt.xlabel('Number of Threads')
plt.ylabel('Time Taken (seconds)')
plt.yscale('log')  # Use logarithmic scale for time taken
plt.xticks(sorted(performance_data.keys()))  # Ensure the thread counts are correctly labeled
plt.legend(title='Array Size')
plt.grid(True, linestyle='--', alpha=0.7)
plt.savefig('thread_wise_performance.png')  # Save the plot as an image
plt.close()
