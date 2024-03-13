import numpy as np
import sys

# If necessary, add the directory containing basic.so to the path
# sys.path.append('/path/to/directory/containing/basic.so')

import basic  # Import your compiled module

# Create a NumPy array to scale
arr = np.random.rand(100).astype(np.double)  # Ensure it's a double array

# Use the scale_array function
scaled_arr = basic.scale_array(arr, 2.0)  # Example: scale the array by a factor of 2

print("Original array:", arr)
print("Scaled array:", scaled_arr)
