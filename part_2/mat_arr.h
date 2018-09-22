#ifndef MAT2D
 #include "mat2d.h"
#endif

#include <iostream>

class mat_arr: public mat2d {

    private:
    
        float** mat;    

    public:

        void init(int N, int M) {
            if(initialized) {
                throw "logic_error";
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
            curr_row = 0;
        }

        void append(float* row_vals) {
            if(curr_row == rows) {
                throw "out_of_range";
            }
            for(int i=0; i<cols; i++) {
                mat[curr_row][i] = row_vals[i];
            }
            curr_row++;            
        }
 
        float get(int i, int j) {
            if(i >= rows || j >= cols) {
                throw "out_of_range";
            }
            return mat[i][j];
        }

};
