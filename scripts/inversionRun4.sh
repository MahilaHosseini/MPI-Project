#!/bin/bash


# Path to the MPI binary
BINARY="./mpi_matrix_inversion"

# Hostfile
HOSTFILE="hostfile2"

# Output file for all results
OUTPUT_FILE="./results/mpi_inversion_results_summary4.txt"
mkdir -p ./results

# Create or overwrite the summary file
echo "MPI Results Summary" > $OUTPUT_FILE
echo "-------------------" >> $OUTPUT_FILE

echo "Running with np=2..."
    
    # Append information to the output file
echo "Running with np=2:" >> $OUTPUT_FILE
    
    # Run the MPI program and append its output to the file
mpirun -np 2 -hostfile $HOSTFILE $BINARY 1024 >> $OUTPUT_FILE
    
    # Add a separator between runs
echo "-------------------" >> $OUTPUT_FILE

echo "Running with np=4..."
    
    # Append information to the output file
echo "Running with np=4:" >> $OUTPUT_FILE
    
    # Run the MPI program and append its output to the file
mpirun -np 4 -hostfile $HOSTFILE $BINARY 2048 >> $OUTPUT_FILE
    
    # Add a separator between runs
echo "-------------------" >> $OUTPUT_FILE

echo "Running with np=8..."
    
    # Append information to the output file
echo "Running with np=8:" >> $OUTPUT_FILE
    
    # Run the MPI program and append its output to the file
mpirun -np 8 -hostfile $HOSTFILE $BINARY 4096 >> $OUTPUT_FILE
    
    # Add a separator between runs
echo "-------------------" >> $OUTPUT_FILE

echo "Running with np=16..."
    
    # Append information to the output file
echo "Running with np=16:" >> $OUTPUT_FILE
    
    # Run the MPI program and append its output to the file
mpirun -np 16 -hostfile $HOSTFILE $BINARY 8192 >> $OUTPUT_FILE
    
    # Add a separator between runs
echo "-------------------" >> $OUTPUT_FILE

echo "All results appended to $OUTPUT_FILE"



