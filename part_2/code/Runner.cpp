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
#include <list>
#include <queue>
#include <sstream>
#include"MatrixImpl.cpp"

using namespace std;

// Load an input file into an array based matrix
IMatrix *load_arr(char *input_file) {
    ifstream input;
    string line, t;
    stringstream s;
    IMatrix *mat = new ArrayMatrix;
    int N, M;
    // Open the file
    input.open(input_file);
    if (!input.is_open()) {
        throw invalid_argument(string("Input file does not exist!"));
    }
    // Load data into the matrix
    try {
        getline(input, line);
        s.str(line);
        s >> t;
        N = stoi(t); // Get no. of rows
        t = "";
        s >> t;
        M = stoi(t); // Get no. of columns
        mat->init(N, M);
        float *row = new float[M];
        for (int i = 0; i < N; i++) {
            getline(input, line);
            stringstream s(line);
            for (int j = 0; j < M; j++) { // Scan each row from file
                t = "";
                s >> t;
                row[j] = stof(t);
            }
            mat->append(row);
        }
    }
    catch (const invalid_argument &ia) {
        throw invalid_argument(string("File has invalid characters or format!"));
    }
    // Close the file
    input.close();
    return mat;
}

// Load an input file into an csr based matrix
IMatrix *load_csr(char *input_file) {
    ifstream input;
    string line, t;
    stringstream s;
    IMatrix *mat = new CSRMatrix;
    int N, M;
    // Open the file
    input.open(input_file);
    if (!input.is_open()) {
        throw invalid_argument(string("Input file does not exist!"));
    }
    // Load data into the matrix
    try {
        getline(input, line);
        s.str(line);
        s >> t;
        N = stoi(t); // Get no. of rows
        t = "";
        s >> t;
        M = stoi(t); // Get no. of columns
        mat->init(N, M);
        float *row = new float[M];
        for (int i = 0; i < N; i++) {
            getline(input, line);
            stringstream s(line);
            for (int j = 0; j < M; j++) { // Scan each row from file
                t = "";
                s >> t;
                row[j] = stof(t);
            }
            mat->append(row);
        }
    }
    catch (const invalid_argument &ia) {
        throw invalid_argument(string("File has invalid characters or format!"));
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
    if (!output.is_open()) {
        throw invalid_argument(string("Output file does not exist!"));
    }
    // Write the data to the file
    output << rows << "\t" << cols << "\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            output << fixed << setprecision(3) << mat->get(i, j);
            if (j < cols - 1)
                output << "\t";
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
void add(IMatrix *mat1, IMatrix *mat2, IMatrix *mat3) {
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
    add(mat1, mat2, mat3);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end); // End timer

    print_mat(mat3, output_file);
    // Print time taken in milliseconds to stdout
    cout << (end.tv_nsec - start.tv_nsec) / 1000000.0 + (end.tv_sec - start.tv_sec) * 1000 << "\n";

    return;
}

// Multiplies two matrices and stores the result in a result matrix
void multiply(IMatrix *mat1, IMatrix *mat2, IMatrix *mat3) {
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
    multiply(mat1, mat2, mat3);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end); // End timer

    print_mat(mat3, output_file);
    // Print time taken in milliseconds to stdout
    cout << (end.tv_nsec - start.tv_nsec) / 1000000.0 + (end.tv_sec - start.tv_sec) * 1000 << "\n";

    return;
}


// Class to implement BFS depth and node list
class tl {

public:
    int depth;
    list<int> vid;

    tl(int d) {
        depth = d;
    }

};

// Performs BFS on the given graph and stores the result in a file
void bfs(char *input_file, char *root_id, char *output_file) {


    IMatrix *mat1;
    list <tl> traverse_list;
    queue<int> q;
    int nodes, item, root;
    struct timespec start, end;

    mat1 = load_csr(input_file);
    nodes = mat1->col_count();
    int *dep = new int[nodes]; // Stores the depth of each node
    root = atoi(root_id);

    for (int i = 0; i < nodes; i++) // Initial depth is -1
        dep[i] = -1;

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start); // Start timer
    q.push(root); // Add root to the queue
    dep[root] = 0; // depth of root is zero
    while (!q.empty()) { // Queue is empty if we complete search of entire connected component
        item = q.front(); // Get the front element from the queue
        q.pop();
        if (traverse_list.size() < dep[item] + 1) { // Add a new depth to traverse list if not present already
            tl *new_depth = new tl(dep[item]);
            traverse_list.push_back(*new_depth);
        }
        traverse_list.back().vid.push_back(item); // Add the node to the traverse list
        for (int i = 0; i < nodes; i++) {
            if (dep[i] == -1 && mat1->get(item, i)) { // Add a adjacent node to the queue if not visited already
                dep[i] = dep[item] + 1; // Set the depth of adjacent node to current+1
                q.push(i);
            }
        }
    }
    for (list<tl>::iterator i = traverse_list.begin(); i != traverse_list.end(); i++) {
        i->vid.sort(); // Sort in ascending order
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end); // End timer

    // Store traversal output present in traverse_list into file given by output_file
    ofstream output;
    // Open the file
    output.open(output_file);
    // Write the data to the file
    for (list<tl>::iterator i = traverse_list.begin(); i != traverse_list.end(); i++) {
        output << i->depth;
        for (list<int>::iterator j = i->vid.begin(); j != i->vid.end(); j++) {
            output << "," << *j;
        }
        output << "\n";
    }
    // Close the file
    output.close();

    // Print time taken in milliseconds to stdout
    cout << (end.tv_nsec - start.tv_nsec) / 1000000.0 + (end.tv_sec - start.tv_sec) * 1000 << "\n";

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
    } else {
        cout << "[main] invalid input parameters. Valid usage is..." << endl;
        cout << "./Runner.o load [array|csr] <input_file> <output_file>" << endl;
        cout << "./Runner.o add [array|csr] <input_file_1> <input_file_2> <output_file>" << endl;
        cout << "./Runner.o multiply [array|csr] <input_file_1> <inpout_file_2> <output_file>" << endl;
        cout << "./Runner.o bfs <input_file> <root_row_id> <output_file>" << endl;
    }

    return 0;

}



