#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    srand(time(NULL));
    for (int i=0; i<n; i++) {
        cout << abs(rand()) << "\t" << "This is the " << i << "th element\n";
    }
    return 0;
}