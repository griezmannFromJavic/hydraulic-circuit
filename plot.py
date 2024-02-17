import numpy as np
import matplotlib.pyplot as plt

# Read the CSV file into a NumPy array
data = np.genfromtxt('lagrange-data.csv', delimiter=',')

# Display the array
plt.plot(data[0], data[1])
plt.show()

