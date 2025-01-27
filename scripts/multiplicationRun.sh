#!/bin/bash

# List of np values to test
NP_VALUES=(2 4 8 16)

# Path to the MPI binary
BINARY="./mpi_matrix_multiplication"

# Hostfile
HOSTFILE="hostfile"

# Output file for all results
OUTPUT_FILE="./results/mpi_multi_results_summary.txt"
mkdir -p ./results

# Create or overwrite the summary file
echo "MPI Results Summary" > $OUTPUT_FILE
echo "-------------------" >> $OUTPUT_FILE

# Loop through each np value
for np in "${NP_VALUES[@]}"; do
    echo "Running with np=$np..."
    
    # Append information to the output file
    echo "Running with np=$np:" >> $OUTPUT_FILE
    
    # Run the MPI program and append its output to the file
    mpirun -np $np -hostfile $HOSTFILE $BINARY 1024 >> $OUTPUT_FILE
    
    # Add a separator between runs
    echo "-------------------" >> $OUTPUT_FILE
done

echo "All results appended to $OUTPUT_FILE"

