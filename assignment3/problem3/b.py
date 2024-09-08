import matplotlib.pyplot as plt

# Data for DYNAMIC scheduling
chunk_sizes = [1, 10, 20, 50, 100]
times_taken = [0.001975, 0.000216, 0.000124, 0.000075, 0.000057]

# Plotting the results
plt.figure(figsize=(10, 6))

plt.plot(chunk_sizes, times_taken, marker='o', linestyle='-', color='b')
plt.title('Performance of DYNAMIC Scheduling with Different Chunk Sizes')
plt.xlabel('Chunk Size')
plt.ylabel('Time Taken (seconds)')
plt.yscale('log')  # Logarithmic scale for time taken
plt.grid(True, linestyle='--', alpha=0.7)
plt.xticks(chunk_sizes)
plt.savefig('dynamic_schedule_performance.png')  # Save the plot as an image
plt.show()

