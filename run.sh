if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <executable_name>"
    exit 1
fi

# Assign the first argument to a variable
EXECUTABLE=$1

# Build the project
make clean && make

# Run the provided executable
./"$EXECUTABLE"