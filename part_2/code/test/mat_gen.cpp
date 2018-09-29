#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(){
    int n, p;
    srand(static_cast<unsigned int>(clock()));
    cin>>n>>p;
    cout<<n<<"\t"<<n<<"\n";
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            if(rand()%100 < p) {
                cout<<0<<"\t";
            }
            else
                cout<<float(rand()%100000)/1000.0<<"\t";
        }
        cout<<"\n";
    }
    return 0;
}


