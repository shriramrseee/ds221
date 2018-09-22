
#define MAT2D

class mat2d {

    protected:
	bool initialized;
        int rows;
        int cols;
        int curr_row;

    public:
		
        mat2d() {
           initialized = 0;
           rows = 0;
           cols = 0;
           curr_row = 0;
        }

        virtual void init(int N, int M) = 0;
                
        virtual void append(float* row_vals) = 0;		

 	virtual float get(int i, int j) = 0;

};

