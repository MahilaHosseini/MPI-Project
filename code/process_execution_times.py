import os

def process_execution_times(file_path="execution_times.txt", operation="both", n=1024, num_processors=4):
    """
    Processes execution times for specific operations (multiplication, inversion, or both).
    :param file_path: Path to the execution times file.
    :param operation: Either 'multiplication', 'inversion', or 'both'.
    :param n: Size of the matrix.
    :param num_processors: Number of processors used in parallel computation.
    """
    if not os.path.exists(file_path):
        print(f"File {file_path} not found.")
        return

    # Initialize variables for times
    serial_multiplication = None
    parallel_multiplication = None
    serial_inversion = None
    parallel_inversion = None

    # Read the file and extract times for each operation
    with open(file_path, "r") as file:
        for line in file:
            if "Serial Multiplication" in line:
                serial_multiplication = float(line.strip().split(":")[-1].replace("seconds", "").strip())
            elif "MPI Multiplication" in line:
                parallel_multiplication = float(line.strip().split(":")[-1].replace("seconds", "").strip())
            elif "Serial Inversion" in line:
                serial_inversion = float(line.strip().split(":")[-1].replace("seconds", "").strip())
            elif "MPI Matrix Inversion" in line:
                parallel_inversion = float(line.strip().split(":")[-1].replace("seconds", "").strip())

    # Perform calculations based on the operation
    if operation in ["multiplication", "both"] and serial_multiplication and parallel_multiplication:
        print(f"\n--- Results for Multiplication ---")
        print(f"Matrix Size (n): {n}")
        print(f"Number of Processors: {num_processors}")
        print(f"Serial Time: {serial_multiplication:.6f} seconds")
        print(f"Parallel Time: {parallel_multiplication:.6f} seconds")
        P = 1 - (serial_multiplication / (serial_multiplication + parallel_multiplication))
        print(f"P (Parallelizable Fraction): {P:.6f}")
        speedup = 1 / ((1 - P) + (P / num_processors))
        print(f"Amdahl's Law Speedup: {speedup:.6f}")
        weak_efficiency = (serial_multiplication / parallel_multiplication) / num_processors
        strong_speedup = serial_multiplication / parallel_multiplication
        print(f"Weak Scalability Efficiency: {weak_efficiency:.6f}")
        print(f"Strong Scalability Speedup: {strong_speedup:.6f}")

    if operation in ["inversion", "both"] and serial_inversion and parallel_inversion:
        print(f"\n--- Results for Inversion ---")
        print(f"Matrix Size (n): {n}")
        print(f"Number of Processors: {num_processors}")
        print(f"Serial Time: {serial_inversion:.6f} seconds")
        print(f"Parallel Time: {parallel_inversion:.6f} seconds")
        P = 1 - (serial_inversion / (serial_inversion + parallel_inversion))
        print(f"P (Parallelizable Fraction): {P:.6f}")
        speedup = 1 / ((1 - P) + (P / num_processors))
        print(f"Amdahl's Law Speedup: {speedup:.6f}")
        weak_efficiency = (serial_inversion / parallel_inversion) / num_processors
        strong_speedup = serial_inversion / parallel_inversion
        print(f"Weak Scalability Efficiency: {weak_efficiency:.6f}")
        print(f"Strong Scalability Speedup: {strong_speedup:.6f}")

    # Optional: Clear the file after processing
    clear_file = input("\nDo you want to clear the execution_times.txt file? (yes/no): ").strip().lower()
    if clear_file == "yes":
        with open(file_path, "w") as file:
            file.write("")
        print("The file has been cleared.")

# Prompt user to choose operation
operation = input("Which operation do you want to process? (multiplication/inversion/both): ").strip().lower()
process_execution_times(operation=operation, n=1024, num_processors=4)
