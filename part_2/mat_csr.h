#ifndef MAT2D
 #include "mat2d.h"
#endif

class mat_csr: public mat2d {

    private:
    
        float* a;
        int* ia;
        int* ja;
        int capacity;

    public:
        
        void init(int N, int M) {
            if(initialized) {
                throw "logic_error";
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

        void append(float* row_vals) {
            if(curr_row == rows) {
                throw "out_of_range";
            }
            curr_row++;
            for(int i=0; i<cols; i++) {
                if(ia[curr_row] >= capacity) {
                    extend();
                }
                ja[ia[curr_row]] = i;
                a[ia[curr_row]] = row_vals[i];
                ia[curr_row]++;
            }
            for(int i=curr_row+1; i<rows+1; i++) {
                ia[i] = ia[i-1];
            }                            
        }
 
        float get(int i, int j) {
            if(i >= rows || j >= cols) {
                throw "out_of_range";
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

};
