import subprocess
import numpy
import os
import sys

def get_python_config(flag):
    """Retrieve configuration information from python3-config."""
    output = subprocess.check_output(f"python3-config {flag}", shell=True).decode().strip()
    return output.split()

# Get Python include directories and linker flags
python_includes = get_python_config("--includes")
python_ldflags = get_python_config("--ldflags")

# Get the NumPy include directory
numpy_include = numpy.get_include()

# Determine the source file name, defaulting to "basic.c"
source_file = "basic.c"
if len(sys.argv) > 1:
    source_file = sys.argv[1]

# Construct the output library name based on the source file name
output_lib = os.path.splitext(source_file)[0] + ".so"

# Assemble the build command
build_command = [
    "nvc", "-fPIC", "-shared", "-fopenmp", "-mp=gpu"
] + python_includes + [
    "-I" + numpy_include, source_file, "-o", output_lib
] + python_ldflags

# Print the build command for verification
print("Executing build command:")
print(" ".join(build_command))

# Execute the build command
result = subprocess.run(build_command)

# Check the result of the build process
if result.returncode == 0:
    print(f"Successfully built {output_lib}")
else:
    print("Build failed")
