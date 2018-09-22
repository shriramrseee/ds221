#include <fstream>
#include "mat_arr.h"
#include "mat_csr.h"

using namespace std;

void mat_load(mat2d* mat, istream& input) {
    int N, M;
    input>>N>>M;
    float* row = new float[M];
    mat->init(N, M);
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            input>>row[j];
        }
        mat->append(row);
    }
}
    

int main() {
    
    ifstream input;
    mat_arr* mat_a = new mat_arr;
    mat_csr* mat_b = new mat_csr; 
   
    input.open("input.tsv");

    mat_load(mat_a, input);

    input.seekg(0, ios::beg);
    mat_load(mat_b, input);

    cout<<sizeof(*mat_a)<<"\n"<<sizeof(*mat_b)<<"\n";

    input.close();

    return 0;

}


    
    


