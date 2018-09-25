/**
 * Created by: Shriram R.
 * Roll No: 06-02-01-10-51-18-1-15763
 */

#include"IMatrix.h"
#include<iostream>

using namespace std;


// Matrix implementation  using arrays
class ArrayMatrix : public IMatrix {

private:
    bool initialized; // Indicates if the matrix is initialized (1: initialized and 0: not initialized)
    int rows; // Row size
    int cols; // Column size
    int curr_row; // Stores the index of latest row that has been appended
    int nnz; // Stores the no. of non-zero elements
    float **mat; // pointer to the 2D array

public:

    // Constructor
    ArrayMatrix() {
        initialized = 0;
        rows = 0;
        cols = 0;
        curr_row = 0;
        nnz = 0;
    }

    // Initializes the 2D arrray
    void init(int N, int M) {
        if (initialized) {
            throw logic_error(string("Matrix already initialized!"));
        }
        // If N or M <= 0 (Invalid size), throw an exception
        if (N <= 0 || M <= 0) {
            throw logic_error(string("Row/Column size is not strictly positive!"));
        }
        mat = new float *[N];
        for (int i = 0; i < N; i++) {
            mat[i] = new float[M];
        }
        // Initialize the matrix with 0
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                mat[i][j] = 0;
            }
        }
        initialized = 1;
        rows = N;
        cols = M;
    }

    // Appends the input row to the existing matrix
    void append(float *row_vals) {
        // Throws an exception if the matrix is full
        if (curr_row == rows) {
            throw out_of_range(string("Cannot append more rows!"));
        }
        for (int i = 0; i < cols; i++) {
            mat[curr_row][i] = row_vals[i];
            if (row_vals[i] != 0)
                nnz++; // Increment for each non-zero element
        }
        curr_row++;
    }

    // Returns the value of a particular entry in the matrix
    float get(int i, int j) {
        // Throws an exception if the index is out of range
        if (i >= rows || j >= cols) {
            throw out_of_range(string("Row or Column index is out of range!"));
        }
        return mat[i][j];
    }

    // Returns the number of rows in the matrix
    int row_count() {
        return rows;
    }

    // Returns the number of columns in the matrix
    int col_count() {
        return cols;
    }

    // Returns the number of non zero values in the matrix
    int nnz_count() {
        return nnz;
    }

};


// Matrix Implementation using CSR
class CSRMatrix : public IMatrix {

private:
    bool initialized; // Indicates if the matrix is initialized (1: initialized and 0: not initialized)
    int rows; // Row size
    int cols; // Column size
    int curr_row; // Stores the index of latest row that has been appended
    int nnz; // Stores the no. of non-zero elements
    float *a; // Pointer to the array storing the non-zero elements
    int *ia; // Pointer to the array storing the cumulative count of nnz values in terms of rows
    int *ja; // Pointer to the array storing the column index of nnz elements
    int capacity; // Max. capacity of non-zero elements

public:

    // Constructor
    CSRMatrix() {
        initialized = 0;
        rows = 0;
        cols = 0;
        curr_row = 0;
        nnz = 0;
    }

    // Initializes the 2D arrray
    void init(int N, int M) {
        if (initialized) {
            throw logic_error(string("Matrix already initialized!"));
        }
        // If N or M <= 0 (Invalid size), throw an exception
        if (N <= 0 || M <= 0) {
            throw out_of_range(string("Row/Column size is not strictly positive!"));
        }
        a = new float[2]; // Initial capacity is 2
        ia = new int[N + 1]; // Size is rows + 1
        ja = new int[2]; // Size same as value array 'a'
        for (int i = 0; i < N + 1; i++) {
            ia[i] = 0; // No nnz elements initially
        }
        initialized = 1;
        rows = N;
        cols = M;
        curr_row = 0;
        capacity = 2; // Current capacity
    }

    // Appends the input row to the existing matrix
    void append(float *row_vals) {
        // Throws an exception if the matrix is full
        if (curr_row == rows) {
            throw out_of_range(string("Cannot append row with a different column size!"));
        }
        curr_row++;
        for (int i = 0; i < cols; i++) {
            if (row_vals[i] != 0) { // Execute only if the value is nnz
                if (ia[curr_row] >= capacity) {
                    extend(); // Extend the array if capacity is reached
                }
                ja[ia[curr_row]] = i; // Store the column index
                a[ia[curr_row]] = row_vals[i]; // Store the actual nnz value
                ia[curr_row]++; // Increment the cumulative counter
                nnz++; // Increment the nnz counter
            }
        }
        for (int i = curr_row + 1; i < rows + 1; i++) {
            ia[i] = ia[i - 1]; // Increment the cumulative counter
        }
    }

    // Returns the value of a particular entry in the matrix
    float get(int i, int j) {
        // Throws an exception if the index is out of range
        if (i >= rows || j >= cols) {
            throw out_of_range(string("Row or Column index is out of range!"));
        }
        float val = 0;
        for (int x = ia[i]; x < ia[i + 1]; x++) { // Use the cumulative nnz counter to identify the starting position
            if (ja[x] == j) { // If column index is equal
                val = a[x];
                break;
            }
        }
        return val;
    }

    // Returns the number of rows in the matrix
    int row_count() {
        return rows;
    }

    // Returns the number of columns in the matrix
    int col_count() {
        return cols;
    }

    // Returns the number of non zero values in the matrix
    int nnz_count() {
        return nnz;
    }

    // Extends the arrrays by a factor of 2
    void extend() {
        float *ta;
        int *tja;
        ta = a;
        tja = ja;
        a = new float[capacity * 2]; // New array with double capacity
        ja = new int[capacity * 2]; // New array with double capacity
        for (int i = 0; i < capacity; i++) { // Copy the values from old array to the new array
            a[i] = ta[i];
            ja[i] = tja[i];
        }
        capacity = capacity * 2; // Update the capacity
        delete ta; // Delete old array
        delete tja; // Delete old array
    }


};
