/**
 * Created by: Shriram R.
 * Roll No: 06-02-01-10-51-18-1-15763
 */

#include <iostream>
#include <string.h>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>
#include <fstream>
#include <ctime>
#include"MatrixImpl.cpp"

using namespace std;

// Load an input file into an array based matrix
IMatrix *load_arr(char *input_file) {
    ifstream input;
    IMatrix *mat = new ArrayMatrix;
    int N, M;
    // Open the file
    input.open(input_file);
    if (!input.is_open()) {
        throw invalid_argument(string("Input file does not exist!"));
    }
    // Load data into the matrix
    input >> N >> M;
    mat->init(N, M);
    float *row = new float[M];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            input >> row[j];
        }
        mat->append(row);
    }
    // Close the file
    input.close();
    return mat;

}

// Load an input file into an csr based matrix
IMatrix *load_csr(char *input_file) {
    ifstream input;
    IMatrix *mat = new CSRMatrix;
    int N, M;
    // Open the file
    input.open(input_file);
    if (!input.is_open()) {
        throw invalid_argument(string("Input file does not exist!"));
    }
    // Load data into the matrix
    input >> N >> M;
    mat->init(N, M);
    float *row = new float[M];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            input >> row[j];
        }
        mat->append(row);
    }
    // Close the file
    input.close();
    return mat;
}

// Initialize an array based matrix
IMatrix *init_arr(int rows, int cols) {
    IMatrix *mat = new ArrayMatrix;
    mat->init(rows, cols);
    return mat;
}

// Initialize an csr based matrix
IMatrix *init_csr(int rows, int cols) {
    IMatrix *mat = new CSRMatrix;
    mat->init(rows, cols);
    return mat;
}

// Write a matrix to the specified file
void print_mat(IMatrix *mat, char *output_file) {
    ofstream output;
    int rows, cols;
    rows = mat->row_count();
    cols = mat->col_count();
    // Open the file
    output.open(output_file);
    // Write the data to the file
    output << rows << "\t" << cols << "\t\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            output << setprecision(3) << mat->get(i, j) << "\t";
        }
        output << "\n";
    }
    // Close the file
    output.close();
}

// Loads a matrix from an input file and writes it back to an output file
void load(char *mat_type, char *input_file, char *output_file) {

    IMatrix *mat1;
    struct timespec start, end;

    if (strcmp("array", mat_type) == 0) {
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start); // Start timer
        mat1 = load_arr(input_file);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end); // End timer
    } else if (strcmp("csr", mat_type) == 0) {
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start); // Start timer
        mat1 = load_csr(input_file);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end); // End Timer
    } else
        cout << "[load] invalid matrix type input seen: " << mat_type << endl;

    print_mat(mat1, output_file);
    // Print time taken in milliseconds to stdout
    cout << (end.tv_nsec - start.tv_nsec) / 1000000.0 + (end.tv_sec - start.tv_sec) * 1000 << "\n";
    return;
}

// Adds two matrices and stores the result in a result matrix
void add_mat(IMatrix *mat1, IMatrix *mat2, IMatrix *mat3) {
    int rows, cols;
    rows = mat1->row_count();
    cols = mat1->col_count();

    float *row = new float[cols];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            row[j] = mat1->get(i, j) + mat2->get(i, j);
        }
        mat3->append(row);
    }
}

// Adds two matrices from two input files and writes the result to an output file
void add(char *mat_type, char *input_file1, char *input_file2, char *output_file) {
    IMatrix *mat1;
    IMatrix *mat2;
    IMatrix *mat3;
    struct timespec start, end;

    if (strcmp("array", mat_type) == 0) {
        mat1 = load_arr(input_file1);
        mat2 = load_arr(input_file2);
        // If the matrices are incompatible i.e. row size or column size of the two matrices differ, throw an exception
        if (mat1->row_count() != mat2->row_count() || mat1->col_count() != mat2->col_count()) {
            throw logic_error(string("Cannot add two matrices of different dimensions!"));
        }
        mat3 = init_arr(mat1->row_count(), mat1->col_count());
    } else if (strcmp("csr", mat_type) == 0) {
        mat1 = load_csr(input_file1);
        mat2 = load_csr(input_file2);
        // If the matrices are incompatible i.e. row size or column size of the two matrices differ, throw an exception
        if (mat1->row_count() != mat2->row_count() || mat1->col_count() != mat2->col_count()) {
            throw logic_error(string("Cannot add two matrices of different dimensions!"));
        }
        mat3 = init_csr(mat1->row_count(), mat1->col_count());
    } else {
        cout << "[add] invalid matrix type input seen: " << mat_type << endl;
        return;
    }

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start); // Start timer
    add_mat(mat1, mat2, mat3);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end); // End timer

    print_mat(mat3, output_file);
    // Print time taken in milliseconds to stdout
    cout << (end.tv_nsec - start.tv_nsec) / 1000000.0 + (end.tv_sec - start.tv_sec) * 1000 << "\n";

    return;
}

