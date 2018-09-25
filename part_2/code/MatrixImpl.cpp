#include"IMatrix.h"
#include<iostream>

using namespace std;


/**
 * 2D Matrix Implementation usign Arrays
 */
class ArrayMatrix: public IMatrix
{  

	private:
		bool initialized;
		int rows;
		int cols;
		int curr_row;
                int nnz; 
		float** mat;
   
	public:
		
   
	ArrayMatrix()
	{ 
		initialized = 0;
		rows = 0;
		cols = 0;
		curr_row = 0;
                nnz = 0;
	}
 

	/** Override the init function defined in the IMatrix interface */
	void init (int N, int M)
 	{ 
	    if(initialized) {
                throw logic_error(string("Matrix already initialized!"));
            }
            if (N<=0 || M<=0) {
                throw out_of_range(string("Row/Column size is not strictly positive!"));
            }
            mat = new float*[N];
            for(int i=0; i<N; i++) {
                mat[i] = new float[M];
            }
            for(int i=0; i<N; i++) {
                for(int j=0; j<M; j++) {
                    mat[i][j] = 0;
                }
            }
            initialized = 1;
            rows=N;
            cols=M;
	}

	
	/** Override the append function defined in the IMatrix interface */
   	void append (float* row_vals)
	{ 
	    if(curr_row == rows) {
                throw out_of_range(string("Cannot append row with a different column size!"));
            }
            for(int i=0; i<cols; i++) {
                mat[curr_row][i] = row_vals[i];
                if(row_vals[i]!=0)
		    nnz++;
            }
            curr_row++;
	}

	
	/** Override the get function defined in the IMatrix interface */
	float get(int i, int j)
	{ 
	    if(i >= rows || j >= cols) {
                throw out_of_range(string("Row or Column index is out of range!"));
            }
            return mat[i][j];
	}

	
	/**
	  * This returns the number of rows in the matrix based on init()
	  */
	int row_count()
	{
	    return rows;
	}
	
	/**
	  * This returns the number of columns in the matrix based on init()
	  */
	int col_count() 
	{
	    return cols;
	}

	
	/**
	  * This returns the number of non zero values in the matrix
	  */
	int nnz_count()
	{
	    return nnz++;
	}

};



/**
 * 2D Matrix Implementation usign CSR
 */
class CSRMatrix: public IMatrix
{  	

	private: 
		bool initialized;
		int rows;
		int cols;
		int curr_row;
		int nnz;
		float* a;
		int* ia;
		int* ja;
		int capacity;
   
	public:
   
   
	CSRMatrix()
	{ 
		initialized = 0;
		rows = 0;
		cols = 0;
		curr_row = 0;
                nnz = 0;
	}
 

	/** Override the init function defined in the IMatrix interface */
	void init (int N, int M)
 	{ 
	    if(initialized) {
                throw logic_error(string("Matrix already initialized!"));
            }
            if (N<=0 || M<=0) {
                throw out_of_range(string("Row/Column size is not strictly positive!"));
            }
            a = new float[2];
            ia = new int[N+1];
            ja = new int[2];
            for(int i=0; i<N+1; i++) {
                ia[i] = 0;
            }
            initialized = 1;
            rows=N;
            cols=M;
            curr_row = 0;
            capacity = 2;
	}
	

	/** Override the append function defined in the IMatrix interface */
   	void append (float* row_vals)
	{ 
	    if(curr_row == rows) {
                throw out_of_range(string("Cannot append row with a different column size!"));
            }
            curr_row++;
            for(int i=0; i<cols; i++) {
                if(row_vals[i] != 0)
                {
		        if(ia[curr_row] >= capacity) {
		            extend();
		        }
		        ja[ia[curr_row]] = i;
		        a[ia[curr_row]] = row_vals[i];
		        ia[curr_row]++;
                        nnz++;
                }
            }
            for(int i=curr_row+1; i<rows+1; i++) {
                ia[i] = ia[i-1];
            }
	}

	
	/** Override the get function defined in the IMatrix interface */
	float get(int i, int j)
	{ 
	    if(i >= rows || j >= cols) {
                throw out_of_range(string("Row or Column index is out of range!"));
            }
            float val = 0;
            for(int x=ia[i]; x<ia[i+1]; x++) {
                if(ja[x]==j) {
                    val = a[x];
                    break;
                }
            }
            return val;
	}

	/**
	  * This returns the number of rows in the matrix based on init()
	  */
	int row_count()
	{
	    return rows;	
	}
	
	/**
	  * This returns the number of columns in the matrix based on init()
	  */
	int col_count() 
	{
	    return cols;
	}

	
	/**
	  * This returns the number of non zero values in the matrix
	  */
	int nnz_count()
	{
	    return nnz;	
	}


        void extend() {
            float* ta;
            int* tja;
            ta = a;
            tja = ja;
            a = new float[capacity*2];
            ja = new int[capacity*2];
            for(int i=0; i<capacity; i++) {
                a[i] = ta[i];
                ja[i] = tja[i];
            }
            capacity = capacity*2;
            delete ta;
            delete tja;
        }


	
};
