#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream> // For saving the timings

using namespace std;

// Function to multiply two matrices
vector<vector<int>> multiplyMatrices(const vector<vector<int>>& matrix1, const vector<vector<int>>& matrix2) {
    int n = matrix1.size();
    vector<vector<int>> result(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return result;
}

int main(int argc, char* argv[]) {
    // Parse command-line arguments
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <matrix_size>" << endl;
        return 1;
    }

    int n = atoi(argv[1]); // Get matrix size from command-line argument
    if (n <= 0) {
        cerr << "Matrix size must be a positive integer." << endl;
        return 1;
    }

    vector<vector<int>> matrix1(n, vector<int>(n));
    vector<vector<int>> matrix2(n, vector<int>(n));

    // Initialize matrices with random values
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix1[i][j] = rand() % 100;
            matrix2[i][j] = rand() % 100;
        }
    }

    // Measure time for matrix multiplication
    auto start = chrono::high_resolution_clock::now();
    vector<vector<int>> result = multiplyMatrices(matrix1, matrix2);
    auto end = chrono::high_resolution_clock::now();

    double total_time = chrono::duration<double>(end - start).count();
    cout << "Total time taken (Serial Matrix Multiplication): " << total_time << " seconds." << endl;

    // Save execution time and matrix size in a txt file
    ofstream outfile("execution_times.txt", ios_base::app); // Append mode
    outfile << "Serial Multiplication: " << total_time << " seconds, Matrix size: " << n << "\n";
    outfile.close();

    return 0;
}
