#include"IMatrix.h"
#include<iostream>

using namespace std;


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/**
 * 2D Matrix Implementation usign Arrays
 */
class ArrayMatrix: public IMatrix
{  
	/*#######################################################
	 # Define your own data structures here 
	 #######################################################*/

	private: 
		// TODO
   
	public:
		// TODO
   
   
	/**
     * Default constructor is required.
	 * You may optionally define additional constructors as well.
     */
	ArrayMatrix()
	{ 
		// TODO: Provide implementation for default constructor
	}
 
 
	/*#######################################################
 	  # Override functions defined in IMatrix interface
	  #######################################################*/

	/** Override the init function defined in the IMatrix interface */
	void init (int N, int M)
 	{ 
		// TODO: Provide implementation for init using array
	}

	
	/** Override the append function defined in the IMatrix interface */
   void append (float* row_vals)
	{ 
	    // TODO: Provide implementation for append using array
	}

	
	/** Override the get function defined in the IMatrix interface */
	float get(int i, int j)
	{ 
	    // TODO: Provide implementation for get using array
	}

	
	/**
	  * This returns the number of rows in the matrix based on init()
	  */
	int row_count()
	{
		// TODO: Provide implementation using array
	}
	
	/**
	  * This returns the number of columns in the matrix based on init()
	  */
	int col_count() 
	{
		// TODO: Provide implementation using array
	}

	
	/**
	  * This returns the number of non zero values in the matrix
	  */
	int nnz_count()
	{
		// TODO: Provide implementation using array
	}

	/*#######################################################
	 # Optionally define any other private utility functions here
	 #######################################################*/
	
	// TODO
};

/////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/**
 * 2D Matrix Implementation usign CSR
 */
class CSRMatrix: public IMatrix
{  	

	/*#######################################################
	 # Define your own data structures here 
	 #######################################################*/

	private: 
		// TODO
   
	public:
		// TODO
   
   
	/**
     * Default constructor is required.
	 * You may optionally define additional constructors as well.
     */
	CSRMatrix()
	{ 
		// TODO: Provide implementation for default constructor
	}
 
 
	/*#######################################################
 	  # Override functions defined in IMatrix interface
	  #######################################################*/

	/** Override the init function defined in the IMatrix interface */
	void init (int N, int M)
 	{ 
		// TODO: Provide implementation for init using csr
	}
	

	/** Override the append function defined in the IMatrix interface */
   void append (float* row_vals)
	{ 
	    // TODO: Provide implementation for append using csr
	}

	
	/** Override the get function defined in the IMatrix interface */
	float get(int i, int j)
	{ 
	    // TODO: Provide implementation for get using csr
	}

	/**
	  * This returns the number of rows in the matrix based on init()
	  */
	int row_count()
	{
		// TODO: Provide implementation using csr
	}
	
	/**
	  * This returns the number of columns in the matrix based on init()
	  */
	int col_count() 
	{
		// TODO: Provide implementation using csr
	}

	
	/**
	  * This returns the number of non zero values in the matrix
	  */
	int nnz_count()
	{
		// TODO: Provide implementation using csr
	}

	
	/*#######################################################
	 # Optionally define any other private utility functions here
	 #######################################################*/
	
	// TODO

	
};