// Multiplies two matrices and stores the result in a result matrix
void multiply_mat(IMatrix *mat1, IMatrix *mat2, IMatrix *mat3) {
    int rows1, cols, rows2;
    rows1 = mat1->row_count();
    cols = mat1->col_count();
    rows2 = mat2->col_count();

    float *row = new float[rows2];
    for (int i = 0; i < rows1; i++) { // Iterate over rows of result matrix
        for (int l = 0; l < rows2; l++) { // Initialize the row vector to zero
            row[l] = 0;
        }
        for (int j = 0; j < cols; j++) { // Iterate over columns of first matrix
            for (int k = 0; k < rows2; k++) { // Iterate over columns of result matrix
                row[k] += mat1->get(i, j) * mat2->get(j, k);
            }
        }
        mat3->append(row);
    }
}

// Multiplies two matrices from two input files and writes the result to an output file
void multiply(char *mat_type, char *input_file1, char *input_file2, char *output_file) {
    IMatrix *mat1;
    IMatrix *mat2;
    IMatrix *mat3;
    struct timespec start, end;

    if (strcmp("array", mat_type) == 0) {
        mat1 = load_arr(input_file1);
        mat2 = load_arr(input_file2);
        // If the matrices are incompatible i.e. column size of first and row size of second matrices differ, throw an exception
        if (mat1->col_count() != mat2->row_count()) {
            throw logic_error(string("Input matrices are incompatible for multiplication!"));
        }
        mat3 = init_arr(mat1->row_count(), mat2->col_count());

    } else if (strcmp("csr", mat_type) == 0) {
        mat1 = load_csr(input_file1);
        mat2 = load_csr(input_file2);
        // If the matrices are incompatible i.e. column size of first and row size of second matrices differ, throw an exception
        if (mat1->col_count() != mat2->row_count()) {
            throw logic_error(string("Input matrices are incompatible for multiplication!"));
        }
        mat3 = init_csr(mat1->row_count(), mat2->col_count());

    } else {
        cout << "[multiply] invalid matrix type input seen: " << mat_type << endl;
        return;
    }

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start); // Start timer
    multiply_mat(mat1, mat2, mat3);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end); // End timer

    print_mat(mat3, output_file);
    // Print time taken in milliseconds to stdout
    cout << (end.tv_nsec - start.tv_nsec) / 1000000.0 + (end.tv_sec - start.tv_sec) * 1000 << "\n";

    return;
}


void bfs(char *input_file, char *root_id, char *output_file) {

    // TODO: any validation?

    IMatrix *mat1;
    // TODO: Define a List ADT traverse_list to store output.

    // TODO
    mat1 = load_csr(input_file);

    {
        // TODO: time this region and print "bfs,csr,output_file,time_millisec"
        // TODO: Code for doing BFS on the matrix starting with vertex present in row "root_id"
        // TODO: Add traversed items into traverse_list
    }

    // TODO: store traversal output present in traverse_list into file given by output_file

    return;

}


int main(int n, char *argv[]) {

    if (strcmp("load", argv[1]) == 0) {
        load(argv[2], argv[3], argv[4]);
    } else if (strcmp("add", argv[1]) == 0) {
        add(argv[2], argv[3], argv[4], argv[5]);
    } else if (strcmp("multiply", argv[1]) == 0) {
        multiply(argv[2], argv[3], argv[4], argv[5]);
    } else if (strcmp("bfs", argv[1]) == 0) {
        bfs(argv[2], argv[3], argv[4]);
    } else
        cout << "[main] invalid input parameters. Valid usage is..." << endl;

    return 0;

}



