#!/bin/bash

# List of VM internal IPs
VMS=("10.198.0.9" "10.198.0.5" "10.198.0.6" "10.198.0.7" "10.198.0.8" "10.164.0.2" "10.128.0.4")

# Path to the compiled binary
BINARY_i="./mpi_matrix_inversion"
BINARY_m="./mpi_matrix_multiplication"

# Loop through each VM and copy the binary
for vm in "${VMS[@]}"; do
    echo "Copying $BINARY_i $BINARY_m to $vm..."
    scp $BINARY_i $BINARY_m mahila_hosseini01@$vm:~/
done

echo "Distribution complete!"

