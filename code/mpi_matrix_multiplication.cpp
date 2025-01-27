#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <mpi.h>
#include <fstream> // For saving the timings

using namespace std;

// Function to multiply a block of matrices
void multiplyBlock(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int startRow, int endRow, int n) {
    for (int i = startRow; i < endRow; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Check for proper usage and retrieve matrix size
    if (argc != 2) {
        if (rank == 0) {
            cerr << "Usage: " << argv[0] << " <matrix_size>\n";
        }
        MPI_Finalize();
        return 1;
    }

    int n = atoi(argv[1]); // Get matrix size from command line
    if (n % size != 0) {
        if (rank == 0) {
            cerr << "Matrix size must be divisible by the number of processes.\n";
        }
        MPI_Finalize();
        return 1;
    }

    vector<vector<int>> A(n, vector<int>(n));
    vector<vector<int>> B(n, vector<int>(n));
    vector<vector<int>> C(n, vector<int>(n));

    // Initialize matrices
    if (rank == 0) {
        srand(time(NULL));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A[i][j] = rand() % 100;
                B[i][j] = rand() % 100;
            }
        }
    }

    // Broadcast matrices
    for (int i = 0; i < n; i++) {
        MPI_Bcast(A[i].data(), n, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(B[i].data(), n, MPI_INT, 0, MPI_COMM_WORLD);
    }

    int rowsPerProcess = n / size;
    int startRow = rank * rowsPerProcess;
    int endRow = (rank == size - 1) ? n : (rank + 1) * rowsPerProcess;

    double start_time = MPI_Wtime();
    multiplyBlock(A, B, C, startRow, endRow, n);
    double end_time = MPI_Wtime();

    double total_time = end_time - start_time;
    double max_time;
    MPI_Reduce(&total_time, &max_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        cout << "Total time taken (MPI Matrix Multiplication): " << max_time << " seconds." << endl;

        // Save execution time and matrix size in a file
        ofstream outfile("execution_times.txt", ios_base::app); // Append mode
        outfile << "MPI Multiplication: " << max_time << " seconds, Matrix size: " << n << "\n";
        outfile.close();
    }

    MPI_Finalize();
    return 0;
}
