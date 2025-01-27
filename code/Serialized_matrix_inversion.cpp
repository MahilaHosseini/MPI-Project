#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <fstream> // برای ذخیره زمان‌ها

using namespace std;

// Function to invert a matrix using Gauss-Jordan
bool invertMatrix(vector<vector<double>>& A) {
    int n = A.size();
    vector<vector<double>> I(n, vector<double>(n, 0.0));

    // Initialize the identity matrix
    for (int i = 0; i < n; i++) {
        I[i][i] = 1.0;
    }

    for (int i = 0; i < n; i++) {
        double pivot = A[i][i];
        if (pivot == 0.0) {
            return false; // Matrix is singular
        }

        // Normalize the pivot row
        for (int j = 0; j < n; j++) {
            A[i][j] /= pivot;
            I[i][j] /= pivot;
        }

        // Eliminate other rows
        for (int k = 0; k; k++) {
            if (k != i) {
                double factor = A[k][i];
                for (int j = 0; j < n; j++) {
                    A[k][j] -= factor * A[i][j];
                    I[k][j] -= factor * I[i][j];
                }
            }
        }
    }

    // Copy the inverted matrix back
    A = I;
    return true;
}

int main() {
    int n = 2048;  // Matrix size
    vector<vector<double>> A(n, vector<double>(n));

    // Initialize the matrix with random values
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = rand() % 100 + 1; // Avoid zeros to reduce singularity
        }
    }

    // Measure the time for inversion
    auto start = chrono::high_resolution_clock::now();
    bool success = invertMatrix(A);
    auto end = chrono::high_resolution_clock::now();

    double total_time = chrono::duration<double>(end - start).count();

    if (!success) {
        cerr << "The matrix is singular and cannot be inverted." << endl;
    } else {
        cout << "Matrix inversion completed successfully." << endl;
        cout << "Total time taken (Serial Matrix Inversion): " << total_time << " seconds." << endl;

         
    // Saving execution time in a txt file
        ofstream outfile("execution_times.txt", ios_base::app); // append mode
        outfile << "Serial Inversion: " << total_time << " seconds" << endl;
        outfile.close();
    }

    return 0;
}
