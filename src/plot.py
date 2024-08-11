import numpy as np
import matplotlib.pyplot as plt

# Read the CSV file into a NumPy array
data = np.genfromtxt('lagrange-data.csv', delimiter=',')

# Use the first row as the x-coordinates
x = data[0]

# Plot each subsequent row as y-coordinates
for i in range(1, data.shape[0]):
    plt.plot(x, data[i], label=f'{i}')

# Add labels and legend
plt.xlabel('flow')
plt.ylabel('pressure drop')
plt.title('Pressure characteristics')
plt.legend()

# Display the plot
plt.show()

