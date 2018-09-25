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

IMatrix* load_arr(char* input_file) 
{
    ifstream input;
    IMatrix* mat = new ArrayMatrix;
    int N, M;

    input.open(input_file);
    if(!input.is_open())
    {
     throw invalid_argument(string("Input file does not exist!"));
    }

    input>>N>>M;
    mat->init(N, M);
    float* row = new float[M];
    for(int i=0; i<N; i++) {
	for(int j=0; j<M; j++) {
	    input>>row[j];
	}
	mat->append(row);
    }

    input.close();    
    return mat;

}

IMatrix* load_csr(char* input_file) 
{
    ifstream input;
    IMatrix* mat = new CSRMatrix;
    int N, M;

    input.open(input_file);
    if(!input.is_open())
    {
     throw invalid_argument(string("Input file does not exist!"));
    }

    input>>N>>M;
    mat->init(N, M);
    float* row = new float[M];

    for(int i=0; i<N; i++) {
	for(int j=0; j<M; j++) {
	    input>>row[j];
	}
	mat->append(row);
    }
    
    input.close();
    return mat;
}

IMatrix* init_arr(int rows, int cols) 
{
    IMatrix* mat = new ArrayMatrix;
    mat->init(rows, cols);
    return mat;
}


IMatrix* init_csr(int rows, int cols) 
{
    IMatrix* mat = new CSRMatrix;
    mat->init(rows, cols);
    return mat;
}


void print_mat(IMatrix* mat, char* output_file) 
{
    ofstream output;
    int rows, cols;
    rows = mat->row_count();
    cols = mat->col_count();

    output.open(output_file);

    output<<rows<<"\t"<<cols<<"\t\n";
    for(int i=0; i<rows; i++)
    {
         for(int j=0; j<cols; j++)
         {
             output<<setprecision(3)<<mat->get(i, j)<<"\t";
         }
         output<<"\n";
    }

    output.close();    
}

void load(char* mat_type, char* input_file, char* output_file)
{
	
    IMatrix* mat1;
    struct timespec start, end;

    if (strcmp("array", mat_type)==0) 
    { 
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
        mat1 = load_arr(input_file);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    }  
    else if (strcmp("csr", mat_type)==0)
    {  
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
        mat1 = load_csr(input_file);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    }
    else
	cout<<"[load] invalid matrix type input seen: "<<mat_type<<endl;

    print_mat(mat1, output_file);

    cout<<"load,"<<mat_type<<","<<output_file<<","<<(end.tv_nsec-start.tv_nsec)/1000000.0 + (end.tv_sec-start.tv_sec)*1000<<"\n";
    return;
}


void add_mat(IMatrix* mat1, IMatrix* mat2, IMatrix* mat3) 
{	
    int rows, cols;
    rows = mat1->row_count();
    cols = mat1->col_count();
    float* row = new float[cols];
    for(int i=0; i<rows; i++) {
	for(int j=0; j<cols; j++) {
	    row[j] = mat1->get(i, j) + mat2->get(i, j);
	}
	mat3->append(row);
    }
}


void add(char* mat_type, char* input_file1, char* input_file2, char* output_file)
{ 
	IMatrix* mat1;
        IMatrix* mat2;
        IMatrix* mat3;
	struct timespec start, end;
	
	if (strcmp("array", mat_type)==0) 
        { 
		mat1 = load_arr(input_file1);
		mat2 = load_arr(input_file2);
                if(mat1->row_count() != mat2->row_count() || mat1->col_count() != mat2->col_count())
                {
                  throw logic_error(string("Cannot add two matrices of different dimensions!"));
                }		
		mat3 = init_arr(mat1->row_count(), mat1->col_count());
        }  
	else if (strcmp("csr", mat_type)==0)
	{
		mat1 = load_csr(input_file1);
		mat2 = load_csr(input_file2);
                if(mat1->row_count() != mat2->row_count() || mat1->col_count() != mat2->col_count())
                {
                  throw logic_error(string("Cannot add two matrices of different dimensions!"));
                }		
		mat3 = init_csr(mat1->row_count(), mat1->col_count());
	}
	else {
		cout<<"[add] invalid matrix type input seen: "<<mat_type<<endl;
		return;
	}
	
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
        add_mat(mat1, mat2, mat3);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
	
	print_mat(mat3, output_file);
        cout<<"add,"<<mat_type<<","<<output_file<<","<<(end.tv_nsec-start.tv_nsec)/1000000.0 + (end.tv_sec-start.tv_sec)*1000<<"\n";

	return;
}


void multiply_mat(IMatrix* mat1, IMatrix* mat2, IMatrix* mat3) 
{	
    int rows1, cols, rows2;
    rows1 = mat1->row_count();
    cols = mat1->col_count();
    rows2 = mat2->col_count();

    float* row = new float[rows2];

    for(int i=0; i<rows1; i++) {
        for(int l=0; l<rows2; l++) {
          row[l] = 0;
        }
	for(int j=0; j<cols; j++) {
          for(int k=0; k<rows2; k++) {
	    row[k] += mat1->get(i, j)*mat2->get(j, k);
	  }
        }
	mat3->append(row);
    }
}



void multiply(char* mat_type, char* input_file1, char* input_file2, char* output_file)
{
	IMatrix* mat1;
        IMatrix* mat2;
        IMatrix* mat3;
        struct timespec start, end;

	if (strcmp("array", mat_type)==0) 
        { 
		mat1 = load_arr(input_file1);
		mat2 = load_arr(input_file2);
                if(mat1->col_count() != mat2->row_count())
                {
                  throw logic_error(string("Input matrices are incompatible for multiplication!"));
                }
		mat3 = init_arr(mat1->row_count(), mat2->col_count());
		
	}  
	else if (strcmp("csr", mat_type)==0)
	{
		mat1 = load_csr(input_file1);
		mat2 = load_csr(input_file2);
                if(mat1->col_count() != mat2->row_count())
                {
                  throw logic_error(string("Input matrices are incompatible for multiplication!"));
                }
		mat3 = init_csr(mat1->row_count(), mat2->col_count());
		
	}
	else {
		cout<<"[multiply] invalid matrix type input seen: "<<mat_type<<endl;
		return;
	}
	
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
	multiply_mat(mat1, mat2, mat3);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

	print_mat(mat3, output_file);
        cout<<"multiply,"<<mat_type<<","<<output_file<<","<<(end.tv_nsec-start.tv_nsec)/1000000.0 + (end.tv_sec-start.tv_sec)*1000<<"\n";

	return;
}


void bfs(char* input_file, char* root_id, char* output_file)
{
 
	// TODO: any validation?
	
	IMatrix* mat1;
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




int main(int n, char *argv[])
{

    if(strcmp("load", argv[1])==0)
    {
	load(argv[2], argv[3], argv[4]);
    }
    else if( strcmp("add", argv[1])==0)
    {
	add(argv[2], argv[3], argv[4], argv[5]);
    }
    else if( strcmp("multiply", argv[1])==0 )
    {
        multiply(argv[2], argv[3], argv[4], argv[5]);
    }
    else if(strcmp("bfs", argv[1])==0)
    {
        bfs(argv[2], argv[3], argv[4]);
    }
    else 
        cout<<"[main] invalid input parameters. Valid usage is..."<<endl;

    return 0;
    
}

