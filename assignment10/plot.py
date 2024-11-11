import matplotlib.pyplot as plt

# Data extracted from your output
processes = [1, 2, 4, 8, 10, 16, 20, 25, 30]
broadcast_times = [0.000001, 0.000005, 0.000007, 0.000157, 0.000179, 0.000409, 0.000581, 0.000667, 0.002520]

# Create a plot
plt.figure(figsize=(10, 6))
plt.plot(processes, broadcast_times, marker='o')

# Set the scale for the y-axis to logarithmic for better visibility
plt.yscale('log')

# Add title and labels
plt.title('MPI Broadcast Time vs Number of Processes')
plt.xlabel('Number of Processes')
plt.ylabel('Broadcast Time (seconds) (log scale)')
plt.grid()

# Show the plot
plt.xticks(processes)  # Set x ticks to be the number of processes

# Save the plot as a PNG file
plt.savefig('plot.png', dpi=300, bbox_inches='tight')  # Save the figure with specified resolution and tight bounding box

# Optionally, you can also show the plot if you want to see it
plt.show()
