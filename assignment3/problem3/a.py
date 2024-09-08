import matplotlib.pyplot as plt

# Data for STATIC scheduling
chunk_sizes = [1, 10, 20, 50, 100]
times = [0.000244, 0.000054, 0.000061, 0.000056, 0.000044]

# Plotting the data
plt.figure(figsize=(10, 6))
plt.plot(chunk_sizes, times, marker='o', linestyle='-', color='b', label='STATIC Schedule')

plt.title('Performance of STATIC Scheduling with Different Chunk Sizes')
plt.xlabel('Chunk Size')
plt.ylabel('Time Taken (seconds)')
plt.yscale('log')  # Use logarithmic scale for time taken
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend()

# Save the plot as an image file
plt.savefig('static_schedule_performance.png')

# Show the plot
plt.show()
