import matplotlib.pyplot as plt

# Formatted data for plotting
performance_data = {
    1: [
        (1000, 0.000004),
        (10000, 0.000018),
        (100000, 0.000174),
        (1000000, 0.001751),
        (10000000, 0.017785)
    ],
    2: [
        (1000, 0.000106),
        (10000, 0.000012),
        (100000, 0.000087),
        (1000000, 0.000870),
        (10000000, 0.014493)
    ],
    4: [
        (1000, 0.000152),
        (10000, 0.000007),
        (100000, 0.000047),
        (1000000, 0.008368),
        (10000000, 0.016322)
    ],
    8: [
        (1000, 0.000114),
        (10000, 0.000005),
        (100000, 0.000034),
        (1000000, 0.007984),
        (10000000, 0.049220)
    ]
}

# Extracting the unique vector sizes
vector_sizes = sorted({size for results in performance_data.values() for size, _ in results})

# Plot 1: Performance vs. Vector Size for each thread count
plt.figure(figsize=(10, 6))

for num_threads, results in performance_data.items():
    sizes = [size for size, _ in results]
    times = [time for _, time in results]
    plt.plot(sizes, times, marker='o', label=f'{num_threads} threads')

plt.title('Performance of Vector Scalar Addition with OpenMP')
plt.xlabel('Vector Size')
plt.ylabel('Time Taken (seconds)')
plt.xscale('log')  # Use logarithmic scale for vector size
plt.yscale('log')  # Use logarithmic scale for time taken
plt.legend()
plt.grid(True, ls="--")
plt.savefig('performance_vs_vector_size.png')  # Save the plot as an image
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
    plt.plot(thread_counts, times, marker='o', label=f'Vector Size {size}')

plt.title('Thread-Wise Performance of Vector Scalar Addition with OpenMP')
plt.xlabel('Number of Threads')
plt.ylabel('Time Taken (seconds)')
plt.yscale('log')  # Use logarithmic scale for time taken
plt.xticks(sorted(performance_data.keys()))  # Ensure the thread counts are correctly labeled
plt.legend()
plt.grid(True, ls="--")
plt.savefig('thread_wise_performance.png')  # Save the plot as an image
plt.close()
