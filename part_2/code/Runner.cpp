#include <iostream>
#include <string.h>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>
#include"MatrixImpl.cpp"

using namespace std;


/**
  * Runner code that serves as harness for invoking various functions required 
  * to be implemented for this assignment.
  * You may modify this code, but need to retain the input parameter signature and 
  * output requirements specified in the assignment.
  */  
  
/////////////////////////////////////////////////////////////////////////////

IMatrix* load_arr(char* input_file) 
{
	// TODO: Code for loading matrix from input_file into array impl and returning object

}

IMatrix* load_csr(char* input_file) 
{
	// TODO: Code for loading matrix from input_file into CSR impl and returning object

}

IMatrix* init_arr(int rows, int cols) 
{
	// TODO: Code for initializing an empty matrix using array impl with rows and cols as 
	// dimensions, and returning the object
}


IMatrix* init_csr(int rows, int cols) 
{
	// TODO: Code for initializing an empty matrix using CSR impl with rows and cols as 
	// dimensions, and returning the object
}


void print_mat(IMatrix* mat, char* output_file) 
{
	// TODO: print matrix as TSV to otput_file
}

/////////////////////////////////////////////////////////////////////////////

void load(char* mat_type, char* input_file, char* output_file)
{
	// TODO: any other validation?
	
	IMatrix* mat1;

	if (strcmp("array", mat_type)==0) // TODO: time this region and print "load,array,output_file,time_millisec"
    { 
		mat1 = load_arr(input_file);
    }  
	else if (strcmp("csr", mat_type)==0) // TODO: time this region and print "load,csr,output_file,time_millisec"
	{  
		mat1 = load_csr(input_file);
	}
	else
		cout<<"[load] invalid matrix type input seen: "<<mat_type<<endl;

	// store the loaded matrix mat1 in output file given by output_file
	print_mat(mat1, output_file);
	

	return;
}

/////////////////////////////////////////////////////////////////////////////

void add(char* mat_type, char* input_file1, char* input_file2, char* output_file)
{ 
	// TODO: any other validation?
	
	IMatrix* mat1, mat2, mat3;
	
	if (strcmp("array", mat_type)==0) 
    { 
		mat1 = load_arr(input_file1);
		mat2 = load_arr(input_file2);
		
		// TODO: any other validation?
		
		mat3 = init_arr(mat1->row_count(), mat1->col_count());
    }  
	else if (strcmp("csr", mat_type)==0)
	{
		mat1 = load_csr(input_file1);
		mat2 = load_csr(input_file2);

		// TODO: any other validation?
		
		mat3 = init_csr(mat1->row_count(), mat1->col_count());
	}
	else {
		cout<<"[add] invalid matrix type input seen: "<<mat_type<<endl;
		return;
	}
	
	// TODO: time this method and print "add,mat_type,output_file,time_millisec"
	
	add(mat1, mat2, mat3);
	
	// store output matrix mat3 in file given by output_file
	print_mat(mat3, output_file);

	return;
}

void add(IMatrix* mat1, IMatrix* mat2, IMatrix* mat3) 
{	
	// TODO: Code for adding the mat1 and mat2 and storing in a third matrix mat3
	
	return;
}

/////////////////////////////////////////////////////////////////////////////

void multiply(char* mat_type, char* input_file1, char* input_file2, char* output_file)
{
	// TODO: any other validation?

	IMatrix* mat1, mat2, mat3;

	if (strcmp("array", mat_type)==0) 
    { 
		mat1 = load_arr(input_file1);
		mat2 = load_arr(input_file2);

		// TODO: any other validation?
		
		// TODO: init output matrix mat3 with arr impl
	}  
	else if (strcmp("csr", mat_type)==0)
	{
		mat1 = load_csr(input_file1);
		mat2 = load_csr(input_file2);

		// TODO: any other validation?
		
		// TODO: init output matrix mat3 with csr impl
	}
	else {
		cout<<"[multiply] invalid matrix type input seen: "<<mat_type<<endl;
		return;
	}
	
	// TODO: time this method and print "multiply,csr,output_file,time_millisec"
	multiply(mat1, mat2, mat3);
	
	// store output matrix mat3 in file given by output_file
	print_mat(mat3, output_file);

	return;
}

void multiply(IMatrix* mat1, IMatrix* mat2, IMatrix* mat3) 
{	
	
	// TODO: Code for adding the mat1 and mat2 and storing in a third matrix mat3
	
	return;
}
/////////////////////////////////////////////////////////////////////////////

void bfs(char* input_file, char* root_id, int char* output_file)
{
 
	// TODO: any validation?
	
	IMatrix* mat1;
	// TODO: Define a List ADT traverse_list to store output.

	// TODO
	mat1 = load_csr(input_file1);

	{	
		// TODO: time this region and print "bfs,csr,output_file,time_millisec"
		// TODO: Code for doing BFS on the matrix starting with vertex present in row "root_id"
		// TODO: Add traversed items into traverse_list
	}
	
	// TODO: store traversal output present in traverse_list into file given by output_file
	
	return;

}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

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
        multiply(argv[2], argv[2], argv[4], argv[5]);
	}
    else if(strcmp("bfs", argv[1])==0)
	{
        bfs(argv[2], argv[3], argv[4]);
	} else 
		cout<<"[main] invalid input parameters. Valid usage is..."<<endl;

	return 0;
    
}

