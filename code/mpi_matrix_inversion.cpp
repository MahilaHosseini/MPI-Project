#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <mpi.h>
#include <fstream> // برای ذخیره زمان‌ها

void gaussJordanInversion(std::vector<std::vector<double>>& matrix, int rank, int size, bool& is_singular) {
    int N = matrix.size();

    for (int i = 0; i < N; ++i) {
        // Broadcast the pivot row
        if (i % size == rank) {
            if (matrix[i % size][i] == 0.0) {
                is_singular = true; // Mark as singular if pivot is zero
            } else {
                for (int j = 0; j < N; ++j) {
                    matrix[i % size][j] /= matrix[i % size][i];
                }
            }
        }

        // Broadcast pivot row and singularity status
        MPI_Bcast(matrix[i % size].data(), N, MPI_DOUBLE, i % size, MPI_COMM_WORLD);
        MPI_Bcast(&is_singular, 1, MPI_C_BOOL, i % size, MPI_COMM_WORLD);

        if (is_singular) return; // Stop further computation if matrix is singular

        // Update rows
        for (int k = 0; k < N / size; ++k) {
            if (k != i && i % size != rank) {
                double factor = matrix[k][i];
                for (int j = 0; j < N; ++j) {
                    matrix[k][j] -= factor * matrix[i % size][j];
                }
            }
        }
    }
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Parse input
    if (argc != 2) {
        if (rank == 0) std::cerr << "Usage: " << argv[0] << " <matrix_size>\n";
        MPI_Finalize();
        return 1;
    }

    int N = std::atoi(argv[1]);
    if (N % size != 0) {
        if (rank == 0) std::cerr << "Matrix size must be divisible by the number of processes.\n";
        MPI_Finalize();
        return 1;
    }

    std::vector<double> local_matrix(N * N / size);
    std::vector<double> full_matrix;

    if (rank == 0) {
        full_matrix.resize(N * N);
        srand(time(NULL));
        for (int i = 0; i < N * N; ++i) full_matrix[i] = static_cast<double>(rand() % 100 + 1); // Avoid zeros
    }

    MPI_Scatter(full_matrix.data(), N * N / size, MPI_DOUBLE, local_matrix.data(), N * N / size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    std::vector<std::vector<double>> local_matrix_2d(N / size, std::vector<double>(N));
    for (int i = 0; i < N / size; ++i) {
        for (int j = 0; j < N; ++j) {
            local_matrix_2d[i][j] = local_matrix[i * N + j];
        }
    }

    bool is_singular = false;

    // Measure time for inversion
    double start_time = MPI_Wtime();
    gaussJordanInversion(local_matrix_2d, rank, size, is_singular);
    double end_time = MPI_Wtime();

    double total_time = end_time - start_time;

    double max_time;
    MPI_Reduce(&total_time, &max_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        if (is_singular) {
            std::cerr << "The matrix is singular and cannot be inverted.\n";
        } else {
            std::cout << "Matrix inversion completed successfully.\n";
            std::cout << "Total time taken: " << max_time << " seconds.\n";

            // ذخیره زمان اجرا در فایل
            std::ofstream outfile("execution_times.txt", std::ios_base::app); // append mode
            outfile << "MPI Matrix Inversion: " << max_time << " seconds\n";
            outfile.close();
        }
    }

    MPI_Finalize();
    return 0;
}
